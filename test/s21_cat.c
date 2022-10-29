#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define buf_size 4096

void s21_cat(int fd) {
    char buffer[buf_size];
    int bytes_read = read(fd, buffer, buf_size);
    while (bytes_read > 0) {
        printf("%.*s", bytes_read, buffer);
        bytes_read = read(fd, buffer, buf_size);
    }

}

void parse_args() {
    // Find all the flags
    fd = open(argv[1], O_RDONLY);
    // Find files



}


int main(int argc, char *argv[]) {

    int fd;
    if (argc > 1) {
        parse_args(argc, argv);

    // Mode with args
    ;
        // Stdin mode

        // File mode


    } else {

        // Mode without args
        fd = STDIN_FILENO;
        s21_cat(fd);
    }
    return 0;
}


