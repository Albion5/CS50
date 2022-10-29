#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define buf_size 4096

void s21_cat(int fd) {
    char buffer[buf_size];
    int bytes_read = read(fd, buffer, buf_size);
    while (bytes_read > 0) {
        printf("%.*s", bytes_read, buffer);
        bytes_read = read(fd, buffer, buf_size);
    }

}


int main(int argc, char *argv[]) {

    if (argc > 1) {
    // Mode with args
    ;
        // Stdin mode

        // File mode
    } else {
         // Mode without args
         s21_cat(STDIN_FILENO);
    }
    return 0;
}


