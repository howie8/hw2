/**********************************************************************
*   tdlist.h
*   Chetan Sahai - z3288822
*   Haoxiang Fei - z3464323
*
*   COMP1917 Computing 1
*   Assignment 2: ToDo List Manager
*
*   UNSW Session 2, 2013
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE     128
#define MAX_TEXT    4096

typedef struct 	    date Date;
typedef struct    tdnode TDnode;
typedef struct stacknode StackNode;

struct date 
{
    int day;
    int month;
    int year;
};

struct tdnode 
{
      char* task;
      Date  date;
       int  class;
      char* notes;
    TDnode* next;
};

struct stacknode
{
       TDnode* current;
         char  command;
    StackNode* next;
       TDnode  data;

};

/**********************************************************************
*   Function prototypes
**********************************************************************/

// Stage 0 - Provided Code
  void  free_list( TDnode* list );
  void  print_help();
TDnode* get_node(  void );
  char* get_task(  void );
  char* get_notes( void );
   int  get_class( void );
  void  get_date( Date *d );
   int  scan_date( Date *d );
   
// Stage 2 - Adding, checking and listing items
TDnode *add_node( TDnode* head, TDnode* node );
   int  date_ok(  Date *d );
   int  compare( TDnode* node1, TDnode* node2 );

// Stage 3 - Navigating the List
  void  print_list( TDnode* head, TDnode* current, int toggle );
TDnode* forward( TDnode* head, TDnode* current);
TDnode* back( TDnode* head, TDnode* current);

// Stage 4 - Removing or Changing items
TDnode *remove_node( TDnode* head, TDnode* current );
TDnode *change_task( TDnode* current );
TDnode *change_notes( TDnode* current );
TDnode *change_date( TDnode* head, TDnode* current );
TDnode *change_class( TDnode* head, TDnode* current );

// Stage 5 - Searching the list

// Stage 6 - Undo
     void  free_stack( StackNode* head );
StackNode* push( TDnode* current, StackNode* head, char command );
StackNode* pop( StackNode* head );
   TDnode* undo( StackNode* stack, TDnode* list, TDnode* current );
