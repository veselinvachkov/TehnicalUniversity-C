#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int mainCounter(const char *word);
int secondaryCounter(const char *word);

typedef struct {
    int integers_counts;
    int unsigned_integers;
    int octal_integers;
    int hexadecimal_integers;
    int real;
    int double_numbers;
    int float_numbers;
    int total_numbers;
} NumbersCounts;

NumbersCounts numbersCounts = {0, 0, 0, 0, 0, 0, 0, 0};

#define MAX_WORD_LEN 256

NumbersCounts count_numbers(const char *filename) {

    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Error opening file");
        return numbersCounts;
    }

    char word[MAX_WORD_LEN];
    int index = 0;
    int ch;

    while ((ch = fgetc(f)) != EOF) {
        int state = 0;
        if (ch == ' ' || ch == ',' || ch == '\n' || ch == '\r' || ch == '\t') {
            word[index] = '\0';
            state = mainCounter(word);
            if (state == -1) {
                state = secondaryCounter(word);
            }
            index = 0;
            memset(word, '\0', sizeof(word));

            switch (state) {
                case 1:
                    numbersCounts.integers_counts++;
                    numbersCounts.total_numbers++;
                    break;
                case 2:
                    numbersCounts.unsigned_integers++;
                    numbersCounts.integers_counts++;
                    numbersCounts.total_numbers++;
                    break;
                case 3:
                    numbersCounts.octal_integers++;
                    numbersCounts.integers_counts++;
                    numbersCounts.unsigned_integers++;
                    numbersCounts.total_numbers++;
                    break;
                case 4:
                    numbersCounts.hexadecimal_integers++;
                    numbersCounts.integers_counts++;
                    numbersCounts.unsigned_integers++;
                    numbersCounts.total_numbers++;
                    break;
                case 5:
                    numbersCounts.real++;
                    numbersCounts.total_numbers++;
                    break;
                case 6:
                    numbersCounts.real++;
                    numbersCounts.float_numbers++;
                    numbersCounts.total_numbers++;
                    break;
            }
        }else {
            word[index] = ch;
            index++;
        }
    }

    fclose(f);

    return numbersCounts;
}

int main() {

    NumbersCounts results = count_numbers("veselinvachkov/TehnicalUniversity-C/C_Semester_6/Homework_1/input_1.txt");

    printf("Octal Integer Constants: %d\n", results.octal_integers);
    printf("Hexadecimal Integer Constants: %d\n", results.hexadecimal_integers);
    printf("Unsigned: %d\n", results.unsigned_integers);
    printf("Integer Constants: %d\n", results.integers_counts);
    printf("Floats: %d\n", results.float_numbers);
    printf("Real: %d\n", results.real);
    printf("All numbers: %d\n", results.total_numbers);

    return 0;
}

int mainCounter(const char *word) {
    int i = 0;
    int main_state = 0;
    char prevCh;

    while (1) {
        char ch = word[i];

        switch (main_state) {
            case 0:
                if (ch == '-') {
                    main_state = 1;
                } else if (ch == '+') {
                    main_state = 4;
                } else if (ch >= '1' && ch <= '9') {
                    main_state = 10;
                } else if (ch == '0') {
                    main_state = 15;
                } else {
                    return -1;
                }
                break;
            case 1:
                if (ch >= '1' && ch <= '9') {
                    main_state = 2;
                }else {
                    return -1;
                }
                break;
            case 2:
                if (ch >= '0' && ch <= '9') {
                    main_state = 2;
                } else if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 3;
                } else if (ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 3;
                } else if (ch == '\0') {
                    return 1;
                } else {
                    return -1;
                }
                break;
            case 3:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 28;
                } else if (ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 28;
                } else if (ch == '\0') {
                    return 1;
                } else {
                    return -1;
                }
                break;
            case 4:
                if (ch == '0') {
                    main_state = 5;
                } else if (ch >= '1' && ch <= '9') {
                    main_state = 10;
                } else {
                    return -1;
                }
                break;
            case 5:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 6;
                } else if (ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 6;
                }else if (ch == 'U' || ch == 'u') {
                    main_state = 8;
                } else if (ch == '\0') {
                    return 1;
                } else {
                    return -1;
                }
                break;
            case 6:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 7;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 7;
                }else if (ch == 'U' || ch == 'u') {
                    main_state = 29;
                } else if (ch == '\0') {
                    return 1;
                } else {
                    return -1;
                }
                break;
            case 7:
                if (ch == 'U' || ch == 'u') {
                    main_state = 29;
                } else if (ch == '\0') {
                    return 1;
                } else {
                    return -1;
                }
                break;
            case 8:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 9;
                } else if (ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 9;
                } else if (ch == '\0') {
                    return 2;
                } else {
                    return -1;
                }
                break;
            case 9:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 29;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 29;
                } else if (ch == '\0') {
                    return 2;
                } else {
                    return -1;
                }
                break;
            case 10:
                if (ch >= '0' && ch <= '9') {
                    main_state = 10;
                } else if (ch == 'U' || ch == 'u') {
                    main_state = 11;
                } else if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 13;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 13;
                } else if (ch == '\0') {
                    return 1;
                } else {
                    return -1;
                }
                break;
            case 11:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 12;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 12;
                } else if (ch == '\0') {
                    return 2;
                } else {
                    return -1;
                }
                break;
            case 12:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 29;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 29;
                } else if (ch == '\0') {
                    return 2;
                } else {
                    return -1;
                }
                break;
            case 13:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 14;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 14;
                } else if (ch == 'U' || ch == 'u') {
                    main_state = 29;
                } else if (ch == '\0') {
                    return 1;
                } else {
                    return -1;
                }
                break;
            case 14:
                if (ch == 'U' || ch == 'u') {
                    main_state = 29;
                } else if (ch == '\0') {
                    return 1;
                } else {
                    return -1;
                }
                break;
            case 15:
                if (ch == 'U' || ch == 'u') {
                    main_state = 16;
                } else if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 18;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 18;
                } else if (ch >= '0' && ch <= '7') {
                    main_state = 20;
                } else if (ch == 'x' || ch == 'X') {
                    main_state = 24;
                } else {
                    return -1;
                }
                break;
            case 16:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 17;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 17;
                } else if (ch == '\0') {
                    return 2;
                } else {
                    return -1;
                }
                break;
            case 17:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 29;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 29;
                } else if (ch == '\0') {
                    return 2;
                } else {
                    return -1;
                }
                break;
            case 18:
                if (ch == 'U' || ch == 'u') {
                    main_state = 29;
                } else if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 19;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 19;
                } if (ch == '\0') {
                    return 1;
                } else {
                    return -1;
                }
                break;
            case 19:
                if (ch == 'U' || ch == 'u') {
                    main_state = 29;
                } else if (ch == '\0') {
                    return 1;
                } else {
                    return -1;
                }
                break;
            case 20:
                if (ch >= '0' && ch <= '7') {
                    main_state = 20;
                } else if (ch == 'U' || ch == 'u') {
                    main_state = 21;
                } else if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 23;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 23;
                } else if (ch == '\0') {
                    return 3;
                } else {
                    return -1;
                }
                break;
            case 21:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 22;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 22;
                } else if (ch == '\0') {
                    return 3;
                } else {
                    return -1;
                }
                break;
            case 22:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 30;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 30;
                } else if (ch == '\0') {
                    return 3;
                } else {
                    return -1;
                }
                break;
            case 23:
                if (ch == 'U' || ch == 'u') {
                    main_state = 30;
                } else if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 30;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 30;
                } else if (ch == '\0') {
                    return 3;
                } else {
                    return -1;
                }
                break;
            case 24:
                if (ch >= '0' && ch <= '9'){
                    main_state = 32;
                }else if(ch >= 'a' && ch <= 'f'){
                    main_state = 32;
                }else if(ch >= 'A' && ch <= 'F'){  
                    main_state = 32;
                } else if (ch == '\0') {
                    return 0;
                } else {
                    return -1;
                }
                break;
            case 25:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 26;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 26;
                } else if (ch == '\0') {
                    return 4;
                } else {
                    return -1;
                }
                break;
            case 26:
                if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 31;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 31;
                } else if (ch == '\0') {
                    return 4;
                } else {
                    return -1;
                }
                break;
            case 27:
                if (ch == 'U' || ch == 'u') {
                    main_state = 31;
                } else if (ch == 'L') {
                    if (prevCh == 'l') return 0;
                    main_state = 31;
                } else if(ch == 'l') {
                    if (prevCh == 'L') return 0;
                    main_state = 31;
                } else if (ch == '\0') {
                    return 4;
                } else {
                    return -1;
                }
                break;
            case 28:
                if (ch == '\0') {
                    return 1;
                } else {
                    return -1;
                }
            break;
            case 29:
            if (ch == '\0') {
                return 2;
            } else {
                return -1;
            }
            break;
            case 30:
            if (ch == '\0') {
                return 3;
            } else {
                return -1;
            }
            break;
            case 31:
            if (ch == '\0') {
                return 4;
            } else {
                return -1;
            }
            break;
            case 32:
            if (ch >= '0' && ch <= '9'){
                main_state = 32;
            }else if(ch >= 'a' && ch <= 'f'){
                main_state = 32;
            }else if(ch >= 'A' && ch <= 'F'){  
                main_state = 32;
            } else if (ch == 'U' || ch == 'u') {
                main_state = 25;
            } else if (ch == 'L') {
                if (prevCh == 'l') return 0;
                main_state = 27;
            } else if(ch == 'l') {
                if (prevCh == 'L') return 0;
                main_state = 27;
            } else if (ch == '\0') {
                return 4;
            } else {
                return -1;
            }
            break;
        }
        prevCh = ch;
        i++; 
    }
}

int secondaryCounter(const char *word) {
    int i = 0;
    int secondary_state = 0;

    while (1) {
        char ch = word[i];
        switch (secondary_state) {
            case 0:
                if (ch == '-' || ch == '+') {
                    secondary_state = 1;
                } else if (ch == '0') {
                    secondary_state = 2;
                } else if(ch >= '1' && ch <= '9') {
                    secondary_state = 6;
                } else if(ch == '.') {
                    secondary_state = 7;
                } else {
                    return 0;
                }
            break;
            case 1:
                if (ch == '.') {
                    secondary_state = 7;
                } else if (ch == '0') {
                    secondary_state = 2;
                } else if(ch >= '1' && ch <= '9') {
                    secondary_state = 6;
                }else {
                    return 0;
                }
            break;
            case 2:
                if (ch == 'e' || ch == 'E') {
                    secondary_state = 3;
                } else if(ch == '.') {
                    secondary_state = 8;
                }else {
                    return 0;
                }
            break;
            case 3:
                if (ch == '-' || ch == '+') {
                    secondary_state = 4;
                } else if(ch >= '1' && ch <= '9') {
                    secondary_state = 5;
                }else {
                    return 0;
                }
            break;
            case 4:
                if (ch >= '1' && ch <= '9') {
                    secondary_state = 5;
                }else {
                    return 0;
                }
            break;
            case 5:
                if (ch == 'l' || ch == 'L') {
                    secondary_state = 10;
                }else if(ch == 'f' || ch == 'F') {
                    secondary_state = 9;
                }else if(ch >= '0' && ch <= '9') {
                    secondary_state = 5;
                }else if(ch == '\0') {
                    return 5;
                }else {
                    return 0;
                }
            break;
            case 6:
                if (ch >= '0' && ch <= '9') {
                    secondary_state = 6;
                } else if(ch == 'e' || ch == 'E') {
                    secondary_state = 3;
                }else if(ch == '.') {
                    secondary_state = 8;
                }else {
                    return 0;
                }
            break;
            case 7:
                if (ch >= '0' && ch <= '9') {
                    secondary_state = 8;
                }else {
                    return 0;
                }
            break;
            case 8:
                if(ch >= '0' && ch <= '9') {
                    secondary_state = 8;
                }else if(ch == 'e' || ch == 'E') {
                    secondary_state = 3;
                }else if(ch == 'f' || ch == 'F') {
                    secondary_state = 9;
                }else if(ch == 'l' || ch == 'L') {
                    secondary_state = 10;
                }else if(ch == '\0') {
                    return 5;
                }else {
                    return 0;
                }
            break;
            case 9:
                if (ch == '\0') {
                    return 6;
                }
                return 0;
            break;
            case 10:
                if (ch == '\0') {
                    return 5;
                }
                return 0;
            break;
        }
    i++;
    }
    return 0;
}