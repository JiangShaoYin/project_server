 /// @date    2018-07-03 17:00:11

#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "MutexLock.h"

class Condition {
	public:
		Condition(MutexLock & mutex) : _mutex(mutex) {//Condition实现需要一把互斥锁，传入MutexLock对象,进行加解锁,初始时将该锁传入
			pthread_cond_init(&_cond, NULL);
		}
		void wait() { pthread_cond_wait(&_cond, _mutex.getMutex());}//解开mutex指向的锁，等待条件_cond(阻塞)
		void notify() {	pthread_cond_signal(&_cond);}
		void notifyAll() { pthread_cond_broadcast(&_cond); };
		~Condition() {pthread_cond_destroy(&_cond);}
	private:
		pthread_cond_t _cond;
		MutexLock & _mutex;
};


#endif
