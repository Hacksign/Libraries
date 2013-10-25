#ifndef _H_UTILS_
#define _H_UTILS_
#include <map>
#include <vector>
#include <boost/thread.hpp>
namespace HUtils{
	class IThread{
		public:
			virtual ~IThread(){}
		protected:
			virtual void operator()() = 0;
	};
	template <typename Thread_T>
		class ThreadPool{
			private:
				typedef std::map<Thread_T *, boost::thread *> _object_thread_t;
				_object_thread_t _object_thread;
				boost::thread_group _thread_pool;
				boost::mutex _thread_pool_mutex;
			public:
				ThreadPool(){
				}
				ThreadPool(Thread_T* _thread){
					add(_thread);
				}
				~ThreadPool(){
					release();
				}
			public://iterator(s)
				template<typename T, typename Item_T>
					class Iterator_base{
						public:
							Iterator_base(T& obj_trd) : _obj_trd(obj_trd), _iterator_position(0){}
							virtual ~Iterator_base(){}
							virtual bool operator!=(size_t size){
								if(_iterator_position < size) return true;
								return false;
							}
							virtual const Iterator_base& operator++(){
								++_iterator_position;
								return *this;
							}
							virtual const Iterator_base& operator--(){
								--_iterator_position;
								return *this;
							}
							virtual Item_T operator*(){
								int i = 0;
								for(typename T::iterator it = _obj_trd.begin(); it != _obj_trd.end(); ++it){
									if(i++ == _iterator_position){
										return *(it->first);
									}
								}
							}
							virtual Item_T* operator->(){
								int i = 0;
								for(typename T::iterator it = _obj_trd.begin(); it != _obj_trd.end(); ++it){
									if(i++ == _iterator_position){
										return it->first;
									}
								}
							}
							virtual Item_T* get(){
								return operator->();
							}
							size_t pos(){
								return _iterator_position;
							}
						private:
							T _obj_trd;
							size_t _iterator_position;
					};
				typedef Iterator_base<_object_thread_t, Thread_T> iterator;
			public:
				bool add(Thread_T* _thread){
					boost::mutex::scoped_lock lock(_thread_pool_mutex);
					for(typename _object_thread_t::iterator it = _object_thread.begin(); it != _object_thread.end(); ++it){
						if(_thread == it->first) return true;
					}
					boost::thread *_pthread = new boost::thread(boost::ref(*_thread));
					_thread_pool.add_thread(_pthread);
					_object_thread[_thread] = _pthread;
					lock.unlock();
					return true;
				}
				bool release(Thread_T* _thread){
					bool bRet = false;
					boost::mutex::scoped_lock lock(_thread_pool_mutex);
					for(typename _object_thread_t::iterator it = _object_thread.begin(); it != _object_thread.end(); ++it){
						if(it->first == _thread){
							it->second->join();
							_thread_pool.remove_thread(it->second);
							_object_thread.erase(it);
							bRet = true;
							break;
						}
					}
					lock.unlock();
					return bRet;
				}
				bool release(){
					_thread_pool.join_all();
					_object_thread.clear();
				}
				size_t size(){
					return _object_thread.size();
				}
				bool empty(){
					return _object_thread.empty();
				}
				iterator begin(){
					return iterator(_object_thread);	
				}
				size_t end(){
					return size();
				}
		};
}
#endif
