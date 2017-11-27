#ifndef ADD_TO_LIST_H_   
#define ADD_TO_LIST_H_



void insert_to_list(char* document_id, char* feature, char* section);

void print_list();

struct node* find(char* feature);

void update_data(char* old, char* feature, char* section);


#endif // ADD_TO_LIST_H_
