#include "../includes/environment.h"
#include "../includes/process.h"
#include "../includes/module.h"
#include "../includes/shm.h"
#include "../includes/device.h"

void writeDev(int fd,void *data,size_t size){
	if(fd==-1){//for led (mmap)
		*led_addr=*((int *)data);
	}
	else{//for other device
		write(fd,data,size);
	}
}
void writeFnd(int fd,int data){//fnd write
	unsigned char str[4];
	int i;
	for(i=3;i>=0;i--){
		str[i]=data%10;
		data/=10;
	}
	writeDev(fd,str,4);
}
void writeDot(int fd){//dot write
	int i,j;
	unsigned char copy[10];
	for(i=0;i<10;i++)
		copy[i]=0;
	for(i=0;i<10;i++)
		for(j=0;j<7;j++)
			if(outputBuffer->dotBuffer[i*7+j])
				copy[i]+=1<<(6-j);
	writeDev(fd,copy,10);
}
