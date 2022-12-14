#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

//isto é o 2

int main(int argc, char *argv[]){
    int pipe_fd[2];
    if (pipe(pipe_fd)<0){
        perror("pipe");
        return -1;
    }

    

    if(!fork()){
        close(pipe_fd[1]);

        int read_bytes;
        char buf[4];

        while((read_bytes=read(pipe_fd[0],buf,4))>0){
            printf("read some data..\n");
            write(1,buf,read_bytes);
        }
        _exit(0);
    }
    
    close(pipe_fd[0]);

    printf("sending...\n");

    write(pipe_fd[1],"data",4);

    close(pipe_fd[1]);

    wait(NULL);
    
    return 0;
}