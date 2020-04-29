#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_WORD_LENGTH 32

int main () 
{
    //VARIABLES
    FILE * dictionaryFile;
    const int MAX_SIZE = 8 * 1024 + 1;
    char filename[] = "data/words_alpha.txt";
    int *a,temp,count = 0;
    int numLines = 0;
    char word[MAX_WORD_LENGTH];
    char c = 0;

    //OPEN FILE
    dictionaryFile = fopen(filename,"r");

    if (dictionaryFile == NULL) 
    { 
        printf("Could not open file %s", filename); 
        return 1; 
    } 
    
    for(c = fgetc(dictionaryFile); c != EOF; c = fgetc(dictionaryFile)){
        if(c == '\n')
            numLines++;
    }
    fclose(dictionaryFile);
    dictionaryFile = fopen(filename,"r");

    char lines [numLines][MAX_WORD_LENGTH];
    int i = 0;

    while( fgets(lines[i], MAX_WORD_LENGTH - 1 ,dictionaryFile) != NULL){
        lines[i][strlen(lines[i]) - 1] = '\0';
        printf("%s\n",lines[i]);
        i++;
    }
    fclose(dictionaryFile);




    printf("There are %d lines\n",numLines);

    return 0;
}