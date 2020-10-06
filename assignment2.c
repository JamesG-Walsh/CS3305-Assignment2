#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Reading and writing end of the pipe
#define READ_END 0
#define WRITE_END 1

int main(int argc, char **argv)
{

	/*************************************** command line arguments ***************************************
		To compile assignment2.c: gcc assignment2.c -o assignment2
		To run your program: ./assignment2 "CS" "3305" " is fun!"
		argv[0] = "./assignment2"
		argv[1] = "CS"
		argv[2] = "3305"
		argv[3] = " is fun!"

		Number of arguments (argc) = 4

		In this assignment, the parent process reads argv[1] and the child process reads argv[2] and argv[3]
		e.g. In the parent process: char *x = argv[1];
	*******************************************************************************************************/

	// If the user does not pass X, Y and Z, the program will terminate
	if (argc != 4)
	{
		printf("Invalid arguments\n");
		exit(0);
	}

	/*
	// You must insert the following into your code (Replace zeros with the appropriate values/variables)
	printf("A pipe is created for communication between parent (PID %d) and child\n", 0);
	printf("parent (PID %d) created a child (PID %d)\n", 0, 0);
	printf("parent (PID %d) receives X = \"%s\" from the user\n", 0, 0);
	printf("child (PID %d) receives Y = \"%s\" and Z = \"%s\" from the user\n", 0, 0, 0);
	printf("child (PID %d) concatenates Y and Z to generate Y'= %s\n", 0, 0);
	printf("child (PID %d) writes Y' into the pipe\n", 0);
	printf("parent (PID %d) reads Y' from the pipe (Y' = \"%s\")\n", 0, 0);
	printf("parent (PID %d) concatenates X and Y' to generate the string: %s\n", 0, 0);
	*/
	// Note: You do not need to implement a function to concatenate two strings. "string.h" header file has been included



	/***************************************************************************************************
	 * 										   YOUR CODE GOES HERE	
	 * CS305A - Assignment 2
	 * James Walsh - jwalsh57 - 250481718
	 ***************************************************************************************************/
	int port[2];
	pid_t forking_pid, parent_pid, child_pid;

	char x[80];
	strcpy(x, argv[1]);

	char y[80];
	strcpy(y, argv[2]);

	char z[80];
	strcpy(z, argv[3]);

	if (pipe(port) < 0)
	{
		perror("pipe error");
		exit(0);
	}
	printf("A pipe is created for communication between parent (PID %d) and child\n", getpid());

	forking_pid = fork();
	if (forking_pid < 0)
	{
		perror("fork error");
		exit(0);
	}

	parent_pid = getpid();

	if(forking_pid > 0) // parent
	{
		child_pid = forking_pid;
		
		printf("parent (PID %d) created a child (PID %d)\n", parent_pid, child_pid);

		printf("parent (PID %d) receives X = \"%s\" from the user\n", parent_pid, x);

		char y_prime[80];

		read(port[READ_END], y_prime, 160);
		printf("parent (PID %d) reads Y' from the pipe (Y' = \"%s\")\n", parent_pid, y_prime);

		strcat(x,y_prime);
		printf("parent (PID %d) concatenates X and Y' to generate the string: %s\n", parent_pid, x);
	}

	if(forking_pid == 0) //child
	{
		child_pid = getpid();

		printf("child (PID %d) receives Y = \"%s\" and Z = \"%s\" from the user\n", child_pid, y, z);

		strcat(y, z);
		printf("child (PID %d) concatenates Y and Z to generate Y'= %s\n", child_pid, y);

		write(port[WRITE_END],y, strlen(y) );
		printf("child (PID %d) writes Y' into the pipe\n", child_pid);
	}
	return 0;
}
