#include <my_global.h>
#include <mysql.h>

/*
replace names accordingly...
gcc database.c -o ../bin/database  `mysql_config --cflags --libs`
*/

void connect_to_database();
void abort_action();
void close_connection();
void create_table(char table_name);
void insert_data(char table_name);

MYSQL *con;

void connect_to_database_(){

  if (con == NULL) {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "data_user", "p@cl!ckb@!tss",
                               NULL, 0, NULL, 0) == NULL) {

      abort_action(con);
  }

}


void abort_action(){
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

/*
this method at the end of each file this file is included
*/
void close_connection(){

mysql_close(con);
}



void create_table(char table_name){
/*
LABEL COLUMN VALUE
0 : no-clickbait
1 : clickbait
*/
 if (mysql_query(con, strcat("DROP TABLE IF EXISTS ", table_name))) {
      abort_action(con);
  }

  if (mysql_query(con, strcat("CREATE TABLE ", table_name) + " (Id INT, Feature TEXT, PostText INT, PostMedia INT, Title INT, DescriptionINT,KeywordsINT,Paragraphs INT, Captions INT, Label INT)"))) {
      abort_action(con);
  }


}

/*

void insert_data(char table_name){

  if (mysql_query(con, "INSERT INTO Cars VALUES(1,'Audi',52642)")) {
      abort_action(con);
  }


}

*/
                                           
