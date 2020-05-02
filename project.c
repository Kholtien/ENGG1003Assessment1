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
//#include "lib/2LevelRailCipher.h"
int main_menu(void);
int rail_menu(void);
int rail2_menu(void);
int subs_menu(void);

int main(int argc, char *argv[])
{
    if(argc == 1){
        //no arguments
        main_menu();
    }
    else if (strcasecmp(argv[1],"help") == 0){
        printf("This is not helpful\n");
    }
    else if (strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"encrypt") == 0){
        char encrypted[1000];
        railFenceEncrypt(argv[3],encrypted,atoi(argv[4]));
        printf("%s\n",encrypted);
    }
    else if (strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[4],"try") != 0){
        char decrypted[1000];
        railFenceDecrypt(argv[3],decrypted,atoi(argv[4]));
        printf("%s\n",decrypted);
    }
    else if (strcasecmp(argv[1],"rail") == 0 && strcasecmp(argv[2],"decrypt") == 0 && strcasecmp(argv[4],"try") == 0){
        printf("Attempting to decrypt '%s' with rail keys 2 through 10",argv[3]);
        char decrypted[1000];
        railFenceDecryptTry(argv[3],decrypted,10);
        printf("%s\n",decrypted);
    }
//    else if (strcasecmp(argv[1],"rail2") == 0 && strcasecmp(argv[2],"encrypt") == 0){
//        int key1 = atoi(argv[4]);
//        int key2 = atoi(argv[5]);
//        if (key1 < key2){
//            int aux = key1;
//            key1 = key2;
//            key2 = aux;
//            printf("Swapped keys as key 1 was less than key 2");
//        }
//        if(key2 <= 1){
//            printf("Error: Second Key must be 2 or greater");
//            return 1;
//        }
//
//        char encrypted[1000];
//        rail2encrypt(argv[3],encrypted,key1,key2);
//        printf("%s\n",encrypted);
//    }
    else{
        printf("got to the else");
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

        printf("Colton Millington ENGG1003 Asessment 1\nC3267533 -- Main Menu: \n\n");
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