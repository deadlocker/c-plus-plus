#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

// main function
int main( ) {
    /******************************************************************************
    variables declaration
    ******************************************************************************/
    char *p;
    char *split, *command, *cmdArg;
    int path= 0, pathSize, i, arrSize, process = 0;
    pid_t child_pid, parent_pid;
    
    p = getenv("PATH");
    pathSize = strlen(p);
    
    char *pathInfo[pathSize];
    char inputCommand[256];
    char copyStr[256];
    
    /******************************************************************************
    break string
    ******************************************************************************/
    
    printf ("changing %s\n into the array:\n",p);
    split = strtok(p, ":");
    while ( split != NULL ) {
        pathInfo[path++] = split;
        split = strtok(NULL, ":");
    }
    /******************************************************************************
    loop through the path
    *******************************************************************************/
    for (i = 0; i < path; i++) {
        printf("%s\n", pathInfo[i]);
    }
    printf("\n");
    
    /******************************************************************************
    fork and process
    ******************************************************************************/

    for (;;) {
        //prompt user for input 
        printf("Mani ko Shell || quit/exit to quit shell: $ ");
        //read the user command
        fgets(inputCommand, sizeof(inputCommand), stdin);
        //if new line exists sanitize it
        inputCommand[strlen(inputCommand)-1] = '\0';
        //display the command
        printf("\nThe command entered is : %s ", inputCommand);
        printf("\n");
        //compare the command to quit or exit
        //if matches close the program else proceed to the array
        if( strcmp(inputCommand, "quit")== 0 ||strcmp(inputCommand,"exit" )== 0 ) {
            printf("\n Shell program exit successfully");
            exit(0);
            //exit with success
        }else {
            command = strtok(inputCommand, " ");
            cmdArg = strtok(NULL, " ");
            //forking for child
            child_pid = fork();
            if( child_pid == 0 ) {
                for( i = 0; i < path; i++ ) {
                    //copy the string
                    strcpy( copyStr, pathInfo[i] );
                    //Appends a copy of the source string to the destination string
                    strcat( copyStr, "/");
                    strcat( copyStr, command);
                    //creates a new process image from a regular, executable file. 
                    execl(copyStr, command, cmdArg, 0);
                }//end of for loop
                printf("\nThe command \%s was not found.\n", command);
            }else{
                 while((parent_pid = wait(&process)) > 0);  
                 //wait for all child process 
            }
        }//end of else loop
    }//end of for loop
}//end of main function

