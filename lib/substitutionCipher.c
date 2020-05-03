#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "substitutionCipher.h"

#define MAX_SIZE_FILE_CM 8193 //8 * 1024 + 1

struct WordCount
{
    char word[30];
    int count;
};


void substitutionCipherEncrypt(char* toEncrypt,char* encrypted, const char* key)
{
    stringToUpper(toEncrypt);
    for(int i = 0; i < strlen(toEncrypt); i++){
        if(toEncrypt[i] >= 'A' && toEncrypt[i] <= 'Z'){
            encrypted[i] = (key[(int)toEncrypt[i] - 65]);
        }
        else{
            encrypted[i] = toEncrypt[i];
        }
    }
    return;
}

void stringToUpper(char* str)
{
    for(int i=0; i < strlen(str); i++){
        if(str[i] >= 'a' && str[i] <= 'z'){
            str[i] -= 32;
        }
    }
}

void substitutionCipherDecrypt(char* toDecrypt,char* decrypted, const char* key)
{
    stringToUpper(toDecrypt);
    char invertedKey[27];
    invertSubstitutionKey(key,invertedKey);
    for(int i = 0; i < strlen(toDecrypt); i++){
        if(toDecrypt[i] >= 'A' && toDecrypt[i] <= 'Z'){
            decrypted[i] = invertedKey[(int)toDecrypt[i] - 65];
        }
        else{
            decrypted[i] = toDecrypt[i];
        }
    }
}

void invertSubstitutionKey(const char* key, char* invertedKey)
{
    for(int i = 0, j = 'A'; j < 'A' + 26; i++,j++){
        invertedKey[(int)(key[i]-65)] = j;
    }
}

void frequencyAnalysis(const char* encrypted, int freqAnalysis[27])
{
    int totLetters = 0;
    for(int i = 0; i <= 26; i++){
        freqAnalysis[i] = 0;
    }
    for(int i = 0; i < strlen(encrypted); i++){
        if(encrypted[i] >= 'A' && encrypted[i] <= 'Z'){
            freqAnalysis[(int)(encrypted[i] - 65)]++;
            freqAnalysis[26]++;
        }
    }
}


//https://asecuritysite.com/challenges/scramb?coding=NOPQRSTUVWXYZABCDEFGHIJKLM~this%20is%20a%20message

void frequencyOrder(int* freqAnalysis, char letterAnalysis[][27])
{
    int highestFreq = -1;
    int highestFreqIndex;
    for(int j = 0; j < 26; j++){
        for(int i = 0; i < 26; i++){
            if(freqAnalysis[i] > highestFreq){
                highestFreqIndex = i;
                highestFreq = freqAnalysis[i];
            }
        }
        letterAnalysis[1][j] = 65 + highestFreqIndex;
        freqAnalysis[highestFreqIndex] = -1;
        highestFreq = -1;
    }
    return;
}

//int indexOfRankedFrequency(int* freqAnalysis,int rank)
//{
//    
//}

void subCipherDecryptTry(char* toDecrypt,char* decrypted, char* key)
{
    int messageLen = strlen(toDecrypt);
    char toDecryptCopy[messageLen];
    int MAX_NUMBER_OF_WORDS = 10000;
    stringToUpper(toDecrypt);
    strcpy(toDecryptCopy,toDecrypt);
    int letterFreq[27];
    char keyGuess [26][2];
    char oneLetterWords [MAX_NUMBER_OF_WORDS][2];
    char twoLetterWords [MAX_NUMBER_OF_WORDS][3];
    char threeLetterWords [MAX_NUMBER_OF_WORDS][4];
    char * pch;

    //Zero's out letter frequency as well as putting the letters of the alphabet into keyGuess[][0]
    for (int i = 0, j = 'A'; i <= 26; i++,j++){
        letterFreq[i] = 0;
        keyGuess[i][0] = j;
    }
    frequencyAnalysis(toDecrypt, letterFreq);
    char engLetterFreq[] = "ETAOINSRHDLUCMFYWGPBVKXQJZ";
    //                      ABCDEFGHIJKLMNOPQRSTUVWXYZ
    //                      GHIDXZLMBNOPFQERSTCUVWAKYJ

    //get count of one letter words
    
    int i1 = 0, i2 = 0,i3 = 0;
    
    struct WordCount oneCount[MAX_NUMBER_OF_WORDS];
    struct WordCount twoCount[MAX_NUMBER_OF_WORDS];
    struct WordCount threeCount[MAX_NUMBER_OF_WORDS];

    for(pch = strtok(toDecryptCopy," ,.()\n"); pch != NULL; pch = strtok(NULL," ,.()\n")){
        if(strlen(pch) == 1){
            strcpy(oneLetterWords[i1],pch);
            i1++;
            for()
        }
        else if(strlen(pch) == 2){
            strcpy(twoLetterWords[i2],pch);
            i2++;
        }
        else if(strlen(pch) == 3){
            strcpy(threeLetterWords[i3],pch);
            i3++;
        }
    }



    //Puts the most frequently used letters in the encrypted text and normalizes it against engLetterFreq.
    for(int i = 0; i < 26; i++){
        int maxVAL[2] = {0,0};
        for(int j = 0; j < 26; j++){
            if(letterFreq[j] > maxVAL[0]){
                maxVAL[0] = letterFreq[j];
                maxVAL[1] = j;
            }
        }
        keyGuess[engLetterFreq[i] - 65][1] = maxVAL[1] + 65;
        letterFreq[maxVAL[1]] = -1;
    }

    //copies keyGuess into key. Probably could've just use strcpy... 
    for(int i = 0; i < 26; i++){
        key[i] = keyGuess[i][1];
    }

    substitutionCipherDecrypt(toDecrypt,decrypted,key);

    printf("Using the key %s\n\nIs this close?\n\n\n%s\n\n",key,decrypted);
}
//abcdefghijklmnopqrstuvwxyz
//QAXBSWKGYFHMEDCOPUZJRINATA
//QAXBSWOUYAHMEDCIPGZJRKTFNA
//qazxswedcvfrtgbnhyujmkilop