 /// @date    2018-07-12 22:12:01
 
#ifndef __EPOLLPOLLER_H__
#define __EPOLLPOLLER_H__
#include "TcpConnection.h"
#include "Acceptor.h"
#include <vector>
#include <map>


class EpollPoller {
using EpollCb = TcpConnection::TcpConnCb;
	public:
		EpollPoller(Acceptor& acceptor);
		void loop();
		void unloop();
	private:
		void wakeUp();
		void waitEpollFd();
			void handleNewConntiton();
			void handleMsg();
			void handleRead();
	private:
		Acceptor _acceptor;
		int _efd;
		int _newfd;//用于与客户端通信的fd
		bool _looping;
		vector<struct epoll_event> _eventList;
		map<int,TcpConnPtr> _conMap;
			EpollCb _onConnCb;
			EpollCb _onMsgCb;
			EpollCb _onCloseCb;
};




#endif
