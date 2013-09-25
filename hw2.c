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

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "tdlist.h"

#define MAX_LINE     128
#define MAX_TEXT    4096

void    print_help();
TDnode *get_node(  void );
char   *get_task(  void );
char   *get_notes( void );
int     get_class( void );
void    get_date( Date *d );
int    scan_date( Date *d );
int     date_ok(  Date *d );

/**********************************************************************
   Print the list of commands available to the user,
   and a brief summary of what each command does.
**********************************************************************/
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

/**********************************************************************
   Allocate space for a new ToDo item and get the
   task, date, class and notes from the user.
**********************************************************************/
TDnode * get_node( void )
{
    TDnode * new_node;

    new_node = (TDnode *)malloc( sizeof( TDnode ));
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

/**********************************************************************
   Read one line of text from standard input,
   store it in a string and return a pointer to the string.
**********************************************************************/
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

/**********************************************************************
   Read several lines of text from standard input,
   store them in a string and return a pointer to the string.
**********************************************************************/
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

/**********************************************************************
    Get class of item from user
**********************************************************************/
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

/**********************************************************************
    Get date from standard input; if date is invalid, ask the user to 
    re-enter it.
**********************************************************************/
void get_date( Date *d )
{
  printf("Date:  ");
  while( !scan_date( d ) || !date_ok( d )) {
     printf("Re-enter date in format dd/mm/yy: ");
  }
}

/**********************************************************************
    Scan date in the format dd/mm/yy
**********************************************************************/
int scan_date( Date *d )
{
    char s[MAX_LINE];

    fgets( s, MAX_LINE, stdin );
    return(
        sscanf(s,"%d/%d/%d",&d->day,&d->month,&d->year)==3);
}

/**********************************************************************
    Return 1 if date is valid; 0 otherwise.
**********************************************************************/
int date_ok( Date *d )
{
    int month_length = 0;

    // Initial test
    if (d->day <= 0 || d->day > 31 || d->month <= 0 || d->month > 12 ) {
        return 0;
    }

    // April, June, September, November
    if (d->month == 4||d->month == 6||d->month == 9||d->month == 11) {
        month_length = 30;
    }
    // February
    else if (d->month == 2) {
        // Leap year
        if ( d->year % 4 == 0 && d->year != 0 ) {
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


// INSERT NEW FUNCTIONS, AS APPROPRIATE

/**********************************************************************
    MAIN FUNCTION
**********************************************************************/

int main( void )
{
    TDnode *list = NULL;
    //TDnode *node;
    int ch;
    int op;

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

            case 'a': case 'A': // Add item
                //node = get_node();
                // INSERT CODE HERE
            break;

            case 'f': case 'F': // move Forward
            
            break;

            case 'b': case 'B': // move Back
        
            break;

            case 'p': case 'P': // Print item

            break;

            case 'l': case 'L': // List items

            break;

            case 'r': case 'R': // Remove item

            break;

            case 't': case 'T': // change Task

            break;

            case 'd': case 'D': // change Date

            break;

            case 'c': case 'C': // change Class

            break;

            case 'n': case 'N': // change Notes

            break;

            case 's': case 'S': // Search
        
            break;

            case 'u': case 'U': // Undo

            break;

            case 'h': case 'H': // Help
                print_help();
            break;

            case 'q': case 'Q': // Quit
                free_list( list );
                printf("Bye!\n");
            return 0;

        }
    }

  return 0;
}
