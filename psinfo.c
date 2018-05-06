/**
*   Laboratorio#2 para el curso de Sistemas operativos
*   Desarrollado por : Andrés Moreno González y José Luis Aguirre
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Processes {
    char pid[512];
    char name[512];
    char status[512];
    char memsize[512];
    char memtext[512];
    char memstack[512];
    char memdata[512];
    char vcontext[512];
    char nvcontext[512];
}Process;

void printInformation(char[]);
void filter(char[]);
void filterW(char[],char[],Process[],int);
void formatString(char[],char[], int);
void fillArray(Process[],int,char[]);
void writeFile(Process[],char[],int);
void makePath(char[],char[],int);

/**
*   @brief  función principl del programa
*   @param argc Cantidad de argumentos ingresados al ejecutar el programa
*   @param argv Los argumentos ingresados al ejecutar el programa
*   @return    int indica si se terminó con éxito el programa al devolver un 0, cualquier otro caso es
*   un código de error
*/
int main(int argc, char *argv[]) {
    if( argc == 2 ) {
      printInformation(argv[1]);
   }
   else if( argc > 2 ) {

      int i = 0;
      int j = 0;
      int size = argc - 2;
      char result[256];
      memset(result,0,sizeof(result));
      Process processes[size];
      switch(argv[1][1]){

          case 'l':
            for(i = 2; i < argc ; i++){
                printf("PID L-> %s \n",argv[i]);
                printInformation(argv[i]);
            }
            break;

           case 'r':
                for(i = 2;i<argc;i++){
                    fillArray(processes,j,argv[i]);

                    if(i == (argc - 1)){
                        makePath(result,argv[i],1);
                    }else{
                        makePath(result,argv[i],0);
                    }
                    j++;
                }
                writeFile(processes,result,size);
                break;

            default:
                printf("Proporcione un argumento válido \n");
                printf("Recuerde que los parámetros válidos son -l seguido de una lista de procesos válidos \n");
                printf("ó -r seguido de una lista de procesos válidos \n");
                break;
      }
   }
   else {
      printf("Se esperaba un argumento.\n");
   }

    return 0;
}

/**
*   @brief Obtiene los datos necesarios de un proceso y los almacena en la posición indicada
*   en un arreglo de procesos.
*   @param  path archivo en el cual se encuentra la información necesaria.
*   @param  pid id del proceso al cual se le quiere obtener información.
*   @param  array arreglo de procesos en el cual se guardará la información
*   @param  index indice en el cual se ingresará la información del proceso
*   @return void
*
*/
void filterW(char path[],char pid[],Process array[],int index){
    int line = 0;
    FILE *pointerToFile = fopen(path,"r");
    char input[512];
    char ninput[512];
    int size = 0;
    memcpy(array[index].pid,pid,sizeof(array[index].pid));
    if(pointerToFile == NULL){
        printf("Por favor ingrese un id de proceso válido \n");
        exit(-1);
    }
    while(fgets(input,512,pointerToFile)){
        line++;
        switch(line){
            case 1:
                formatString(input,ninput,strlen(input));
                memcpy(array[index].name,ninput,sizeof(array[index].name));
                printf("Name -> %s",array[index].name);
                break;
            case 3:
                formatString(input,ninput,strlen(input));
                memcpy(array[index].status,ninput,sizeof(array[index].status));
                printf("Estado: %s",ninput);
                break;
            case 18:
                formatString(input,ninput,strlen(input));
                memcpy(array[index].memsize,ninput,sizeof(array[index].memsize));
                printf("Tamaño total de la imagen en memoria: %s",ninput);
                break;
            case 26:
                formatString(input,ninput,strlen(input));
                memcpy(array[index].memtext,ninput,sizeof(array[index].memtext));
                printf("Tamaño de la sección de memoria TEXT: %s",ninput);
                break;
            case 27:
                formatString(input,ninput,strlen(input));
                memcpy(array[index].memdata,ninput,sizeof(array[index].memdata));
                printf("Tamaño de la sección de memoria DATA: %s",ninput);
                break;
            case 28:
                formatString(input,ninput,strlen(input));
                memcpy(array[index].memstack,ninput,sizeof(array[index].memstack));
                printf("Tamaño de la sección de memoria STACK: %s",ninput);
                break;
            case 51:
                formatString(input,ninput,strlen(input));
                memcpy(array[index].vcontext,ninput,sizeof(array[index].vcontext));
                printf("Número de cambios de contexto voluntarios realizados: %s",ninput);
                break;
            case 52:
                formatString(input,ninput,strlen(input));
                memcpy(array[index].nvcontext,ninput,sizeof(array[index].nvcontext));
                printf("Número de cambios de contexto no-voluntarios realizados: %s",ninput);
                break;
        }
    }
    fclose(pointerToFile);
}

/**
*   @brief  genera la ruta en la cual se generará el archivo con la información de los procesos
*   @param  result string resultante
*   @param  arg id de proceso
*   @param  indica si es el último proceso que se debe agregar al string para así evitar colocar el
*   símbolo '-' después de este
*   @return void
*/
void makePath(char result[],char arg[],int opt){
    char minus[] = "-";
    strcat(result,arg);
    if(opt == 0){
        strcat(result,minus);
    }
    return;
}

/**
*   @brief escribe en el archivo path la información de los procesos pasados por parametro
*   @param  array arreglo de procesos a escribir en el archivo
*   @param  procString string donde se indican los procesos que se van a escribir en el archivo
*   @param  size tamaño del arreglo de procesos
*   @return void
*/
void writeFile(Process array[],char procString[],int size){
    char psinfo[] = "psinfo-report-";
    char extension[]  = ".info";
    char path[512];
    int i = 0;
    snprintf(path, sizeof(path), "%s%s%s", psinfo, procString, extension);
    FILE *fileToWrite = fopen(path,"w");
    if(fileToWrite == NULL){
        printf("Ha sucedido un error no fue posible crear el archivo \n");
        exit(-1);
    }
    for(i = 0; i < size;i++){
        fprintf(fileToWrite,"PID -> %s",array[i].pid);
        fprintf(fileToWrite,"Name -> %s",array[i].name);
        fprintf(fileToWrite,"Estado: %s",array[i].status);
        fprintf(fileToWrite,"Tamaño total de la imagen en memoria: %s",array[i].memsize);
        fprintf(fileToWrite,"Tamaño de la sección de memoria TEXT: %s",array[i].memtext);
        fprintf(fileToWrite,"Tamaño de la sección de memoria DATA: %s",array[i].memdata);
        fprintf(fileToWrite,"Tamaño de la sección de memoria STACK: %s",array[i].memstack);
        fprintf(fileToWrite,"Número de cambios de contexto voluntarios realizados: %s",array[i].vcontext);
        fprintf(fileToWrite,"Número de cambios de contexto no-voluntarios realizados: %s",array[i].nvcontext);
    }
    return;
}

/**
*   @brief  filtra los datos necesarios para el desarrollo de la práctica
*   @param  path ruta donde se encuentra el archivo que contiene la información del proceso
*   @return void
*/
void filter(char path[]){

    int line = 0;
    FILE *pointerToFile = fopen(path,"r");
    char input[512];
    char ninput[512];
    int size = 0;
    if(pointerToFile == NULL){
        printf("Proceso no encontrado, por favor ingrese un proceso válido \n");
        exit(-1);
    }
    while(fgets(input,512,pointerToFile)){
        line++;
        switch(line){
            case 1:
                formatString(input,ninput,strlen(input));
                printf("Nombre del proceso: %s",ninput);
                break;
            case 3:
                formatString(input,ninput,strlen(input));
                printf("Estado: %s",ninput);
                break;
            case 18:
                formatString(input,ninput,strlen(input));
                printf("Tamaño total de la imagen en memoria: %s",ninput);
                break;
            case 26:
                formatString(input,ninput,strlen(input));
                printf("Tamaño de la sección de memoria TEXT: %s",ninput);
                break;
            case 27:
                formatString(input,ninput,strlen(input));
                printf("Tamaño de la sección de memoria DATA: %s",ninput);
                break;
            case 28:
                formatString(input,ninput,strlen(input));
                printf("Tamaño de la sección de memoria STACK: %s",ninput);
                break;
            case 51:
                formatString(input,ninput,strlen(input));
                printf("Número de cambios de contexto voluntarios realizados: %s",ninput);
                break;
            case 52:
                formatString(input,ninput,strlen(input));
                printf("Número de cambios de contexto no-voluntarios realizados: %s",ninput);
                break;
        }
    }
    fclose(pointerToFile);
}

/**
*   @brief llena el arreglo de procesos en el indice indicado con el id indicado
*   @param  array arreglo de procesos a llenar.
*   @param  index indice en el cual se ingresará la información del proceso
*   @param  processid id del proceso a ingresar en el arreglo
*   @return void
*/
void fillArray(Process array[], int index ,char processid[]){
    char proc[] = "/proc/";
    char status[]  = "/status";
    char path[256];
    snprintf(path, sizeof(path), "%s%s%s", proc, processid, status);
    filterW(path,processid,array,index);
}

/**
*   @brief  imprime la información de un proceso pasado por parametro
*   @param  processid id del proceso al cual se le debe imprimir información
*   @return void
*/
void printInformation(char processid[]){
    char proc[] = "/proc/";
    char status[]  = "/status";
    char path[256];
    snprintf(path, sizeof(path), "%s%s%s", proc, processid, status);
    filter(path);
}

/**
*   @brief  retira los datos no necesarios en un string donde se tiene información de un proceso
*   @param  string que se va a procesar
*   @param  result string resultanto
*   @param  size tamaño del string a procesar
*   @return void
*/
void formatString(char string[],char result[],int size){
    int flag = 0;
    int i = 0;
    int j = 0;
    memset(result,0,sizeof(result));
    for(i = 0 ; i < size ; i++){
        if(flag){
            result[j] = string[i];
            j++;
        }
        if(string[i] == ':'){
            flag = 1;
        }
    }
    return;
}