#include <stdio.h>
#include <string.h>

// static const char pos_fl[][SIZE] = {
//     "-b", "--number-nonblank", "-e", "-E", "-n",  "--number",
//     "-s", "--squeeze-blank",   "-t", "-T", "NULL"};

typedef struct Flags {
    int b;
    int e;
    int E;
    int n;
    int s;
    int t;
    int T;
    int count;
} Flags;

// typedef struct Data {
//     int empty_lines_count;
//     int e;
//     int E;
//     int n;
// } Data;

int check_double(const char *string, Flags *flags);
int check_flags(int n, char **args, Flags *flags, int *end);
int check_string(const char *string, Flags *flags);
int check_char(char symbol, Flags *flags);
void initialize_flags(Flags* flags);
void s21_cat_stdin(Flags *flags);
int s21_cat_files(const char *filename, Flags *flags);
void work_with_file(FILE *file, Flags *flags);
void handle_e(char *buffer, Flags *flags, int len);
void handle_flags(char *buffer, Flags *flags, int len);
int not_empty_line(const char* line) ;
void handle_b(char *buffer, Flags *flags);
void handle_n(char *buffer, Flags *flags);
void handle_t(char *buffer, Flags *flags, int len);
void printout_content(char *buffer, Flags *flags, int len);
// void handle_n(int* ordinal);


int main(int argc, char* argv[]) {
    int res = 0;
    Flags *flags;
//    initialize_flags(flags);
    // printf("%d %d\n", flags->b, flags->e);
    int index;
    if (check_flags(argc, argv, flags, &index)) {
        printf("\n");
        printf("%d %d\n", index, argc);
        if (index == argc) {
            printf("work with stdin\n");
            s21_cat_stdin(flags);
        } else {
            while (index <= argc - 1) {
                printf("handle new file\n");
                s21_cat_files(argv[index], flags);
                index++;
            }
//            printf("here\n");
        }

    } else {
        res = 1;
        for (int i = 0; i < argc; i++) {
            printf("%s \n", argv[i]);
        }
        fprintf(stderr, "Usage: cat [OPTION] [FILE]\n");
    }
    return res;
}

int check_flags(int n, char **args, Flags *flags, int *end) {
    int res = 1;
    int stop = 0;
    int i = 1;
    int temp;
    *end = i;
    while (i < n && stop == 0) {
        temp = check_string(args[i], flags);
        // if (!temp) {
        //     stop = 1;
        // }
        if (temp == 2) {
            stop = 2;
            *end == i;
        } else if (temp == 0) {
            stop = 1;
            *end == n;
        } else {
            *end += 1;
        }
        i++;
    }
    if (stop == 1) {
        res = 0;
    }

    printf("Flags are valid: %d\n", res);
    return res;
}

int check_double(const char *string, Flags *flags) {
    int res = 1;
    if (!strcmp(string, "--number-nonblank")) {
        flags->b = 1;
    } else if (!strcmp(string, "--squeeze-blank")) {
        flags->s = 1;
    } else if (!strcmp(string, "--number")) {
        flags->n = 1;
    }  else if (strlen(string) != 2) {
        res = 0;
    }
    printf("Double flag: %d\n", res);
    return res;

}

int check_string(const char *string, Flags *flags) {
    int res = 1;
    int stop = 0;
    if (string[0] == '-') {
        int len = strlen(string);
        int i = 1;
        while (!stop && i < len) {
            if (string[i] == '-' && len != 1) {
                res = check_double(string, flags);
                stop = 1;
            } else {
                res = check_char(string[i], flags);
                stop = !res;
            }
            i++;
        }
    } else {
        res = 2;
    }
    printf("String consists valid flags: %d\n", res);
    return res;

}

int check_char(char symbol, Flags *flags) {
    int res = 1;
    switch (symbol) {
            case 'b': /* Number non empty lines */
              flags->b = 1;
              break;
            case 'e': /* equivalent to -vE */
              flags->e = 1;
              break;
            case 'E': /* Display $ at end of each line */
              flags->E = 1;
              break;
            case 'n': /* Number all output lines */
              flags->n = 1;
              break;
            case 's': /* Suppress repeated empty output lines */
              flags->s = 1;
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



void initialize_flags(Flags* flags) {
    flags->b = 0;
    flags->e = 0;
    flags->E = 0;
    flags->n = 0;
    flags->s = 0;
    flags->t = 0;
    flags->T = 0;
    flags->count = 0;
}

void s21_cat_stdin(Flags *flags) {
    int buffer_size = 4096;
    char buffer[buffer_size];
    while (fgets(buffer, buffer_size, stdin)) {
        buffer[strlen(buffer) - 1] = '\0';
        fprintf(stdout, "%s\n", buffer);
    }
}

int s21_cat_files(const char *filename, Flags *flags) {
    flags->count = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        printf("File exists\n");
        work_with_file(f, flags);
        fclose(f);
    } else {
        fprintf(stderr, "cat: %s: No such file or directory\n", filename);
    }
}

void work_with_file(FILE *file, Flags *flags) {
    //printf("b=%d e=%d E=%d n=%d, s=%d, t=%d, T=%d", flags->b, flags->e, flags->E, flags->n, flags->s, flags->t, flags->T);
    int buffer_size = 4096;
    char buffer[buffer_size];
    //flags->count = 0;
    while (fgets(buffer, buffer_size, file)) {
        // handle_e();
        int len = strlen(buffer);
        //buffer[len - 1] = '\0';
        handle_flags(buffer, flags, len);
        printout_content(buffer, flags, len);

    }
}

void handle_flags(char *buffer, Flags *flags, int len) {
    // Data *data;
    int empty = 0;
    //printf("For every line handle flags\n");
    // if flags->b == 1 && strcmp()
    handle_b(buffer, flags);
    handle_n(buffer, flags);
    //handle_e(buffer, flags, len);
    // handle_n();
    //printf("%d\n", not_empty_line(buffer));
}

void handle_e(char *buffer, Flags *flags, int len) {
    // if (is_empty_line(buffer) != 0) {
    if (flags->e) {
        buffer[len - 1] = '$';
    }
    // }
}
void handle_b(char *buffer, Flags *flags) {
    if ((flags->b) && (not_empty_line(buffer))) {
        // flags->count++;
        printf("%6d\t", ++(flags->count));
    }
}

void handle_n(char *buffer, Flags *flags) {
    if ((flags->n && !(flags->b))) {
        // flags->count++;
        printf("%6d\t", ++(flags->count));
    }
}

void handle_t(char *buffer, Flags *flags, int len) {
    if ((flags->T)) {
        // char c;
        for (int i = 0; i < len; i++) {
            if (buffer[i] == '\t') {
                buffer[i] = '^';
            }
        }
        // flags->count++;
        // printf("%6d\t", ++(flags->count));
    }
}

// void handle_n(int* ordinal) {
//     printf("%6d\t", *ordinal);
//     ++*ordinal;
// }

int not_empty_line(const char* line) {
    return strcmp(line, "\n");
}

void printout_content(char *buffer, Flags *flags, int len) {
    //printf("%d\n", len);
    for (int i = 0; i < len; i++) {
        if ((flags->T) && (buffer[i] == '\t')) {
            printf("^l");
        } else {
            if ((flags->e) && (!not_empty_line(buffer))) {
                printf("$");
            } else if ((flags->e) && (buffer[i] == '\n')) {
                printf("$");
            }
            printf("%c", buffer[i]);
        }
//        if ((flags->e)  && (i == len - 2)) {
//            printf("$");
//        }
    }


// unprintable
    // if (c >= 0 && c <= 32) {
    //     printf("^%c", c + 64);
    // }


    // handle_t(buffer, flags, len);
    // fprintf(stdout, "%s", buffer);
}
