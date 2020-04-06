#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//function prototypes
const char* padMessage2Rail(const char* message,int a, int b);
const char* rail2(const char* message,int a, int b);

int main (void)
{
    char message[] = "HOLY COW THIS MESSAGE IS EVEN BETTER";
    int  a = 6, b = 3;
    const char* paddedMessage = padMessage2Rail(message,a,b);

    printf("%s\n",paddedMessage);

    char testMsg[] = "HOLY_COW_THIS_MESSAGE_IS_EVEN_BETTERNGZAEOG";
    const char* encryptedMessage = rail2(paddedMessage,6,3);
    printf("%s\n",encryptedMessage);
    free((char*)paddedMessage);
    free((char*)encryptedMessage);

    return 0;
}

const char* padMessage2Rail(const char* message,int a, int b)
{
    int  messageLen = strlen(message);

    int oneCycle = 2*a + 2*b - 3; //number of letters in one 'cycle'
    int numCycles = (int)ceil((float)messageLen/oneCycle); //number of complete "W" shapes in the rail
    int numChars = numCycles * oneCycle - numCycles + 1; //this is the number of characters in the padded string
    char messWithExtraChar[numChars + 1]; //this creates string array with the right number of characters plus the null character

    
    //fill in messWithExtraChar with message and extra characters if required then the null character at the end
    for (int i = 0; i < numChars; i++) {
        if(i < messageLen)
            messWithExtraChar[i] = message[i];
        else 
            messWithExtraChar[i] = (char)(65 + rand() % 26);
    }
    messWithExtraChar[numChars] = (char)0;

    char* out = malloc(numChars + 1);
    for (int i = 0; i <= numChars; i++){
        out[i] = messWithExtraChar[i];
    }

    return out;
}
const char* rail2(const char* message,int a, int b)
{
    int  messageLen = strlen(message);

    int oneCycle = 2*a + 2*b - 3; //number of letters in one 'cycle'
    int numCycles = (int)ceil((float)messageLen/oneCycle); //number of complete "W" shapes in the rail
    int numChars = numCycles * oneCycle - numCycles + 1; //this is the number of characters in the padded string
//    int peakIndex[numCycles + 1]; //This array will contain the index numbers for the peaks
//    int middlePeakIndex[numCycles]; //this array will cointain the index numbers of the middle peaks
//    int basesIndex[2 * numCycles];
    int encryptedIndexes[messageLen];




//    char charArray[numChars][a];
//    for(int i = 0; i < numChars; i++){
//        for(int j = 0; j < a; j++){
//            charArray[i][j] = (char)0;
//        }
//    }




//    //setting the values of the peakIndex
//    peakIndex[0] = 0; //first peak is always at 0
//    for(int i = 0, j = 0; i < numCycles; i++, j += oneCycle - 1){
//        peakIndex[i] = j;
//    }
//
//    //setting the values of the middlePeakIndex
//    //first middle peak is at the index of the first peak divided by 2 
//    // (the index where the cipher first returns to the top rail)
//    for(int i = peakIndex[1]/2, j = 0; i < numChars; i += peakIndex[1], j++){
//        middlePeakIndex[j] = i;
//    }
//
//    //setting values for basesIndex
//    for(int i = 0, j = b - 1; i < 2 * numCycles; i += 2, j += oneCycle - 1){
//        basesIndex[i] = j;
//        basesIndex[i+1] = j + 2 * b - 2;
//    }
    



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
    
    
    char* out = malloc(numChars + 1);
    for (int i = 0; i <= numChars; i++){
        out[i] = message[encryptedIndexes[i] - 1];
    }

    return out;
}

