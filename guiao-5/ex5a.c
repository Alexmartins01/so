#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){

    int input=open(argv[1],O_RDONLY);
    int output=open(argv[2],O_WRONLY);
    

    int pipe_fd[2];
    if (pipe(pipe_fd)<0){
        perror("pipe0");
        return -1;
    }

    if(!fork()){

        dup2(pipe_fd[0],input);
        close(pipe_fd[0]);

    
        dup2(pipe_fd[1],1);
        close(pipe_fd[1]);
    
        execlp("cat","cat",NULL);
        

        _exit(0);
    }

    wait(NULL);

    int i=1;


    while(i<5-1){

        dup2(pipe_fd[0],0);
        close(pipe_fd[0]);


        if (pipe(pipe_fd)<0){
            perror("pipe");
            return -1;
        }
        
        

        if(!fork()){
            dup2(pipe_fd[1],1);
            close(pipe_fd[1]);

            


            execlp("cat","cat",NULL);

            _exit(0);
        }

        
        wait(NULL);
        

        i++;
        
    }

    if(!fork()){

        dup2(pipe_fd[0],0);
        close(pipe_fd[0]);

    
        dup2(pipe_fd[1],output);
        close(pipe_fd[1]);
    
        execlp("cat","cat",NULL);


        _exit(0);
    }

    wait(NULL);
    return 0;
}