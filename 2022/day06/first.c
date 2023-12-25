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
                int flag = 0;
                for(int i = 0; i < 4; i++) {
                    for(int j = 0; j < 4; j++) {
                        if(i == j) continue;

                        if(packets[i] == packets[j]) {
                            flag = 0;
                            break;
                        } else {
                            flag = 1;
                        }
                    }
                    if(flag == 0) break;
                }

                if(flag == 1) {
                    printf("result: %d\n", i+1);
                    break;
                }
            }
        }
    }

    fclose(fp);
    free(line);

    return 0;
}
