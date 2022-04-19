#include "../includes/environment.h"
#include "../includes/process.h"
#include "../includes/module.h"
#include "../includes/shm.h"

const char pad[][3]={//for switch board input
    "", 
    ".QZ", "ABC", "DEF",
    "GHI", "JKL", "MNO",
    "PRS", "TUV", "WXY"
};

void texteditorMode(int sw[10],int change){
	static char text[32]={'\0'};
	static int mode=1;//initiallized alphabet(1-alphbet, 0-number)
	static int count=0;
	static int prevKey=-1;
	static int prevKeycount=0;
	static int offset=0;
	//for print
	outputBuffer->Use[FND]=1;
	outputBuffer->Use[LED]=0;
	outputBuffer->Use[LCD]=1;
	outputBuffer->Use[DOT]=1;
	int i;
	if(change==1){
		memset(text, ' ',32);
		mode=1;
		count=0;
		prevKey=-1;
		prevKeycount=0;
		offset=0;
	}

	if(sw[2]&&sw[3]){//initialize lcd
		memset(text, ' ',32);
		count+=1;
		prevKey=-1;
		prevKeycount=0;
		offset=0;
	}
	else if(sw[5]&&sw[6]){//mode change
		mode=(mode+1)%2;
		count+=1;
		prevKey=-1;
		prevKeycount=0;
	}
	else if(sw[8]&&sw[9]){//push blank
		count+=1;
		prevKey=-1;
		prevKeycount=0;
		write_text(offset,' ',text);
		offset+=1;
		if(offset==8)
			offset-=1;
	}
	else if(mode==1){//alphabet mode
		for(i=1;i<=9;i++){
			if(sw[i]==1){
				if(i==prevKey){
					prevKeycount=(prevKeycount+1)%3;
					prevKey=i;
					if(offset!=7)
						offset-=1;
					write_text(offset,pad[i][prevKeycount],text);
					offset+=1;
					if(offset==8)
						offset-=1;
				}
				else{
					prevKey=i;
					prevKeycount=0;
					write_text(offset,pad[i][prevKeycount],text);
					offset+=1;
					if(offset==8)
						offset-=1;
				}
				count+=1;
				break;
			}
		}
	}
	else{//number mode
		for(i=1;i<=9;i++){
			if(sw[i]==1){
				count+=1;
				prevKey=-1;
				prevKeycount=0;
				write_text(offset,'0'+sw[i],text);
				offset+=1;
				if(offset==8)
					offset-=1;
				break;
			}
		}
	}
	count %=10000;
//output Buffer setting
	outputBuffer->fndBuffer=count;
	if(mode==1)
		outputBuffer->dotChar='A';
	else
		outputBuffer->dotChar='1';
	memcpy(outputBuffer->lcdBuffer,text,32);
}
void write_text(int offset,char c,char *text){
	if(offset==7){
		int i;
		for(i=1;i<=7;i++)
			text[i-1]=text[i];
	}
		text[offset]=c;
}
