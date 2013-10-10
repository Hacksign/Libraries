#ifndef _H_UTILS_
#define _H_UTILS_
#include <map>
#include <vector>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
namespace HUtils{
	class IThread{
		public:
			virtual ~IThread(){}
		protected:
			virtual void operator()() = 0;
	};
	template <typename Thread_T>
		class ThreadPool{
			public:
				typedef boost::shared_ptr<boost::thread> thread_t;
				typedef std::map<Thread_T*, thread_t> object_thread_t;
				typedef std::map<boost::thread::id, object_thread_t> threadpool_t;
				typedef typename threadpool_t::iterator threadpool_iterator_t;
				template<typename T, typename Item_T>
					class Iterator_base{
						public:
							Iterator_base(T& item) : _item(item), iterator_position(0){
							}
							const Iterator_base& operator++(){
								++iterator_position;
								return *this;
							}
							const Iterator_base& operator--(){
								--iterator_position;
								return *this;
							}
							Item_T& operator*(){
								int i = 0;
								for(typename T::iterator tmp = _item.begin(); tmp != _item.end(); ++tmp){
									if(i++ != iterator_position) continue;
									else return *(tmp->first);
								}
							}
							Item_T* operator->(){
								int i = 0;
								for(typename T::iterator tmp = _item.begin(); tmp != _item.end(); ++tmp){
									if(i++ != iterator_position) continue;
									else return tmp->first;
								}
							}
							bool operator!=(size_t size){
								if(iterator_position < size) return true;
								return false;
							}
						private:
							T _item;
							size_t iterator_position;
					};
				typedef Iterator_base<object_thread_t, Thread_T> iterator;

			public:
				//init an empty pool
				ThreadPool(){
					_joiner_running = true;
					_joiner = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&ThreadPool<Thread_T>::_join_thread, this)));
				}
				//init an pool with a thread
				ThreadPool(Thread_T &_thread){
					_joiner_running = true;
					_joiner = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&ThreadPool<Thread_T>::_join_thread, this)));
					add(_thread);
				}
				~ThreadPool(){
					release();
				}
				boost::thread::id add(Thread_T& _thread){
					for(threadpool_iterator_t it = _thread_pool.begin(); it != _thread_pool.end(); ++it){
						object_thread_t _each_thread = it->second; 
						typename object_thread_t::iterator  tmp = _each_thread.begin();
						if(&_thread == tmp->first) return it->first;
					}
					thread_t _t = thread_t(new boost::thread(boost::ref(_thread)));
					object_thread_t _obj_trd;
					_obj_trd[&_thread] = _t;
					_thread_pool[_t->get_id()] = _obj_trd; 
					_thread_objects[&_thread] = _t;
					return _t->get_id();
				}
				//get pool size
				size_t size(){
					return _thread_pool.size();
				}
				bool empey(){
					return _thread_pool.empty();
				}
				void release(){
					_joiner_running = false;
					for(threadpool_iterator_t it = _thread_pool.begin(); it != _thread_pool.end(); ++it){
						object_thread_t _each_thread = it->second; 
						typename object_thread_t::iterator  tmp = _each_thread.begin();
						tmp->second->join();
					}
					_joiner->join();
				}
				//for iterators
				iterator begin(){
					return iterator(_thread_objects);
				}
				size_t end(){
					return _thread_objects.size();
				}
			//private functions
			private:
				void _join_thread(){
					while(_joiner_running){
						std::vector<threadpool_iterator_t> _joined_thread;
						//join thread
						for(threadpool_iterator_t it = _thread_pool.begin(); it != _thread_pool.end(); ++it){
							object_thread_t _each_thread = it->second; 
							typename object_thread_t::iterator  tmp = _each_thread.begin();
							if(tmp->second->timed_join(boost::posix_time::microseconds(100)))  _joined_thread.push_back(it);
						}
						//erase from thread pool
						for(typename std::vector<threadpool_iterator_t>::iterator begin = _joined_thread.begin(); begin != _joined_thread.end(); ++begin){
							_thread_pool.erase(*begin);
						}
						if(!_thread_pool.empty()) sleep(1);
						else sleep(5);
					}
				}
			//protected variables
			protected:
				object_thread_t _thread_objects;
			//private variables
			private:
				threadpool_t _thread_pool;
				boost::shared_ptr<boost::thread> _joiner;
				bool _joiner_running;
		};
}
#endif
