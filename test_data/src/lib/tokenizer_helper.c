#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include "tokenizer_helper.h"
#include "add_to_list.h"


char* tokenize_text(char* input, char* section, char* temp_features, char* doc_id){

char* stop_words = "and above are because before down for from off too";

strcpy(temp_features, input);
char* token = strtok(temp_features, " ");

  while (token) {
     //printf("%s\n", token);

     if(strlen(token) > 2 && strlen(token) < 20){
          if(strstr(stop_words, token) == NULL){
           
            insert_to_list(doc_id, token, section);       
            usleep(300);
          
          }
    }
token = strtok(NULL, " ");
  }
//printf("\n-----------------------------------\n");



return token;

}


void reset_input(char* input){

   for(int y = 0; y < strlen(input); y++){
     input[y] = 32;
   }
}



