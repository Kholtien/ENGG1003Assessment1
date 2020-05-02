#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "railcipher.h"

#define MAX_SIZE_FILE_CM 8193 //8 * 1024 + 1

//
//void railFenceEncrypt(char* toEncrypt,char* encrypted, int key);
//void padMessageRail(char* message,int key);
//void railFenceDecrypt(char* toDecrypt,char* decrypted, int key);
//int railFenceDecryptTry(char* toDecrypt,char* decrypted, int keyMAX);
//
//int main()
//{
//    int i, len, rails;
//    char str[1000];
//    char encryptedStr[1000];
//
//    char message[] = "Wow, this is a really cool message";
//    len = strlen(message);
//    rails = 4;
//    for (i = 0; i < len; i++){
//        str[i] = message[i];
//    }
//    str[i] = 0;
//
//    //printf("Enter a Secret Message (one line only)\n");
//    //scanf("%[^\n]%*c", str);
//    
//    //printf("Enter number of rails\n");
//    //scanf("%d", &rails);
//
//    railFenceEncrypt(str,encryptedStr,rails);
//
//    printf("%s\n%s\n",str,encryptedStr);
//
//    railFenceDecrypt(encryptedStr,str,rails);
//
//    printf("%s\n%s\n",str,encryptedStr);
//
//    railFenceDecryptTry(encryptedStr,str,10);
//
//    return 0;
//}

void padMessageRail(char* message,int key)
{
    int messageLen = strlen(message);

    int oneCycle = 2 * key - 2; //number of letters in one 'cycle'
    int numCycles = ceil(messageLen/oneCycle); //number of complete "W" shapes in the rail
    int numChars = numCycles * oneCycle + 1; //this is the number of characters in the padded string
    if (numChars < messageLen){
        //the above algorithm for numCycles sometimes is one lower which causes the number of characters to be less than it should be in the 
        //padded string. This will add another cycle thus increasing the number of characters to the right number. 
        numCycles++;
        numChars = numCycles * oneCycle + 1;
    }
    
    //fill in messWithExtraChar with message and extra characters if required then the null character at the end
    for (int i = messageLen; i < numChars; i++) {
        message[i] = (char)(65 + rand() % 26);
    }
    message[numChars] = (char)0;
}

void railFenceEncrypt(char* toEncrypt,char* encrypted, int key)
{
    //used algorithm from http://article.nadiapub.com/IJFGCN/vol11_no2/3.pdf
    padMessageRail(toEncrypt,key);
    int len = strlen(toEncrypt);
    int flg, plainChar;
    int cipherChar = 1;

    for(int i = 1; i <= key; i++){
        flg = 1;
        plainChar = i;
        while(plainChar <= len){
            encrypted[cipherChar - 1] = toEncrypt[plainChar - 1];
            cipherChar++;
            if(i == 1 || i == key){
                plainChar = plainChar + (key - 1) * 2;
            }
            else {
                if (flg == 1){
                    plainChar = plainChar + (key - i) * 2;
                    flg = 0;
                }
                else {
                    plainChar = plainChar + ((i - 1) * 2);
                    flg = 1;
                }
            }
        }
    }
    encrypted[len] = 0;
}



void railFenceDecrypt(char* toDecrypt,char* decrypted, int key){
    int cipherChar = 1;
    int len = strlen(toDecrypt);
    int flg, plainChar;

    for(int i = 1; i <= key; i++){
        flg = 1;
        plainChar = i;
        while (plainChar <= len){
            decrypted[plainChar - 1] = toDecrypt[cipherChar - 1];
            cipherChar ++;
            if (i == 1 || i == key){
                plainChar = plainChar + (key - 1) * 2;
            }
            else {
                if(flg == 1){
                    plainChar = plainChar + (key - i) * 2;
                    flg = 0;
                }
                else {
                    plainChar = plainChar + ((i - 1) * 2);
                    flg = 1;
                }
            }
        }
    }
    decrypted[len] = 0;
}

int railFenceDecryptTry(char* toDecrypt,char* decrypted, int keyMAX)
{
    char temp[MAX_SIZE_FILE_CM];
    int choice;
    int messageLen = strlen(toDecrypt);
    int oneCycle;
    int numCycles;
    int numChars;


    strcpy(temp,decrypted);

    for(int i = 2; i <= keyMAX; i++){
        oneCycle = 2 * i - 2; //number of letters in one 'cycle'
        numCycles = ceil(messageLen/oneCycle); //number of complete "W" shapes in the rail
        numChars = numCycles * oneCycle + 1; //this is the number of characters in the padded string
        if (numChars < messageLen){
            //the above algorithm for numCycles sometimes is one lower which causes the number of characters to be less than it should be in the 
            //padded string. This will add another cycle thus increasing the number of characters to the right number. 
            numCycles++;
            numChars = numCycles * oneCycle + 1;
        }
        if(numChars == messageLen){
            railFenceDecrypt(toDecrypt,temp,i);
            printf("Key: %d\t\tMessage: %s\n",i,temp);
        }
    }
    printf("\n\nWhich key is correct?: ");
    scanf("%d",&choice);
    railFenceDecrypt(toDecrypt,decrypted,choice);

    return choice;
}