#include "./includes/environment.h"
#include "./includes/process.h"
#include "./includes/module.h"
#include "./includes/shm.h"

int main(void){
	struct environment *env;
	construct_environment(&env);
	if((env->pid_IN=fork())==0){//input fork
		input_process(env);
		exit(0);
	}
	else if(env->pid_IN<0)
		perror("fork error");
	if((env->pid_OUT=fork())==0){//output fork
		output_process(env);
		exit(0);
	}
	else if(env->pid_OUT<0)
		perror("fork error");
	int running=1,i;
	char temp[15];
	while(running){
		semop(semID,&p[0],1);//main->input(wait main process)
		for(i=0;i<12;i++){
			temp[i]=inputBuffer->msg[i];
			inputBuffer->msg[i]=0;//reset input buffer
		}
		temp[CHANGE]=0;
		if(temp[FLAG_EVENT]==1){
			if(temp[KEY_EVENT]==BACK){//BACK
				running=0;
			}
			else if(temp[KEY_EVENT]==VOL_M){//VOL-
				env->mode=(env->mode+3)%4;
				if(env->mode==0) env->mode=4;//mode change
				temp[CHANGE]=1;
			}
			else if(temp[KEY_EVENT]==VOL_P){//VOL+
				env->mode=(env->mode+1)%4;
				if(env->mode==0) env->mode=4;	//mode change
				temp[CHANGE]=1;
			}

		}
		temp[MODE]=env->mode;
		pthread_create(&(env->main_thread),&(env->attr),main_process,temp);
	}
	destruct_environment(&env);
	return 0;
}
