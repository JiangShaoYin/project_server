 /// @date    2018-07-03 16:04:53
 
#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__
#include <pthread.h>

class MutexLock {
	public:
		MutexLock() {
			pthread_mutex_init(&_mutex,NULL);
		}
		void lock() {pthread_mutex_lock(&_mutex);}
		void unlock() {pthread_mutex_unlock(&_mutex);}
		pthread_mutex_t * getMutex() {	return &_mutex;}//传指针效率更高？
		~MutexLock() {	pthread_mutex_destroy(&_mutex);}
	private:
	pthread_mutex_t _mutex;
};
class MutexLockGuard : public MutexLock {
	public:
		MutexLockGuard(MutexLock & mutex) :_mutex(mutex){_mutex.lock();}
		~MutexLockGuard() {_mutex.unlock();}
	private:
		MutexLock & _mutex;
};
#endif
