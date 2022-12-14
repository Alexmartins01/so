#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

int main(){
    int pid,status,finished_pid;
    int i=0;

    while(i<10){
        pid=fork();
        if(pid==0){
            printf("pid: %d\n", getpid());
            printf("ppid: %d\n", getppid());
            _exit(i);
        }

        finished_pid = wait(&status);

        printf("child pid finished: %d;\n",finished_pid);
        i++;
    }

    return 0;
}