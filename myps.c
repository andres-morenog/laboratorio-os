#define _GNU_SOURCE
#include <dirent.h>     /* Defines DT_* constants */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#define handle_error(msg) \
       do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct linux_dirent {
   long           d_ino;
   off_t          d_off;
   unsigned short d_reclen;
   char           d_name[];
};

#define BUF_SIZE 1024*1024*5
#define ARRAY_SIZE 1024
int
main(int argc, char *argv[])
{
   int fd, nread;
   char buf[BUF_SIZE];
   char *array[ARRAY_SIZE];
   struct linux_dirent *d;
   int bpos;
   char d_type;

   fd = open(argc > 1 ? argv[1] : "/proc", O_RDONLY | O_DIRECTORY);
   if (fd == -1)
       handle_error("open");
    int i = 0;
   for ( ; ; ) {
       nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
       if (nread == -1)
           handle_error("getdents");

       if (nread == 0)
           break;

       for (bpos = 0; bpos < nread;) {
           d = (struct linux_dirent *) (buf + bpos);
           if (d->d_ino != 0) {
   //            printf("%s\n", (char *) d->d_name);
               array[i] = d->d_name;
               i++;
           }
           bpos += d->d_reclen;
       }
   }
    int j = 0;
    int count = 0;
    int atoiResult;
    for(j=0;j<i;j++){
        atoiResult = atoi(array[j]);
        if(atoiResult != 0){
            count++;
        }
    }
    int arraypid[count];
    char *namearray[count];
    int k = 0;
    for(j=0;j<i;j++){
        atoiResult = atoi(array[j]);
        if(atoiResult != 0){
           arraypid[k] = atoiResult;
 //          printf("pid %d\n",arraypid[k]);
 //          printf("k %d\n",k);
           k++;
        }
    }
    k = 0;
    char proc[] = "/proc/";
    char comm[]  = "/comm";
    char path[256];
    char stringpid[10];
    printf("PID    CMD\n");
    for(;k<count;k++){
        FILE *ptr_file;
        char buf[1000];
        sprintf(stringpid,"%d",arraypid[k]);
        snprintf(path, sizeof(path), "%s%s%s", proc, stringpid, comm);
	    ptr_file =fopen(path,"r");
	    if (!ptr_file){
	        return 1;
	    }
	    while (fgets(buf,1000, ptr_file)!=NULL){
	        printf("%d    %s\n",arraypid[k],buf);
//	        printf("%d",arraypid[k]);
//	        printf("%s",buf);
	    }
	fclose(ptr_file);
    }
    
    
   exit(EXIT_SUCCESS);
}