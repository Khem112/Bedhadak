#include <time.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/select.h>
#include <sys/un.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <netinet/ether.h>
#include <netinet/udp.h>
#include <semaphore.h>
#include <bits/stdc++.h>
using namespace std;
using namespace std;
int cnt=0;
int *x,*y;

void handler1(int signum){
    key_t key1 = ftok("/tmp/key1",65);
    int shmid1 = shmget(key1,1024,0666|IPC_CREAT);
    int *x = (int *) shmat(shmid1,0,0);
    key_t key2 = ftok("/tmp/key2",65);
    int shmid2 = shmget(key2,1024,0666|IPC_CREAT);
    int *y = (int *) shmat(shmid2,0,0);
    cout << "Value of X = " << *x << " Read by " << getpid() << "\n";
    cout << "Value of Y = " << *y << " Read by " << getpid() << "\n";
    int temp = *y;
    temp++;
    (*y) = temp;
    cout << "Value of Y increased to " << *y << " Read by " << getpid() << "\n";
    kill(getppid(),SIGUSR2);

    sleep(1);    
}

int main(){
    signal(SIGUSR1,handler1);
    mkfifo("tmp/fifo1",0666);
    mkfifo("tmp/fifo2",0666);
    int fd1 = open("tmp/fifo2",O_RDONLY);
    int fd2 = open("tmp/fifo1",O_WRONLY);
    int myId = getpid();
    int sendId;
    write(fd2,&myId,1024);
    close(fd2);
    read(fd1,&sendId,1024);
    close(fd1);
    fflush(stdout);
    sleep(2);
    kill(getppid(),SIGUSR2);
    sleep(10);
    return 0;
}