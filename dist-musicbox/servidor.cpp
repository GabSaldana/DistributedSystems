#include <cstdio>

#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#include "ConcurrentList.hpp"

#include "SocketDatagrama.hpp"
#include "PaqueteDatagrama.hpp"
#include "messages.hpp"

void * send(void * args) {
	sendThreadData *std = (sendThreadData *) args;
	SocketDatagrama *ssock = std->ssock;
//	ConcurrentList<int> *machines = std->machines;
	
	char ip[17] = {0};
	sprintf(ip, "%s%d", PREFIX, 255);
	
	struct timespec sleep = { 0, 100000000 };
	
	while (true) {
		sem_wait(std->mutexDif);
		
		messageSC msc = { *(std->playing), *(std->musPoint) };
		
		PaqueteDatagrama packSend((char *) &msc, sizeof msc, ip, CPORT);
		ssock->envia(packSend);
		
		nanosleep(&sleep, NULL);
		
		sem_post(std->mutexTbl);
	}
	
	return NULL;
}

void * table(void *args) {
	tableThreadData *ttd = (tableThreadData *) args;
	ConcurrentList<int> *machines = ttd->machines;
	
	while (true) {
		sem_wait(ttd->mutexTbl);
		
		machines->sort();
		machines->unique();
		
		bool found = false;
		
		for (list<int>::iterator it = machines->begin(); it != machines->end(); it++) {
			if (*it == *(ttd->playing)) {
				found = true;
				break;
			}
//			printf("%s%d\n", PREFIX, *it);
		}
		
		if (!found || *(ttd->playing) == 0) {
			found = true;
			*(ttd->playing) = machines->front();
		}
		
		machines->clear();
		
		sem_post(ttd->mutexDif);
	}
	
	return NULL;
}

void * receive(void *args) {
	receiveThreadData *rtd = (receiveThreadData *) args;
	SocketDatagrama *ssock = rtd->ssock;
	ConcurrentList<int> *machines = rtd->machines;
	
	while (true) {
		PaqueteDatagrama packRecv(sizeof(messageCS));
		
		if ( ssock->recibe(packRecv) >= 0 ) {
			messageCS *mcs = (messageCS *) packRecv.obtieneDatos();
//			char *ip = packRecv.obtieneDireccion();
			
//			int lastByte;
//			sscanf(ip, "%*d.%*d.%*d.%d", &lastByte);
			
			machines->push_back(mcs->numPc);
			
			if (mcs->point.mins != 0 || mcs->point.secs != 0) {
				rtd->musPoint->mins = mcs->point.mins;
				rtd->musPoint->secs = mcs->point.secs;
			}
		} else {
			perror("Error al recibir un paquete");
		}
	}
	
	return NULL;
}

int main() {
	SocketDatagrama *ssock = new SocketDatagrama(SPORT);
	ssock->setBroadcast();
	
	Time musPoint = { 0, 0 };
	int playing = 0;
	
	ConcurrentList<int> machines;
	
	pthread_t sendThread, tableThread, receiveThread;
	sem_t mutexDif, mutexTbl;
	
	sem_init(&mutexDif, 0, 1);
	sem_init(&mutexTbl, 0, 0);
	
	sendThreadData std = { ssock, &playing, &musPoint, &mutexDif, &mutexTbl };
	tableThreadData ttd = { &machines, &playing, &mutexDif, &mutexTbl };
	receiveThreadData rtd = { ssock, &machines, &musPoint, &mutexTbl };
	
	pthread_create(&sendThread, NULL, send, &std);
	pthread_create(&tableThread, NULL, table, &ttd);
	pthread_create(&receiveThread, NULL, receive, &rtd);
	
	pthread_join(sendThread, NULL);
	pthread_join(tableThread, NULL);
	pthread_join(receiveThread, NULL);
	
	delete ssock;
	
	return 0;
}
