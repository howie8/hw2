hw2
===

ToDo List Manager

Introduction

Personal Digital Assistants (PDA's) like the iPhone, Android, etc. have become commonplace over the past few years. Along with an address book and calendar, one item of software that is commonly provided with PDA's is a ToDo list (or Task list) manager. ToDo list manager software allows the user to create a list of items that they need to complete and acts as a reminder of outstanding tasks. As items on a ToDo list are completed, they can be marked off or deleted. In this project you are to implement a program which allows the user to add, view and manipulate ToDo items.

Stage 0 - Provided Code
We have provided the program in the directory hw2/src as a base for you to begin the assignment. Notice that it consists of two files hw2.c and tdlist.c, and the header file tdlist.h. Copy these files to your own directory and compile them by typing

gcc -Wall -o hw2 hw2.c tdlist.c

Now run the program. You will be presented with these options:

Enter command (A,F,B,P,L,R,T,D,C,N,S,U,Q, H for Help): 

If you type 'h' for Help, you will see a more detailed list of commands:

 A - Add item
 F - move Forward
 B - move Back
 P - Print item
 L - List items
 R - Remove item
 T - change Task
 D - change Date
 C - change Class
 N - change Notes
 S - Search
 U - Undo
 Q - Quit
 H - Help

Now type 'a' to Add an item. You will be invited to enter the following data:

Task:  (a one-line string)
Date:  (in the format dd/mm/yy)
Class: (H,M,L or C for High, Medium, Low or Completed)
Notes: (free-form text which may extend over several lines)

You signal the end of the "Notes" by typing a dot '.' on a line by itself. When you have finished, type 'q' to Quit.

Stage 1 - Writing a Makefile
Write a Makefile as discussed in Lab 8, so that the program will be re-compiled when you type "make", producing an executable called hw2.

Stage 2 - Adding, checking and listing items
For Stage 2, you will need to make these modifications to the program:

    Write code for the function date_ok() to check whether the date entered actually exists (for example, 29/02/13 does not exist). For simplicity, we use only two digits for the year and thus consider only dates in the current century.

    Complete the coding for the A command so that it links the newly-created node into an ordered linked list. The items should be ordered so that earlier dates are listed before later ones. Items with the same Date should be ordered according to their Class - with "High" items listed first, followed by "Medium", "Low" and "Completed".

    After each new item is added, your program should print the list of all ToDo items, in the following format:

    ->20/09/13 H 1917 Assignment 2
      04/11/13 M grocery shopping

    Each item should occupy one line. The "current item" (i.e. the most recently added one) should be distinguished by the characters "->" at the beginning of the line; the other items should begin their line with two blank spaces. The next 8 characters on the line should contain the date, in the formant dd/mm/yy. Then there should be a blank space, followed by the letter H, M, L or C to indicate the Class of the item, followed by another blank space, followed by the Task itself. 

Stage 3 - Navigating the List
For Stage 3, you will need to implement these commands:

 F - move Forward
 B - move Back
 P - Print item
 L - print List

The F and B commands allow the user to move Forward and Back in the list by changing which item is the "current" item. The F command finds the next item after the current item and makes it the current item. The B command finds the previous item to the current item, and makes it the current item. The F command fails (has no effect) if the current item is the last item in the list; B has no effect if the current item is the first item in the list.

The P and L commands should toggle the program between two different printing "modes". In "L" mode, the entire list of items should be printed as in Stage 2. In "P" mode, only the current item should be printed, but in this format:

Task:  1917 Assignment 2
Date:  20/09/13
Class: High
Notes: get started early;
don't leave it until the last minute!

After each successful A,F,B,P,L,R,T,D,C,N or U command, your program should either print the entire list of items or the current item, depending on the current printing mode.

Stage 4 - Removing or Changing items
For Stage 4 you will need to implement these commands:

 R - Remove item
 T - change Task
 D - change Date
 C - change Class
 N - change Notes

The R command should remove the current item from the list. The new current item should be the next one after the deleted item. If the deleted item was the last item in the list, the previous item (which is now the last item) should become the current item.

The commands T,D,C and N allow the user to change the Task, Date, Class or Notes of an existing item. In each case, the user should be prompted with the name of the field to be changed, and enter it in the same manner as in Stage 2. When the Date or Class of an item is changed, it should be removed from the list and re-inserted in its new position.

If the list is already empty, the commands F,B,R,T,D,C and N should have no effect.
Stage 5 - Searching the list
For Stage 5 you are to implement a search command:

 S - Search items

The S command should:

    a) prompt the user like this:
      Search text: 

    b) scan one line of text into an array of char (until the first newline character is encountered, or the maximum of 128 characters is exceeded)

    c)s earch for all ToDo items containing the search text within its Task or Notes field. Note that the search should NOT be case-sensitive (i.e. the strings "text" and "Text" DO match). For each item where text appears in these fields, print the entire item, in the "P" format described in Stage 3. The search text should be highlighted, wherever it occurs in the Task or Notes field, by converting all lowercase letters to uppercase. Note that the actual contents of these fields should not be modified in any way. If the item is subsequently printed, it should appear as normal. 

Stage 6 - Undo
For Stage 6, you need to implement one final command:

 U - Undo

If the previous command was A,F,B,R,T,D,C or N the U command should undo the previous command and return the list to its prior state. If the previous command was P,L,H,S or U, or if it had no effect, the U command should have no effect. (You do not have to Undo the Undo!)
Sample files and tools
Examples of input files have been provided in the directory hw2/sample.

A compiled solution to the assignment will be provided for you in the executable tools/hw2
Your program should produce exactly the same output as this executable.

Feel free to copy chunks of code from the list.c program, if you find it helpful.

Groups
This assignment may be done individually, or in groups of two students. Each group should send an email to cs1917.hw2@cse by 30 September, indicating the names of the group member(s). We will then assign you a group number. If you intend to do the assignment on your own, please send us an email for that as well. If you are working in a group, you are strongly advised to make use of file sharing tools like Apache Subversion or DropBox (which are safer and more convenient that emailing code back and forth to each other).

Submission
For this project you will need to submit a Makefile as well as program files (.c and .h files).

Once you have been assigned a group number, you should submit by typing

give cs1917 hw2 Makefile *.[ch]

Please ensure that you submit the source files and NOT any binary file (i.e., compiled hw2 or .o files). There is no need to submit the binary file as we will compile your program using your Makefile before testing it via the automarking program. It is therefore VERY IMPORTANT that you include a Makefile in your submission and that, when run with the make command, it will produce a compiled binary file called hw2 which performs exactly as described in the specification.

You can submit as many times as you like - later submissions will overwrite earlier ones, and submissions by one group member will overwrite those of the other group member. You can check that your submission has been received by using the following command:

1917 classrun -check

The submission deadline is Sunday 20 October, 11:59 pm
15% penalty will be applied to the (maximum) mark for every 24 hours late after the deadline.

Additional information may be found in the FAQ and will be considered as part of the specification for the project. Questions relating to the project can also be posted to the MessageBoard on the course Web page.

If you have a question that has not already been answered on the FAQ or the MessageBoard, you can email it to your tutor, or to cs1917.hw2@cse.unsw.edu.au
Marking
This project will be marked on functionality in the first instance, so it is very important that the output of your program be EXACTLY correct. Submissions which score very low on the automarking will be looked at by a human and may receive a few marks, provided the code is well-structured and commented.

Programs that generate compilation errors will receive a very low mark, no matter what other virtues they may have. In general, a program that attempts a substantial part of the job but does that part correctly will receive more marks than one attempting to do the entire job but with many errors. 
