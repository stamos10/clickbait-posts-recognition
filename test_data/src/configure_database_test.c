#include <stdio.h>
#include <unistd.h>
#include <my_global.h>
#include <mysql.h>
#include "lib/configure_database_helper.h"

/*
cd into bin
replace names accordingly...
gcc ../src/configure_database_test.c ../src/lib/configure_database_helper.c  -o configure_database  `mysql_config --cflags --libs`
./configure_database
populates tables into bag_of_words database
*/



int main(void){

MYSQL *con = mysql_init(NULL);

connect_to_database(con);

          create_table(con, "test_data");
          printf("Creating table test_data\n");
          usleep(100000);

printf("---------Done creating Tables---------\n");
close_connection(con);

return 0;
}






                                           
