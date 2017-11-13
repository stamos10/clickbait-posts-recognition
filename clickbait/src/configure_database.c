#include <stdio.h>
#include <unistd.h>
#include <my_global.h>
#include <mysql.h>
#include "lib/configure_database_helper.h"

/*
cd into bin
replace names accordingly...
gcc ../src/configure_database.c ../src/lib/configure_database_helper.c  -o configure_database  `mysql_config --cflags --libs`
./configure_database
populates tables into bag_of_words database
*/



int main(void){

MYSQL *con = mysql_init(NULL);

connect_to_database(con);

          create_table(con, "postText");
          printf("Creating table postText\n");
          usleep(100000);

          create_table(con, "title");
          printf("Creating table title\n");
          usleep(100000);

	  create_table(con, "description");
          printf("Creating table description\n");
          usleep(100000);

          create_table(con, "paragraphs");
          printf("Creating table paragraphs\n");
          usleep(100000);



printf("---------Done creating Tables---------\n");
close_connection(con);

return 0;
}






                                           
