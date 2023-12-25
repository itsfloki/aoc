#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE 500

int run(char *);

int main() {
    char line[MAX_LINE];

    int result = run(line);

    printf("result = %d\n", result);

    return 0;
}

int run(char *line) {
    int count = 0;
    FILE *fp = fopen("input.txt", "r");
    char nums[2] = {0, 0};

    if(fp == NULL) {
        printf("Not able to read the file\n");
        exit(1);
    }

    while(fgets(line, MAX_LINE, fp)) {
        char *line_cpy = line;
        int flag = 0;

        while(*line_cpy) {
            printf("%c", *line_cpy);
            // if number
            if(isdigit(*line_cpy) && flag == 0) {
                nums[0] = *line_cpy;
                nums[1] = *line_cpy;
                flag = 1;
            }

            if(isdigit(*line_cpy) && flag != 0) {
                nums[1] = *line_cpy;
            }

            line_cpy++;
        }
        count += atoi(nums);

        nums[0] = 0;
        nums[1] = 0;
    }

    fclose(fp);

    return count;
}
