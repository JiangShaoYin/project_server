/// @date    2018-07-04 22:56:45

#ifndef __PRODUCER_H__
#define __PRODUCER_H__
#include <unistd.h>
#include <iostream>
using namespace std;
class  Producer {
	public:
	void produce() {
		srand(time(NULL));
			int num = rand()%100;
			cout << " produce a num :" << num << endl;
			sleep(1);
		}	
};
#endif
