/**********************************************************************
*   hw2.c
*   Chetan Sahai - z3288822
*   Haoxiang Fei - z3464323
*
*   COMP1917 Computing 1
*   Assignment 2: ToDo List Manager
*
*   UNSW Session 2, 2013
**********************************************************************/

#include "tdlist.h"

/**********************************************************************
*   STAGE 0 - Provided Code   
**********************************************************************/
// Print the list of commands available to the user, and a brief 
// summary of what each command does.
void print_help()
{
    printf("\n");
    printf(" A - Add item\n" );
    printf(" F - move Forward\n" );
    printf(" B - move Back\n" );
    printf(" P - Print item\n" );
    printf(" L - List items\n" );
    printf(" R - Remove item\n");
    printf(" T - change Task\n");
    printf(" D - change Date\n");
    printf(" C - change Class\n");
    printf(" N - change Notes\n");
    printf(" S - Search\n");
    printf(" U - Undo\n");
    printf(" Q - Quit\n");
    printf(" H - Help\n");
    printf("\n");
}


// Allocate space for a new ToDo item and get the task, date, class and 
// notes from the user.
TDnode * get_node( void )
{
    TDnode* new_node;

    new_node = (TDnode*)malloc( sizeof( TDnode ));
    if( new_node == NULL ) {
        printf("Error: could not allocate memory.\n");
        exit( 1 );
    }

    printf("\n");
    new_node->task = get_task();
    get_date( &new_node->date );
    new_node->class = get_class();
    new_node->notes = get_notes();

    return( new_node );
}


// Read one line of text from standard input, store it in a string and 
// return a pointer to the string.
char * get_task( void )
{
    char buffer[MAX_TEXT];
    char *task;
    int length;
    int ch;
    int i;

    // prompt user for input
    printf( "Task:  " );
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
    task = (char *)malloc((length + 1)*sizeof(char));
    if( task == NULL ) {
        printf("Error: could not allocate memory.\n");
        exit( 1 );
    }
    // copy text from buffer into new string
    for( i = 0; i < length; i++ ) {
        task[i] = buffer[i];
    } 
    task[i] = '\0'; // add end-of-string marker

    return( task );
}


// Read several lines of text from standard input, store them in a 
// string and return a pointer to the string.
char * get_notes( void )
{
    char buffer[MAX_TEXT];
    char *notes;
    int length;
    int ch;
    int i;

    printf("Notes: ");
    ch = getchar();
    i = 0;

    while(( i < MAX_TEXT )&&( ch != EOF )) {
        buffer[i++] = ch;
        ch = getchar();

        // Stop when you encounter a dot on a line by itself
        if(( i > 1 )&&( ch == '\n' )&&( buffer[i-1] == '.' )
                                 &&( buffer[i-2] == '\n')) {
            ch = EOF;
            i  = i - 2; // Strip off the dot and newlines
        }
    }
    length = i;

    // Allocate just enough space to store the string
    notes = (char *)malloc((length+1)*sizeof(char));
    if( notes == NULL ) {
        printf("Error: could not allocate memory.\n");
        exit( 1 );
    }
    // Copy text from buffer to new string
    for( i = 0; i < length; i++ ) {
        notes[i] = buffer[i];
    }
    notes[i] = '\0'; // Add end-of-string marker

    return( notes );
}


// Get class of item from user
int get_class( void )
{
    char s[MAX_LINE];
    int class = 0;
    int i;

    printf("Class: ");           // prompt user
    fgets( s, MAX_LINE, stdin ); // scan a line of input

    // Keep scanning until class is successfully entered
    while( class == 0 ) {

        // Scan input for first non-space character
        for( i=0;( i<MAX_LINE )&&( isspace(s[i])); i++ )
            ;

        switch( s[i] ) {
            case 'h': case 'H':  // High
                class = 1;
            break;

            case 'm': case 'M':  // Medium
                class = 2;
            break;

            case 'l': case 'L':  // Low
                class = 3;
            break;

            case 'c': case 'C':  // Completed
                class = 4;
            break;
        }

        if( class == 0 ) {
            printf("Enter H,M,L or C: ");
            fgets( s, MAX_LINE, stdin );
        }
    }

    return( class );
}

// Get date from standard input; if date is invalid, ask the user to 
// re-enter it.
void get_date( Date* d )
{
  printf("Date:  ");
  while( !scan_date( d ) || !date_ok( d )) {
     printf("Re-enter date in format dd/mm/yy: ");
  }
}

// Scan date in the format dd/mm/yy
int scan_date( Date* d )
{
    char s[MAX_LINE];

    fgets( s, MAX_LINE, stdin );
    return(
        sscanf(s,"%d/%d/%d",&d->day,&d->month,&d->year)==3);
}

/**********************************************************************
*   MAIN FUNCTION
**********************************************************************/
int main( void )
{
    StackNode* stack = NULL;
    TDnode* list = NULL;
    TDnode* node = NULL;
    int ch;
    int op;
    int toggle = 0;
    TDnode* current = list;
    char *search_text;

    stack = push( current, stack, '\0' );

    // enter a loop, reading and executing commands from the user
    while( 1 ) {

        printf("Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): ");
        ch = getchar();

        while( !isalpha(ch) &&( ch != '\n' )) {
            ch = getchar();
        }

        op = ch;

        // Skip the rest of the line until newline is encountered
        while( ch != '\n' ) {
            ch = getchar();
        }

        switch( op ) {
            /**********************************************************
            * Add item
            **********************************************************/
            case 'a': case 'A':
                node = get_node();
                node->next = NULL;

                list = add_node( list, node );

                current = node;
                stack = push( current, stack, op );
                print_list( list, current, toggle );
                
            break;

            /**********************************************************
            * move Forward
            **********************************************************/
            case 'f': case 'F':
                if(current != forward( list, current )) {
                    current = forward( list, current );
                    print_list( list, current, toggle );
                };
                stack = push( current, stack, op );
            break;

            /**********************************************************
            * move Back
            **********************************************************/
            case 'b': case 'B':
                if(current != back( list, current )) {
                    current = back( list, current );
                    print_list( list, current, toggle );
                };
                stack = push( current, stack, op );
            break;

            /**********************************************************
            * Print item
            **********************************************************/
            case 'p': case 'P':
               toggle = 1;
               stack = push( current, stack, op );
               print_list( list, current, toggle );
            break;

            /**********************************************************
            * List items
            **********************************************************/
            case 'l': case 'L':
               toggle = 0;
               stack = push( current, stack, op );
               print_list( list, current, toggle );
            break;

            /**********************************************************
            * Remove item
            **********************************************************/
            case 'r': case 'R':
                list = remove_node( list, current );
                TDnode* tmp = current;
                if( list == NULL ){
                    current = NULL;
                }
        
                else if( current->next == NULL ){
                    TDnode* prev_node = list;
        
                    while( prev_node->next != NULL ){
                        prev_node = prev_node->next;
                    }
                    
                    current = prev_node;
                }
                
                else{
                    current = current->next;
                }
                free( tmp );

                stack = push( current, stack, op );
                print_list( list, current, toggle );
                
            break;

            /**********************************************************
            * change Task
            **********************************************************/
            case 't': case 'T':              
                current = change_task( current );
		        stack = push( current, stack, op );                
                print_list( list, current, toggle );
            break;

            /**********************************************************
            * change Date
            **********************************************************/
            case 'd': case 'D':
                list = change_date( list, current );  
                stack = push( current, stack, op );           
                print_list( list, current, toggle );
            break;

            /**********************************************************
            * change Class
            **********************************************************/
            case 'c': case 'C':                
                list = change_class( list, current );
                stack = push( current, stack, op );             
                print_list( list, current, toggle );
            break;

            /**********************************************************
            * change Notes
            **********************************************************/
            case 'n': case 'N':
                current = change_notes( current );
                stack = push( current, stack, op );                
                print_list( list, current, toggle );
            break;

            /**********************************************************
            * Search
            **********************************************************/
             case 's': case 'S':                    
                search_text = store_text();
                
                search( list, search_text );
            break;

            /**********************************************************
            * Undo
            **********************************************************/
            case 'u': case 'U':
                if( list != NULL ){
                    TDnode* undone = undo( stack, list, current );
                    if( undone == NULL ) {
                        stack = pop( stack );
                        current = stack->current;
                    }
                    else {                    
                        list = undone;
                        if( stack->command == 'r' ) {
                            TDnode* new_node = (TDnode*)malloc(sizeof(TDnode));

                            new_node->task = stack->next->data.task;
                            new_node->date = stack->next->data.date;
                            new_node->class = stack->next->data.class;
                            new_node->notes = stack->next->data.notes;

                            list = add_node( list, new_node );
                            current = new_node;

                            stack = pop( stack );
                        }
                        else if( stack->command == 'a' ) {
                            stack = pop( stack );
                            TDnode* tmp = current;
                            current = stack->current;
                            free( tmp->notes );
                            free( tmp->task );
                            free( tmp );
                        }
                        else {
                            stack = pop( stack );
                            current = stack->current;
                        }
                        print_list( list, current, toggle );
                    }
                }
            break;

            /**********************************************************
            * Help
            **********************************************************/
            case 'h': case 'H': // Help
                print_help();
                stack = push( current, stack, op );
            break;

            /**********************************************************
            * Quit
            **********************************************************/
            case 'q': case 'Q': // Quit
                free_list( list );
                free_stack( stack );
                printf("Bye!\n");
            return 0;

        }
    }

    return 0;
}
