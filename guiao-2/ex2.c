#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

int main(){
    int pid;

    pid = fork();

    if(pid==0){
        printf("pid: %d\n", getpid());
        printf("ppid: %d\n", getppid());
        _exit(0);
    } else{
        printf("child pid: %d\n",pid);
        printf("pid: %d\n", getpid());
        printf("ppid: %d\n", getppid());
        int status;
        int finished_pid = wait(&status);

        if(WIFEXITED(status)){
            printf("child pid finished: %d; status code: %d;\n",finished_pid,WEXITSTATUS(status));
        }
        else printf("error: %d;\n",WIFEXITED(status));
    }
    

    return 0;
}