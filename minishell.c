#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* Author: Joseph Pietroluongo
// PID: 5901749
// I affirm that I wrote this program myself without any help
// from any other people or sources from the internet
// Summary: This program is designed in C language, for the purpose to
// creates two child processes: one to execute 'ls -al' and the
// other to execute ‘grep minishell.c’.
*/
// Formatting: Standard formating, opening curly brace on the right end of the line above with the block begins.


char *cmd1[] = { "/bin/ls","-al", 0 }; 
char *cmd2[] = { "/bin/grep", "minishell.c" , 0 };
void rungiven(int pfd[]); 
void tester(int pfd[]);

int main(int argc, char **argv)
{
	int pid, status; 
	int fd[2];

	pipe(fd); 

	rungiven(fd); 
	tester(fd); 

	close(fd[0]); close(fd[1]); 	

	while ((pid = wait(&status)) != -1)
	{
		fprintf(stderr, "Child's ID is: %d \n",pid);
	}
	exit(0);
}


void rungiven(int pfd[])	
{
	int pid;	

	switch (pid = fork()) 
	{

	case 0: 
		dup2(pfd[1], 1);	
		close(pfd[0]); 		
		execvp(cmd1[0], cmd1);	
		perror(cmd1[0]);	

	default: 
		break;

	case -1:
		perror("Fork");
		exit(1);
	}
}

void tester(int pfd[])	
{
	int pid;

	switch (pid = fork()) 
	{

	case 0: 
		dup2(pfd[0], 0);	
		close(pfd[1]);		
		execvp(cmd2[0], cmd2);	
		perror(cmd2[0]);	

	default: 
		break;

	case -1:
		perror("Fork");
		exit(1);
	}
}