 /// @date    2018-07-11 19:43:56

#ifndef __INETADDR_H__
#define __INETADDR_H__
#include "Configuration.h"
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
using namespace std;

class InetAddr {
	public:
		InetAddr(string & ip, unsigned short port) {
			memset(&_addr, 0 , sizeof(_addr));
			_addr.sin_family = AF_INET;
			_addr.sin_addr.s_addr = inet_addr(ip.c_str());	
			_addr.sin_port = htons(port);	
		}
		InetAddr() {
			Configuration conf("/home/jiang/project_server/conf/conf.txt");
			map<string,string> confMap = conf.getConfigMap();
			memset(&_addr, 0 , sizeof(_addr));
				_addr.sin_family = AF_INET;
				_addr.sin_addr.s_addr = inet_addr(confMap["ip"].c_str());	
				_addr.sin_port = htons(atoi(confMap["port"].c_str()));
		}
		InetAddr(struct sockaddr_in& addr) :_addr(addr) {}
		string ip() const ;
		unsigned short port() const;
		struct sockaddr_in* getInetAddrPtr();
	private:
		struct sockaddr_in _addr; 
};
#endif
