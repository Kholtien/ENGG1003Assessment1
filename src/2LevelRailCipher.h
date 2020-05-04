#ifndef RAILCYPHER_2_H_
#define RAILCYPHER_2_H_


//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <math.h>
//function prototypes

//Pads message to fit full length of zig zag
void padMessage2Rail(char* message,int a, int b);

//Ecnrypts the message. Returns encrypted string. 
//const char* rail2encrypt(const char* message,int a, int b);
void rail2Encrypt(char* toEncrypt,char* encrypted, int a, int b);

//decrypts the message. Unencrypted message is in decrypted string.
void rail2Decrypt(char* toDecrypt,char* decrypted, int a, int b);

//starts off encryption process
void rail2encryptstart(char* stringToEncrypt, int charLim);

//tries multiple keys up to key1 == 10
void rail2DecryptTry(char* toDecrypt,char* decrypted, int keyMAX);


#endif //RAILCYPHER_2_H_

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
//////    const char* paddedMessage = padMessage2Rail(input,key1,key2);
////
//////    printf("%s\n",paddedMessage);
////
////    char testMsg[] = "HOLY_COW_THIS_MESSAGE_IS_EVEN_BETTERNGZAE";
////    const char* encryptedMessage = rail2encrypt(input,key1,key2);
////    printf("%s\n",encryptedMessage);
////    free((char*)encryptedMessage);
//    printf("%s\n",string);
//    return 0;
//}
//
//void rail2encryptstart(char* stringToEncrypt, int charLim){
//    printf("Enter a phrase (under %d characters long)\n",charLim);
//    char input[charLim];
//    scanf("%[^\n]%*c", input);
//
//
//    printf("Enter The first key in the 2 level rail cipher:\n");
//    int key1;
//    scanf("%d", &key1);
//
//    
//    printf("Enter The second key in the 2 level rail cipher:\n");
//    int key2;
//    scanf("%d", &key2);
//
//    const char* encryptedMessage = rail2encrypt(input,key1,key2);
//    printf("%s\n",encryptedMessage);
//
//    strcpy(stringToEncrypt,encryptedMessage);
//    free((char*)encryptedMessage);
//}
//
//const char* padMessage2Rail(const char* message,int a, int b)
//{
//    int  messageLen = strlen(message);
//
//    int oneCycle = 2*a + 2*b - 3; //number of letters in one 'cycle'
//    int numCycles = (int)ceil((float)messageLen/oneCycle); //number of complete "W" shapes in the rail
//    int numChars = numCycles * oneCycle - numCycles + 1; //this is the number of characters in the padded string
//    if (numChars < messageLen){
//        //the above algorithm for numCycles sometimes is one lower which causes the number of characters to be less than it should be in the 
//        //padded string. This will add another cycle thus increasing the number of characters to the right number. 
//        numCycles++;
//        numChars = numCycles * oneCycle - numCycles + 1;
//    }
//    char messWithExtraChar[numChars + 1]; //this creates string array with the right number of characters plus the null character
//
//    
//    //fill in messWithExtraChar with message and extra characters if required then the null character at the end
//    for (int i = 0; i < numChars; i++) {
//        if(i < messageLen)
//            messWithExtraChar[i] = message[i];
//        else 
//            messWithExtraChar[i] = (char)(65 + rand() % 26);
//    }
//    messWithExtraChar[numChars] = (char)0;
//
//    char* out = malloc(numChars + 1);
//    for (int i = 0; i <= numChars; i++){
//        out[i] = messWithExtraChar[i];
//    }
//
//    return out;
//}
//const char* rail2encrypt(const char* message,int a, int b)
//{
//    const char* paddedMessage = padMessage2Rail(message,a,b);
//    int  messageLen = strlen(paddedMessage);
//
//    int oneCycle = 2*a + 2*b - 3; //number of letters in one 'cycle'
//    int numCycles = (int)ceil((float)messageLen/oneCycle); //number of complete "W" shapes in the rail
//    int numChars = numCycles * oneCycle - numCycles + 1; //this is the number of characters in the padded string
//    if (numChars < messageLen){
//        //the above algorithm for numCycles sometimes is one lower which causes the number of characters to be less than it should be in the 
//        //padded string. This will add another cycle thus increasing the number of characters to the right number. 
//        numCycles++;
//        numChars = numCycles * oneCycle - numCycles + 1;
//    }
//
//    int encryptedIndexes[messageLen];
//
//
////algorithm for merging the message onto a 1D array for the rail.
//    for(int i = 0, curRail = 1, totRail = a, midRail = b; i <= messageLen; i++){
//        
//
//        if(curRail == 1){
//            encryptedIndexes[i] = 1 + (oneCycle - 1) * i;
//            if(i >= numCycles)
//                curRail++;
//        }
//        else if(curRail > 1 && curRail < totRail - midRail + 1){
//            for(int j = 0; j < numCycles; j++,i++){
//                encryptedIndexes[i]   = curRail                                  + (oneCycle - 1) * j;
//                encryptedIndexes[++i] = curRail + (oneCycle - (2 * curRail - 1)) + (oneCycle - 1) * j;
//            }
//            curRail++;
//            i--;
//        }
//        else if(curRail == totRail - midRail + 1){
//            for(int j = 0; j < numCycles; j++,i++){
//                encryptedIndexes[i]   = curRail                               + (oneCycle - 1) * j;
//                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2     + (oneCycle - 1) * j;
//                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2 * 2 + (oneCycle - 1) * j;
//            }
//            curRail++;
//            i--;
//        }
//        else if(curRail < totRail && curRail > totRail - midRail + 1){
//            for(int j = 0; j < numCycles; j++,i++){
//                encryptedIndexes[i]   = curRail                                                                       + (oneCycle - 1) * j;
//                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2                                             + (oneCycle - 1) * j;
//                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2     + (midRail + curRail - totRail - 1) * 2 + (oneCycle - 1) * j;
//                encryptedIndexes[++i] = curRail + (totRail - curRail) * 2 * 2 + (midRail + curRail - totRail - 1) * 2 + (oneCycle - 1) * j;
//            }
//            curRail++;
//            i--;
//        }
//        else if(curRail == totRail){
//            for(int j = 0; j < numCycles; j++,i++){
//                encryptedIndexes[i]   = curRail                                         + (oneCycle - 1) * j;
//                encryptedIndexes[++i] = curRail + (midRail + curRail - totRail - 1) * 2 + (oneCycle - 1) * j;
//            }
//        }
//        else{
//            printf("Something went wrong :(");
//        }
//    }
//    
//    char* out = malloc(numChars + 1);
//    for (int i = 0; i < numChars; i++){
//        out[i] = paddedMessage[encryptedIndexes[i] - 1];
//    }
//    out[numChars] = 0;
//
//    return out;
//}

