#include "../includes/environment.h"
#include "../includes/process.h"
#include "../includes/module.h"
#include "../includes/shm.h"

void counterMode(int sw,int change){
	static int value=0,radix=10;
	int fnd=0,led=LED1,print;
	char str[5];
	str[4]='\0';
	//for write
	outputBuffer->Use[FND]=1;
	outputBuffer->Use[LED]=1;
	outputBuffer->Use[LCD]=0;
	outputBuffer->Use[DOT]=0;
	//update value and radix
	if(change){
		value=0;
		radix=10;
		led=LED2;
	}
	else if(sw==1){
		radix=change_radix(radix);
	}
	else{
		value+=update_value(sw,radix);
	}
	//get value by radix
	print=value%(radix*radix*radix);
	if(radix==10){
		sprintf(str,"%04d\n",print);
		led=LED2;
	}
	else if(radix==8){
		sprintf(str,"%04o\n",print);
		led=LED3;
	}
	else if(radix==4){
		str[0]=((print>>6)&0b11)+'0';
		str[1]=((print>>4)&0b11)+'0';
		str[2]=((print>>2)&0b11)+'0';
		str[3]=((print>>0)&0b11)+'0';
		led=LED4;
	}
	else if(radix==2){
		str[0]=((print>>3)&1)+'0';
		str[1]=((print>>2)&1)+'0';
		str[2]=((print>>1)&1)+'0';
		str[3]=((print>>0)&1)+'0';
		led=LED1;
	}
	fnd=atoi(str);
	printf("COUNTER:%d\n",fnd);
	//update output buffer
	outputBuffer->fndBuffer=fnd;
	outputBuffer->ledBuffer=led;
}
int update_value(int sw,int radix){
	if(sw==4)
		return 1;
	else if(sw==3)
		return radix;
	else if(sw==2) {
		return radix*radix;
	}
	else
		return 0;
}
int change_radix(int radix){
	if(radix==10)
		return 8;
	else if(radix==8)
		return 4;
	else if(radix==4)
		return 2;
	else
		return 10;
}
