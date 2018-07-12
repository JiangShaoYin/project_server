 /// @date    2018-07-12 00:27:22

#include "TcpConnection.h"
#include <string.h>
#include <stdio.h>

TcpConnection::TcpConnection(int fd, EpollPoller* poller)
	:_sockfd(fd),
	 _sockIO(fd),
	 _shutDown(false),
	 _poller(poller), 
	 _localAddr(Socket::getLocalAddr(fd)),
	 _peerAddr(Socket::getPeerAddr(fd))  {_sockfd.nonBlock();}

TcpConnection::TcpConnection(int fd)
	:_sockfd(fd),
	 _sockIO(fd),
	 _shutDown(false),
	 _localAddr(Socket::getLocalAddr(fd)),
	 _peerAddr(Socket::getPeerAddr(fd))  {_sockfd.nonBlock();}

string TcpConnection::receive() {
	char buf[65536];
	memset(buf, 0, sizeof(buf));
	size_t ret = _sockIO.readline(buf, sizeof(buf));
	if(ret == 0)
		return string();
	else
		return string(buf);
}
void TcpConnection::send(const string & msg) {
	_sockIO.writen(msg.c_str(), msg.size());
}
void TcpConnection::shutDown() {
	if(!_shutDown)
		_sockfd.shutDownWrite();
	_shutDown = true;
}

string TcpConnection::connectionInfo() {
	char buf[200];
	snprintf(buf, sizeof(buf), "Local:%s : %d -> peer:%s : %d",
			 _localAddr.ip().c_str(),
			 _localAddr.port(),
			 _peerAddr.ip().c_str(),
			 _peerAddr.port());
	return string(buf);
}
