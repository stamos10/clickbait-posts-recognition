#include <stdio.h>
#include <unistd.h>
#include <my_global.h>
#include <mysql.h>
#include "lib/configure_database_helper.h"

/*
cd into bin
replace names accordingly...
gcc ../src/porter.c ../src/lib/configure_database_helper.c  -o porter  `mysql_config --cflags --libs`
./porter
fetches data from database bag_of_words, passes them to porter methods and updates features with stemmed features
*/



int main(void){

MYSQL *con = mysql_init(NULL);

connect_to_database(con);

char query[1024];
strcpy(query, "SELECT Feature FROM postText");
fetch_data(con, query);
query[1024] = 0;
usleep(2000);

close_connection(con);

return 0;
}






                                           
