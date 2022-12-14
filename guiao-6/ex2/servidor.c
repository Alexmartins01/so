#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char * argv[]){
    int fifo_fd=open("fifo",O_RDONLY);
    if(fifo_fd<0){
        perror("open");
        return 1;
    }

    int fifo_fd_write=open("fifo",O_WRONLY);


    int log=open("log.txt",O_CREAT | O_TRUNC |O_RDWR);

    while(1){
        int bytes_read;
        char buf[16];
        while(bytes_read = read(fifo_fd,&buf,16)){
            write(log,&buf,bytes_read);
        }
        write(log,"\n",1);
    }

    close(fifo_fd);

    


    return 0;
}