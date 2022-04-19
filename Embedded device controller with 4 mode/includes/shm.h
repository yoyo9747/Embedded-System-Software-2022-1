#ifndef __SHM_H__
#define __SHM_H__

#include <sys/sem.h>

#define SHM_KEY_IN (key_t) 0x10 
#define SHM_KEY_OUT (key_t) 0x20 
#define SHM_KEY_SEMA (key_t) 0x20
#define FLAG_SWITCH 9
#define FLAG_EVENT 10
#define KEY_EVENT 11

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};//semaphore

typedef struct msgbuf1{
	char msg[12];
}inmsg_buf;

typedef struct msgbuf2{
	int Use[4];//FND, LED, LCD, DOT
	int fndBuffer;
	int ledBuffer;
	char lcdBuffer[32];
	bool dotBuffer[70];
	char dotChar;
}outmsg_buf;
//outmsg_buf;
inmsg_buf *inputBuffer;
outmsg_buf *outputBuffer;
struct sembuf p[4],v[4];
int semID,shmID_IN,shmID_OUT;
int Shmget(key_t key, void **buf, size_t buffer_size);
void Semget();
#endif
