/*
########################################################################
#
#   Course:     ENGG1003
#   Project:    Programming Assignment 1
#   Author:     Colton Millington c3267533 
#   Date:       2020-04-30
#   Details:    Main file for running the encryption/decryption
#               programs
#   Usage:      Run with no arguments will get CLI menu***NOT IMPLEMENTED... Menu only. doesn't actually do anything
#                   Will have the choice to import text from 
#                   files or write them in the console ***NOT IMPLEMENTED
#               Run with arguments to do a single command
#                   such as `./c3267533.out sub decrypt data/cypher.txt try file`
#               Compile using `gcc -o c3267533.out c3267533.c -lm` need the -lm flag 
#                   or the math library won't work properly
#
########################################################################
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAX_SIZE_FILE_CM 8193 //8 * 1024 + 1

int main_menu(void);
int rail_menu(void);
int rail2_menu(void);
int subs_menu(void);
void stringToFileQuestion(char* stringToWriteToFile);


//##############################################################
//from railcipher.h
//##############################################################

//required by project
//message is the unencrypted text that you want to encrypt
//cipherText is the encrypted text.
//length??? I'm not sure what this is supposed to be used for it is not mentioned in the spec
//A is the key for the rail cipher
void railFence(char *message, char *cipherText, int length, int A);

//encrypts the string toEncrypt. The encrypted string will at the pointer encrypted
void railFenceEncrypt(char* toEncrypt,char* encrypted, int key);

//pads message so it will complete the zig zag
void padMessageRail(char* message,int key);

//decrypts the string toDecrypt and the decrypted string will be the decrypted string
void railFenceDecrypt(char* toDecrypt,char* decrypted, int key);

//runs the railFenceDecrypt function through key = 2 to key = keyMAX
int railFenceDecryptTry(char* toDecrypt,char* decrypted, int keyMAX);

//##############################################################
//from 2LevelRailCipher.h
//##############################################################

//required by project
//message is the unencrypted text that you want to encrypt
//cipherText is the encrypted text.
//length??? I'm not sure what this is supposed to be used for it is not mentioned in the spec
//A is the key for the rail cipher
//B is the second key for the rail cipher
void railFence2(char *message, char *cipherText, int length, int A, int B,int dir);

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

//##############################################################
//from substitutionCipher.h
//##############################################################

//Encrypts the message. Encrypted message is in string variable "encrypted"
void substitutionCipherEncrypt(char* toEncrypt,char* encrypted, const char* key);

//Decrypts the message. Decrypted message is in the string variable "unecrypted"
void substitutionCipherDecrypt(char* toDecrypt,char* decrypted, const char* key);

void subCipherDecryptTry(char* toDecrypt,char* decrypted, char* key);

//Changed the strings to uppercase
void stringToUpper(char* str);

//Inverts the substitution key to help decrypt
void invertSubstitutionKey(const char* key, char* invertedKey);

//Analises the frequency of every letter in the encrypted message.
//useful to try and analyze the freqeuncy to try and decrypt based on statistical distribution
//of letters in the english language. 
void frequencyAnalysis(const char* encrypted, int freqAnalysis[27]);

//Tries to get a key of letter matches. 
void frequencyOrder(int* freqAnalysis, char letterAnalysis[][27]);

//##############################################################
//from Actual Project
//##############################################################
int main(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++){
        printf("%d\t%s\n",i,argv[i]);
    }
    if(argc == 1){
        //no arguments
        main_menu();
    }
    else if (argc == 2 && strcasecmp(argv[1],"help") == 0){
        printf("########################################################################\n");
        printf("#\n");
        printf("#   Course:     ENGG1003\n");
        printf("#   Project:    Programming Assignment 1\n");
        printf("#   Author:     Colton Millington c3267533 \n");
        printf("#   Date:       2020-04-30\n");
        printf("#   Details:    Main file for running the encryption/decryption\n");
        printf("#               programs\n");
        printf("#   Usage:      Run with no arguments will get CLI menu***NOT IMPLEMENTED... Menu only. doesn't actually do anything\n");
        printf("#                   Will have the choice to import text from \n");
        printf("#                   files or write them in the console ***NOT IMPLEMENTED\n");
        printf("#               Run with arguments to do a single command\n");
        printf("#                   such as `./c3267533.out sub decrypt data/cypher.txt try file`\n");
        printf("#               Compile using `gcc -o c3267533.out c3267533.c -lm` need the -lm flag \n");
        printf("#                   or the math library won't work properly\n");
        printf("#               ********************************************\n");
        printf("#               NOTE: Only tested in Linux (Ubuntu 18.04.4 LTS) environment\n");
        printf("#               Uses some linux only commands like clear and file paths may not work if run in Windows\n");
        printf("#               ********************************************\n");
        printf("#\n");
        printf("########################################################################\n");
        printf("Here's a few examples of commands you can use:\n\n");
        printf("There may be some segmentation faults in these. Please mark the file I/O ones below:\n\n");
        printf("./c3267533.out rail encrypt 'This is such a great message. Truly Tremendous.' 4\n");
        printf("./c3267533.out rail decrypt 'Ts asTTdWhi haetsa r rnoNi sc r eg.uyeeu.sugmelms' 4\n");
        printf("./c3267533.out rail decrypt 'Ts asTTdWhi haetsa r rnoNi sc r eg.uyeeu.sugmelms' try\n");
        printf("./c3267533.out rail2 encrypt 'This is such a great message. Truly Tremendous.' 7 4\n");
        printf("./c3267533.out rail2 decrypt 'TaTQhet rMir yeBsugmelmsB sc eg.ueu.Ri hasa rnoNLs sTdW' 7 4\n");
        printf("./c3267533.out rail2 decrypt 'TaTQhet rMir yeBsugmelmsB sc eg.ueu.Ri hasa rnoNLs sTdW' try\n");
        printf("./c3267533.out sub encrypt 'This is such a great message. Truly Tremendous.' GHIDXZLMBNOPFQERSTCUVWAKYJ\n");
        printf("./c3267533.out sub decrypt 'UMBC BC CVIM G LTXGU FXCCGLX. UTVPY UTXFXQDEVC.' GHIDXZLMBNOPFQERSTCUVWAKYJ\n");
        printf("./c3267533.out sub decrypt 'UMBC BC CVIM G LTXGU FXCCGLX. UTVPY UTXFXQDEVC.' try *****\n");
        printf("########################################################################\nFILEPATH I/O\n");
        printf("\nYou can also replace the message with a filepath and add an additional argument 'file'\n\n");
        printf("./c3267533.out rail encrypt data/alchemist.txt 6 file\n");
        printf("./c3267533.out rail decrypt data/alchemistEncryptedRail6.txt 6 file\n");
        printf("./c3267533.out rail decrypt data/alchemistEncryptedRail6.txt try file\n");
        printf("./c3267533.out rail2 encrypt data/alchemist.txt 7 4 file\n");
        printf("./c3267533.out rail2 decrypt data/alchemistRail2Encrypt74.txt 7 4 file\n");
        printf("./c3267533.out rail2 decrypt data/alchemistRail2Encrypt74.txt try file\n");
        printf("./c3267533.out sub encrypt data/alchemist.txt GHIDXZLMBNOPFQERSTCUVWAKYJ file\n");
        printf("./c3267533.out sub decrypt data/alchemistSubEncrypted.txt GHIDXZLMBNOPFQERSTCUVWAKYJ file\n");
        printf("./c3267533.out sub decrypt data/cypher.txt try file *****\n");
        printf("\n\t\t*****\t this feature isn't yet fully implemented but may still work for longer messages\n");

    }
    /*
    #################################################################################################################################
    Inline CLI Argument FUNCTIONS
    #################################################################################################################################   
    */
    else if (argc == 5 && strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"encrypt") == 0){
        char encrypted[MAX_SIZE_FILE_CM];
        railFenceEncrypt(argv[3],encrypted,atoi(argv[4]));
        printf("\n\n%s\n",encrypted);
    }
    else if (argc == 5 && strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"decrypt") == 0){
        char * toDecrypt = argv[3];
        char decrypted[MAX_SIZE_FILE_CM];
        railFenceDecrypt(toDecrypt,decrypted,atoi(argv[4]));
        printf("%s\n",decrypted);
    }
    else if (argc == 5 && strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[4],"try") == 0){
        const int railMAX = 10;
        printf("Attempting to decrypt the below with rail keys 2 through %d\n\n%s",railMAX,argv[3]);
        char decrypted[MAX_SIZE_FILE_CM];
        railFenceDecryptTry(argv[3],decrypted,railMAX);
        printf("%s\n",decrypted);
    }
    else if (argc == 6 && strcasecmp(argv[1],"rail2") == 0 && strcasecmp(argv[2],"encrypt") == 0){
        int key1 = atoi(argv[4]);
        int key2 = atoi(argv[5]);
        char encrypted[MAX_SIZE_FILE_CM];
        char* toEncrypt = argv[3];
        //strcpy(toEncrypt,argv[3]);


        if (key1 < key2){
            int aux = key1;
            key1 = key2;
            key2 = aux;
            printf("Swapped keys as key 1 (%d) was less than key 2 (%d)\n", key2, key1);
        }
        if(key2 <= 1){
            printf("Error: Second Key must be 2 or greater\n");
            return 1;
        }

        printf("Original:  %s\n",toEncrypt);
        rail2Encrypt(toEncrypt,encrypted,key1,key2);
        printf("Encrypted: %s\n",encrypted);
    }
    else if (argc == 6 && strcasecmp(argv[1],"rail2") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[4],"try") != 0/* && isdigit(argv[4]) && isdigit(argv[5])*/){
        int key1 = atoi(argv[4]);
        int key2 = atoi(argv[5]);
        char decrypted[MAX_SIZE_FILE_CM];
        char* toDecrypt = argv[3];
        //strcpy(toEncrypt,argv[3]);


        if (key1 < key2){
            int aux = key1;
            key1 = key2;
            key2 = aux;
            printf("Swapped keys as key 1 (%d) was less than key 2 (%d)\n", key2, key1);
        }
        if(key2 <= 1){
            printf("Error: Second Key must be 2 or greater\n");
            return 1;
        }

        printf("Original:  %s\n",toDecrypt);
        rail2Decrypt(toDecrypt,decrypted,key1,key2);
        printf("Decrypted: %s\n",decrypted);
    }
    else if (argc == 5 && strcasecmp(argv[1],"rail2") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[4],"try") == 0){
        int keyMAX = 10;
        char decrypted[MAX_SIZE_FILE_CM];
        char* toDecrypt = argv[3];
        //strcpy(toEncrypt,argv[3]);


        //printf("Original:  %s\n",toDecrypt);
        rail2DecryptTry(toDecrypt,decrypted,keyMAX);
        printf("Decrypted: %s\n",decrypted);
    }
    else if (argc == 5 && strcasecmp(argv[1],"sub") == 0 && strcasecmp(argv[2],"encrypt") == 0 && strlen(argv[4]) == 26){
        char* toEncrypt = argv[3];
        char* key = argv[4];
        char encrypted[MAX_SIZE_FILE_CM];

        printf("Original:  %s\n\n",toEncrypt);
        substitutionCipherEncrypt(toEncrypt, encrypted, key);
        printf("Encrypted: %s\n\n",encrypted);

    }
    else if (argc == 5 && strcasecmp(argv[1],"sub") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strlen(argv[4]) == 26){
        char* toDecrypt = argv[3];
        char* key = argv[4];
        char decrypted[MAX_SIZE_FILE_CM];

        printf("Original:  %s\n\n",toDecrypt);
        substitutionCipherDecrypt(toDecrypt, decrypted, key);
        printf("Encrypted: %s\n\n",decrypted);

    }
    else if (argc == 5 && strcasecmp(argv[1],"sub") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[4],"try") == 0){
        char * toDecrypt = argv[3];
        char decrypted[strlen(toDecrypt) + 1];
        int charCount = 0;
        char key[27];

        printf("Original:  %s\n\n",toDecrypt);
        subCipherDecryptTry(toDecrypt, decrypted, key);
        printf("\nDecrypted Attempt using decryption key %s: \n\n%s\n\n",key,decrypted);
    }
    /*
    #################################################################################################################################
    FILE FUNCTIONS
    #################################################################################################################################   
    */
    else if (argc == 6 && strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"encrypt") == 0 && strcasecmp(argv[5],"file") == 0){
        char * filePath = argv[3];
        FILE * fileToEncrypt;
        int charCount = 0;
        int key = atoi(argv[4]);

        //Opening File
        fileToEncrypt = fopen(filePath,"r");
        if (fileToEncrypt == NULL){ 
            printf("Could not open file %s", filePath); 
            return 1; 
        } 

        unsigned int fileSize;
        fseek(fileToEncrypt,0L,SEEK_END);
        fileSize = ftell(fileToEncrypt);
        rewind(fileToEncrypt);
        
        char toEncrypt[fileSize];
        char encrypted[fileSize];

        //transcribing file to string.
        for(char c = fgetc(fileToEncrypt); c != EOF && charCount != MAX_SIZE_FILE_CM; c = fgetc(fileToEncrypt),charCount++){
            toEncrypt[charCount] = c;
        }
        toEncrypt[charCount] = 0;


        railFenceEncrypt(toEncrypt,encrypted,key);
        printf("\n\nEncrypted:\n\n%s\n",encrypted);

        stringToFileQuestion(encrypted);

    }
    else if (argc == 6 && strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[5],"file") == 0 && strcasecmp(argv[4],"try") != 0){

        char* filePath = argv[3];
        FILE * fileToDecrypt;
        int charCount = 0;
        int key = atoi(argv[4]);

        fileToDecrypt = fopen(filePath,"r");
        if (fileToDecrypt == NULL) 
        { 
            printf("Could not open file %s", filePath); 
            return 1; 
        } 

        unsigned int fileSize;
        fseek(fileToDecrypt,0L,SEEK_END);
        fileSize = ftell(fileToDecrypt);
        rewind(fileToDecrypt);
        
        char toDecrypt[fileSize];
        char decrypted[fileSize];

        for(char c = fgetc(fileToDecrypt); c != EOF && charCount != MAX_SIZE_FILE_CM; c = fgetc(fileToDecrypt),charCount++){
            toDecrypt[charCount] = c;
        }
        toDecrypt[charCount] = 0;
        railFenceDecrypt(toDecrypt,decrypted,key);
        printf("%s\n",decrypted);

        stringToFileQuestion(decrypted);
    }
    else if (argc == 6 && strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[4],"try") == 0 && strcasecmp(argv[5],"file") == 0){
        char* filePath = argv[3];
        FILE * fileToDecrypt;
        int charCount = 0;
        const int railMAX = 10;

        fileToDecrypt = fopen(filePath,"r");
        if (fileToDecrypt == NULL) 
        { 
            printf("Could not open file %s", filePath); 
            return 1; 
        } 

        unsigned int fileSize;
        fseek(fileToDecrypt,0L,SEEK_END);
        fileSize = ftell(fileToDecrypt);
        rewind(fileToDecrypt);
        
        char toDecrypt[fileSize];
        char decrypted[fileSize];


        for(char c = fgetc(fileToDecrypt); c != EOF && charCount != MAX_SIZE_FILE_CM; c = fgetc(fileToDecrypt),charCount++){
            toDecrypt[charCount] = c;
        }
        toDecrypt[charCount] = 0;


        printf("Attempting to decrypt the below with rail keys 2 through %d\n\n%s\n\n",railMAX,argv[3]);
        railFenceDecryptTry(toDecrypt,decrypted,railMAX);
        printf("%s\n",decrypted);

        stringToFileQuestion(decrypted);
    }
    else if (argc == 7 && strcasecmp(argv[1],"rail2") == 0 && strcasecmp(argv[2],"encrypt") == 0 && strcasecmp(argv[6],"file") == 0){
        char* filePath = argv[3];
        FILE * fileToEncrypt;
        int charCount = 0;

        int key1 = atoi(argv[4]);
        int key2 = atoi(argv[5]);

        //Opening File
        fileToEncrypt = fopen(filePath,"r");
        if (fileToEncrypt == NULL){ 
            printf("Could not open file %s", filePath); 
            return 1; 
        } 

        unsigned int fileSize;
        fseek(fileToEncrypt,0L,SEEK_END);
        fileSize = ftell(fileToEncrypt);
        rewind(fileToEncrypt);
        
        char toEncrypt[fileSize];
        char encrypted[fileSize];

        //transcribing file to string.
        for(char c = fgetc(fileToEncrypt); c != EOF && charCount != MAX_SIZE_FILE_CM; c = fgetc(fileToEncrypt),charCount++){
            toEncrypt[charCount] = c;
        }
        toEncrypt[charCount] = 0;



        if (key1 < key2){
            int aux = key1;
            key1 = key2;
            key2 = aux;
            printf("Swapped keys as key 1 (%d) was less than key 2 (%d)\n", key2, key1);
        }
        if(key2 <= 1){
            printf("Error: Second Key must be 2 or greater\n");
            return 1;
        }

        printf("Original:\n\n %s\n\n",toEncrypt);
        rail2Encrypt(toEncrypt,encrypted,key1,key2);
        printf("Decrypted:\n\n %s\n\n",encrypted);

        stringToFileQuestion(encrypted);


    }
    else if (argc == 7 && strcasecmp(argv[1],"rail2") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[6],"file") == 0 && strcasecmp(argv[4],"try") != 0){
        int key1 = atoi(argv[4]);
        int key2 = atoi(argv[5]);

        char* filePath = argv[3];
        FILE * fileToDecrypt;
        int charCount = 0;

        fileToDecrypt = fopen(filePath,"r");
        if (fileToDecrypt == NULL) 
        { 
            printf("Could not open file %s", filePath); 
            return 1; 
        } 

        unsigned int fileSize;
        fseek(fileToDecrypt,0L,SEEK_END);
        fileSize = ftell(fileToDecrypt);
        rewind(fileToDecrypt);
        
        char toDecrypt[fileSize];
        char decrypted[fileSize];


        for(char c = fgetc(fileToDecrypt); c != EOF && charCount != MAX_SIZE_FILE_CM; c = fgetc(fileToDecrypt),charCount++){
            toDecrypt[charCount] = c;
        }
        toDecrypt[charCount] = 0;



        if (key1 < key2){
            int aux = key1;
            key1 = key2;
            key2 = aux;
            printf("Swapped keys as key 1 (%d) was less than key 2 (%d)\n", key2, key1);
        }
        if(key2 <= 1){
            printf("Error: Second Key must be 2 or greater\n");
            return 1;
        }

        printf("Original:\n\n %s\n\n",toDecrypt);
        rail2Decrypt(toDecrypt,decrypted,key1,key2);
        printf("Decrypted:\n\n%s\n\n",decrypted);

        stringToFileQuestion(decrypted);
    }
    else if (argc == 6 && strcasecmp(argv[1],"rail2") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[4],"try") == 0 && strcasecmp(argv[5],"file") == 0){
        int keyMAX = 10;
        char* filePath = argv[3];
        FILE * fileToDecrypt;
        int charCount = 0;

        fileToDecrypt = fopen(filePath,"r");
        if (fileToDecrypt == NULL) 
        { 
            printf("Could not open file %s", filePath); 
            return 1; 
        } 

        unsigned int fileSize;
        fseek(fileToDecrypt,0L,SEEK_END);
        fileSize = ftell(fileToDecrypt);
        rewind(fileToDecrypt);
        
        char toDecrypt[fileSize];
        char decrypted[fileSize];


        for(char c = fgetc(fileToDecrypt); c != EOF && charCount != MAX_SIZE_FILE_CM; c = fgetc(fileToDecrypt),charCount++){
            toDecrypt[charCount] = c;
        }
        toDecrypt[charCount] = 0;


        //printf("Original:  %s\n",toDecrypt);
        rail2DecryptTry(toDecrypt,decrypted,keyMAX);
        printf("Decrypted: %s\n",decrypted);

        stringToFileQuestion(decrypted);
    }
    else if (argc == 6 && strcasecmp(argv[1],"sub") == 0 && strcasecmp(argv[2],"encrypt") == 0 && strlen(argv[4]) == 26 && strcasecmp(argv[5],"file") == 0){
        char * filePath = argv[3];
        FILE * fileToEncrypt;
        int charCount = 0;
        char * key = argv[4];

        //Opening File
        fileToEncrypt = fopen(filePath,"r");
        if (fileToEncrypt == NULL){ 
            printf("Could not open file %s", filePath); 
            return 1; 
        } 

        unsigned int fileSize;
        fseek(fileToEncrypt,0L,SEEK_END);
        fileSize = ftell(fileToEncrypt);
        rewind(fileToEncrypt);
        
        char toEncrypt[fileSize];
        char encrypted[fileSize];

        //transcribing file to string.
        for(char c = fgetc(fileToEncrypt); c != EOF && charCount != MAX_SIZE_FILE_CM; c = fgetc(fileToEncrypt),charCount++){
            toEncrypt[charCount] = c;
        }
        toEncrypt[charCount] = 0;

        printf("Original:\n\n%s\n\n",toEncrypt);
        substitutionCipherEncrypt(toEncrypt, encrypted, key);
        printf("Encrypted:\n\n%s\n\n",encrypted);


        stringToFileQuestion(encrypted);
    }
    else if (argc == 6 && strcasecmp(argv[1],"sub") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strlen(argv[4]) == 26 && strcasecmp(argv[5],"file") == 0){
        char * filePath = argv[3];
        FILE * fileToDecrypt;
        int charCount = 0;
        char * key = argv[4];

        //Opening File
        fileToDecrypt = fopen(filePath,"r");
        if (fileToDecrypt == NULL){ 
            printf("Could not open file %s", filePath); 
            return 1; 
        } 


        unsigned int fileSize;
        fseek(fileToDecrypt,0L,SEEK_END);
        fileSize = ftell(fileToDecrypt);
        rewind(fileToDecrypt);
        
        char toDecrypt[fileSize];
        char decrypted[fileSize];

        //transcribing file to string.
        for(char c = fgetc(fileToDecrypt); c != EOF && charCount != MAX_SIZE_FILE_CM; c = fgetc(fileToDecrypt),charCount++){
            toDecrypt[charCount] = c;
        }
        toDecrypt[charCount] = 0;

        printf("Original:  %s\n\n",toDecrypt);
        substitutionCipherDecrypt(toDecrypt, decrypted, key);
        printf("Decrypted: \n%s\n\n",decrypted);

        stringToFileQuestion(decrypted);
    }
    else if (argc == 6 && strcasecmp(argv[1],"sub") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[5],"file") == 0 && strcasecmp(argv[4],"try") == 0){
        char * filePath = argv[3];
        FILE * fileToDecrypt;
        int charCount = 0;
        char key[26];

        //Opening File
        fileToDecrypt = fopen(filePath,"r");
        if (fileToDecrypt == NULL){ 
            printf("Could not open file %s", filePath); 
            return 1; 
        } 


        unsigned int fileSize;
        fseek(fileToDecrypt,0L,SEEK_END);
        fileSize = ftell(fileToDecrypt);
        rewind(fileToDecrypt);
        
        char toDecrypt[fileSize];
        char decrypted[fileSize];

        //transcribing file to string.
        for(char c = fgetc(fileToDecrypt); c != EOF && charCount != fileSize; c = fgetc(fileToDecrypt),charCount++){
            toDecrypt[charCount] = c;
        }
        toDecrypt[charCount] = 0;

        printf("Original:  %s\n\n",toDecrypt);
        subCipherDecryptTry(toDecrypt, decrypted, key);
        //printf("\nDecrypted Attempt using decryption key %s: \n\n%s\n\n",key,decrypted);

        stringToFileQuestion(decrypted);
    }
    else{
        printf("Incorrect arguments\n if you need help try './c3267533.out help'\n");
    }
    return 0;
}

int main_menu()
{
    char char_choice[3];
    int int_choice = 0;

    do
    {
        system("clear");//
        printf("\n");

        printf("Colton Millington ENGG1003 Asessment 1\t***IN PROGRESS***\nC3267533 -- Main Menu: \n\n");
        printf("1. Rail Cipher\n");
        printf("2. 2 Level Rail Cipher\n");
        printf("3. Substitution Cipher\n");
        printf("9. Exit\n\n");

        scanf("%s", char_choice);
        int_choice = atoi(char_choice);

        switch (int_choice)
        {
            case 1:
                rail_menu();
                break;
            case 2:
                rail2_menu();
                break;
            case 3:
                subs_menu();
                break;
            case 9:
                return 0;
                break;
            case 99:
                break;
            default:printf("Wrong choice. Enter Again");
                break;
        }
    }while(int_choice !=99);
    return 0;
}


int rail_menu(void)
{
    char char_choice[3];
    int int_choice = 0;

    do
    {
        system("clear");//
        printf("\n");

        printf("Colton Millington ENGG1003 Asessment 1\nC3267533 -- Rail Cipher Menu: \n\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt with known key\n");
        printf("3. Decrypt with maximum key\n");
        printf("9. Back\n\n");

        scanf("%s", char_choice);
        int_choice = atoi(char_choice);

        switch (int_choice)
        {
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                break;
            case 9:
                return 0;
                break;
            case 99:
                break;
            default:printf("Wrong choice. Enter Again");
                break;
        }
    }while(int_choice !=99);
    return 0;
}

int rail2_menu(void)
{
    char char_choice[3];
    int int_choice = 0;

    do
    {
        system("clear");//
        printf("\n");

        printf("Colton Millington ENGG1003 Asessment 1\nC3267533 -- Rail Cipher 2-Level Menu: \n\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt with known key\n");
        printf("3. Decrypt with maximum key\n");
        printf("9. Back\n\n");

        scanf("%s", char_choice);
        int_choice = atoi(char_choice);

        switch (int_choice)
        {
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                break;
            case 9:
                return 0;
                break;
            case 99:
                break;
            default:printf("Wrong choice. Enter Again");
                break;
        }
    }while(int_choice !=99);
    return 0;
}

int subs_menu(void)
{
    char char_choice[3];
    int int_choice = 0;

    do
    {
        system("clear");//
        printf("\n");

        printf("Colton Millington ENGG1003 Asessment 1\nC3267533 -- Substitution Cipher Menu: \n\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt with known key\n");
        printf("3. Decrypt with maximum key\n");
        printf("9. Back\n\n");

        scanf("%s", char_choice);
        int_choice = atoi(char_choice);

        switch (int_choice)
        {
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                break;
            case 9:
                return 0;
                break;
            case 99:
                break;
            default:printf("Wrong choice. Enter Again");
                break;
        }
    }while(int_choice !=99);
    return 0;
}

void stringToFileQuestion(char* stringToWriteToFile)
{

    
    char fileChoice[] = " ";

    //Asking to see if you want to write to a file or just leave it on the screen. 
    do{
        printf("\n\nDo you want to write to a file? (y/n)\n");
        scanf("%s",fileChoice);
    } while (strcasecmp(fileChoice,"y") != 0 && strcasecmp(fileChoice,"n") != 0 );

    if(strcasecmp(fileChoice,"y") == 0){
        char fileWritePath[256];
        FILE * encryptedFile;

        printf("Please Enter the file path to write to\nThis will overwrite the file if it exists\nThis will create a new file if path exists\n");
        scanf("%s",fileWritePath);
        encryptedFile = fopen(fileWritePath,"w");

        if(encryptedFile == NULL){ 
            printf("Could not open file %s", fileWritePath); 
            return; 
        }
        fprintf(encryptedFile,"%s",stringToWriteToFile);
        printf("done writing file\n");
    }


}
//##############################################################
//from railcipher.c
//##############################################################
void railFence(char *message, char *cipherText, int length, int A)
{
    railFenceEncrypt(message,cipherText,A);
    printf("encryptedMessage:\n\n%s\n",cipherText);
}

void padMessageRail(char* message,int key)
{
    int messageLen = strlen(message);

    int oneCycle = 2 * key - 2; //number of letters in one 'cycle'
    int numCycles = ceil(messageLen/oneCycle); //number of complete "W" shapes in the rail
    int numChars = numCycles * oneCycle + 1; //this is the number of characters in the padded string
    while (numChars < messageLen){
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
        while (numChars < messageLen){
            //the above algorithm for numCycles sometimes is one lower which causes the number of characters to be less than it should be in the 
            //padded string. This will add another cycle thus increasing the number of characters to the right number. 
            numCycles++;
            numChars = numCycles * oneCycle + 1;
        }
        if(numChars == messageLen){
            railFenceDecrypt(toDecrypt,temp,i);
            printf("\n\nKey: %d\t\tMessage: %s\n",i,temp);
        }
    }
    printf("\n\nWhich key is correct?: ");
    scanf("%d",&choice);
    railFenceDecrypt(toDecrypt,decrypted,choice);

    return choice;
}

//##############################################################
//from 2LevelRailCipher.c
//##############################################################

void railFence2(char *message, char *cipherText, int length, int A, int B,int dir)
{
    if(dir == 0){
        rail2Encrypt(message,cipherText,A,B);
    }
    else if (dir == 1){
        rail2Decrypt(cipherText,message,A,B);
    }
    else {
        printf("invalid dir. Valid Values are 0 to encrypt and 1 to decrypt");
    }
}

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

//##############################################################
//from substitutionCipher.c
//##############################################################

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
    decrypted[strlen(toDecrypt)] = 0;
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
            //for() //was going to do some word frequency analysis here but ran out of time...
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