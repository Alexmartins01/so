#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>



int main(int argc,char* argv[]){
    int n_files = argc-2;

    int i=0;
    int pid;

    while(n_files>i){
        if(!(pid=fork())){
            execlp("grep","grep",argv[1],argv[2],NULL);
            _exit(0);
        }
        i++;
    }
    int status;
    while(i>0){
        i--;
        wait(&status);
        if(WIFEXITED(status)){
        if(WEXITSTATUS(status)==0){
                kill(pid,SIGKILL);
            }
    }
    }
}