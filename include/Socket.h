/// @date    2018-07-11 22:01:47

#ifndef __SOCKET_H__
#define __SOCKET_H__

class InetAddr;
class Socket {
	public:
		Socket();
		~Socket();
		Socket(int sockfd);
		void nonBlock();
		void shutDownWrite();
		int fd()const{	return _sockfd;	}
	static InetAddr getLocalAddr(int sockfd);
	static InetAddr getPeerAddr(int sockfd);
	private:
		int _sockfd;
}; 
#endif
