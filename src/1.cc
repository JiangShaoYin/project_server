/// @date    2018-07-11 21:32:20

#include "InetAddr.h"
#include "Configuration.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include <stdlib.h>

int main() {
	Acceptor acceptor;
	acceptor.ready();

	TcpConnection conn(acceptor.accept());
	cout << "..............................." << endl;
	cout << acceptor.ipPort() << endl;
	cout << "..............................." << endl;
	cout << conn.connectionInfo() << endl;
	conn.send("welcome to server!");
	conn.shutDown();
	while(1){
		cout << "server receive" << ": ";
		string msg = conn.receive();
		cout << msg << endl;
		conn.send(msg);
	}
}
