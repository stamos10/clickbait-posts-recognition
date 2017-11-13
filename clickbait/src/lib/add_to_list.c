#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "add_to_list.h"
#include <my_global.h>
#include <mysql.h>
//#include "configure_database_helper.c"
#include "configure_database_helper.h"



struct node {
   char* document_id;
   char* feature;
   char* section;
   struct node *next;
};


struct node *head = NULL;
struct node *current = NULL;

int database_id = 1;

void insert_to_list(char* document_id, char* feature, char* section) {
   
   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->document_id = document_id;
   link->feature = feature;
   link->section = section;
   printf("Feature: [ %s ] Section: [ %s ] Document ID: [ %s ] \n", link->feature, link->section, link->document_id);	
   insert_data(connector(),  link->document_id, link->feature, link->section, " ");
   link->next = head;
   close_connection(connector());
   head = link;
    usleep(300);
}


void print_list() {
   
   struct node *ptr = head;
   
	
   while(ptr != NULL) {
      printf("[%s --%s -- %s ]\n\n ",ptr->feature, ptr->section, ptr->document_id);
      ptr = ptr->next;
   }
	
  
}


struct node* find(char* feature) {

   struct node* current = head;

   if(head == NULL) {
      return NULL;
   }
   
  
   while(current->feature != feature) {
	
          if(current->next == NULL) {
            return NULL;
          }else{
            current = current->next;
          }
  } 
   
   
   return current;
}


void update_data(char* old, char* feature, char* section) {
   int pos = 0;
   
   if(head==NULL) {
        
     return;
   } 

   current = head;
   while(current->next != NULL) {
      if(current->feature == old){
         current->feature = feature;
         current->section = section;
        
  
         return;
      }
      current = current->next;
      pos++;
   }
  
}
