#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 4096

// Function to display file content with optional line numbering
int display_file(const char *filename, int show_line_numbers) {
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    int line_number = 1;
    int at_line_start = 1;

    // Open file for reading
    if (strcmp(filename, "-") == 0) {
        fd = STDIN_FILENO;
    } else {
        fd = open(filename, O_RDONLY);
        if (fd < 0) {
            perror(filename);
            return -1;
        }
    }

    // Read and display content
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (show_line_numbers && at_line_start) {
                printf("%6d  ", line_number++);
                at_line_start = 0;
            }
            putchar(buffer[i]);
            if (buffer[i] == '\n') {
                at_line_start = 1;
            }
        }
    }

    if (bytes_read < 0) {
        perror("read");
        if (fd != STDIN_FILENO) close(fd);
        return -1;
    }

    if (fd != STDIN_FILENO) {
        close(fd);
    }

    return 0;
}

// Function to handle input redirection (cat < filename)
int handle_input_redirection(const char *filename, int show_line_numbers) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror(filename);
        return -1;
    }

    // Redirect stdin to file
    if (dup2(fd, STDIN_FILENO) < 0) {
        perror("dup2");
        close(fd);
        return -1;
    }
    close(fd);

    // Now read from stdin (which is redirected to file)
    return display_file("-", show_line_numbers);
}

// Function to handle output redirection (cat > filename or cat >> filename)
int handle_output_redirection(const char *filename, int append_mode) {
    int fd;
    int flags = O_WRONLY | O_CREAT;

    if (append_mode) {
        flags |= O_APPEND;
    } else {
        flags |= O_TRUNC;
    }

    fd = open(filename, flags, 0644);
    if (fd < 0) {
        perror(filename);
        return -1;
    }

    // Redirect stdout to file
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        close(fd);
        return -1;
    }
    close(fd);

    // Read from stdin and write to stdout (which is redirected to file)
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("write");
            return -1;
        }
    }

    if (bytes_read < 0) {
        perror("read");
        return -1;
    }

    return 0;
}

// Function to handle basic cat (read from stdin)
int handle_stdin() {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("write");
            return -1;
        }
    }

    if (bytes_read < 0) {
        perror("read");
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    int show_line_numbers = 0;
    int arg_start = 1;

    // Check for -n flag
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        show_line_numbers = 1;
        arg_start = 2;
    }

    // Case 1: cat (no arguments) - read from stdin
    if (argc == 1 || (argc == 2 && show_line_numbers)) {
        return handle_stdin();
    }

    // Check for output redirection operators
    for (int i = arg_start; i < argc; i++) {
        // Case 2: cat > filename (output redirection - overwrite)
        if (strcmp(argv[i], ">") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: No filename specified after '>\n");
                return 1;
            }
            return handle_output_redirection(argv[i + 1], 0);
        }

        // Case 3: cat >> filename (output redirection - append)
        if (strcmp(argv[i], ">>") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: No filename specified after '>>\n");
                return 1;
            }
            return handle_output_redirection(argv[i + 1], 1);
        }

        // Case 4: cat < filename (input redirection)
        if (strcmp(argv[i], "<") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: No filename specified after '<\n");
                return 1;
            }
            return handle_input_redirection(argv[i + 1], show_line_numbers);
        }
    }

    // Case 5 & 6: cat filename(s) or cat -n filename(s) - display file(s)
    int exit_status = 0;
    for (int i = arg_start; i < argc; i++) {
        if (display_file(argv[i], show_line_numbers) < 0) {
            exit_status = 1;
        }
    }

    return exit_status;
}
