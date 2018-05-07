#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc == 3){
        int fileOrg, fileDes;
        fileOrg = open(argv[1], O_RDONLY);
        if(fileOrg < 0){
            printf("no se pudo leer");
            return 1;
        }
        ssize_t valor = 0;
        char line [100];
        fileDes = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH );
        if(fileDes < 0){
            printf("no se pudo escribir");
            return 1;
        }
        while(valor = read(fileOrg, line, 40)){
            write(fileDes,line,valor);
        }
        close(fileOrg);
        close(fileDes);
        return 0;

    }else{
        printf("Ingrese correctamente la cantidad de argumentos");
        return 0;
    }
}
