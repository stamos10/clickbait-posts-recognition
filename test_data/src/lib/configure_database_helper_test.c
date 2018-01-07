#include <stdio.h>
#include <unistd.h>
#include <my_global.h>
#include <mysql.h>
#include "configure_database_helper.h"

MYSQL* connector(){

MYSQL *con = mysql_init(NULL);

return con;
} 


void connect_to_database(MYSQL *con){

  if (con == NULL) {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "cessna172stam",
                               "bag_of_words", 0, NULL, 0) == NULL) {

      abort_action(con);
  }

}


void abort_action(MYSQL *con){
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

/*
this method at the end of each file this file is included
*/

void close_connection(MYSQL *con){

mysql_close(con);
}



void create_table(MYSQL *con, char* table_name){

/*
LABEL COLUMN VALUE
0 : no-clickbait
1 : clickbait
*/

char query[1024];
strcpy(query, "CREATE TABLE ");
strcat(query, table_name);
strcat(query, " (Document_id TEXT, Feature TEXT, Section TEXT, Num INT, Label TEXT NULL);");

  if (mysql_query(con, query)) {
      abort_action(con);
  }
query[1024] = 0;
}



void insert_data(MYSQL *con,  char* document_id, char* feature, char* section, char* label){

connect_to_database(con);
/*-------------------get label-------------------------*/
char query1[1024];
strcpy(query1, "SELECT Label FROM TEST_LABELS WHERE Document_id = '");
strcat(query1, document_id);
strcat(query1, "'");

if (mysql_query(con, query1)) 
  {
     abort_action(con);
  }
  
  MYSQL_RES *result1 = mysql_store_result(con);
  
  if (result1 == NULL) 
  {
      abort_action(con);
  }

  int num_fields1 = mysql_num_fields(result1);

   MYSQL_ROW row1;
  
  while ((row1 = mysql_fetch_row(result1))) 
  { 
      for(int i = 0; i < num_fields1; i++) 
      { 
       label = row1[0];
       break;   
      } 
          
  }


  
query1[1024] = 0;
mysql_free_result(result1);
/*check if already in database and in current document

char query2[1024];
strcpy(query2, "SELECT Feature FROM "); 
strcat(query2, "data");
strcat(query2, " WHERE Feature = '"); 
strcat(query2, feature);
strcat(query2, "'");
strcat(query2, " AND Section = '");
strcat(query2, section);
strcat(query2, "'");
strcat(query2, " AND Document_id = '");
strcat(query2, document_id);
strcat(query2, "'");

if (mysql_query(con, query2)) 
  {
     abort_action(con);
  }
  
  MYSQL_RES *result2 = mysql_store_result(con);
  
  if (result2 == NULL) 
  {
      abort_action(con);
  }

  int num_fields2 = mysql_num_fields(result2);

   MYSQL_ROW row2;
  
  while ((row2 = mysql_fetch_row(result2))) 
  { 
      for(int i = 0; i < num_fields2; i++) 
      { 
          	
      } 
          
  }
  
query2[1024] = 0;
mysql_free_result(result2);
	

if(mysql_num_rows(result2) > 0){
char query_u[1024];
strcpy(query_u, "UPDATE ");
strcat(query_u, "data");
strcat(query_u, " SET Num = Num + 1 ");  
strcat(query_u, " WHERE Feature = '"); 
strcat(query_u, feature);
strcat(query_u, "'");
strcat(query_u, " AND Section = '");
strcat(query_u, section);
strcat(query_u, "'");
strcat(query_u, " AND Document_id = '");
strcat(query_u, document_id);
strcat(query_u, "'");
 if (mysql_query(con, query_u)) {
      abort_action(con);
  }
query_u[1024] = 0;
}else{
*/
/*if no insert new record */
/*-------------------INSERT------------------*/
char query[1024];
strcpy(query, "INSERT INTO ");
strcat(query, "test_data");
strcat(query, " (Document_id, Feature, Section, Num, Label)");
strcat(query, " VALUES(");

strcat(query, "'");
strcat(query, document_id);
strcat(query, "',");
strcat(query, "'");
strcat(query, feature);
strcat(query, "',");
strcat(query, "'");
strcat(query, section);
strcat(query, "',");
strcat(query, "1");
strcat(query, ",");
strcat(query, "'");
strcat(query, label);
strcat(query, "')");

  if (mysql_query(con, query)) {
      abort_action(con);
  }
query[1024] = 0;



close_connection(con);
usleep(300);
}


void fetch_data(MYSQL *con, char* query){

if (mysql_query(con, query)) 
  {
     abort_action(con);
  }
  
  MYSQL_RES *result = mysql_store_result(con);
  
  if (result == NULL) 
  {
      abort_action(con);
  }

  int num_fields = mysql_num_fields(result);

   MYSQL_ROW row;
  
  while ((row = mysql_fetch_row(result))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          //printf("%s ", row[i] ? row[i] : "NULL"); 
            print_feature(row[i]);
      } 
          printf("\n"); 
  }


  mysql_free_result(result);


}

char* print_feature(char* feature){

printf("%s", feature);
return feature;
}





