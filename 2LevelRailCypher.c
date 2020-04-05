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
    free((char*)paddedMessage);

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
    int peakIndex[numCycles + 1]; //This array will contain the index numbers for the peaks
    int middlePeakIndex[numCycles]; //this array will cointain the index numbers of the middle peaks

    char charArray[numChars][a];
    for(int i = 0; i < numChars; i++){
        for(int j = 0; j < a; j++){
            charArray[i][j] = (char)0;
        }
    }


    int curRail = 1;
    int prevRail = curRail - 1;

    //setting the values of the peakIndex
    peakIndex[0] = 0; //first peak is always at 0
    for(int i = 0, curPeak = 1; i < numChars; i++){
        if(i % (oneCycle - 1) == 0){//peaks are at indexes divisbile by the length of onc Cycle minus 1
            peakIndex[curPeak] = i;
            curPeak++;
        }
    }

    //setting the values of the middlePeakIndex
    //first middle peak is at the index of the first peak divided by 2 
    // (the index where the cipher first returns to the top rail)
    for(int i = peakIndex[1]/2, j = 0; i < numChars; i += peakIndex[1], j++){
        middlePeakIndex[j] = i;
    }

    for(int i = 0; i < numChars; i++){
        charArray[i][curRail] = message[i];
        if(curRail == a - 1){ //if at bottom
            curRail--;//next rail is current rail minus 1
        }
        //else if(curRail ==)
    }
}

