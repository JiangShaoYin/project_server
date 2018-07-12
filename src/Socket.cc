/// @date    2018-07-11 22:13:11

#include "Socket.h"
#include "InetAddr.h"
#include "SocketUtil.h"

Socket::Socket(int sockfd)	: _sockfd(sockfd) {}

Socket::Socket(): _sockfd(createSocketFd()) {}

Socket::~Socket() {::close(_sockfd);}

void Socket::nonBlock() {setNonblock(_sockfd);}
void Socket::shutDownWrite(){
	if(::shutdown(_sockfd, SHUT_WR) == -1)	{
		perror("shudown write error!");
	}
}

InetAddr Socket::getLocalAddr(int sockfd){
	struct sockaddr_in addr;
	socklen_t len = sizeof(sockaddr_in);
	if(::getsockname(sockfd, (struct sockaddr *)&addr, &len) == -1)	{
		perror("getsockname error");
	}
	return InetAddr(addr);
}

InetAddr Socket::getPeerAddr(int sockfd){
	struct sockaddr_in addr;
	socklen_t len = sizeof(sockaddr_in);
	if(::getpeername(sockfd, (struct sockaddr *)&addr, &len) == -1)	{
		perror("getpeername error");
	}
	return InetAddr(addr);
}
