/**********************************************************************
*   tdlist.c
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

#include "tdlist.h"

/**********************************************************************
   Free all the memory occupied by a
   linked list of ToDo items.
**********************************************************************/
void free_list( TDnode *head )
{
    TDnode *node;

    while( head != NULL ) {
        node = head;
        head = head->next;
        free( node->task );
        free( node->notes );
        free( node );
    }
}

TDnode* remove_node( TDnode* head, TDnode* current )
{  
    if( head != NULL ){
        if( current == head ){
            head = head->next;
        }
        
        else{
            TDnode* prev_node = head;
        
            while( prev_node->next != current ){
                prev_node = prev_node->next;
            }
        
            prev_node->next = current->next;
        }
    }
    
    return( head );
}
// INSERT NEW FUNCTIONS, AS APPROPRIATE
