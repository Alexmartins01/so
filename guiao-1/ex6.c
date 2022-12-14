#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct person{
    char name[20];
    int age;
} Person;

int compare_person(Person p, Person *ps, int bytes){
    int i=0;
    while(bytes>0){
        if(strcmp(p.name,ps[i].name)) return i;
        bytes-=24;
        i++;
    }

    return 0;
}

int main(int argc, char *argv[]){
    int aux=0;
    int i;

    int file_fd = open(argv[1], O_RDWR);
    
    if(file_fd < 0){
        perror("open file");
        return 1;
    }
    if(strcmp("-i",argv[2])) aux = 1;
    i=3;



    Person p1;

    strcpy(p1.name,argv[i]);

    p1.age = atoi(argv[++i]);

    if(aux!=0){
        lseek(file_fd,0,SEEK_END);
        int bytes = write(file_fd, &p1, sizeof(Person));
    }
    else{
        Person p_read[170];
        int bytes = 0;
        int res = 0;
        int person = 0;
        while(res==0 && (bytes = read(file_fd,&p_read,4080))>0){
            res=compare_person(p1,p_read,bytes);
            person+=170;
        }

        if(res>0) {
            lseek(file_fd,(person+res)*24,SEEK_SET);
            //alterar fich podemos simplesmente escrever a idade por cima
        }
        
    }


   int people_fd = open("people.bin", O_CREAT | O_APPEND | O_RDWR, 0640);

    int bytes = write(people_fd, &p1, sizeof(Person));
    printf("%d\n",bytes);

    lseek(people_fd, -sizeof(Person), SEEK_CUR); // imprime registo alterado

    Person p1_read;

    bytes = read(people_fd, &p1_read, sizeof(Person));  // nao le nada porque esta no fim do ficheiro

    printf("\nread: %d bytes\n", bytes);
    printf("p1.name: %s\n", p1.name);
    printf("p1.age: %d\n", p1.age);

}

/*
 Aloca bloco de 24 bytes
 20 do nome + 4 da idade

 struct Person p;
 _________20_____________4__
 |       name         | age|
 |_________________________|

 write(fd,&p,sizeof(struct(Person))=24) escreve bloco de bytes

 No ficheiro final vai ter vários blocos, para saltar de pessoa em pessoa, é só ler de 24 em 24 bytes
*/