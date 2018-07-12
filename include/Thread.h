 /// @date    2018-07-02 13:20:31

#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <functional>
using namespace std;
using CallBack = function<void()>;

class Thread {
	public:
		Thread(CallBack && cb) : _pid(0),
								_is_runing(false), 
								_cb(move(cb)) {}
		void start();
		void join();
		virtual ~Thread();
	private:
		static void * ThreadFunc(void*);//pthread_create()的要求，该函数参数和返回值都是void*
	private:
		pthread_t _pid;
		bool _is_runing;
		CallBack _cb;
};//end of namespace w



#endif
