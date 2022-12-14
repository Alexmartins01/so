#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){


    if(fork()==0){
        if(execl("/bin/ls","/bin/ls","-l",NULL)<0)
            perror("ls");
        _exit(1);
    }
    else {
        int status;
        int finished_pid = wait(&status);
    }

    printf("done\n");
    
    return 0;
}

/*
int execl(const char *path, const char *arg0, ..., NULL);
int execlp(const char *file, const char *arg0, ..., NULL);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
*/