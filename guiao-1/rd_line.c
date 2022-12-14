#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>

ssize_t readln(int fd, char *line, size_t size){
    int i =0, bytes_read=0;
    while((bytes_read = read(fd,line+i,1))>0 && i<size){
        if(line[i]=='\n') return i+1;

        i++;
    }

    
    return i;
} // funcional pelo sor 

char readln_buf[4096];

int readln_buf_end;

int readln_buf_pos;

int readc(int fd, char *c){ // fazia o que o while fazia na readln

    // verifica se tenho mais bytes para ler

    // se tiver, retorna escreve no endereço (c) e atualiza o estado global (pos atual)

    // se nao tiver vai ler a disco e retorna 1

    // usa-se isto na readln2 com o buffer global
    return read(fd,c,1);
}

ssize_t readln2(int fd, char *line, size_t size){
    // Ler para um buffer de certa quantidade e fazer lseek para tras, para o sitio do \n
    // Com lseek ainda tem varias chamadas ao sistema mas já é melhor
    int i=0, bytes_read=0;
    bytes_read = read(fd,line,size);
    while(line[i]!='\n' && i<size) i++;

    if(line[i]!='\n'){
        strcpy(line,readln_buf);

        return size;
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


    char buf[1024];

    int bytes_read = 0;

    while((bytes_read = readln2(file1_fd,&buf,1024))>0){
        write(file2_fd, "0 ", 2);
        write(file2_fd, &buf, bytes_read);
    }
    
    return 0;
}