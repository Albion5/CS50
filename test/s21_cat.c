#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define buf_size 4096

typedef struct Flags {
    int number_all;
    int number_non_empty;
    int show_tab;
    int show_end;
    int show_unprintable;
    int squeeze;
    int count;
} Flags;

void s21_cat(int fd) {
    char buffer[buf_size];
    int bytes_read = read(fd, buffer, buf_size);
    while (bytes_read > 0) {
        printf("%.*s", bytes_read, buffer);
        bytes_read = read(fd, buffer, buf_size);
    }

}

void parse_args(int argc, char *argv[], Flags *flags) {
    // Find all the flags




    // Find files
    // fd = open(argv[1], O_RDONLY);
    printf("Parsing\n");
    find_flags();


}


int main(int argc, char *argv[]) {

    int fd;
    if (argc > 1) {
        Flags flags = {0, 0, 0, 0, 0, 0, 0};
        parse_args(argc, argv, &flags);

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


