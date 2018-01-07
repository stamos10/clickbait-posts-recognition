#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <ctype.h>
#include <locale.h>

#include <my_global.h>
#include <mysql.h>
#include "lib/configure_database_helper.h"
#include "lib/tokenizer_helper.h"
#include "lib/add_to_list.h"
#define LEN 3971241
#define LEN_END 3971242

/*
cd into bin
compile: gcc ../src/tokenizer_test.c ../src/lib/tokenizer_helper.c ../src/lib/add_to_list.c  ../src/lib/configure_database_helper.c `mysql_config --cflags --libs` -o tokenizer

run: ./tokenizer

reads pretty json file and tokenizes
*/

void tokenize();


char* buf;
char* features;

char* id;
char* timeStamp;
char* postText;
char* postMedia;
char* title;
char* description;
char* keywords;
char* paragraphs;
char* captions;

int document = 0;
int step = 0;


int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;
int g = 0;
int h = 0;
int j = 0;






int main(int argc, char *argv[]){

//connect_to_database(connector());

char *locale;

locale = setlocale(LC_ALL, "");

int fd;
int i;
int start;

features = (char *)malloc(LEN);
buf = (char *)malloc(LEN); 
id = calloc(30, sizeof(char));
timeStamp = calloc(50, sizeof(char));
postText = calloc(2000, sizeof(char));
postMedia = calloc(1024, sizeof(char));
title = calloc(1024, sizeof(char));
description = calloc(4000, sizeof(char));
keywords = calloc(4000, sizeof(char));
paragraphs = calloc(18000, sizeof(char));
captions = calloc(18000, sizeof(char));


fd = open("../docs/instances_test.json", O_RDONLY);

if(fd == -1){

printf("Failed to open file\n");
exit(1);
}


if (locale) {
        
read(fd, buf, LEN);
buf[LEN_END] = '\0';
}

close(fd);

for(i = 0; i < LEN_END; i++){

	
	   if(buf[i] == '"' && buf[i - 1] == '[' || buf[i] == ']' && buf[i - 1] == '['){
             if(step > 0 && step <= 4){
              start = 0;
             }
            }else if(buf[i] == '"' && buf[i - 1] == ':'){
              if(step == 0 || step > 4){
                start = 0;
              } 
             }
           
            
            if(buf[i] == ',' && buf[i - 1] == ']'){
              if(step > 0 && step <= 4){
                start = 1;
                step++;
              }
             }else if( buf[i] == ',' && buf[i - 1] == '"'){
		if(step ==0 || step > 4){
                start = 1;
                step++;
               }
             }else if(buf[i] == '}'){
		 if(step == 8){
                start = 1;
              }
             }

              
              
               
               
             

           

          
           if(buf[i] == '[' || buf[i] == ']'){
             
             continue;
           }
           if(buf[i] == '"'){
             
             continue;
           }
           if(buf[i] == ','){
              
                    continue;
           }
           if(buf[i] == '.'){
              
                    continue;
           }
           if(buf[i] == 39 || buf[i] == 96){
               
                    continue;
           }
           if(buf[i] == '/'){
              
                    continue;
           }
           if(buf[i] == 92){
              
                    continue;
           }
           if(buf[i] == '!'){
              
                    continue;
           }
           
           if(buf[i] == '-'){
              
                    continue;
           }
           if(buf[i] == ')'){
            
                    continue;
           }
           if(buf[i] == '('){
            
                    continue;
           }
           if(buf[i] == ':'){
            
                    continue;
           }
	   if(buf[i] == '?'){
            
                    continue;
           }
	   if(buf[i] == '@'){
            
                    continue;
           }
	   if(buf[i] == '&'){
            
                    continue;
           }
           if(buf[i] == '%'){
            
                    continue;
           }
           if(buf[i] == '#'){
            
                    continue;
           }
           
           if(buf[i] == ';'){
            
                    continue;
           }
           if(buf[i] == '{'){ 
            start = 1;
                           
            continue;
           }
           if(buf[i] == '}'){ 
            start = 1;              
            continue;
           }
            
            if(buf[i - 1] == '}'){

                  tokenize();
                  document++;
           }
          
           
           
		if(start == 0 && step == 0){

                 id[a] = tolower(buf[i]);
                 a++;
                   
		}

		if(start == 0 && step == 5){

                 timeStamp[b] = tolower(buf[i]);
                 b++;
		}

		if(start == 0 && step == 4){

                 postText[c] = tolower(buf[i]);
                 c++;
                  
		}

		if(start == 0 && step == 1){
                     if(buf[i - 1] == '/'){
                       postMedia[d] = tolower(buf[i - 1]);
                       d++;  
                     }
                      if(buf[i - 1] == '.'){
                       postMedia[d] = tolower(buf[i - 1]);
                       d++;  
                     }
                 postMedia[d] = tolower(buf[i]);
                 d++;
                  
		}

		if(start == 0 && step == 6){
                
                 title[e] = tolower(buf[i]);
                 e++;
                 
		}

		if(start == 0 && step == 7){

                 description[f] = tolower(buf[i]);
                 f++;
                 
		}

		if(start == 0 && step == 8){
                   if(buf[i - 1] == ','){
                     keywords[g] = ' ';
                     g++;
                   }
                 keywords[g] = tolower(buf[i]);
                 g++;
                 
		}

                if(start == 0 && step == 2){
                     
                  
                 
                  
                  paragraphs[h] = tolower(buf[i]);
                  h++;
		  
               }

               if(start == 0 && step == 3){
                     
                 
                 
                  captions[j] =tolower(buf[i]);
                  j++;
                  
               }
                  
}


//close_connection(connector());

free(id);
free(timeStamp);
free(postText);
free(postMedia);
free(title);
free(description);
free(keywords);
free(paragraphs);
free(captions);
free(buf);
free(features);

return 0;
}






void tokenize(){

//tokenize_text(id, "id", features, id);
//tokenize_text(timeStamp, "timeStamp",  features, id);
tokenize_text(postText, "postText", features, id);
//tokenize_text(postMedia, "postMedia", features, id);
//tokenize_text(title, "title", features, id);
//tokenize_text(description, "description", features, id);
//tokenize_text(keywords, "keywords", features, id);
//tokenize_text(paragraphs, "paragraphs", features, id);
//tokenize_text(captions, "captions", features, id);

//reset_input(id);
//reset_input(timeStamp);
reset_input(postText);
//reset_input(postMedia);
//reset_input(title);
//reset_input(description);
//reset_input(keywords);
//reset_input(paragraphs);
//reset_input(captions);

a = 0;
b = 0;
c = 0;
d = 0;
e = 0;
f = 0;
g = 0;
h = 0;
j = 0;
step = 0; 

printf("\n*****************\n");
}







