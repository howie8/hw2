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

// INSERT NEW FUNCTIONS, AS APPROPRIATE
