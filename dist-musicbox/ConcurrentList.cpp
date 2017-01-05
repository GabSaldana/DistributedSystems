// #include "ConcurrentList.hpp"

template <typename elemType>
ConcurrentList<elemType>::ConcurrentList() {
	pthread_mutex_init(&mutex, NULL);
}

template <typename elemType>
void ConcurrentList<elemType>::pop_front() {
	pthread_mutex_lock(&mutex);
//	elemType& elem = data.front();
	
//	for (typename list<timerData>::iterator it = timers.begin(); it != timers.end(); ) {
//		if (it->elem == elem) {
//			it = timers.erase(it);
//		} else {
//			++it;
//		}
//	}
	
	data.pop_front();
	pthread_mutex_unlock(&mutex);
}

template <typename elemType>
void ConcurrentList<elemType>::pop_back() {
	pthread_mutex_lock(&mutex);
//	elemType& elem = data.back();
	
//	for (typename list<timerData>::iterator it = timers.begin(); it != timers.end(); ) {
//		if (it->elem == elem) {
//			it = timers.erase(it);
//		} else {
//			++it;
//		}
//	}
	
	data.pop_back();
	pthread_mutex_unlock(&mutex);
}

template <typename elemType>
void ConcurrentList<elemType>::push_front(const elemType& val) {
	pthread_mutex_lock(&mutex);
//	delete_old();
//	timerData td = { (elemType&) val, lastAccess };
	data.push_front(val);
//	timers.push_front(td);
	
	pthread_mutex_unlock(&mutex);
}

template <typename elemType>
void ConcurrentList<elemType>::push_back(const elemType& val) {
	pthread_mutex_lock(&mutex);
//	delete_old();
//	timerData td = { (elemType&) val, lastAccess };
	data.push_back(val);
//	timers.push_back(td);
	
	pthread_mutex_unlock(&mutex);
}

template <typename elemType>
elemType ConcurrentList<elemType>::front() {
	pthread_mutex_lock(&mutex);
//	delete_old();
	elemType& elem = data.front();
	pthread_mutex_unlock(&mutex);
	
	return elem;
}

template <typename elemType>
elemType ConcurrentList<elemType>::back() {
	pthread_mutex_lock(&mutex);
//	delete_old();
	elemType& elem = data.back();
	pthread_mutex_unlock(&mutex);
	
	return elem;
}

template <typename elemType>
void ConcurrentList<elemType>::sort() {
	pthread_mutex_lock(&mutex);
//	delete_old();
	data.sort();
	pthread_mutex_unlock(&mutex);
}

template <typename elemType>
void ConcurrentList<elemType>::unique() {
	pthread_mutex_lock(&mutex);
//	delete_old();
	data.unique();
	pthread_mutex_unlock(&mutex);
}

template <typename elemType>
typename list<elemType>::iterator ConcurrentList<elemType>::begin() {
	pthread_mutex_lock(&mutex);
//	delete_old();
	pthread_mutex_unlock(&mutex);
	return data.begin();
}

template <typename elemType>
typename list<elemType>::iterator ConcurrentList<elemType>::end() {
	pthread_mutex_lock(&mutex);
//	delete_old();
	pthread_mutex_unlock(&mutex);
	return data.end();
}

template <typename elemType>
elemType& ConcurrentList<elemType>::operator*() {
	return data;
}

template <typename elemType>
void ConcurrentList<elemType>::delete_old() {
	pthread_mutex_lock(&mutex);
	
	gettimeofday(&lastAccess, NULL);
	
	struct timeval thres = { 0, 75000000 };
	
	for (typename list<timerData>::iterator it = timers.begin(); it != timers.end(); ) {
		struct timeval tv = it->savetime;
		struct timeval dif;
		timersub(&lastAccess, &tv, &dif);
		
		if ( !timercmp(&dif, &thres, >) ) {
			data.remove(it->elem);
			it = timers.erase(it);
		} else {
			it++;
		}
	}
	
	pthread_mutex_unlock(&mutex);
}

template <typename elemType>
void ConcurrentList<elemType>::clear() {
	pthread_mutex_lock(&mutex);
	data.clear();
	pthread_mutex_unlock(&mutex);
}
