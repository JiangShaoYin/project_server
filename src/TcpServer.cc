 /// @date    2018-07-13 15:50:24
 
#include "TcpServer.h"

void TcpServer::start() {
	_acceptor.ready();
	_epollPoller.setOnConnCb(_onConnCb);
	_epollPoller.setOnMsgCb(_onMsgCb);
	_epollPoller.setOnCloseCb(_onCloseCb);

	_epollPoller.loop();
}
void TcpServer::stop() {
	_epollPoller.unloop();
}
