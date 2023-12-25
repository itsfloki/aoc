#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 4096

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("call with input file path\n");
        return -1;
    }

    char* line = (char*) malloc(sizeof(char) * MAXLINE);
    FILE* fp = fopen(argv[1], "r");

    if(fp == NULL) {
        printf("file not found.\n");
        return -1;
    }

    while(fgets(line, MAXLINE, fp)) {
        char packets[4];
        for(int i = 0; line[i]; i++) {
            packets[i % 4] = line[i];

            // start comparing after 4th iteration
            if(i > 2) {
                if(packets[0] != packets[1] &&
                   packets[0] != packets[2] &&
                   packets[0] != packets[3] &&
                   packets[1] != packets[0] &&
                   packets[1] != packets[2] &&
                   packets[1] != packets[3] &&
                   packets[2] != packets[0] &&
                   packets[2] != packets[1] &&
                   packets[2] != packets[3] &&
                   packets[3] != packets[0] &&
                   packets[3] != packets[1] &&
                   packets[3] != packets[2]
                        ) {
                    printf("%d\n", i+1);
                    break;
                }
            }
        }
    }

    fclose(fp);
    free(line);

    return 0;
}
