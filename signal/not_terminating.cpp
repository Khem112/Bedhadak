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
using namespace std;
int cnt=0;

void handler(int signum){
    if(++cnt==5) signal(SIGINT,SIG_DFL);
    else cout << "I won't terminate";
}

int main(){
    signal(SIGINT,handler);
    while(1){
        cout << "HI";
        fflush(stdout);
        sleep(1);
    }
    return 0;
}