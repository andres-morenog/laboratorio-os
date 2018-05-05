#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <parser.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define SIZE 100

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
        printf(ANSI_COLOR_GREEN "%s:" ANSI_COLOR_RESET ANSI_COLOR_BLUE "%s#" ANSI_COLOR_RESET ,name,directory);
        fgets(input,SIZE,stdin);
        num = separaItems (input, &items, &background);
        if (num>0)
        {
            for (i=0; i<num; i++)
                printf ("%d \"%s\"\n", i+1, items[i]);
                printf ("Background: %d\n", background);
        }
        liberaItems (items);
    }
}