#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int i = 1;

    //execvp existe

    if(fork()==0){
        if(execvp(argv[1],&argv[1])<0)
            _exit(0);
        _exit(1);
    }
    
    int status;
    int finished_pid = wait(&status);

    if(WIFEXITED(status)){
        if(WEXITSTATUS(status)==0){
                printf("ok\n");
            }
    }
    else printf("noo\n");
        

    
    return 0;
}