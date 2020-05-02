#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "substitutionCipher.h"

#define MAX_SIZE_FILE_CM 8193 //8 * 1024 + 1


//int main()
//{
//
//    //This all is required to get it to work
//    char key[] = "VIOGCAPWYSTZJNBRKQFMLDXEHU";
//    char engLetterFreq[] = "ETAOINSHRDLUCMFWYPVBGKJQXZ";
//    //            ABCDEFGHIJKLMNOPQRSTUVWXYZ
//    char filename[] = "data/paragraph.txt";
//    FILE * fp = fopen(filename,"r");
//
//    char toEncrypt[8 * 1024 + 1];
//    char buffer[8 * 1024 + 1];
//    while(fgets(buffer,1000,fp)){
//        strcat(toEncrypt,buffer);
//    }
//    //below is all stuff related to solving with an unknown 
//
//
//
//
//    int freqAnalysis[27];//one for each letter and then a total
//    char letterAnalysis[2][27];
//    for(int i = 0; i < 26; i++){
//        letterAnalysis[0][i] = engLetterFreq[i];
//    }
//    letterAnalysis[0][26] = 0;
//    letterAnalysis[1][26] = 0;
//
//
//    substitutionCypherEncrypt(toEncrypt,buffer,key);
//    printf("Original:\n%s\n\n\nEncrypted\n%s\n\n\n",toEncrypt,buffer);
//
//    frequencyAnalysis(buffer,freqAnalysis);
//
//    frequencyOrder(freqAnalysis,letterAnalysis);
//    frequencyAnalysis(buffer,freqAnalysis);
//    substitutionCypherUnencrypt(buffer,toEncrypt,key);
//    printf("unencrypted:\n%s",toEncrypt);
//
//
//
//    return 0;
//}

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

void frequencyAnalysis(const char* encrypted, int* freqAnalysis)
{
    int totLetters = 0;
    for(int i = 0; i < 26; i++){
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