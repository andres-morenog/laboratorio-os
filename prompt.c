#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <parser.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define SIZE 200
void myclr();
void myecho(char** ,int);
void mytime();
void mypwd();
int mykill(int,int);
void myexit();


int main(int argc, char *argv[])
{

    char ** items;
    int i, num, background;
    char buffer[SIZE];
    char input[SIZE]; 
    char* directory = getwd(buffer);
    char name[SIZE];
    cuserid(name);
    while(1){        
        printf(ANSI_COLOR_GREEN "%s:" ANSI_COLOR_RESET ANSI_COLOR_BLUE "%s# " ANSI_COLOR_RESET ,name,directory);
        fgets(input,SIZE,stdin);
        num = separaItems (input, &items, &background);
        if (num>0)
        {
            if(strcmp(input,"myecho") == 0){
			if (num>1){
				myecho(items,num);
			}
	    }else if(strcmp(input,"myexit") == 0){
			return(0);
	    }else if(strcmp(input,"myclr") == 0){
		
	    }else if(strcmp(input,"mytime") == 0){
			if(num > 1){
				printf("Por favor ingrese el comando correctamente\n");
			}else{
			     mytime();
			}
	    }else if(strcmp(input,"mypwd") == 0){
			mypwd();
	    }else if(strcmp(input,"mycp") == 0){
	    }else if(strcmp(input,"psinfo") == 0){
	    	int i = 0;
	    	char* array[num+1];
	    	for(i;i<num+1;i++){
	    		if(i<num){
	    			array[i] = items[1];
	    		}else{
	    			array[i] = NULL;
	    	 		}
	    		}
	    	int pfork = fork();	
	    	if(pfork == 0){
	    		execv("./psinfo",array);
	    	}else if(pfork > 0){
	    		wait(NULL);
	    	}else{
	    		printf("Error creating child process");
	    	}
	    }else if(strcmp(input,"myps") == 0){
	    }else if(strcmp(input,"mygrep") == 0){
	    }else if(strcmp(input,"mykill") == 0){
	    	if(num > 3 && num < 3){
				printf("Por favor ingrese el comando correctamente\n");
			}else{
			     mykill(atoi(items[1]),atoi(items[2]));
			}
	    }else{
			printf("Por favor ingrese un comando válido \n");
		}
        }
        liberaItems (items);
    }
}

void myecho(char** message,int num){
	int i;

	for(i=1;i<num;i++){
		printf("%s ",message[i]);
	}
	printf("\n");
}

void mytime(){
	int horas,minutos,segundos,dia,mes,year;
	time_t tiempo;
	time(&tiempo);
//	printf("today is : %s",ctime(&now));
	struct tm *local = localtime(&tiempo);
	horas = local->tm_hour;
	minutos = local->tm_min;
	segundos = local->tm_sec;

	dia = local->tm_mday;
	mes = local->tm_mon+1;
	year = local->tm_year+1900;

	printf("La fecha actual es: %02d/%02d/%d\n",dia,mes,year);
	printf("La hora actual es: %02d:%02d:%02d\n",horas,minutos,segundos);

}

void mypwd(){
	char buffer[SIZE];
	char* directory = getwd(buffer);
	printf("el directorio actual es: %s\n",directory);
}

void myclr(){
	printf("Please complete");
}

int mykill(int pid, int signalp){
	int result = kill(pid,signalp);
	if(result == -1){
		if(errno == EINVAL){
			printf("Ha ingresado una señal inválida\n");
		}else if(errno == ESRCH){
			printf("El PID no existe,ingrese uno válido\n");
		}
	}
}