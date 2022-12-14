#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){


    //if(execl("/bin/ls","/bin/ls","-l",NULL)<0)
    //    perror("excl");

    //if(execlp("ls","ls","-l",NULL)<0)
    //    perror("excl");

    /*char *exec_args[] = {
        "/bin/ls",
        "-l",
        NULL,
    };

    if(execv("/bin/ls",exec_args)<0)
        perror("excl");*/

    sleep(10);

    if(execlp("sleep","sleep","10",NULL)<0)
        perror("excl");

    // quando executamos o sleep o pid fica o do programa original
    return 0;
}

/*
int execl(const char *path, const char *arg0, ..., NULL);
int execlp(const char *file, const char *arg0, ..., NULL);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
*/