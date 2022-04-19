#include "../includes/environment.h"
#include "../includes/process.h"
#include "../includes/module.h"
#include "../includes/shm.h"

void clockMode(int sw,int change){//clock Mode
	static int edit_mode=0,min=0,plus=0,temp_plus=0;
	int fnd=0,led=LED1;
	
	//for write
	outputBuffer->Use[FND]=1;
	outputBuffer->Use[LED]=1;
	outputBuffer->Use[LCD]=0;
	outputBuffer->Use[DOT]=0;
	//actual device time update
	time_t t;
	time(&t);
	struct tm* t_info=localtime(&t);
	int devSec=t_info->tm_sec;
	int devMin=t_info->tm_hour*60+t_info->tm_min;
	//update value and radix
	if(change==1){
		temp_plus=plus;
		edit_mode=0;
	}
	if(edit_mode==1){
		if(sw==1){
			edit_mode=0;
			plus=temp_plus;
			led=LED1;
		}
		else{
			if(sw==2){
				plus=0;
				temp_plus=0;
			}
			else if(sw==3){
				temp_plus+=60;
			}
			else if(sw==4){
				temp_plus+=1;
			}
			if((devSec%2)!=0)
				led=LED3;
			else
				led=LED4;
			if(temp_plus>=24*60)
				temp_plus-=24*60;
		}
	}
	else{//not edit mode
		if(sw==1){
			edit_mode=1;
			min=devMin;
			led=LED3|LED4;
		}
		else
			led=LED1;
	}
	int temp=temp_plus;
	if(edit_mode==1)
		temp+=min;
	else
		temp+=devMin;
	int phour=(temp/60)%24;
	int pmin=temp%60;
	fnd=phour*100+pmin;
	//update output Buffer
	outputBuffer->fndBuffer=fnd;
	outputBuffer->ledBuffer=led;
}
