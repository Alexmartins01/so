#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

    int ifd = open("/etc/passwd",O_RDONLY);
    int ofd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0640);
    int efd = open("erros.txt", O_CREAT | O_TRUNC | O_RDWR, 0640);

    int o_stdin_fd = dup(1);

    dup2(ifd,0);
    close(ifd);
    
    dup2(ofd,1);
    close(ofd);

    dup2(efd,2);
    close(efd);

    if(!fork()){
        write(1,"terminei",8);
        _exit(0);
    }


    return 0;
}