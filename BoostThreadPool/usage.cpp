#include <iostream>
#include "ThreadPool.h"
#include <unistd.h>

using namespace HUtils;
using namespace std;

class MyThreadClass{
	public:
		MyThreadClass(int i) : number(i){};
		void operator()(){
			++number;
		}
	public:
		int number;
};

int main(){
	MyThreadClass t1(1);
	ThreadPool<MyThreadClass> thread_pool(t1);
	//cout<<"pool size:"<<thread_pool.size()<<endl;
	MyThreadClass t2(2);
	thread_pool.add(t2);
	//cout<<"pool size:"<<thread_pool.size()<<endl;
	sleep(3);
	//cout<<"pool size:"<<thread_pool.size()<<endl;
	cout<<t1.number<<endl;
	cout<<t2.number<<endl;
	return 0;
}
