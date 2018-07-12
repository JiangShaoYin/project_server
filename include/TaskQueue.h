 /// @date    2018-07-03 17:44:34

#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__
#include "Condition.h"
#include "MutexLock.h"
#include <queue>
#include <functional>
using std::queue;
typedef std::function<void()> Task;

class TaskQueue {
//	using  Task = std::function<void()>;
	public:
		TaskQueue(size_t qsize) : _qsize(qsize),
								 _notFull(_mutex),
								 _notEmpty(_mutex), 
							     _threadRunning(true) {}
		bool empty();
		bool full();
		void push(Task&&);
		Task pop();
		void wakeUp();
	private:
		size_t _qsize;
		queue<Task> _que;
		MutexLock _mutex;
		Condition _notFull;
		Condition _notEmpty;
		bool _threadRunning;
};


#endif
