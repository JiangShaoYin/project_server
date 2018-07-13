 /// @date    2018-07-11 22:42:23
 
#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "Socket.h"
#include "InetAddr.h"
#include <string>
using namespace std;

class Acceptor{
public:
	Acceptor(int sfd, const InetAddr & addr);
	Acceptor();
	void ready();			//服务器准备监听
	int accept();			//接收新连接，返回与客户通信的newfd(peerfd)
	int fd() const{	return _sfd.fd();}//
	string ipPort()const;
private:
	void setReuseAddr(bool on);//ready依次调用
	void setReusePort(bool on);
	void bind();
	void listen();
private:
	Socket _sfd;
	InetAddr _addr;
};
#endif
