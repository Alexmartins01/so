#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <string.h>

char readln_buf[4096];

int readln_buf_end; // quantos bytes e necessario dar l_seek para tras

int readln_buf_pos; // posicao atual

ssize_t readln2(int fd, char *line, size_t size){
    // Ler para um buffer de certa quantidade e fazer lseek para tras, para o sitio do \n
    // Com lseek ainda tem varias chamadas ao sistema mas já é melhor
    int i=0, bytes_read=0;
    bytes_read = read(fd,line,size);
    while(line[i]!='\n' && i<size) i++;

    if(line[i]!='\n'){
        strcpy(line,readln_buf+readln_buf_pos);
        readln_buf_pos+=size;

        return size;
    }
    else {
        
        readln_buf_end = readln_buf_pos;
    }


    

    // Ler para um buffer global | é preciso numero de bytes lidos e indice atual | quando se tiver
    // lido tudo, voltar a fazer chamada ao sistema para o buffer global

    

    return i;
}

int main(int argc, char * argv[]){
    int file1_fd = open(argv[1], O_RDONLY);
    int file2_fd = 1; // STDOUT_FILENO

    if(file1_fd < 0){
        perror("open file 1");
        return 1;
    }


    char buf[16];

    int bytes_read = 0;

    readln_buf_end = 0, readln_buf_pos = 0;

    while((bytes_read = readln2(file1_fd,&buf,16))>0){
        write(file2_fd, "0 ", 2);
        write(file2_fd, &buf, bytes_read);
    }
    
    return 0;
}