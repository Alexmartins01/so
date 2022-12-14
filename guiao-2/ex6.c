#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc<=1){
        return 0;
    }
    int aux = atoi(argv[1]);
    int l = atoi(argv[2]);
    int c = atoi(argv[3]);

    int m[l][c];

    printf("matrix creation\n");

    for (int i = 0; i < l; i++){
        for (int j = 0; j < c; j++){
            m[i][j]=rand()%100;
        }
        printf("\n");
    }

    printf("\nsearch\n");

    int pid;

    for (int i = 0; i < l; i++){
        if((pid=fork())==0){
            for (int j = 0; j < c; j++){
                if(m[i][j]==aux) _exit(i+1);
            }
        _exit(0);
        }
    }
    int status;

    for (int count = 0; count < l; count++){
            int finished_pid = wait(&status);

        if(WIFEXITED(status)){
            if(WEXITSTATUS(status)!=0){
                printf("Linha %d\n",WEXITSTATUS(status));
            }
        }
        else printf("error: %d;\n",WIFEXITED(status));
    }

    
    return 0;
}