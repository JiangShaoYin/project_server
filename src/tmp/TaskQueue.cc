 /// @date    2018-07-03 17:51:12
 
#include "TaskQueue.h"

bool TaskQueue::full() {  return _qsize== _que.size();}
bool TaskQueue::empty() {	return _que.size() == 0;}

void TaskQueue::push(Task &&task) {
	MutexLockGuard autolock(_mutex);
	while(full()) {		//队满，等待_notFull条件发生,不使用if是防止wait被异常唤醒（bug:多核cpu，一个信号可能唤醒多个cond）
		_notFull.wait();//1.解锁，阻塞等待条件，2.条件满足，加锁，离开,继续判断while看是否队不满(防止异常唤醒)
	}
	_que.push(std::move(task));
	_notEmpty.notify();//通知等待_notEmpty条件的线程
}
//子线程调用
Task TaskQueue::pop() {
	MutexLockGuard autolock(_mutex);
	while(_threadRunning && empty()) {
		_notEmpty.wait();
	}
	
	if(_threadRunning) {
	Task tmp = _que.front();
	_que.pop();
	_notFull.notify();
	return tmp;
	}
	else
		return NULL;
}

void TaskQueue::wakeUp() {
	_threadRunning = false;
	_notEmpty.notifyAll();	
}

