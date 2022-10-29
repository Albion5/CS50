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


int check_char(char symbol, Flags *flags) {
    int res = 1;
    switch (symbol) {
            case 'b': /* Number non empty lines */
              flags->number_non_empty = 1;
              break;
            case 'e': /* equivalent to -vE */
              flags->show_end = 1;
              flags->show_unprintable = 1;
              break;
            case 'E': /* Display $ at end of each line */
              flags->show_end = 1;
              break;
            case 'n': /* Number all output lines */
                flags->number_all = 1;
              break;
            case 's': /* Suppress repeated empty output lines */
              flags->squeeze = 1;
              break;
            case 't': /* equivalent to -vT */
              flags->t = 1;
              break;
            case 'T': /* Display TAB characters as ^I */
              flags->T = 1;
              break;
            default: /* Not valid char */
                res = 0;
    }
    printf("Char is a flag: %d\n", res);
    return res;
}

void check_flag(char *string, Flags *flags) {
    printf("Flag checking\n");
    if (string[0] == '-') {
        if (string[1] == '-') {
            printf("double flag found\n");
        } else {
            printf("single flag found\n");
        }
    } else {
        printf("Flag not found\n");
    }

}

void find_flags(int argc, char *argv[], Flags *flags) {
    printf("Searching for flags\n");
    // Find all the flags
    int error = 0;
    int i = 1;
    while (i < argc) {
        check_flag(argv[i], flags);
        i++;
    }

}

void parse_args(int argc, char *argv[], Flags *flags) {
    printf("Parsing\n");
    // Find all the flags

    find_flags(argc, argv, flags);



    // Find files
    // fd = open(argv[1], O_RDONLY);



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


