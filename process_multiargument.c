#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CMDLEN 80
#define SPACE " "

int main()
{
	int pid;
	int status;
	int i, fd;
	char command[CMDLEN];

	int counter = 0;
	int bg;
	char *str;
	char *argv[100];

	printf( "Program begins.\n" );

	for (;;)
	{
		printf( "Please enter a command: " );
		counter = 0;
		fgets( command, CMDLEN, stdin );
		command[strlen(command)-1] = '\0';

		if ( strcmp(command, "quit") == 0 )
			break;
		argv[0] = strtok(command, SPACE);
		while( (argv[++counter] = strtok(0, SPACE)) != 0 );
		bg = 0;
		if(strcmp(argv[counter-1], "&") == 0){
			argv[counter-1] = NULL;
			bg = 1;
		}
		pid = fork();
		if ( pid < 0 )
		{
			printf( "Error in fork.\n" );
			exit(-1);
		}
		if ( pid != 0 )
		{ 
			waitpid( pid, &status, 0 );
		}
		else
		{
			execvp(argv[0], argv);			
			exit(0);
		}
	}
}
