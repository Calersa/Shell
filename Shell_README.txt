
# Minimal Shell (main.c)

main.c is a basic Unix-like shell written in C. It allows users to execute commands, change directories, print the working directory, and exit the shell. The shell includes fundamental command parsing, environment variable handling, and process management functionality.


## Features 
1. Custom Shell Prompt: Displays the current hostname, directory, and a $ character.
2. Built-in Commands:
 * cd: Change the current working directory.
* pwd: Print the current working directory.
* exit: Exit the shell.
3. Path Resolution: Resolves commands using the PATH environment variable.
4. Command Execution: Executes commands via execv in child processes.
5. Error Handling: Handles errors like invalid commands or missing arguments.
## Requirements
1. A Unix-based operating system (Linux or macOS).
2. GCC or any compatible C compiler.
## Installation 
1. Clone the repository:
git clone <repository-url>

2. Navigate to the project directory:
cd minishell

3. Compile the program:
gcc -o shell main.c
## Usage
1. Run the shell:
./shell 

2. Enter commands as you would in a typical Unix shell. Examples:
* Navigate to a directory: 
  cd /path/to/directory

* Print the current working directory:
  pwd

* Execute external commands: ls -l

* Exit the shell:exit

## Shell Prompt
The prompt is displayed in the format:

<hostname>:<current_directory>$
## Command Execution
1. User input is read and parsed into tokens.
2. Internal commands (cd, pwd, exit) are handled directly.
3. External commands are searched for in the directories specified by the PATH environment variable. If found, they are executed in a child process.
## Error Handling 
* Invalid commands or arguments print error messages without crashing the shell.
* Memory allocated for command arguments is freed to avoid leaks.
## Known Limitations 
* Does not handle advanced shell features like piping (|), input/output redirection, or background processes (&).
* Limited to a maximum number of arguments and directories (defined by MAX_ARGS and MAX_PATHS).
## Future Improvements
* Add support for input/output redirection and pipelines.
* Implement job control for background processes.
* Enhance error reporting for more clarity.
## Authors

- Cameron Lewis 
- Juan Lerma 
- Justin Magana
