#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Call with input file path\n");
        return -1;
    }
    int maxlen = 100;
    int result = 0;
    char* line = (char*) malloc(sizeof(char) * maxlen);

    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("File not found\n");
        return -1;
    }

    while(fgets(line, maxlen, fp)) {
        // iterate over each character of line
        int min1, max1, min2, max2;
        int flag;

        min1 = min2 = max1 = max2 = flag = 0;

        for(int i = 0; line[i]; i++) {
            if(*(line+i) == '-' || *(line+i) == ',') {
                flag++;
            }
            if(isdigit(*(line + i))) {
                switch (flag) {
                    case 0:
                        min1 = (min1 * 10) + ((*(line+i)) - '0');
                        break;
                    case 1:
                        max1 = (max1 * 10) + (*(line+i) - '0');
                        break;
                    case 2:
                        min2 = (min2 * 10) + (*(line+i) - '0');
                        break;
                    case 3:
                        max2 = (max2 * 10) + (*(line+i) - '0');
                        break;
                    default:
                        break;
                }
            }
        }

        if(min2 >= min1 && max1 >= min2) {
            result++;
        } else if(min1 >= min2 && min1 <= max2) {
            result++;
        }
    }

    printf("result: %d\n", result);

    fclose(fp);
    free(line);

    return 0;
}
