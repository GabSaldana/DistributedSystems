#ifndef __CONCLIST
#define __CONCLIST

#include <list>

#include <pthread.h>
#include <sys/time.h>

using namespace std;

template <typename elemType>
class ConcurrentList {
	private:
		typedef struct {
			elemType& elem;
			struct timeval savetime;
		} timerData;
		
		struct timeval lastAccess;
		list<elemType> data;
		list<timerData> timers;
		pthread_mutex_t mutex;
	public:
		typedef typename list<elemType>::iterator iterator;
		ConcurrentList();
		void pop_front();
		void pop_back();
		void push_front(const elemType& val);
		void push_back(const elemType& val);
		elemType front();
		elemType back();
		void sort();
		void unique();
		typename list<elemType>::iterator begin();
		typename list<elemType>::iterator end();
		elemType& operator*();
		void delete_old();
		void clear();
};

#include "ConcurrentList.cpp"

#endif
