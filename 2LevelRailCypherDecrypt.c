#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void rail2dencrypt(char* message,int a, int b);
void getEncryptedIndexes(int* encryptedIndexes,const char* message,int a, int b);
void rail2dencryptTry(char* message,int maxRails);

int main ()
{
    char encrypted[] = "TRAEPHHA__S.QIPSSCAZRS_EIORYS_SA.I_O_HXVTI__TLPWU";
    int key1 = 6,key2 = 2;
    printf("%s\n",encrypted);

    rail2dencrypt(encrypted,key1,key2);
    printf("%s\n",encrypted);


    char encrypted2 [] = "TRAEPHHA__S.QIPSSCAZRS_EIORYS_SA.I_O_HXVTI__TLPWU";
    rail2dencryptTry(encrypted2,10);



    return 0;
}

void rail2dencrypt(char* message,int a, int b)
{
    
    int  messageLen = strlen(message);
    char tempStr[messageLen];
    strcpy(tempStr,message);

    int oneCycle = 2*a + 2*b - 3; //number of letters in one 'cycle'
    int numCycles = (int)ceil((float)messageLen/oneCycle); //number of complete "W" shapes in the rail
    int numChars = numCycles * oneCycle - numCycles + 1; //this is the number of characters in the padded string
    if (numChars < messageLen){
        //the above algorithm for numCycles sometimes is one lower which causes the number of characters to be less than it should be in the 
        //padded string. This will add another cycle thus increasing the number of characters to the right number. 
        numCycles++;
        numChars = numCycles * oneCycle - numCycles + 1;
    }

    int encryptedIndexes[messageLen];
    getEncryptedIndexes(encryptedIndexes,message,a,b);


    for (int i = 0; i < messageLen; i++){
        message[encryptedIndexes[i]-1] = tempStr[i];
    }

    return;

}

void getEncryptedIndexes(int* encryptedIndexes,const char* message,int a, int b)
{
    int  messageLen = strlen(message);

        

    int oneCycle = 2*a + 2*b - 3; //number of letters in one 'cycle'
    int numCycles = (int)ceil((float)messageLen/oneCycle); //number of complete "W" shapes in the rail
    int numChars = numCycles * oneCycle - numCycles + 1; //this is the number of characters in the padded string
    if (numChars < messageLen){
        //the above algorithm for numCycles sometimes is one lower which causes the number of characters to be less than it should be in the 
        //padded string. This will add another cycle thus increasing the number of characters to the right number. 
        numCycles++;
        numChars = numCycles * oneCycle - numCycles + 1;
    }


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

    return;
}

void rail2dencryptTry(char* message,int maxRails)
{
    int  messageLen = strlen(message);
    char temp [strlen(message)];
    strcpy(temp,message);

    printf("Possible Decryptions:\n\n==========================================================================================\n");

    for (int i = 3; i <= maxRails; i++){
        for(int j = 2; j < i; j++){
            int oneCycle = 2*i + 2*j - 3; //number of letters in one 'cycle'
            int numCycles = (int)ceil((float)messageLen/oneCycle); //number of complete "W" shapes in the rail
            int numChars = numCycles * oneCycle - numCycles + 1; //this is the number of characters in the padded string
            if (numChars < messageLen){
            //the above algorithm for numCycles sometimes is one lower which causes the number of characters to be less than it should be in the 
            //padded string. This will add another cycle thus increasing the number of characters to the right number. 
            numCycles++;
            numChars = numCycles * oneCycle - numCycles + 1;
            }

            if(numChars == messageLen){
                rail2dencrypt(message,i,j);
                printf("Key1: %d,\t\tKey2: %d\t\tdecryption attempt: %s\n",i,j,message);
                strcpy(message,temp);
            }
        }
    }
    printf("==========================================================================================\n\n");
}