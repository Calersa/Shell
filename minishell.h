/*

Authors: Juan Lerma, Cameron Lewis, Justin Magana

Course: COSC 4302 Operating Systems

Assignment: Group Project

Instructor: Bo Sun

Due Date: 12/2/2024, 10:00 AM

Description:
Header file for the shell program, containung function prototypes, macro definitions, and data structure declarations
necessary for building and running the shell. This file provides the interface between the main implementation ('main.c')
and the shell's supporting functions

Requirements:
This header must be included in the main shell source file ('main.c').

Known bugs/Limitations:
None identified at the time of submission

*/
#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LINE_LEN 80				//Maximum length of a command line input
#define MAX_ARGS 64				//Maximum number of arguments a command can have
#define MAX_ARGS_LEN 16			//Maximum length of each argument
#define MAX_PATHS 64			//Maximum numner of directories in the PATH variable
#define MAX_PATH_LEN 96			//Maximum length of a single directory path
#define WHITESPACE " .,\t\n"	//Delimiters to tokenize the input command line

#ifndef NULL
#define NULL 0
#endif

//Command structure
struct command_t{
	char *name;				//Name of command
	int argc;				//Number of arguments provided with the command
	char *argv[MAX_ARGS];	//Array of pointers to argument strings
};

//Function prototypes
void printPrompt();											//Displays the shell prompt
void readCommand(char *buffer);								//Reads a command line input from the user into the provided buffer
int parseCommand(char *cLine, struct command_t *cmd);		//Parses a command line string into a structured format
int parsePath(char *dirs[]);								//Parses the PATH environment variable into an array of directory paths
char *lookupPath(char **argv, char **dirs);					//Searches the directories in PATH for the specified command

#endif
