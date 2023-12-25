// Maeve K. Kennedy
// Advent of Code 2023 Day 1
// written Dec 4th (late start)
// I cant believe I solved part 2 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char getNumberFromWord(char* section){
    char out = '\0';
   //needs to be broken out into search lenghts to prevent segfaults
   //so three length words
    if(strlen(section)>=3){
        char* names[3][2] = {{"one","1"}, {"two","2"}, {"six","6"}};
        for(int index = 0; index<3; index++){
            if(strncmp(section, *(names+index)[0], sizeof(char)*3)==0){ //compares 3 chars
                out = *(names[index])[1]; //derefrenece the indexth value of names and access its 1st value
            }
        }
    }

    //then 4 lenght words
    if(strlen(section)>=4 && out=='\0'){
        char* names[3][2] = {{"four","4"}, {"five","5"}, {"nine","9"}};
        for(int index = 0; index<3; index++){
            if(strncmp(section, *(names+index)[0], sizeof(char)*4)==0){ //compares 4 chars
                out = *(names[index])[1]; 
            }
        }
    }

    //then 5 lenght words
    if(strlen(section)>=5 && out=='\0'){
        char* names[3][2] = {{"three","3"},  {"seven","7"}, {"eight","8"}}; //compares 5 chars
        for(int index = 0; index<3; index++){
            if(strncmp(section, *(names+index)[0], sizeof(char)*5)==0){
                out = *(names[index])[1];
            }
        }
    }
    return out; // just like the other functions, \0 impiles not found
}

char getFirst(char *line) {
    char retVal = '\0'; // \0 means not found
    int offset = 0;
    while (offset < strlen(line) && retVal == '\0') { 
        if ( isdigit( *(line + offset) )) {
            retVal = line[offset];
        }
        else{ retVal = getNumberFromWord(line+offset); } 
        // getNubmerFromWord returns \0 on fail so the loop keeps looping.
        offset++;
    }//walks forward until digit or word is found
    return retVal;
}

char getLast(char *line) {
    char retVal = '\0'; // \0 means not found
    int offset = strlen(line);
    while (offset > 0 && retVal == '\0') {
        --offset;
        if ( isdigit( *(line + offset) )) {
            retVal = line[offset];
        }
        else{ retVal = getNumberFromWord(line+offset); }
    }//walks backwards until digit or word is found
    return retVal;
}

int main(int argc, char** argv) {
    
    if(argc < 2){ printf("call with path as argv[1]\n"); return -1; } // prevents errors
    int maxlen = 64;
    char *line = (char *)malloc(sizeof(char) * maxlen);

    //file setup
    FILE* file = fopen( argv[1], "r");//open readonly
    if(file==NULL){ printf("file not found\n"); return -1; } //catch fnf

    char values[2];
    int total = 0;
    while(fgets(line, maxlen, file)){ //while next line exists, copy it into &line

        values[0] = getFirst(line);
        values[1] = getLast(line);
        total+=atoi(values); //this is cause C is such a cool language
        printf("%s %d\n", line, atoi(values));

    }
    fclose(file);
    free(line);
    
    printf("%i\n",total);
    return 0;
}
