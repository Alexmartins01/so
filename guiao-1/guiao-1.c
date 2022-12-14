#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>


int main(int argc, char * argv[]){
    int file1_fd = open(argv[1], O_RDONLY);

    if(file1_fd < 0){
        perror("open file 1");
        return 1;
    }

    int file2_fd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0640);

    if(file2_fd < 0){
        perror("open file 2");
        return 1;
    }


    char buf[1024];

    int bytes_read = 0;

    while((bytes_read = read(file1_fd,&buf,1024))>0){
        write(file2_fd, &buf, bytes_read);
    }
    
    return 0;
}