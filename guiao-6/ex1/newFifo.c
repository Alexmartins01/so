#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>


int main(int argc, char * argv[]){
    if(mkfifo(argv[1],0666)<0){
        perror("fifo");
        return 1;
    }

    return 0;
}