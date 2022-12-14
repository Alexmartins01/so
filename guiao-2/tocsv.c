#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

    int l = atoi(argv[1]);
    int c = atoi(argv[2]);

    int file1_fd = open("matrix.bin", O_RDONLY, 0640);
    if(file1_fd < 0){
        perror("create file");
        return 1;
    }

    int file2_fd = open("matrix.csv", O_CREAT | O_TRUNC | O_WRONLY, 0640);
    if(file2_fd < 0){
        perror("create file");
        return 1;
    }

    
    size_t lsize = c * sizeof(int);
    char line[lsize];
    int bytes_read;

    for (int i = 0; i < l; i++){
        while((bytes_read = read(file1_fd,&line,lsize))>0){
            write(file2_fd,&line,bytes_read);
        }
    }
}