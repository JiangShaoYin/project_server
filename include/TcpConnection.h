 /// @date    2018-07-11 23:44:13

#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__
#include "Socket.h"
#include "SocketIO.h"
#include "InetAddr.h"
#include <string>
#include <memory>
using namespace std;
class EpollPoller;
class TcpConnection;

using TcpConnPtr = shared_ptr<TcpConnection>;

class TcpConnection {
	public:
		using TcpConnCb = function<void(const TcpConnPtr&)>;
	public:
		TcpConnection(int fd, EpollPoller* poller);
		TcpConnection(int fd);
		string receive();
		void send(const string & msg);
		void shutDown();
		string connectionInfo();
			void setOnConnCb(const TcpConnCb &cb) { _onConnCb = cb;}
			void setOnMsgCb(const TcpConnCb &cb) { _onMsgCb = cb;}
			void setOnCloseCb(const TcpConnCb &cb) { _onCloseCb = cb;}
		void handleOnConnCb() {_onConnCb(const TcpConnPtr&);}
		void handleOnMsgCb() { _onMsgCb();}
		void handleOnCloseCb() { _onCloseCb();}
	private:
		Socket _sockfd;
		SocketIO _sockIO;
		bool _shutDown;
		EpollPoller* _poller;
		const InetAddr _localAddr;
		const InetAddr _peerAddr;
			TcpConnCb _onConnCb;
			TcpConnCb _onMsgCb;
			TcpConnCb _onCloseCb;
};//end of TcpConnection
#endif
