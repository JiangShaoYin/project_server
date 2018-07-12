 /// @date    2018-07-04 12:50:15
 //
#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.h"
#include "Thread.h"
#include <memory>
#include <vector>
using namespace std;
//class Thread;
class ThreadPool {
	public:
		ThreadPool(size_t threadNum, size_t qsize)	:_threadNum(threadNum),
													_qsize(qsize),
													_taskQue(_qsize),
													_exit(false) {_threads.reserve(_threadNum);}
		void start();
		void stop();
		void addTask(Task&&);
		~ThreadPool();
	private:
		void threadFunc();
		Task getTask();
	private:
		size_t _threadNum;
		size_t _qsize;//接收任务数量的队列
		TaskQueue _taskQue;
		vector<shared_ptr<Thread>> _threads;
		bool _exit;
};



#endif
