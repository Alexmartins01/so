#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>


// ctrl + D para dar eof


int main(int argc, char *argv[]){
    int pipe_fd[2];
    if (pipe(pipe_fd)<0){
        perror("pipe");
        return -1;
    }

    

    if(!fork()){
        close(pipe_fd[1]);

        dup2(pipe_fd[0],0);
        close(pipe_fd[0]);

        execlp("wc","wc",NULL);
        _exit(0);
    }
    
    close(pipe_fd[0]);

    printf("reading...\n");

    int bytes_read;

    char buf[16];

    while(bytes_read=read(0,&buf,16)){
        write(pipe_fd[1],buf,16);
    }

    close(pipe_fd[1]);

    wait(NULL);
    
    return 0;
}