/// @date    2018-07-12 10:43:17

#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
#include "Acceptor.h"
#include "SocketUtil.h"
#include "EpollPoller.h"

using CbFunction = function<void(const TcpConnPtr&)>;
class TcpServer {
	public:
		TcpServer()
			:_epollPoller(_acceptor) {	}
		void start();
		void stop();
		void setOnConnCb(const CbFunction &cb) { _onConnCb = cb;}
		void setOnMsgCb(const CbFunction &cb) { _onMsgCb = cb;}
		void setOnCloseCb(const CbFunction &cb) { _onCloseCb = cb;}

	private:
		Acceptor _acceptor;
		EpollPoller _epollPoller;
		CbFunction _onConnCb;
		CbFunction _onMsgCb;
		CbFunction _onCloseCb;
};

#endif
