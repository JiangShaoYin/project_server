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
using CbFunction = function<void(const TcpConnPtr&)>;
					//TcpConnection的成员函数，需要把当前类对象作为参数使用
class TcpConnection : public enable_shared_from_this<TcpConnection> {
	public:
		TcpConnection(int fd, EpollPoller* poller);
		TcpConnection(int fd);
		string receive();
		void send(const string & msg);
		void shutDown();
		void sendResultToIOthread(const string &result);//计算线程要与IO线程进行通信： 计算线程要通知IO线程发送结果()
		string connectionInfo();
			void setOnConnCb(const CbFunction &cb) { _onConnCb = cb;}
			void setOnMsgCb(const CbFunction &cb) { _onMsgCb = cb;}
			void setOnCloseCb(const CbFunction &cb) { _onCloseCb = cb;}
		void handleOnConnCb() {_onConnCb(shared_from_this());}
		void handleOnMsgCb() { _onMsgCb(shared_from_this());}
		void handleOnCloseCb() { _onCloseCb(shared_from_this());}
		~TcpConnection();
	private:
		Socket _sockfd;
		SocketIO _sockIO;
		bool _shutDown;
		EpollPoller* _epollPoller;
		const InetAddr _localAddr;
		const InetAddr _peerAddr;
			CbFunction _onConnCb;
			CbFunction _onMsgCb;
			CbFunction _onCloseCb;
		//void sendAndClose(const string &result);
};//end of TcpConnection
#endif
