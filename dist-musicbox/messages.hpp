#include <semaphore.h>

#include "SocketDatagrama.hpp"
#include "PaqueteDatagrama.hpp"
#include "ConcurrentList.hpp"

#define PREFIX "192.168.43."

#define CPORT 6800
#define SPORT 7200

#define GETNUM 1
#define ACK 2

typedef struct {
	int mins;
	int secs;
} Time;

typedef struct {
	int numPc;
	int opcode;
	Time point;
} messageCS;

typedef struct {
//	char ip[17];
	int playing;
	Time point;
} messageSC;

typedef struct {
	SocketDatagrama *ssock;
	int *playing;
	Time *musPoint;
	sem_t *mutexDif;
	sem_t *mutexTbl;
} sendThreadData;

typedef struct {
	ConcurrentList<int> *machines;
	int *playing;
	sem_t *mutexDif;
	sem_t *mutexTbl;
} tableThreadData;

typedef struct {
	SocketDatagrama *ssock;
	ConcurrentList<int> *machines;
	Time *musPoint;
	sem_t *mutexTbl;
} receiveThreadData;
