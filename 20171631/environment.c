#include "./includes/environment.h"
#include "./includes/process.h"
#include "./includes/module.h"
#include "./includes/shm.h"

void construct_environment(struct environment **env){
	//IPC set
	shmID_IN=Shmget(SHM_KEY_IN, (void **)&inputBuffer, sizeof(inmsg_buf));
	shmID_OUT=Shmget(SHM_KEY_OUT, (void **)&outputBuffer, sizeof(outmsg_buf));
	Semget();	
	//environment set, open fd
	struct environment *new=calloc(1,sizeof(struct environment));
	new->fd[SWT]=open("/dev/fpga_push_switch",O_RDWR|O_NONBLOCK);
	new->fd[KEY]=open("/dev/input/event0",O_RDWR|O_NONBLOCK);
	new->fd[FND]=open("/dev/fpga_fnd",O_RDWR);
	new->fd[LED]=open("/dev/mem",O_RDWR);
	new->fd[LCD]=open("/dev/fpga_text_lcd",O_RDWR);
	new->fd[DOT]=open("/dev/fpga_dot",O_RDWR);
	new->mode=1;
	//pthread flag set for multithreading
	pthread_attr_init(&(new->attr));
	pthread_attr_setdetachstate(&(new->attr),PTHREAD_CREATE_DETACHED);
	//led address set for mmap	
	unsigned long *fpga_addr = (unsigned long *)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,new->fd[LED],FPGA_BASE_ADDRESS);
	led_addr=(unsigned char *)((void*)fpga_addr + LED_ADDR);
	int i;	
	//output Buffer initialize
	outputBuffer->fndBuffer=0;
	outputBuffer->ledBuffer=0;
	for(i=0;i<32;i++)
		outputBuffer->lcdBuffer[i]=' ';
	for(i=0;i<70;i++)
		outputBuffer->dotBuffer[i]=false;
	outputBuffer->dotChar='\0';
	*env=new;
}

void destruct_environment(struct environment ** env){
	//destroy environment
	munmap((void*)led_addr,4096);
	int in=(*env)->pid_IN,out=(*env)->pid_OUT;
	if(kill(in,SIGKILL)!=-1){//kill input process
		waitpid(in,NULL,0);
	}
	else
		perror("kill error");
	if(kill(out,SIGKILL)!=-1){//kill output process
		waitpid(out,NULL,0);
	}
	else
		perror("kill error");
	int i;
	for(i=0;i<6;i++)
		close((*env)->fd[i]);//close fd
	//free IPC structure
	semctl(semID,0,IPC_RMID,0);
	shmctl(shmID_IN,IPC_RMID,0);
	shmctl(shmID_OUT,IPC_RMID,0);
	free(*env);
}
