#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    if(argc<=2){
        return 0;
    }

    int x = atoi(argv[1]);
    size_t lsize = sizeof(int);
    char line[lsize];


    int file1_fd = open("teste.bin", O_RDWR, 0640);
    if(file1_fd < 0){
        perror("create file");
        return 1;
    }

    write(file1_fd, &x, sizeof(int));

    if(strncmp(&line[0],argv[1],sizeof(int)) == 0) printf("found\n");
}