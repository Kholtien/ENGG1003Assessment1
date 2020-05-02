/*
########################################################################
#
#   Course:     ENGG1003
#   Project:    Programming Assignment 1
#   Author:     Colton Millington c3267533 
#   Date:       2020-04-30
#   Details:    Main file for running the encryption/decryption
#               programs
#   Usage:      Run with no arguments will get CLI menu
#                   Will have the choice to import text from 
#                   files or write them in the console
#               Run with arguments to do a single command
#                   such as project.exe encrypt ./data/ciphpher.txt
#
########################################################################
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "lib/railcipher.h"
#include "lib/2LevelRailCipher.h" 
#include "lib/substitutionCipher.h"

#define MAX_SIZE_FILE_CM 8193 //8 * 1024 + 1

int main_menu(void);
int rail_menu(void);
int rail2_menu(void);
int subs_menu(void);
void stringToFileQuestion(char* stringToWriteToFile);

int main(int argc, char *argv[])
{
    if(argc == 1){
        //no arguments
        main_menu();
    }
    else if (argc == 2 && strcasecmp(argv[1],"help") == 0){
        printf("Here's a few examples of commands you can use:\n\n");
        printf("bin/project rail encrypt 'This is such a great message. Truly Tremendous.' 4\n");
        printf("bin/project rail decrypt 'Ts asTTdWhi haetsa r rnoNi sc r eg.uyeeu.sugmelms' 4\n");
        printf("bin/project rail decrypt 'Ts asTTdWhi haetsa r rnoNi sc r eg.uyeeu.sugmelms' try\n");
        printf("bin/project rail2 encrypt 'This is such a great message. Truly Tremendous.'7 4\n");
        printf("bin/project rail2 decrypt 'TaTQhet rMir yeBsugmelmsB sc eg.ueu.Ri hasa rnoNLs sTdW' 7 4\n");
        printf("bin/project rail2 decrypt 'TaTQhet rMir yeBsugmelmsB sc eg.ueu.Ri hasa rnoNLs sTdW' try\n");
        printf("bin/project sub encrypt 'This is such a great message. Truly Tremendous.' GHIDXZLMBNOPFQERSTCUVWAKYJ\n");
        printf("bin/project sub encrypt 'UMBC BC CVIM G LTXGU FXCCGLX. UTVPY UTXFXQDEVC.' GHIDXZLMBNOPFQERSTCUVWAKYJ\n");
        printf("bin/project sub encrypt 'UMBC BC CVIM G LTXGU FXCCGLX. UTVPY UTXFXQDEVC.' try *****\n");
        printf("\nYou can also replace the message with a filepath and add an additional argument 'file'\n\n");
        printf("bin/project rail encrypt data/alchemist.txt 4 file\n");
        printf("\n\t\t*****\t this feature isn't yet implemented\n");

    }
    /*
    #################################################################################################################################
    Inline CLI Argument FUNCTIONS
    #################################################################################################################################   
    */
    else if (argc == 5 && strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"encrypt") == 0){
        char encrypted[1000];
        railFenceEncrypt(argv[3],encrypted,atoi(argv[4]));
        printf("%s\n",encrypted);
    }
    else if (argc == 5 && strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[4],"try") != 0){
        char decrypted[1000];
        railFenceDecrypt(argv[3],decrypted,atoi(argv[4]));
        printf("%s\n",decrypted);
    }
    else if (argc == 5 && strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[4],"try") == 0){
        const int railMAX = 10;
        printf("Attempting to decrypt the below with rail keys 2 through %d\n\n%s",railMAX,argv[3]);
        char decrypted[1000];
        railFenceDecryptTry(argv[3],decrypted,railMAX);
        printf("%s\n",decrypted);
    }
    else if (argc == 6 && strcasecmp(argv[1],"rail2") == 0 && strcasecmp(argv[2],"encrypt") == 0){
        int key1 = atoi(argv[4]);
        int key2 = atoi(argv[5]);
        char encrypted[1000];
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
    else if (argc == 6 && strcasecmp(argv[1],"rail2") == 0 && strcasecmp(argv[2],"decrypt") == 0){
        int key1 = atoi(argv[4]);
        int key2 = atoi(argv[5]);
        char decrypted[1000];
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
        char decrypted[1000];
        char* toDecrypt = argv[3];
        //strcpy(toEncrypt,argv[3]);


        //printf("Original:  %s\n",toDecrypt);
        rail2DecryptTry(toDecrypt,decrypted,keyMAX);
        printf("Decrypted: %s\n",decrypted);
    }
    else if (argc == 5 && strcasecmp(argv[1],"sub") == 0 && strcasecmp(argv[2],"encrypt") == 0 && strlen(argv[4]) == 26){
        char* toEncrypt = argv[3];
        char* key = argv[4];
        char encrypted[8 * 1024 + 1];

        printf("Original:  %s\n\n",toEncrypt);
        substitutionCipherEncrypt(toEncrypt, encrypted, key);
        printf("Encrypted: %s\n\n",encrypted);

    }
    else if (argc == 5 && strcasecmp(argv[1],"sub") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strlen(argv[4]) == 26){
        char* toDecrypt = argv[3];
        char* key = argv[4];
        char decrypted[8 * 1024 + 1];

        printf("Original:  %s\n\n",toDecrypt);
        substitutionCipherDecrypt(toDecrypt, decrypted, key);
        printf("Encrypted: %s\n\n",decrypted);

    }
    else if (argc == 5 && strcasecmp(argv[1],"sub") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[4],"try") == 0){
        printf("Not yet supported. See ./project help for available functions");
    }
    /*
    #################################################################################################################################
    FILE FUNCTIONS
    #################################################################################################################################   
    */
    else if (argc == 6 && strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"encrypt") == 0 && strcasecmp(argv[5],"file") == 0){
        char * filePath = argv[3];
        FILE * filetoEncrypt;
        char toEncrypt[MAX_SIZE_FILE_CM];
        char encrypted[MAX_SIZE_FILE_CM];
        int charCount = 0;
        int key = atoi(argv[4]);

        //Opening File
        filetoEncrypt = fopen(filePath,"r");
        if (filetoEncrypt == NULL){ 
            printf("Could not open file %s", filePath); 
            return 1; 
        } 

        //transcribing file to string.
        for(char c = fgetc(filetoEncrypt); c != EOF && charCount != MAX_SIZE_FILE_CM; c = fgetc(filetoEncrypt),charCount++){
            toEncrypt[charCount] = c;
        }
        toEncrypt[charCount] = 0;


        railFenceEncrypt(toEncrypt,encrypted,key);
        printf("Encrypted:\n\n%s\n",encrypted);

        stringToFileQuestion(encrypted);

    }
    else if (argc == 6 && strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[5],"file") == 0 && strcasecmp(argv[4],"try") != 0){
        char* filePath = argv[3];
        FILE * fileToDecrypt;
        char toDecrypt[MAX_SIZE_FILE_CM];
        char decrypted[MAX_SIZE_FILE_CM];
        int charCount = 0;
        int key = atoi(argv[4]);

        fileToDecrypt = fopen(filePath,"r");
        if (fileToDecrypt == NULL) 
        { 
            printf("Could not open file %s", filePath); 
            return 1; 
        } 

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
        char toDecrypt[MAX_SIZE_FILE_CM];
        char decrypted[MAX_SIZE_FILE_CM];
        int charCount = 0;
        const int railMAX = 10;

        fileToDecrypt = fopen(filePath,"r");
        if (fileToDecrypt == NULL) 
        { 
            printf("Could not open file %s", filePath); 
            return 1; 
        } 

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
    else if (argc == 6 && strcasecmp(argv[1],"rail2") == 0 && strcasecmp(argv[2],"decrypt") == 0){
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
        char encrypted[8 * 1024 + 1];

        printf("Original:  %s\n\n",toEncrypt);
        substitutionCipherEncrypt(toEncrypt, encrypted, key);
        printf("Encrypted: %s\n\n",encrypted);

    }
    else if (argc == 5 && strcasecmp(argv[1],"sub") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strlen(argv[4]) == 26){
        char* toDecrypt = argv[3];
        char* key = argv[4];
        char decrypted[8 * 1024 + 1];

        printf("Original:  %s\n\n",toDecrypt);
        substitutionCipherDecrypt(toDecrypt, decrypted, key);
        printf("Encrypted: %s\n\n",decrypted);

    }
    else{
        printf("Incorrect arguments\n if you need help try 'project help'\n");
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