#include <stdio.h>
#include <string.h>
void substitutionCypherEncrypt(char* toEncrypt,char* encrypted, const char* key);
void substitutionCypherUnencrypt(char* toDencrypt,char* unencrypted, const char* key);
void stringToUpper(char* str);
void invertSubstitutionKey(const char* key, char* invertedKey);
void frequencyAnalysis(const char* encrypted, int* freqAnalysis);

int main()
{
    char key[] = "VIOGCAPWYSTZJNBRKQFMLDXEHU";
    //            ABCDEFGHIJKLMNOPQRSTUVWXYZ
    char filename[] = "data/paragraph.txt";
    FILE * fp = fopen(filename,"r");

    char toEncrypt[8 * 1024 + 1];
    char buffer[8 * 1024 + 1];
    while(fgets(buffer,1000,fp)){
        strcat(toEncrypt,buffer);
    }
    int freqAnalysis[27];//one for each letter and then a total


    substitutionCypherEncrypt(toEncrypt,buffer,key);
    printf("Original:\n%s\n\n\nEncrypted\n%s\n\n\n",toEncrypt,buffer);

    frequencyAnalysis(buffer,freqAnalysis);
    
    substitutionCypherUnencrypt(buffer,toEncrypt,key);
    printf("unencrypted:\n%s",toEncrypt);



    return 0;
}

void substitutionCypherEncrypt(char* toEncrypt,char* encrypted, const char* key)
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

void substitutionCypherUnencrypt(char* toDencrypt,char* unencrypted, const char* key)
{
    char newKey[27];
    invertSubstitutionKey(key,newKey);
    for(int i = 0; i < strlen(toDencrypt); i++){
        if(toDencrypt[i] >= 'A' && toDencrypt[i] <= 'Z'){
            unencrypted[i] = newKey[(int)toDencrypt[i] - 65];
        }
        else{
            unencrypted[i] = toDencrypt[i];
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