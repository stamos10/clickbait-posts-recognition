#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <ctype.h>
#include <my_global.h>
#include <mysql.h>

#define LEN 496
#define LEN_END 497

/*
cd into bin
compile: gcc ../src/tokenizer_truth.c `mysql_config --cflags --libs` -o tokenizer_truth
run: ./tokenizer_truth

*/



char* id;
char* label;
char* buf;

int fd;
int i;
int start;
int step;
int a = 0;
int b = 0;


void insert_to_database(MYSQL *con, char* id, char* label);
void connectdt(MYSQL *con);
void abort_action(MYSQL *con);
void create_table(MYSQL *con);
MYSQL* connector();


int main(int argc, char* argv[]){

MYSQL *con = mysql_init(NULL);

/*-----------------------------------*/

buf = malloc(LEN);
id = calloc(21, sizeof(char));
label = calloc(14, sizeof(char));
/*-----------------------------------*/

fd = open("../docs/truth.jsonl", O_RDONLY);

if(fd == -1){

printf("Failed to open file\n");
exit(1);
}

read(fd, buf, LEN);
buf[LEN_END] = '\0';


close(fd);
/*-----------------------------------*/


connectdt(con);
create_table(con);


/*-----------------------------------*/

for(i = 0; i < LEN; i++){

if(buf[i] == '{'){
start = 1;
step = 0;
}

if(i > 3){
	if(buf[i - 2] == '"' && buf[i - 1] ==':' && buf[i] == '"'){
	  start = 0;
           if(buf[i - 3] == 'd'){
             step = 0;
	   }else{
             step = 1;
          }

        }

        if(buf[i] == ',' || buf[i] == '}'){

         start = 1;
         step = 0;
        }

}

if(buf[i] == '"'){

continue;
}



if(step == 0 && start == 0){
id[a] = buf[i];
a++;
}else if(step == 1 && start == 0){
label[b] = buf[i];
b++;
}
if(buf[i] == '}'){

insert_to_database(con, id, label);

 for(int y = 0; y < strlen(id); y++){
     id[y] = 32;
      
   }
for(int z = 0; z < strlen(label); z++){
     
      label[z] = 32;
   }
a = 0;
b = 0;
}
}

/*-----------------------------------*/

mysql_close(con);
free(buf);
free(id);
free(label);


return 0;
} 

void insert_to_database(MYSQL *con, char* id, char* label){

char query[1024];
strcpy(query, "INSERT INTO LABELS ");
strcat(query, " (Document_id, Label)");
strcat(query, " VALUES(");

strcat(query, "'");
strcat(query, id);
strcat(query, "',");
strcat(query, "'");
strcat(query, label);
strcat(query, "')");

  if (mysql_query(con, query)) {
      abort_action(con);
  }
query[1024] = 0;
usleep(300);

}

void connectdt(MYSQL *con){

  if (con == NULL) {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "cessna172stam",
                               "bag_of_words", 0, NULL, 0) == NULL) {

      abort_action(con);
  }

}

void create_table(MYSQL *con){

/*
LABEL COLUMN VALUE
0 : no-clickbait
1 : clickbait
*/

char query[1024];
strcpy(query, "CREATE TABLE LABELS (Id INT AUTO_INCREMENT NOT NULL PRIMARY KEY, Document_id TEXT, Label TEXT);");

  if (mysql_query(con, query)) {
      abort_action(con);
  }
query[1024] = 0;
}


MYSQL* connector(){

MYSQL *con = mysql_init(NULL);

return con;
} 


void abort_action(MYSQL *con){
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

