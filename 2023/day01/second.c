#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *numbers[] = {
    "one", "two", "six", 
    "four", "five", "nine", 
    "three", "seven", "eight",
};


char* replaceWord(const char* s, const char* oldW, 
                const char* newW) 
{ 
    char* result; 
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW); 
 
    // Counting the number of times old word 
    // occur in the string 
    for (i = 0; s[i] != '\0'; i++) { 
        if (strstr(&s[i], oldW) == &s[i]) { 
            cnt++; 
 
            // Jumping to index after the old word. 
            i += oldWlen - 1; 
        } 
    } 
 
    // Making new string of enough length 
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1); 
 
    i = 0; 
    while (*s) { 
        // compare the substring with the result 
        if (strstr(s, oldW) == s) { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
            result[i++] = *s++; 
    } 
 
    result[i] = '\0'; 
    return result; 
}

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

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("call with path as argv[1]\n");
        return -1;
    }

    int maxlen = 64;
    char *line = (char *) malloc(sizeof(char) * maxlen);

    FILE* file = fopen(argv[1], "r");

    if(file == NULL) {
        printf("file not found\n");
        return -1;
    }

    char values[2];
    int total = 0;
    while(fgets(line, maxlen, file)) {
        if(strcmp(line, "\n") == 0) break;

        char *new_line = line;

        for(int i = 0; i < 9; i++) {
            char charString[2];

            charString[0] = (i+1) + '0';
            charString[1] = '\0';
            new_line = replaceWord(new_line, numbers[i], charString);
        }


        values[0] = getFirst(new_line);
        values[1] = getLast(new_line);
        values[2] = '\0';

        total += atoi(values);
        printf("%s %d %s\n", line, atoi(values), new_line);

    }

    fclose(file);
    free(line);
    
    printf("%i\n", total);

    return 0;
}
