// ref: https://github.com/callmeMaevey/Advent2023/blob/main/1/1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char getFirst(char *line) {
    char retVal = '\0';
    int offset = 0;
    while (offset < strlen(line) && retVal == '\0') {
        if ( isdigit( *(line + offset) )) {
            retVal = line[offset];
        }
        offset++;
    }
    return retVal;
}

char getLast(char *line) {
    char retVal = '\0';
    int offset = strlen(line);
    while (offset > 0 && retVal == '\0') {
        --offset;
        if ( isdigit( *(line + offset) )) {
            retVal = line[offset];
        }
    }
    return retVal;
}

int main(int argc, char** argv) {
    
    if(argc < 2){ printf("call with path as argv[1]\n"); return -1; }
    int maxlen = 64;
    char *line = (char *)malloc(sizeof(char) * maxlen);

    FILE* file = fopen( argv[1], "r");
    if(file==NULL){ printf("file not found\n"); return -1; }

    char values[2];
    int total = 0;
    while(fgets(line, maxlen, file)) {

        values[0] = getFirst(line);
        values[1] = getLast(line);
        total+=atoi(values);

    }
    fclose(file);
    free(line);
    
    printf("%i\n",total);
    return 0;
}
