#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    int i = 1;

    while(i<argc){
        if(fork()==0){
            if(execlp(argv[i],argv[i],NULL)<0)
                perror("excv");
            _exit(1);
        }
        i++;   
    }

    int status;
    for (int count = 1; count < argc; count++){
        int finished_pid = wait(&status);
    }
        

    printf("done\n");
    
    return 0;
}