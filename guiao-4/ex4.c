#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

// sem input file nao funciona
/**
 * @brief Executa comando dados, pode rederecionar stdin e stdout
 * 
 * @param argc 
 * @param argv flag -i input; flag -o output; comando com flags
 * @return int 
 */
int main(int argc, char *argv[]){

    int ifd,ofd,aux=1,iflags=0,oflags=0;

    if(argc>4){
        if(!strcmp(argv[1],"-i")) iflags = 1;
        else  if(!strcmp(argv[3],"-i")) iflags = 3;

        if(!strcmp(argv[1],"-o")) oflags = 1;
        else  if(!strcmp(argv[3],"-o")) oflags = 3;
    }

    

    switch (iflags)
    {
    case 1:
        ifd = open(argv[2],O_RDONLY);
        aux = 3;

        dup2(ifd,0);
        close(ifd);
        
        break;

    case 3:
        ifd = open(argv[4],O_RDONLY);
        aux = 5;

        dup2(ifd,0);
        close(ifd);

        break; 
    
    default:
        break;
    }

    switch (oflags)
    {
    case 1:
        ofd = open(argv[2],O_CREAT | O_TRUNC | O_RDWR, 0640);

        dup2(ofd,1);
        close(ofd);

        if(aux<3) aux = 3;
        break;

    case 3:
        ofd = open(argv[4],O_CREAT | O_TRUNC | O_RDWR, 0640);
        aux = 5;

        dup2(ofd,1);
        close(ofd);
        
        break; 
    
    default:
        break;
    }
    
    int efd = open("erros.txt", O_CREAT | O_TRUNC | O_RDWR, 0640);

    dup2(efd,2);
    close(efd);

    if(fork()==0){
        if(execvp(argv[aux],&argv[aux])<0)
            _exit(0);
        _exit(1);
    }

    int status;
    int finished_pid = wait(&status);

    if(WIFEXITED(status))
        if(WEXITSTATUS(status)!=0) perror("status");

    


    return 0;
}