#include "../includes/environment.h"
#include "../includes/process.h"
#include "../includes/shm.h"
#include "../includes/module.h"

void *main_process(void * temp){
	char *input=(char *)temp;
	int mode=input[MODE];
	int change=input[CHANGE];
	int i;
	int sw=0,stext[10];
	switch(mode){
		case 1://CLOCK
			for(i=0;i<4;i++){
				if(input[i]==1){
					sw=i+1;
					break;
				}
				i+=sw;
			}
			clockMode(sw,change);
			break;
		case 2://COUNTER
			for(i=0;i<4;i++){
				if(input[i]==1){
					sw=i+1;
					break;
				}
			}
			counterMode(sw,change);
			break;
		case 3://TEXT_EDITOR
			for(i=1;i<=9;i++)
				stext[i]=input[i-1];
			texteditorMode(stext,change);
			break;
		case 4://DRAW_BOARD
			for(i=1;i<=9;i++)
				stext[i]=input[i-1];
			drawboardMode(stext,change);
			break;
		default:
			break;
	}
	semop(semID,&v[2],1);//main->output(make output proceed)
	semop(semID,&p[3],1);//output->main(wait output process)
	semop(semID,&v[1],1);//main->input(make input proceed)
	return NULL;
}
