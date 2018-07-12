/// @date    2018-07-12 22:21:12

#include "EpollPoller.h"
#include "SocketUtil.h"
#include "assert.h"

EpollPoller::EpollPoller(Acceptor& acceptor)
	:_acceptor(acceptor), 
	 _efd(createEpollFd()),
     _newfd(_acceptor.fd()),
 	 _looping(false),
     _eventList(1024) {
		addEpollFdRead(_efd, _newfd);//将newfd加入efd的监控中
	}

void EpollPoller::loop() {
	_looping = true;
	while(_looping) {//由别的线程来打破while循环？
		waitEpollFd();
	}
}
void EpollPoller::unloop() {_looping = false;}

void EpollPoller::handleNewConntiton() {
	int newfd = _acceptor.fd();
	addEpollFdRead(_efd, newfd);				//有新的客户请求，创建到新客户的连接
	TcpConnPtr connPtr(new TcpConnection(newfd, this));//将epoll的this指针传入TcpConnection 
		connPtr->setOnConnCb(_onConnCb);					//TcpConnect连接中需要执行Epoll中的runInLoop方法
		connPtr->setOnMsgCb(_onMsgCb);
		connPtr->setOnCloseCb(_onCloseCb);
	auto ret = _conMap.insert(make_pair(newfd, connPtr));//将
	assert(ret.second == true);
	(void)ret;
		connPtr->handleOnConnCb();//注册3个，执行1个

}

