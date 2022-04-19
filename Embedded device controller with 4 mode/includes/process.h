#ifndef __PROCESS__
#define __PROCESS__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#include <linux/input.h> //struct input_event {int ev[1], value, code;}

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/shm.h>

//for input
#define FLAG_SWITCH 9
#define FLAG_EVENT 10
#define KEY_EVENT 11
#define MODE 12
#define CHANGE 13

void input_process(struct environment *env);
void output_process(struct environment *env);
void *main_process(void* input);

#endif
