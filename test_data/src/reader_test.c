#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define LEN 12431123
#define LEN_END 12431123

/*

cd into bin
compile: gcc ../src/reader_test.c -o reader
run: ./reader > train.json

converts input file to preety json file

*/

int main(int argc, char *argv[]){

long fd;
char *buf = (char *)malloc(12431123); 

fd = open("../docs/instances_test.jsonl", O_RDONLY);

if(fd == -1){

printf("Failed to open file\n");
exit(1);
}

read(fd, buf, LEN);
buf[LEN_END] = '\0';


close(fd);


for(long i = 0; i < LEN; i++){

       if(i == 0){
 
          printf("%c", buf[0]);
       }else if( i > 0){

	   if(buf[i - 1] == '{') {
             printf("\n%c",buf[i]);
	   }else if(buf[i -1] == '"' && buf[i] ==  ','  || buf[i - 1] == ']'  && buf[i] ==   ',') {
             printf("%c\n\n", buf[i]);
           }else if(buf[i] ==  '}') {
             printf("\n%c\n\n\n\n", buf[i]);
           }else{    
            printf("%c", buf[i]);	
           }
	}
}



free(buf);

return 0;
}












