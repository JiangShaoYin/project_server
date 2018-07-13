
#include "TcpServer.h"
#include "ThreadPool.h"
#include <iostream>
using namespace std;

class ThreadTask{
public:
	ThreadTask(const string & query, const TcpConnPtr & conn)
	: _queury(query)
	, _conn(conn)
	{}
	void process() {//
		cout << "> task is processing" << endl;
		//decode
		//process
		//encode
		//_conn->send(_queury);//如果直接去使用send，在计算线程里面完成了数据发送,不可取
		//应该将_queury换成_result
		_conn->sendResultToIOthread(_queury);
		cout << "_conn->sendResultToIOthread(_queury) Done!!!" << endl;
	}
private:
	string _queury;
	TcpConnPtr _conn;
};

ThreadPool * g_threadpool = NULL;

void onConnection(const TcpConnPtr &conn){
	cout << conn->connectionInfo() << endl;
    conn->send("hello, welcome to Chat Server.\r\n");
}

//运行在IO线程
void onMessage(const TcpConnPtr &conn){
    string s(conn->receive());

	ThreadTask task(s, conn);
	g_threadpool->addTask(bind(&ThreadTask::process, task));
	cout << "> add task to threadpool" << endl;
}

void onClose(const TcpConnPtr &conn){
    printf("%s close\n", conn->connectionInfo().c_str());
}

int main(){
	ThreadPool threadpool(4, 20);
	g_threadpool = &threadpool;
	threadpool.start();

	TcpServer tcpserver;
	tcpserver.setOnConnCb(&onConnection);
	tcpserver.setOnMsgCb(&onMessage);
	tcpserver.setOnCloseCb(&onClose);

	tcpserver.start();

    return 0;
}
