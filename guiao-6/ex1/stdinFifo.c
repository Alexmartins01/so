#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char * argv[]){
    int fifo_fd=open("fifo",O_WRONLY);
    if(fifo_fd<0){
        perror("open");
        return 1;
    }

    int bytes_read;
    char buf[16];
    while(bytes_read = read(0,&buf,16)){
        write(fifo_fd,&buf,bytes_read);
    }



    return 0;
}