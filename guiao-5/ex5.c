#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char *argv[]){

    /**
     * @brief pipe 0
     * usado para leitura do cut e escrita do grep
     */
    int pipe_fd0[2];
    if (pipe(pipe_fd0)<0){
        perror("pipe0");
        return -1;
    }


    if(!fork()){

        close(pipe_fd0[0]);

    
        dup2(pipe_fd0[1],1);
        close(pipe_fd0[1]);
    
        execlp("grep","grep","-v","^#","/etc/passwd",NULL);
    }

    close(pipe_fd0[1]);

    /**
     * @brief pipe 1
     * usado para a escrita do cut e leitura do uniq
     */
    int pipe_fd1[2];
    if (pipe(pipe_fd1)<0){
        perror("pipe1");
        return -1;
    }

    
    if(!fork()){
        dup2(pipe_fd1[1],1);
        close(pipe_fd1[1]);

        dup2(pipe_fd0[0],0);
        close(pipe_fd0[0]);

        execlp("cut","cut","-f7","-d:",NULL);
        _exit(0);
    }

    close(pipe_fd0[0]);
    close(pipe_fd1[1]);



    /**
     * @brief pipe 2
     * usado para a escrita do uniq e leitura do wc
     */
    int pipe_fd2[2];
    if (pipe(pipe_fd2)<0){
        perror("pipe2");
        return -1;
    }

    if(!fork()){
        dup2(pipe_fd2[1],1);
        close(pipe_fd2[1]);

        dup2(pipe_fd1[0],0);
        close(pipe_fd1[0]);

        execlp("uniq","uniq",NULL);
        _exit(0);
    }

    close(pipe_fd1[0]);
    close(pipe_fd2[1]);



    if(!fork()){

        dup2(pipe_fd2[0],0);
        close(pipe_fd2[0]);

        execlp("wc","wc","-l",NULL);
        _exit(0);
    }

    close(pipe_fd2[0]);


    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);    
    
    return 0;
}