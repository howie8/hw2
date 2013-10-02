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

typedef struct  date  Date;
typedef struct tdnode TDnode;

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
    int   class;
    char* notes;
    TDnode* next;
};

void free_list( TDnode* list );
int compare( TDnode* node1, TDnode* node2 );
void print_list( TDnode* head, TDnode* current, int toggle );
//void remove_node( TDnode* head, TDnode* current );

// INSERT NEW FUNCTION PROTOTYPES, AS APPROPRIATE
