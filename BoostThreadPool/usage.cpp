#include <iostream>
#include "ThreadPool.h"
#include <unistd.h>

//use below command to compile me:
//	g++ usage.cpp -o test -lboost_thread -lboost_system

using namespace HUtils;
using namespace std;

class MyThreadClass : public IThread{
	public:
		MyThreadClass(int i) : number(i), thread_id(number){};
		virtual void operator()(){
			++number;
		}
		void print(){
			cout<<"id:"<<thread_id<<endl;
		}
	public:
		int number;
		int thread_id;
};

int main(){
	MyThreadClass t1(1);
	ThreadPool<MyThreadClass> thread_pool(t1);
	MyThreadClass t2(2);
	thread_pool.add(t2);
	for(ThreadPool<MyThreadClass>::iterator it = thread_pool.begin(); it != thread_pool.end(); ++it){
		it->print();
	}
	sleep(1);//wait all done
	return 0;
}
