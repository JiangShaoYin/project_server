/// @date    2018-07-12 22:21:12

#include "EpollPoller.h"
#include "SocketUtil.h"
#include "MutexLockGuard.h"
#include <assert.h>
#include <unistd.h>

EpollPoller::EpollPoller(Acceptor& acceptor)
	:_acceptor(acceptor), 
	 _efd(createEpollFd()),
     _sfd(_acceptor.fd()),
	 _eventfd(createEventFd()),
 	 _looping(false),
     _eventList(1024) {
		 cout << "_efd:" << _efd << endl;
         cout << "_sfd:" << _sfd << endl;
		addEpollFdRead(_efd, _sfd);//将newfd加入efd的监控中
		addEpollFdRead(_efd, _eventfd);
		cout << "_eventfd: " << _eventfd << endl;
	}

void EpollPoller::loop() {
	_looping = true;
	while(_looping) {//由别的线程来打破while循环？
		waitEpollFd();
	}
}
void EpollPoller::unloop() {_looping = false;}

void EpollPoller::setOnConnCb(CbFunction cb) {	_onConnCb = cb;}
void EpollPoller::setOnMsgCb(CbFunction cb) { _onMsgCb = cb;}
void EpollPoller::setOnCloseCb(CbFunction cb) { _onCloseCb = cb;}

void EpollPoller::regesterToThreadIO(const Functor& cb) {
	MutexLockGuard lock(_mutex);	
		_threadIOtodoList.push_back(cb);
	wakeUp();//向io线程里放入一个回调函数，提醒io线程执行
}

void EpollPoller::wakeUp() {
	uint64_t Buf8B = 1;
	int ret = write(_eventfd, &Buf8B, sizeof(Buf8B));
	if(ret != sizeof(Buf8B))
		perror("write error");
}

void EpollPoller::waitEpollFd() {
	int activeFdNum = epollwaitAndCheckReturn();	
	traverseActiveFd(activeFdNum);
}

int EpollPoller::epollwaitAndCheckReturn() {
	int activeFdNum;
	do {
		activeFdNum = epoll_wait(_efd, &(*_eventList.begin()), _eventList.size(), 5000);		
	}while(activeFdNum == -1 && errno == EINTR);

	if(activeFdNum == -1) {
		perror("epoll_wait error");
		exit(1);
	}
	else if(activeFdNum == 0) {
		cout << "epoll_wait timeout" << endl;
	}
	else if(activeFdNum == static_cast<int>(_eventList.size()))
		_eventList.resize(2 * _eventList.size());	
	return activeFdNum;
}

void EpollPoller::traverseActiveFd(int activeFdNum) {
	for(int idx = 0; idx < activeFdNum; ++idx){//把&换成==试一下？
		if(_eventList[idx].data.fd == _sfd && _eventList[idx].events&EPOLLIN) {
			handleNewConntiton();	
		}
		else if(_eventList[idx].data.fd == _eventfd && _eventList[idx].events&EPOLLIN) {
			handleActiveEventFd();
			cout << "doPendingFunctors" << endl;
			doPendingFunctors();
		}
		else {
			if(_eventList[idx].events&EPOLLIN)//处理旧连接
				handleMsg(_eventList[idx].data.fd);
		}
	}
}

void EpollPoller::handleNewConntiton() {
	int newfd = _acceptor.accept();
	addEpollFdRead(_efd, newfd);				//有新的客户请求，创建到新客户的连接
	TcpConnPtr connPtr(new TcpConnection(newfd, this));//将epoll的this指针传入TcpConnection 
		connPtr->setOnConnCb(_onConnCb);					//TcpConnect连接中需要执行Epoll中的runInLoop方法
		connPtr->setOnMsgCb(_onMsgCb);
		connPtr->setOnCloseCb(_onCloseCb);
	auto ret = _conMap.insert(make_pair(newfd, connPtr));//将新的连接放入map中保存
	assert(ret.second == true);
	(void)ret;
		connPtr->handleOnConnCb();//注册3个，执行1个
}

void EpollPoller::handleMsg(int newfd) {
	bool ConnClose = isConnectionClosed(newfd);//看客户端是否掉线
	auto it = _conMap.find(newfd);
		assert(it != _conMap.end());//找到这个连接assert(true),执行下面的语句
	if(!ConnClose)//如果连接没有关闭
		it->second->handleOnMsgCb();	
	else{		//连接关闭
		it->second->handleOnCloseCb();	
		delEpollReadFd(_efd, newfd);//将_epf上监控的描述符删除
		_conMap.erase(it);//把_conMap里这对连接移除
		}
}

void EpollPoller::handleActiveEventFd() {
	uint64_t buf8B;
	int ret = read(_eventfd, &buf8B, sizeof(buf8B));
	if(ret != sizeof(buf8B))
		perror("read error");
}

void EpollPoller::doPendingFunctors() {
	vector<Functor> functors;
	{
		MutexLockGuard lock(_mutex);	
		functors.swap(_threadIOtodoList);
	}
	for(size_t idx=0; idx < functors.size(); ++idx)
		functors[idx]();	
}

EpollPoller::~EpollPoller() {	close(_efd);}
