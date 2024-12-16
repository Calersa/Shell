#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include "minishell.h"

void printPrompt(){
	char hostname[HOST_NAME_MAX + 1];
	char cwd[PATH_MAX + 1];

      	gethostname(hostname, sizeof(hostname));

      	if (getcwd(cwd, sizeof(cwd)) != NULL) {
        	printf("%s:%s$ ", hostname, cwd);
        } else {
        	perror("getcwd");
        }
}
void readCommand(char *buffer){
	fgets(buffer, LINE_LEN, stdin);
}
int parseCommand(char *cLine, struct command_t *cmd){
	int argc=0;
	char **clPtr= &cLine;
	argc=0;
	cmd->argv[argc] = (char *) malloc(MAX_ARGS_LEN);

	while(argc < MAX_ARGS-1 && (cmd->argv[argc] = strsep(clPtr, WHITESPACE)) != NULL){
		cmd->argv[++argc] = (char *) malloc(MAX_ARGS_LEN);
	}

	cmd->argc = argc-1;
	cmd->name = (char *) malloc(sizeof(cmd->argv[0]));
	strcpy(cmd->name, cmd->argv[0]);
	return 1;
}
int parsePath(char *dirs[]){
	char *pathEnvVar;
	char *thePath;

	for(int i=0; i<MAX_ARGS; i++){
		dirs[i] = NULL;
	}
	pathEnvVar = (char *) getenv("PATH");
	thePath = (char *) malloc(strlen(pathEnvVar)+1);
	strcpy(thePath, pathEnvVar);
	
	int i=0;
	char *token = strtok(thePath, ":");
	while (token != NULL && i < MAX_PATHS -1){
		dirs[i++]=token;
		token = strtok(NULL, ":");
	}
	dirs[i] = NULL;
	free(thePath);
	return i;
}
char *lookupPath(char **argv, char **dir){
	char *result;
	char pName[MAX_PATH_LEN];

	if(*argv[0] == '/'){
		result = malloc(strlen(argv[0])+1);
		strcpy(result, argv[0]);
		return result;	
	}
	for(int i=0; i<MAX_PATHS; i++){
		snprintf(pName, sizeof(pName), "%s%s", dir[i], argv[0]);
		if(access(pName, X_OK)== 0){
			result = malloc(strlen(pName)+1);
			strcpy(result, pName);
			return result;
		}
	}
	fprintf(stderr, "%s: command not found\n", argv[0]);
	return NULL;	
}
int main(){
	struct command_t cmd;
	char commandLine[LINE_LEN];
	char *pathv[MAX_PATHS];
	pid_t pid;	

	int numPaths = parsePath(pathv);

	while(1){
		printPrompt();
		readCommand(commandLine);
		if (strlen(commandLine) == 0) {
         		continue;
       	 	}
		parseCommand(commandLine, &cmd);
		cmd.name = lookupPath(cmd.argv, pathv);
		if(cmd.name == NULL){
			continue;
		}
	pid=fork();
	if(pid ==0){
		execv(cmd.name, cmd.argv);
		perror("execv");
		exit(EXIT_FAILURE);
	}else if (pid>0){
		waitpid(pid, NULL, 0);
	}
	free(cmd.name);
	}	
	return 0;
}
