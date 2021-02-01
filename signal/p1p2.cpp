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

void handler1(int signum){
    cout << "process" << *x <<  " called me(" << getpid() <<  ")\n";
    signal(SIGINT,SIG_DFL);
}

void handler2(int signum){
    cout << "process" << *y <<  " called me(" << getpid() <<  ")\n";
    signal(SIGINT,SIG_DFL);
}

int main(){
    key_t key1 = ftok("shmfile",65); 
	int shmid1 = shmget(key1,1024,0666|IPC_CREAT); 
	x = (int*) shmat(shmid1,(void*)0,0); 
    key_t key2 = ftok("shmfile",65); 
	int shmid2 = shmget(key2,1024,0666|IPC_CREAT); 
	y = (int*) shmat(shmid2,(void*)0,0); 
    int i = fork();
    if(i==0){
        cout << "I am process " << getpid() << "\n";
        *x = getpid();
        signal(SIGINT,handler1);
        sleep(1);
        kill(getppid(),SIGINT);
        cout << "OK";
    }
    else{
        cout << "I am process " << getpid() << "\n";
        signal(SIGINT,handler2);
        *y = getpid();
        sleep(1);
        kill(*x,SIGINT);
        cout << "HI";
    }
    wait(NULL);
    return 0;
}