#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

int main(){
    printf("pid: %d\n", getpid());
    printf("pid: %d\n", getppid());

    sleep(30);

    return 0;
}