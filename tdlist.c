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

#include "tdlist.h"

// Free all the memory occupied by a linked list of ToDo items.
void free_list( TDnode* head )
{
    TDnode* node;

    while( head != NULL ) {
        node = head;
        head = head->next;
        free( node->task );
        free( node->notes );
        free( node );
    }
}

// Free all the memory occupied by a stack
void free_stack( StackNode* head )
{
    StackNode* node = head;
    StackNode* tmp;

    while( node != NULL ) {
        tmp = node;
        node = node->next;
        free( tmp );  
    }
}
/**********************************************************************
*   STAGE 2 - Adding, checking and listing items
**********************************************************************/

// Return 1 if date is valid; 0 otherwise.
int date_ok( Date* d )
{
    int month_length = 0;

    // Initial test
    if (d->day <= 0 || d->day > 31 || d->month <= 0 || d->month > 12 || d->year < 0 || d->year > 99) {
        return 0;
    }

    // April, June, September, November
    if (d->month == 4||d->month == 6||d->month == 9||d->month == 11) {
        month_length = 30;
    }
    // February
    else if (d->month == 2) {
        // Leap year
        if ( d->year % 4 == 0 ) {
            month_length = 29;
        }
        else {
            month_length = 28;
        }
    }
    // If input date is in other months.
    else {
        month_length = 31;
    }
    
    // Check that day of month is valid.
    if (d->day > month_length) {
        return 0;
    }

    return 1;
}

// Compare nodes. Returns 1 if later, 0 if earlier or equal
int compare( TDnode* node1, TDnode* node2 )
{
    if( node1->date.year < node2->date.year ) {
        return 0;    
    }
    else if( node1->date.year > node2->date.year ) {
        return 1;
    }
    else if( node1->date.month < node2->date.month ) {
        return 0;
    }
    else if( node1->date.month > node2->date.month ) {
        return 1;
    }
    else if( node1->date.day < node2->date.day ) {
        return 0;
    }
    else if( node1->date.day > node2->date.day ) {
        return 1;    
    }
    else if( node1->class < node2->class ){
        return 0;
    }
    else if( node1->class > node2->class ){
        return 1;
    }
    else {
        return 0;
    }
}

// Add item
TDnode * add_node( TDnode* head, TDnode* node )
{
    // Check for empty list
    if( head == NULL ){
        head = node;                
    }
    // Else check if node belongs at start of list
    else if( compare( node, head ) == 0 ) {
        node->next = head;
        head = node;
    }
    // Else try to insert node in middle or tail
    else {
        TDnode* prev_node = head;
        while( 1 ) {
            // Check for insertion at tail
            if( prev_node->next == NULL ) {
                prev_node->next = node;
                node->next = NULL;
                break;
            }
            // Check for insertion in middle
            else if( compare(node, prev_node->next)==0 ) {
                node->next = prev_node->next;
                prev_node->next = node;
                break;
            }

            // Update pointer
            prev_node = prev_node->next;
        }
    }

    return head;
}

// Prints the current ToDo list.
void print_list( TDnode* head, TDnode* current, int toggle )
{
    if( head != NULL ){
        TDnode* next_node = head;
        char* class;
    
        printf("\n\n");
        if( toggle == 0 ){
            while( next_node != NULL ){
                if( next_node == current){
                    printf( "->" );
                }
      
                else{
                    printf( "  " );
                }

                if( next_node->class == 1 ){
                   class = "H";
                }
            
                else if( next_node->class == 2 ){
                    class = "M";
                }
         
                else if( next_node->class == 3 ){
                    class = "L";
                }
         
                else if( next_node->class == 4 ){
                    class = "C";
                }
      
                printf( "%02d/%02d/%02d ", next_node->date.day, next_node->date.month, next_node->date.year );
                printf( "%s %s\n", class, next_node->task );
                next_node = next_node->next;
            }
        }
   
        if( toggle == 1 ){
            if( current->class == 1 ){
                class = "High";
            }
      
            else if( current->class == 2 ){
                class = "Medium";
            }
      
            else if( current->class == 3 ){
                class = "Low";
            }
      
            else if( current->class == 4 ){
                class = "Completed";
            }
      
            printf( "Task:  %s\nDate:  %02d/%02d/%02d\n", current->task, current->date.day, current->date.month, current->date.year );
            printf( "Class: %s\nNotes: %s\n", class, current->notes );
        }
        printf("\n");
    }
}

/**********************************************************************
*   STAGE 3 - Navigating the list
**********************************************************************/
// Move forward
TDnode* forward( TDnode* head, TDnode* current )
{
    if( head != NULL && current->next != NULL ){
        current = current->next;
    }
    
    return current;
}

// Move back
TDnode* back( TDnode* head, TDnode* current )
{
    if( head != NULL && current != head ){
        TDnode* prev_node = head;
        
        while( prev_node->next != current ){
            prev_node = prev_node->next;
        }
                    
        current = prev_node;
    }

    return current;   
}
/**********************************************************************
*   STAGE 4 - Removing or Changing items
**********************************************************************/
// Remove item
TDnode* remove_node( TDnode* head, TDnode* current )
{  
    if( head != NULL ) {
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
    return head ;
}

TDnode *change_task( TDnode* current )
{
    if( current != NULL ){
        current->task = get_task();
    }
           
    return current;
}

TDnode *change_notes( TDnode* current )
{
    if( current != NULL ){
        current->notes = get_notes(); 
    }
      
    return current;
}

TDnode *change_date( TDnode* head, TDnode* current )
{
    if( current != NULL ){
        head = remove_node( head, current );
        get_date( &current->date );
        head = add_node( head, current );
    }
     
    return head;
}

TDnode *change_class( TDnode* head, TDnode* current )
{
    if( current != NULL ){
        head = remove_node( head, current );
        current->class = get_class();
        head = add_node( head, current );
    }
     
    return head;
}

/**********************************************************************
*   STAGE 5 - Searching the list
**********************************************************************/
// Store search text into a string
char *store_text( void )
{
    char buffer[MAX_TEXT];
    char *search;
    int length;
    int ch;
    int i;

    // prompt user for search text
    printf( "Search text: " );
    // skip any intial newline character
    if(( ch = getchar()) == '\n' ) {
        ch = getchar();
    }
    // read text initially into a buffer
    i = 0;
    while((i < MAX_TEXT)&&(ch != '\n')&&(ch != EOF)) {
        buffer[i++] = ch;
        ch = getchar();
    }
    // allocate just enough space to store the string
    length = i;
    search = (char *)malloc((length + 1)*sizeof(char));
    if( search == NULL ) {
        printf("Error: could not allocate memory.\n");
        exit( 1 );
    }
    // copy text from buffer into new string
    for( i = 0; i < length; i++ ) {
        search[i] = buffer[i];
    } 
    search[i] = '\0'; // add end-of-string marker

    return( search );
}

// Search list for text in Task or Notes field
void search( TDnode *head, char *search_text )
{
    TDnode *node = head;
    char ori_task[MAX_LINE];
    char ori_notes[MAX_TEXT];
    char *task = NULL;
    char *notes = NULL;
    
    while( node != NULL ){
    
        strcpy( ori_task, node->task );
        strcpy( ori_notes, node->notes);  
        
        task = search_task( search_text, node->task );
        notes = search_notes( search_text, node->notes );
    
        if( task != NULL || notes != NULL ){
            if( task != NULL ){
                node->task = task;
            }
            
            if( notes != NULL ){
                node->notes = notes;
            }
            
            print_list( node, node, 1 );
            
            strcpy( node->task, ori_task );
            strcpy( node->notes, ori_notes );            
        }
                        
        node = node->next;
    }
}

char *search_task( char *search_text, char *task )
{
    char *p = strcasestr( task, search_text );
    
    int i;
    
    if( p != NULL ){
        for( i=0; i<strlen(search_text); i++ ){
            if( islower( p[i] ) > 0 ){
                p[i] = toupper( p[i] );
            }
        }
        
        char *next = p+strlen(search_text);
        
        if( search_task( search_text, next ) == NULL ){
            return task;
        }
        
        else{        
            return task;
        }            
    }
    
    else{
        return p;
    }
}

char *search_notes( char *search_text, char *notes )
{
    char *p = strcasestr( notes, search_text );
    
    int i;
    
    if( p != NULL ){
        for( i=0; i<strlen(search_text); i++ ){
            if( islower( p[i] ) > 0 ){
                p[i] = toupper( p[i] );
            }
        }
        
        char *next = p+strlen(search_text);
        
        if( search_notes( search_text, next )  == NULL ){
            return notes;
        }
        
        else{        
            return notes;
        }            
    }
    
    return p ;
}


/**********************************************************************
*   STAGE 6 - Undo
**********************************************************************/
// Push a stack node
StackNode* push( TDnode* current, StackNode* head, char command )
{
    StackNode* new_node = (StackNode*)malloc( sizeof( StackNode ));
    if( new_node == NULL ) {
        fprintf( stderr, "Error: memory allocation failed.\n");
        exit( 1 );
    }

    new_node->current = current;
    new_node->command = tolower( command );
    new_node->next    = head;
    
    if( current != NULL ) {
        new_node->data.task  = current->task;
        new_node->data.date  = current->date;
        new_node->data.class = current->class;
        new_node->data.notes = current->notes;
    }

    return new_node;
}

// Pop a stack node
StackNode* pop( StackNode* head )
{
    StackNode* tmp;
    
    if( head != NULL ) {
        tmp = head;
        head = head->next;
        free( tmp );        
    }    
    return head;
}

// Undo
TDnode* undo( StackNode* stack, TDnode* list, TDnode* current )
{
    if( stack->command != '\0' ) {
        int op = stack->command;

        switch( op ) {
            case 'a':
                list = remove_node( list, current );
            break;

            case 'f':
                if( current == stack->next->current ) {
                    return NULL;
                }
                else {
                    current = back( list, current );
                }
            break;
            
            case 'b':
                if( current == stack->next->current ) {
                    return NULL;
                }
                else {
                    current = forward( list, current );
                }
            break;

            case 't':
                list = remove_node( list, current );
                current->task = stack->next->data.task;
                list = add_node( list, current );
            break;

            case 'd':
                list = remove_node( list, current );
                current->date = stack->next->data.date;
                list = add_node( list, current );
            break;

            case 'c':
                list = remove_node( list, current );
                current->class = stack->next->data.class;
                list = add_node( list, current );
            break;

            case 'n':
                list = remove_node( list, current );
                current->notes = stack->next->data.notes;
                list = add_node( list, current );
            break;
            
            default:

            break;
        }
    }

    return list;
}
