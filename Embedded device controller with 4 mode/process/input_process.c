#include "../includes/environment.h"
#include "../includes/process.h"
#include "../includes/module.h"
#include "../includes/shm.h"

void input_process(struct environment *env){
	int running =1;
	struct input_event ev[64];
	unsigned char swbuff[9];
	int i,flag;
	while (running){
		for(i=0;i<12;i++)
			inputBuffer->msg[i]=0;
		if((read(env->fd[KEY], ev, sizeof(struct input_event))>=sizeof(struct input_event))&&ev[0].value==1){//read key
			inputBuffer->msg[FLAG_EVENT]=1;
			inputBuffer->msg[KEY_EVENT]=ev[0].code;
		}
		else {
			flag=0;
			read(env->fd[SWT], &swbuff,sizeof(swbuff));//read switch
			for(i=0;i<9;i++){
				flag |= swbuff[i];
				inputBuffer->msg[i]=swbuff[i];
			}
			inputBuffer->msg[FLAG_SWITCH]=flag;
		}
		usleep(170000);//sleep for input quality
		semop(semID,&v[0],1);//input->main(make main proceed)
		semop(semID,&p[1],1);//main->input(wait main process))
	}
}
