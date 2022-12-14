#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[]){
    if(argc<=1){
        return 0;
    }
    
    int l = atoi(argv[2]);
    int c = atoi(argv[3]);

    int m[l][c];

    int pid;
    size_t lsize = c * sizeof(int);
    char line[lsize];
    int bytes_read;
    int seek_pointer=0;

    // cria matriz e escreve no ficheiro

    int file1_fd = open("matrix.bin", O_CREAT | O_TRUNC | O_RDWR, 0640);
    if(file1_fd < 0){
        perror("create file");
        return 1;
    }

    int x=0;

    for (int i = 0; i < l; i++){
        for (int j = 0; j < c; j++){
            m[i][j]=rand()%100;
        }
    }


    for (int i = 0; i < l; i++){
            write(file1_fd, m[i], sizeof(int)*c);
    }

    
    // procura de aux no ficheiro

    lseek(file1_fd,SEEK_SET,0);

    for (int i = 0; i < l; i++){
        while((bytes_read = read(file1_fd,&line,lsize))>0){
            seek_pointer++;
            if(seek_pointer%4==0 && strncmp(&line[seek_pointer],argv[1],sizeof(int)) == 0) printf("%d",seek_pointer/4);
        }
    }

    close(file1_fd);
    /*
    int status;

    for (int count = 0; count < l; count++){
            int finished_pid = wait(&status);

        if(WIFEXITED(status)){
            if(WEXITSTATUS(status)!=0){
                printf("Linha %d\n",WEXITSTATUS(status));
            }
        }
        else printf("error: %d;\n",WIFEXITED(status));
    }*/

    
    return 0;
}