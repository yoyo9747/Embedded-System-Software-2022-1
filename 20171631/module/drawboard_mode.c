#include "../includes/environment.h"
#include "../includes/process.h"
#include "../includes/module.h"
#include "../includes/shm.h"

void drawboardMode(int sw[10],int change){
	static int X=0,Y=0,cursor=1,count=0;
	static bool pad[70]={false};
	//for write
	outputBuffer->Use[FND]=1;
	outputBuffer->Use[LED]=0;
	outputBuffer->Use[LCD]=0;
	outputBuffer->Use[DOT]=1;
	int i,j;
	if(change==1){
		X=0;
		Y=0;
		cursor=1;
		count=0;
		for(i=0;i<10;i++)
			for(j=0;j<7;j++)
				pad[i*10+j]=false;
	}
	if(sw[1]==1){//dot matrix reset
		X=0;
		Y=0;
		cursor=1;
		count=0;
		for(i=0;i<10;i++)
			for(j=0;j<7;j++)
				pad[i*7+j]=false;
	}
	else if(sw[3]==1){//cursor invisible/visible
		cursor=(cursor+1)%2;
		count+=1;
	}
	else if(sw[7]==1){//only dot matrix reset
		for(i=0;i<10;i++)
			for(j=0;j<7;j++)
				pad[i*7+j]=false;
		count+=1;	
	}
	else if(sw[9]==1){//inverset dot matrix
		for(i=0;i<10;i++)
			for(j=0;j<7;j++)
				pad[i*7+j]=!pad[i*7+j];
		count+=1;	
	}
	//move cursor
	else{
		if(sw[2]==1){
			X-=1;
			if(X==-1)
				X=9;
		count+=1;
		}
		else if(sw[4]==1){
			Y-=1;
			if(Y==-1)
				Y=6;
		count+=1;
		}
		else if(sw[5]==1){
			pad[X*7+Y]=true;
		count+=1;
		}
		else if(sw[6]==1){
			Y+=1;
			if(Y==7)
				Y=0;
		count+=1;
		}
		else if(sw[8]==1){
			X+=1;
			if(X==10)
				X=0;
		count+=1;
		}
	}
	count %=10000;
	//output buffer update
	outputBuffer->fndBuffer=count;
	outputBuffer->dotChar='\0';
	for(i=0;i<10;i++)
		for(j=0;j<7;j++)
			outputBuffer->dotBuffer[i*7+j]=pad[i*7+j];
	if(cursor==1){//blink cursor
		time_t t;
		time(&t);
		struct tm* t_info=localtime(&t);
		int devSec=t_info->tm_sec;
		if(devSec%2==0)
			outputBuffer->dotBuffer[X*7+Y]=false;
		else
			outputBuffer->dotBuffer[X*7+Y]=true;
	}
}
