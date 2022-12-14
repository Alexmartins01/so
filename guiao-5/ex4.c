#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char *argv[]){
    int pipe_fd[2];

    if (pipe(pipe_fd)<0){
        perror("pipe");
        return -1;
    }

    

    if(!fork()){
        close(pipe_fd[0]);

    
        dup2(pipe_fd[1],1);
        close(pipe_fd[1]);
    
        execlp("ls","ls","/etc",NULL);
    }

    close(pipe_fd[1]);

    if(!fork()){

        dup2(pipe_fd[0],0);
        close(pipe_fd[0]);

        execlp("wc","wc","-l",NULL);
        _exit(0);
    }

    close(pipe_fd[0]);
    wait(NULL);
    
    return 0;
}