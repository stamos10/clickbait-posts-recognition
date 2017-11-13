#ifndef CONFIGURE_DATABASE_HELPER_H_   
#define CONFIGURE_DATABASE_HELPER_H_ 

MYSQL* connector();

void connect_to_database(MYSQL *con);

void abort_action(MYSQL *con);

void close_connection(MYSQL *con);

void create_table(MYSQL *con, char* table_name);

void insert_data(MYSQL *con, char* document_id, char* feature, char* section, char* label);

void fetch_data(MYSQL *con, char* query);

char* print_feature(char* feature);

#endif //CONFIGURE_DATABASE_HELPER_H_ 
