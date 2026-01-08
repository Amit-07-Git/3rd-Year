#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64
#define MAX_PIPES 10

void display_prompt();
char* read_command();
char** parse_command(char *cmd, char *delim);
int count_pipes(char **args);
void execute_command(char **args);
void execute_with_redirection(char **args);
void execute_piped_commands(char **args);
int has_redirection(char **args);

int main() {
    char *input;
    char **args;
    
    while (1) {
        display_prompt();
        input = read_command();
        
        if (input == NULL) {
            printf("\n");
            break;
        }
        
        if (strlen(input) == 0) {
            free(input);
            continue;
        }
        
        args = parse_command(input, " \t\n");
        
        if (args[0] != NULL) {
            execute_command(args);
        }
        
        free(args);
        free(input);
    }
    
    return 0;
}

void display_prompt() {
    char *username = getenv("USER");
    if (username == NULL) username = "user";
    printf("[%s]$ ", username);
    fflush(stdout);
}

char* read_command() {
    char *input = malloc(MAX_INPUT);
    if (input == NULL) {
        perror("malloc");
        exit(1);
    }
    
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        free(input);
        return NULL;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
    }
    
    return input;
}

char** parse_command(char *cmd, char *delim) {
    char **args = malloc(MAX_ARGS * sizeof(char*));
    char *token;
    int i = 0;
    
    if (args == NULL) {
        perror("malloc");
        exit(1);
    }
    
    token = strtok(cmd, delim);
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, delim);
    }
    args[i] = NULL;
    
    return args;
}

int count_pipes(char **args) {
    int count = 0;
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            count++;
        }
    }
    return count;
}

int has_redirection(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0 || strcmp(args[i], ">") == 0) {
            return 1;
        }
    }
    return 0;
}

void execute_command(char **args) {
    if (count_pipes(args) > 0) {
        execute_piped_commands(args);
    } else if (has_redirection(args)) {
        execute_with_redirection(args);
    } else {
        /* Part 1 & 2: Simple command execution with arguments */
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("fork");
            return;
        } else if (pid == 0) {
            execvp(args[0], args);
            perror(args[0]);
            exit(1);
        } else {
            waitpid(pid, NULL, 0);
        }
    }
}

void execute_with_redirection(char **args) {
    /* Part 4: I/O Redirection */
    char *input_file = NULL;
    char *output_file = NULL;
    char *clean_args[MAX_ARGS];
    int j = 0;
    
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0) {
            input_file = args[++i];
        } else if (strcmp(args[i], ">") == 0) {
            output_file = args[++i];
        } else {
            clean_args[j++] = args[i];
        }
    }
    clean_args[j] = NULL;
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return;
    } else if (pid == 0) {
        if (input_file != NULL) {
            int fd_in = open(input_file, O_RDONLY);
            if (fd_in < 0) {
                perror(input_file);
                exit(1);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        
        if (output_file != NULL) {
            int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0) {
                perror(output_file);
                exit(1);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        
        execvp(clean_args[0], clean_args);
        perror(clean_args[0]);
        exit(1);
    } else {
        waitpid(pid, NULL, 0);
    }
}

void execute_piped_commands(char **args) {
    /* Part 3: Pipes and cascading pipes */
    int num_pipes = count_pipes(args);
    char **commands[MAX_PIPES + 1];
    int cmd_idx = 0;
    int arg_idx = 0;
    
    commands[cmd_idx] = malloc(MAX_ARGS * sizeof(char*));
    
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            commands[cmd_idx][arg_idx] = NULL;
            cmd_idx++;
            arg_idx = 0;
            commands[cmd_idx] = malloc(MAX_ARGS * sizeof(char*));
        } else {
            commands[cmd_idx][arg_idx++] = args[i];
        }
    }
    commands[cmd_idx][arg_idx] = NULL;
    int num_commands = cmd_idx + 1;
    
    int pipes[MAX_PIPES][2];
    for (int i = 0; i < num_pipes; i++) {
        if (pipe(pipes[i]) < 0) {
            perror("pipe");
            return;
        }
    }
    
    pid_t pids[MAX_PIPES + 1];
    
    for (int i = 0; i < num_commands; i++) {
        pids[i] = fork();
        
        if (pids[i] < 0) {
            perror("fork");
            return;
        } else if (pids[i] == 0) {
            if (i > 0) {
                dup2(pipes[i-1][0], STDIN_FILENO);
            }
            
            if (i < num_commands - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }
            
            for (int j = 0; j < num_pipes; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            
            execvp(commands[i][0], commands[i]);
            perror(commands[i][0]);
            exit(1);
        }
    }
    
    for (int i = 0; i < num_pipes; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    
    for (int i = 0; i < num_commands; i++) {
        waitpid(pids[i], NULL, 0);
    }
    
    for (int i = 0; i < num_commands; i++) {
        free(commands[i]);
    }
}
