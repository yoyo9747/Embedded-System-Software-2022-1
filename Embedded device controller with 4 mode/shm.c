#include "./includes/environment.h"
#include "./includes/process.h"
#include "./includes/module.h"
#include "./includes/shm.h"

int Shmget(key_t key, void **buf, size_t buffer_size){//shared memory setting
	int shmID=shmget(key,buffer_size,IPC_CREAT);
	if(shmID==-1)
		perror("shmget error");
	*buf=shmat(shmID,0,0);
	if(*buf==(void *)-1)
		perror("shmat error");
	return shmID;
}
void Semget(void){//semaphore setting
	semID=semget(SHM_KEY_SEMA,4,IPC_CREAT);
	if(semID==-1)
		perror("semget error");
	union semun op;
	op.val=0;

	int i;
	for(i=0;i<4;i++){
		if(semctl(semID,i,SETVAL,op)==-1)
			perror("semctl error");
		p[i].sem_num=i;
		v[i].sem_num=i;
		p[i].sem_flg=SEM_UNDO;
		v[i].sem_flg=SEM_UNDO;
		p[i].sem_op=-1;
		v[i].sem_op=1;
	}
}
