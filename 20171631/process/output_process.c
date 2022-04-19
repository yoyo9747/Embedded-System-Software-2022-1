#include "../includes/environment.h"
#include "../includes/process.h"
#include "../includes/module.h"
#include "../includes/shm.h"
#include "../includes/device.h"

char dot_EMPTY[]={0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};//empty dot matrix

char dot_1[]={//1 dot matrix
    (0x0<<4) + 0xC,
    (0x1<<4) + 0xC,
    (0x0<<4) + 0xC,
    (0x0<<4) + 0xC,
    (0x0<<4) + 0xC,
    (0x0<<4) + 0xC,
    (0x0<<4) + 0xC,
    (0x0<<4) + 0xC,
    (0x3<<4) + 0xF,
    (0x3<<4) + 0xF
};
char dot_A[]={//A dot matrix
    (0x1<<4) + 0xC,
    (0x3<<4) + 0x6,
    (0x6<<4) + 0x3,
    (0x6<<4) + 0x3,
    (0x6<<4) + 0x3,
    (0x7<<4) + 0xF,
    (0x7<<4) + 0xF,
    (0x6<<4) + 0x3,
    (0x6<<4) + 0x3,
    (0x6<<4) + 0x3
};

void output_process(struct environment*env){
	int running=1;
	int prevUse[4],i;
	for(i=0;i<4;i++) prevUse[i]=0;
	writeFnd(env->fd[FND],outputBuffer->fndBuffer);//fnd reset
	writeDev(-1,&(outputBuffer->ledBuffer),0);//led reset
	writeDev(env->fd[LCD],outputBuffer->lcdBuffer,32);//lcd reset
	writeDev(env->fd[DOT],dot_EMPTY,10);//dot reset
	while(running){
		semop(semID,&p[2],1);//main->output(wait main process)
		//device print
		if(outputBuffer->Use[FND]==1){
			writeFnd(env->fd[FND],outputBuffer->fndBuffer);
		}
		else if(prevUse[FND]==1){
			outputBuffer->fndBuffer=0;
			writeFnd(env->fd[FND],outputBuffer->fndBuffer);
		}
		if(outputBuffer->Use[LED]==1){
			writeDev(-1,&(outputBuffer->ledBuffer),0);
		}
		else if(prevUse[LED]==1){
			outputBuffer->ledBuffer=0;
			writeDev(-1,&(outputBuffer->ledBuffer),0);
		}
		if(outputBuffer->Use[LCD]==1){
			writeDev(env->fd[LCD],outputBuffer->lcdBuffer,32);
		}
		else if(prevUse[LCD]==1){
			for(i=0;i<32;i++)
				outputBuffer->lcdBuffer[i]=' ';
			writeDev(env->fd[LCD],outputBuffer->lcdBuffer,32);
		}
		if(outputBuffer->Use[DOT]==1){
				if(outputBuffer->dotChar=='A')
					writeDev(env->fd[DOT],dot_A,10);
				else if(outputBuffer->dotChar=='1')
					writeDev(env->fd[DOT],dot_1,10);
				else if(outputBuffer->dotChar=='\0')
					writeDot(env->fd[DOT]);
		}
		else if(prevUse[DOT]==1){
			writeDev(env->fd[DOT],dot_EMPTY,sizeof(dot_EMPTY));
			outputBuffer->dotChar='\0';
		}
		for(i=0;i<4;i++)
			prevUse[i]=outputBuffer->Use[i];
		semop(semID,&v[3],1);//output->main(make main  proceed)
	}
}
