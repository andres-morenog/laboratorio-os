#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc == 3){
        FILE *ptr_file;
        char buf[1000];
	    ptr_file =fopen(argv[2],"r");
	    if (!ptr_file){
	        return 1;
	    }
	    while (fgets(buf,1000, ptr_file)!=NULL){
	        if (strstr(buf, argv[1]) != NULL) {
                 printf("%s",buf);
            }
	    }
	fclose(ptr_file);
    return 0; 
    }else{
        printf("Ingrese correctamente el número de parámetros\n");
    }
}