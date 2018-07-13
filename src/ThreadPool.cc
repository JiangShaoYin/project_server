 /// @date    2018-07-04 13:27:00

#include "ThreadPool.h"
#include "Producer.h"

void ThreadPool::start() {
	for(size_t i=0; i < _threadNum; ++i){
		shared_ptr<Thread> thread(new Thread(std::bind(&ThreadPool::threadFunc, this) ) );
		_threads.push_back(thread);	//上面的操作是消除threadFunc()里的默认的第一个this指针
	}
	for(auto & pthread : _threads){
		pthread->start();
	}
}
void ThreadPool::addTask(Task&& task) {	_taskQue.push(std::move(task));}
//运行在主线程
void ThreadPool::stop() {//执行回收线程操作,pool准备退出，将_exit改为true
	if(!_exit) {
		while(!_taskQue.empty()) {	//更改_exit之前，查看当前任务队列是否还有剩余任务
			sleep(1);				//如果有，则等待，知道任务队列里全部执行完毕，再退出
		}
	_exit = true;
	_taskQue.wakeUp();		//如果有进程阻塞在taskQue的pop上，则广播信号唤醒阻塞的进程
	for(auto & pthread : _threads) 
		pthread->join();
	}
}
//子线程执行的操作方法
void ThreadPool::threadFunc() {
	while(!_exit) {//当线程池不退出时，取taskQue队列中的task，并执行
		Task task = getTask();
		if(task)
			task();
	}
}

Task ThreadPool::getTask() {	return _taskQue.pop();}
ThreadPool::~ThreadPool() {
	cout << "~ThreadPool" << endl;
	if(!_exit) stop();}

