#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "2LevelRailCipher.h"

#define MAX_SIZE_FILE_CM 8193 //8 * 1024 + 1

////function prototypes
//const char* padMessage2Rail(const char* message,int a, int b);
//const char* rail2encrypt(const char* message,int a, int b);
//void rail2encryptstart(char* stringToEncrypt, int charLim);


//int main (void)
//{
//    const int charLim = 1000;
//    char string[charLim];
//    rail2encryptstart(string,charLim);
//
////    printf("Enter a phrase (under %d characters long)\n",charLim);
////    char input[charLim];
////    scanf("%[^\n]%*c", input);
////
////
////    printf("Enter The first key in the 2 level rail cipher:\n");
////    int key1;
////    scanf("%d", &key1);
////
////    
////    printf("Enter The second key in the 2 level rail cipher:\n");
////    int key2;
////    scanf("%d", &key2);
////
//////    const char* toEncrypt = padMessage2Rail(input,key1,key2);
////
//////    printf("%s\n",toEncrypt);
////
////    char testMsg[] = "HOLY_COW_THIS_MESSAGE_IS_EVEN_BETTERNGZAE";
////    const char* encryptedMessage = rail2encrypt(input,key1,key2);
////    printf("%s\n",encryptedMessage);
////    free((char*)encryptedMessage);
//    printf("%s\n",string);
//    return 0;
//}

void rail2encryptstart(char* stringToEncrypt, int charLim){
    printf("Enter a phrase (under %d characters long)\n",charLim);
    char input[charLim];
    scanf("%[^\n]%*c", input);


    printf("Enter The first key in the 2 level rail cipher:\n");
    int key1;
    scanf("%d", &key1);

    
    printf("Enter The second key in the 2 level rail cipher:\n");
    int key2;
    scanf("%d", &key2);

    char encryptedMessage[charLim];

    rail2Encrypt(input,encryptedMessage,key1,key2);
    printf("%s\n",encryptedMessage);

    strcpy(stringToEncrypt,encryptedMessage);

}

void padMessage2Rail(char* message,int a, int b)
{
    int  messageLen = strlen(message);

    int oneCycle = 2*a + 2*b - 3; //number of letters in one 'cycle'
    int numCycles = (int)ceil((float)messageLen/oneCycle); //number of complete "W" shapes in the rail
    int numChars = numCycles * oneCycle - numCycles + 1; //this is the number of characters in the padded string
    while (numChars < messageLen){
        //the above algorithm for numCycles sometimes is one lower which causes the number of characters to be less than it should be in the 
        //padded string. This will add another cycle thus increasing the number of characters to the right number. 
        numCycles++;
        numChars = numCycles * oneCycle - numCycles + 1;
    }
    char messWithExtraChar[numChars + 1]; //this creates string array with the right number of characters plus the null character

    
    //fill in messWithExtraChar with message and extra characters if required then the null character at the end
    for (int i = messageLen; i < numChars; i++) {
        message[i] = (char)(65 + rand() % 26);
    }
    message[numChars] = (char)0;

//    char* out = malloc(numChars + 1);
//    for (int i = 0; i <= numChars; i++){
//        out[i] = messWithExtraChar[i];
//    }
//
//    return out;
}
void rail2Encrypt(char* toEncrypt,char* encrypted, int a, int b)
{
    //influenced by http://article.nadiapub.com/IJFGCN/vol11_no2/3.pdf
    padMessage2Rail(toEncrypt,a,b);
    int  messageLen = strlen(toEncrypt);

    int oneCycle = 2*a + 2*b - 3; //number of letters in one 'cycle'
    int numCycles = (int)ceil((float)messageLen/oneCycle); //number of complete "W" shapes in the rail
    int numChars = numCycles * oneCycle - numCycles + 1; //this is the number of characters in the padded string
    while (numChars < messageLen){
        //the above algorithm for numCycles sometimes is one lower which causes the number of characters to be less than it should be in the 
        //padded string. This will add another cycle thus increasing the number of characters to the right number. 
        numCycles++;
        numChars = numCycles * oneCycle - numCycles + 1;
    }

    int encryptedIndexes[messageLen];


//algorithm for merging the message onto a 1D array for the rail.
    for(int i = 0, curRail = 1, totRail = a, midRail = b; i <= messageLen; i++){
        

        if(curRail == 1){
            encryptedIndexes[i] = 1 + (oneCycle - 1) * i;
            if(i >= numCycles)
                curRail++;
        }
        else if(curRail > 1 && curRail < totRail - midRail + 1){
            for(int j = 0; j < numCycles; j++,i++){
                encryptedIndexes[i]   = curRail                                  + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (oneCycle - (2 * curRail - 1)) + (oneCycle - 1) * j;
            }
            curRail++;
            i--;
        }
        else if(curRail == totRail - midRail + 1){
            for(int j = 0; j < numCycles; j++,i++){
                encryptedIndexes[i]   = curRail                               + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2     + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2 * 2 + (oneCycle - 1) * j;
            }
            curRail++;
            i--;
        }
        else if(curRail < totRail && curRail > totRail - midRail + 1){
            for(int j = 0; j < numCycles; j++,i++){
                encryptedIndexes[i]   = curRail                                                                       + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2                                             + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2     + (midRail + curRail - totRail - 1) * 2 + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2 * 2 + (midRail + curRail - totRail - 1) * 2 + (oneCycle - 1) * j;
            }
            curRail++;
            i--;
        }
        else if(curRail == totRail){
            int j;
            for(j = 0; j < numCycles; j++,i++){
                encryptedIndexes[i]   = curRail                                         + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (midRail + curRail - totRail - 1) * 2 + (oneCycle - 1) * j;
            }
            //curRail++;
        }
        else{
            printf("Something went wrong :(");
        }
    }
    

    for (int i = 0; i < numChars; i++){
        encrypted[i] = toEncrypt[encryptedIndexes[i] -1];
    }
    encrypted[numChars] = 0;
    //free(toEncrypt);
    //char* out = malloc(numChars + 1);
    //for (int i = 0; i < numChars; i++){
    //    out[i] = toEncrypt[encryptedIndexes[i] - 1];
    //}
    //out[numChars] = 0;
//
    //return out;
}

void rail2Decrypt(char* toDecrypt,char* decrypted, int a, int b)
{
    int  messageLen = strlen(toDecrypt);

    int oneCycle = 2*a + 2*b - 3; //number of letters in one 'cycle'
    int numCycles = (int)ceil((float)messageLen/oneCycle); //number of complete "W" shapes in the rail
    int numChars = numCycles * oneCycle - numCycles + 1; //this is the number of characters in the padded string
    while (numChars < messageLen){
        //the above algorithm for numCycles sometimes is one lower which causes the number of characters to be less than it should be in the 
        //padded string. This will add another cycle thus increasing the number of characters to the right number. 
        numCycles++;
        numChars = numCycles * oneCycle - numCycles + 1;
    }

    int encryptedIndexes[messageLen];


//algorithm for merging the message onto a 1D array for the rail.
    for(int i = 0, curRail = 1, totRail = a, midRail = b; i <= messageLen; i++){
        

        if(curRail == 1){
            encryptedIndexes[i] = 1 + (oneCycle - 1) * i;
            if(i >= numCycles)
                curRail++;
        }
        else if(curRail > 1 && curRail < totRail - midRail + 1){
            for(int j = 0; j < numCycles; j++,i++){
                encryptedIndexes[i]   = curRail                                  + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (oneCycle - (2 * curRail - 1)) + (oneCycle - 1) * j;
            }
            curRail++;
            i--;
        }
        else if(curRail == totRail - midRail + 1){
            for(int j = 0; j < numCycles; j++,i++){
                encryptedIndexes[i]   = curRail                               + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2     + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2 * 2 + (oneCycle - 1) * j;
            }
            curRail++;
            i--;
        }
        else if(curRail < totRail && curRail > totRail - midRail + 1){
            for(int j = 0; j < numCycles; j++,i++){
                encryptedIndexes[i]   = curRail                                                                       + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2                                             + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2     + (midRail + curRail - totRail - 1) * 2 + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2 * 2 + (midRail + curRail - totRail - 1) * 2 + (oneCycle - 1) * j;
            }
            curRail++;
            i--;
        }
        else if(curRail == totRail){
            for(int j = 0; j < numCycles; j++,i++){
                encryptedIndexes[i]   = curRail                                         + (oneCycle - 1) * j;
                encryptedIndexes[++i] = curRail + (midRail + curRail - totRail - 1) * 2 + (oneCycle - 1) * j;
            }
        }
        else{
            printf("Something went wrong :(");
        }
    }
    

    for (int i = 0; i < numChars; i++){
        decrypted[encryptedIndexes[i] -1] = toDecrypt[i];
    }
    decrypted[numChars] = 0;
}

void rail2DecryptTry(char* toDecrypt,char* decrypted, int keyMAX)
{    
    char temp[1000];
    int choiceKey1,choiceKey2;
    int messageLen = strlen(toDecrypt);
    int oneCycle;
    int numCycles;
    int numChars;

    for(int i = 3; i <= keyMAX; i++){
        for(int j = 2; j < i; j++){

            oneCycle = 2*i + 2*j - 3; //number of letters in one 'cycle'
            numCycles = (int)ceil((float)messageLen/oneCycle); //number of complete "W" shapes in the rail
            numChars = numCycles * oneCycle - numCycles + 1; //this is the number of characters in the padded string
            while (numChars < messageLen){
                //the above algorithm for numCycles sometimes is one lower which causes the number of characters to be less than it should be in the 
                //padded string. This will add another cycle thus increasing the number of characters to the right number. 
                numCycles++;
                numChars = numCycles * oneCycle - numCycles + 1;
            }

            if(numChars == messageLen){
                rail2Decrypt(toDecrypt, decrypted, i, j);
                printf("Key 1: %d\t\tKey 2: %d\t\tMessage:\n\n%s\n\n\n",i,j,decrypted);
            }
        }
    }
    printf("\n\nWhich key is correct for key 1?: ");
    scanf("%d",&choiceKey1);
    printf("\n\nWhich key is correct for key 2?: ");
    scanf("%d",&choiceKey2);
    rail2Decrypt(toDecrypt, decrypted, choiceKey1, choiceKey2);
}