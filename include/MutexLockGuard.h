 /// @date    2018-07-13 11:44:00
 
#ifndef __MUTEXLOCKGUARD_H__
#define __MUTEXLOCKGUARD_H__
#include "MutexLock.h"

class MutexLockGuard : public MutexLock {
	public:
		MutexLockGuard(MutexLock & mutex) :_mutex(mutex){_mutex.lock();}
		~MutexLockGuard() {_mutex.unlock();}
	private:
		MutexLock & _mutex;
};

#endif
