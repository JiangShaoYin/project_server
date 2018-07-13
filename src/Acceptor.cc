///
/// @file    Acceptor.cpp
/// @author  lemon(haohb13@gmail.com)
/// @date    2017-05-11 18:48:06
///

#include "Acceptor.h"
#include "SocketUtil.h"
#include "InetAddr.h"

#include <iostream>
#include <sstream>
using std::cout;
using std::endl;


Acceptor::Acceptor(int sfd, const InetAddr & addr)
	: _sfd(sfd),
	_addr(addr) {}

Acceptor::Acceptor()
	:_sfd(createSocketFd()) {
	cout << "Acceptor()" << " create a sfd " << endl;
	}

	 void Acceptor::ready() {
		 setReuseAddr(true);
		 setReusePort(true);
		 bind();
		 listen();
	 }

int Acceptor::accept() {
	int peerfd = ::accept(_sfd.fd(), NULL, NULL);
	if(peerfd == -1) {
		perror("accept error");
	}
	return peerfd;
}

void Acceptor::setReuseAddr(bool flag) {
	int on = (flag ? 1 : 0);
	if(::setsockopt(_sfd.fd(), 
				SOL_SOCKET, 
				SO_REUSEADDR, 
				&on, 
				static_cast<socklen_t>(sizeof(on))) == -1) {
		perror("setsockopt reuseaddr error");
		::close(_sfd.fd());
		exit(EXIT_FAILURE);
	}
}


void Acceptor::setReusePort(bool flag) {
#ifdef SO_REUSEPORT
	int on = (flag ? 1 : 0);
	if(::setsockopt(_sfd.fd(), 
				SOL_SOCKET,
				SO_REUSEPORT,
				&on,
				static_cast<socklen_t>(sizeof(on))) == -1) {
		perror("setsockopt reuseport error");
		::close(_sfd.fd());
		exit(EXIT_FAILURE);
	}
#else
	if(flag) {
		fprintf(stderr, "SO_REUSEPORT is not supported!\n");
	}
#endif
}

void Acceptor::bind() {
	if(-1 == ::bind(_sfd.fd(), 
				(const struct sockaddr*)_addr.getInetAddrPtr(), 
				sizeof(InetAddr))) {
		perror("bind error");
		::close(_sfd.fd());
		exit(EXIT_FAILURE);
	}
}

void Acceptor::listen() {
	if(-1 == ::listen(_sfd.fd(), 10)) {
		perror("listen error");
		::close(_sfd.fd());
		exit(EXIT_FAILURE);
	}
}

std::string Acceptor::ipPort() const {
	std::ostringstream oss;
	oss << _addr.port();
	return _addr.ip() + ":" + oss.str();
}

