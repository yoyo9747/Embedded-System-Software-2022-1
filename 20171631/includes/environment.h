#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/mman.h>

struct environment{
	pid_t pid_IN,pid_OUT;
	int fd[6]; 
	int mode;
	pthread_t main_thread;
	pthread_attr_t attr;
};

#define FPGA_BASE_ADDRESS 0x08000000//fpga_base address
#define LED_ADDR 0x16
#define FND 0
#define LED 1
#define LCD 2
#define DOT 3
#define SWT 4
#define KEY 5
#define LED1 1<<7
#define LED2 1<<6
#define LED3 1<<5
#define LED4 1<<4
#define LED5 1<<3
#define LED6 1<<2
#define LED7 1<<1
#define LED8 1<<0

unsigned char* led_addr;

void construct_environment(struct environment **env);
void destruct_environment(struct environment **env);
#endif
