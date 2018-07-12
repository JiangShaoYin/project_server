 /// @date    2018-07-11 20:00:29
 
#include "InetAddr.h"

string InetAddr::ip() const {
	return string(inet_ntoa(_addr.sin_addr));
}
unsigned short  InetAddr:: port() const {
	return ntohs(_addr.sin_port);
}

struct sockaddr_in* InetAddr::getInetAddrPtr() {
	return &_addr;
}
