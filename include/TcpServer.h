 /// @date    2018-07-12 10:43:17

#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
#include "Acceptor.h"
#include "SocketUtil.h"

class TcpServer {
	TcpServer()
		_accept(createSocketFd,) {
	}

	private:
		Acceptor _accept;
};


#endif
