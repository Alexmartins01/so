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

    int bytes_read;
    char buf[16];
    while(bytes_read = read(fifo_fd,&buf,16)){
        write(1,&buf,bytes_read);
    }


    return 0;
}