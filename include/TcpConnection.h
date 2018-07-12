 /// @date    2018-07-11 23:44:13

#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__
#include "Socket.h"
#include "SocketIO.h"
#include "InetAddr.h"
#include <string>
using namespace std;

class EpollPoller;
class TcpConnection {
	public:
		TcpConnection(int fd, EpollPoller* poller);
		TcpConnection(int fd);
		string receive();
		void send(const string & msg);
		void shutDown();
		string connectionInfo();
	private:
		Socket _sockfd;
		SocketIO _sockIO;
		bool _shutDown;
		EpollPoller* _poller;
		const InetAddr _localAddr;
		const InetAddr _peerAddr;
};//end of TcpConnection
#endif
