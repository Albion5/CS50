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

typedef struct Errors {
    int error_code;
    int error_index;
    char symbol;
    char string[200];
} Errors;


void print_long_flag_error(char *option) {
// flag error
    dprintf(STDERR_FILENO, "%s: %s '%s'", "cat",  "unrecognized option", option);
}

void print_single_flag_error(char option) {
// flag error
    dprintf(STDERR_FILENO, "%s: %s '%c'", "cat",  "--invalid option", option);
}

void print_file_error(char *filename) {
// file error
    dprintf(STDERR_FILENO, "%s: %s: %s", "cat",  filename, "No such file or directory");
}


void print_error(Errors *error) {
    printf("error\n");
    switch (error->error_code) {
        case 1:
          print_single_flag_error(error->symbol);
          break;
        case 2:
          print_long_flag_error(error->string);
          break;
        case 3:
          print_file_error(error->string);
          break;
    }
}

int is_repeated_line(char cur, char fut) {
    return cur == '\n' && fut == '\n';
}


void print_with_flags(char *buffer, int len, Flags *flags) {
    // debug
    // printf("Modified line\n");
    // int len = strlen(buffer);
    char cur_char, fut_char;
    cur_char = buffer[0];
//    int start_line = 1;
    int sq = 0;
    for (int i = 1; i < len; i++) {
//        printf("sq=%d\n", );
        fut_char = buffer[i];
        // Handle s flag
        if ((flags->squeeze) && is_repeated_line(cur_char, fut_char)) {
            sq = 1;
//            start_line = 1;
            ;
        } else {
            if (sq == 1) {
                printf("\n");
                sq = 0;
            }

            if (flags->number_all && (cur_char == '\n' || i == 1)) {
                printf("%6d\t", ++(flags->count));
            }

            printf("%c", cur_char);

        }
        cur_char = fut_char;
        if (i == len -1) {
            printf("%c", cur_char);
        }
    }

}

void s21_cat(FILE *source, int mode, Flags *flags) {
    char buffer[buf_size];
    while (fgets(buffer, buf_size, source)) {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;
        if (mode == 1) {
            print_with_flags(buffer, strlen(buffer), flags);
        } else {
            printf("%s\n", buffer);
        }
    }
    fclose(source);
}


void set_no_error(Errors *error) {
    error->error_code = 0;
}

void set_sflag_error(Errors *error, char option, int index) {
    error->error_code = 1;
    error->error_index = index;
    error->symbol = option;
}

void set_lflag_error(Errors *error, char *option, int index) {
    error->error_code = 2;
    error->error_index = index;
    strcpy(error->string, option);
}
void set_file_error(Errors *error, char *filename, int index) {
    error->error_code = 3;
    error->error_index = index;
    strcpy(error->string, filename);
}


void set_b(Flags *flags) {
    flags->number_non_empty = 1;
    flags->number_all = 0;
}

void set_e(Flags *flags) {
    flags->show_end = 1;
    flags->show_unprintable = 1;
}
void set_E(Flags *flags) {
    flags->show_end = 1;
}

void set_n(Flags *flags) {
    if ((!flags->number_non_empty)) {
        flags->number_all = 1;
    }
}

void set_s(Flags *flags) {
    flags->squeeze = 1;
}

void set_t(Flags *flags) {
    flags->show_tab = 1;
    flags->show_unprintable = 1;
}

void set_T(Flags *flags) {
    flags->show_tab = 1;
}

int check_single_flag(char symbol, Flags *flags, Errors *error, int arg_index) {
    int res = 1;
    switch (symbol) {
            case 'b': /* Number non empty lines */
              set_b(flags);
              break;
            case 'e': /* equivalent to -vE */
              set_e(flags);
              break;
            case 'E': /* Display $ at end of each line */
              set_E(flags);
              break;
            case 'n': /* Number all output lines */
              set_n(flags);
              printf("n flag\n");
              break;
            case 's': /* Suppress repeated empty output lines */
              set_s(flags);
              break;
            case 't': /* equivalent to -vT */
              set_t(flags);
              break;
            case 'T': /* Display TAB characters as ^I */
              set_T(flags);
              break;
            default: /* Not valid char */
              res = 0;
            //   print_single_flag_error(symbol);
            set_sflag_error(error, symbol, arg_index);
    }
    printf("Char is a flag: %d\n", res);
    return res;
}


int check_long_flag(char *string, Flags *flags, Errors *error, int arg_index) {
    int res = 1;
    if (strcmp(string, "--number-nonblank") == 0) {
        set_b(flags);
    } else if (!strcmp(string, "--squeeze-blank")) {
        set_s(flags);
    } else if (!strcmp(string, "--number")) {
        set_n(flags);
    }  else if (strlen(string) != 2) {
        res = 0;
        set_lflag_error(error, string, arg_index);
    }
    printf("Double flag: %d\n", res);
    return res;

}

// Check if a string consists valid flags
// Return 0 if flag error, 1 if only valid flag(s) found, 2 if not a flag
int check_flag(char *string, Flags *flags, Errors *error, int arg_index) {
    printf("Flag checking\n");
    int res = 1;
    if (string[0] == '-') {
        if (string[1] == '-') {
            printf("double flag found\n");
            res = check_long_flag(string, flags, error, arg_index);

        } else {
            printf("single flag found\n");
            int i = 1;
            int len = strlen(string);
            while (i < len && res) {
                res = check_single_flag(string[i], flags, error, arg_index);
                i++;
            }
        }

    } else {
        printf("Flag not found\n");
        res = 2;
    }
    return res;

}

// Find valid flags in command line args and save indexes of args with potential file names
void find_flags(int argc, char *argv[], Flags *flags, int *file_indexes, int *count, Errors *error) {
    printf("Searching for flags\n");
    // Find all the flags
    int stop = 0;
    // Arg's index in argv
    int i = 1;
    // Index in file_indexes
    int file_index = 0;
    // While there are args in argv and stop flag is off
    while ((i < argc) && (stop == 0)) {
        // Check if it's a flag
        int flag = check_flag(argv[i], flags, error, i);
        // If it's not a flag, add arg's index to file_indexes
        if (flag == 2) {
            *(file_indexes + file_index) = i;
            // Increase number of elements in files_indexes
            *count += 1;
            file_index += 1;
        // If it's not a valid flag
        } else if (!flag) {
            // Stop checking flags
            stop = 1;
        }
        // Increase arg's index
        i++;
    }
    // If no error occured, update error struct
    if (stop == 0) {
        set_no_error(error);
    }
}

// Try opening a file, then print out it's original or updated content
int work_with_file(char *filename, Errors *error, int arg_index, Flags *flags) {
    int res = 0;
    // debug
    // printf("file=%s\n", filename);
    FILE *file = fopen(filename, "r");

    // If arg is not a file
    if (file == NULL) {
        res = 0;
        // Check if there was no error with flags during parsing
        if (error->error_code == 0) {
            // Update an error struct
            set_file_error(error, filename, arg_index);
        // If a flag error occured, compare arg's indexes to see which arg occures earlier in argv
        } else if (arg_index < error->error_index) {
            // Update an error struct
            set_file_error(error, filename, arg_index);
        }
    // If arg is opened and there was no error earlier with flags
    } else {
        // If file is opened and no error occured with flags
        if (error->error_code == 0) {
        // debug
        // printf("opened %s\n", filename);
            res = 1;
            //
            s21_cat(file, 1, flags);
        }
        // Close file
        fclose(file);
        // debug
        // printf("closed\n");
    }
    return res;
}

void find_files(char *argv[], Flags *flags, int *file_indexes, int count, Errors *error) {
    printf("Searching for files\n");
    // Find all the flags
    int stop = 0;
    int i = 0;
    int file_index = 0;

    while ((i < count) && (stop == 0)) {
        printf("file %d\n", file_index);
        int index = *(file_indexes + i);
        printf("index=%d\n", index);
        // debug
        //printf("%d\n", index);
        //printf("%s\n", argv[index]);
        stop = work_with_file(argv[index], error, index, flags);

        i++;
    }
    // debug
    // printf("count=%d\n", count);

}

void parse_args(int argc, char *argv[], Flags *flags, Errors *error) {
    printf("Parsing\n");
    int file_indexes[argc];
    int count = 0;
    // Find all the flags
    find_flags(argc, argv, flags, file_indexes, &count, error);

    // Find files
    find_files(argv, flags, file_indexes, count, error);

    // debug
    // printf("error=%d\n",error->error_code);

    // In case of an error during parsing
    if (error->error_code != 0) {
        // Print relevant error to stderr
        print_error(error);

    // In case there were no files found and no error occured
    } else if (count == 0) {
        // Print info from stdin with flags
        printf("Work with stdin with flags\n");
        s21_cat(stdin, 1, flags);
    }

}


int main(int argc, char *argv[]) {

//    int fd;
    Flags flags = {0, 0, 0, 0, 0, 0, 0};
    Errors error;
    if (argc > 1) {
        // int flags_indexes[argc];
        parse_args(argc, argv, &flags, &error);

        // Mode with args
        ;
            // Stdin mode

            // File mode


    } else {

        // Mode without args
        s21_cat(stdin, 0, &flags);
    }
    return 0;
}

