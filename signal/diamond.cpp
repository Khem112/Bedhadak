#include<bits/stdc++.h>
#include <fstream> 
#include<stdio.h> 
#include<unistd.h> 
#include<fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
using namespace std;
int cnt=0;
int *x,*y;

void handler(int signum){
    if(x>0 && signum==SIGUSR1){
        cout << "x++";
        fflush(stdout);
    }
    else  if(y>0){
        cout << "Y++";
    }
}

int main(){
    key_t key1 = ftok("/tmp/var1",65); 
	int shmid1 = shmget(key1,1024,0666|IPC_CREAT); 
	x = (int*) shmat(shmid1,(void*)0,0); 
    key_t key2 = ftok("/tmp/var2",65); 
	int shmid2 = shmget(key2,1024,0666|IPC_CREAT); 
	y = (int*) shmat(shmid2,(void*)0,0); 
    *x=0;
    *y=0;
    int i = fork();
    if(i==0){
        while(1){
        signal(SIGUSR1,handler);
        (*x)++;
        kill(getppid(),SIGUSR2);
        sleep(2);
        }
    }
    else{
        while(1){
       signal(SIGUSR2,handler);
       *y++;
       kill(i,SIGUSR1);
       sleep(2);
        }
    }
    wait(NULL);
    return 0;
}