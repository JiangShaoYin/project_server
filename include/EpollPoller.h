 /// @date    2018-07-12 22:12:01
 
#ifndef __EPOLLPOLLER_H__
#define __EPOLLPOLLER_H__
#include "TcpConnection.h"
#include "Acceptor.h"
#include "MutexLock.h"
#include <vector>
#include <map>
//IO线程维护着与各个客户端的通信，由EpollPoller实现
using Functor = function<void()>;
class EpollPoller {
	public:
		EpollPoller(Acceptor& acceptor);
		void loop();
		void unloop();
		void setOnConnCb(CbFunction);
		void setOnMsgCb(CbFunction);
		void setOnCloseCb(CbFunction);

		void regesterToThreadIO(const Functor& cb);
		~EpollPoller();
	private:
		void wakeUp();
		void waitEpollFd();
			int epollwaitAndCheckReturn(); 
			void traverseActiveFd(int activeFdNum);
				void handleNewConntiton();
				void handleMsg(int newfd);//处理旧连接
				void handleActiveEventFd();
				void doPendingFunctors();
	private:
		Acceptor _acceptor;
		int _efd;
		int _sfd;//用于与客户端通信的fd
		int _eventfd;//用于进程间通信
		bool _looping;
		vector<struct epoll_event> _eventList;//epoll_event保存要监控的fd，和监控的事项(EPOLLIN)
		map<int,TcpConnPtr> _conMap;
			CbFunction _onConnCb;
			CbFunction _onMsgCb;
			CbFunction _onCloseCb;
		vector<Functor> _threadIOtodoList;
		MutexLock _mutex;
};




#endif
