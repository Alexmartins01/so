#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int seconds = 0;
void inc_seconds(int signum){
    seconds++;
    alarm(1);
}

void print_seconds(int signum){
    printf("ctrl+c seconds:%d \n",seconds);

}

int main(int argc,char* argv[]){
    printf("pid:%d \n",getpid());
    if(signal(SIGALRM,inc_seconds)==SIG_ERR){
        printf("error\n");
        return 1;
    }

    if(signal(SIGINT,print_seconds)==SIG_ERR){
        printf("error\n");
        return 1;
    }

    alarm(1);
    while(1){
        pause();
    }

    printf("seconds: %d\n",seconds);
    return 0;
}