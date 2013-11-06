## Usage:
	* use below command to compile:
```bash
		g++ usage.cpp -o test -lboost_thread -lboost_system
```
	* usage.cpp:
```bash
			#include <iostream>
			#include "ThreadPool.h"

			using namespace HUtils;
			using namespace std;

			#define MAX_THREADS 100

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
				ThreadPool<MyThreadClass> thread_pool;
				//create 10 threads
				for(int i = 0; i < MAX_THREADS; ++i){
					thread_pool.add(new MyThreadClass(i));

				}
				cout<<"size:"<<thread_pool.size()<<endl;
				vector<MyThreadClass *> p;
				for(ThreadPool<MyThreadClass>::iterator it = thread_pool.begin(); it != thread_pool.end(); ++it){
					cout<<(*it).number<<"\t"<<it->number<<endl;
					p.push_back(it.get());

				}
				for(vector<MyThreadClass *>::iterator it = p.begin(); it != p.end(); ++it){
					thread_pool.release(*it);
					delete *it;

				}
				MyThreadClass* pMyTrdClassObj = new MyThreadClass(0);
				thread_pool.add(pMyTrdClassObj);
				boost::thread* pthread = thread_pool.grab(pMyTrdClassObj);
				pthread->join();
				delete pthread; //do not forget delete thread instance after grab it out from ThreadPool
				delete pMyTrdClassObj;
				thread_pool.release();
				return 0;

			}
```
	For more information see 'ThreadPool.h'.
