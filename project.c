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
#include "./lib/railcypher.h"
int main_menu(void);

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

		printf("Vorpal Hoff -- Main Menu: \n\n");
		printf("1. Quick Connect\n");
		printf("2. FTDI Menu\n");
		printf("3. Open HM-1X Menu\n");
		printf("4. Connect LPC\n");
		printf("5. Program Chip\n");
		printf("6. Erase LPC\n");
		printf("7. Decode UUE debug file\n");
		printf("8. Parse hex-file and write to debug.hex\n");
		printf("9. Exit\n");

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
			case 4:
				// Not yet used.
				break;
			case 5:
				
			    break;
			case 6:
				// Not yet used.
			    break;
			case 7:
				// Not yet used.
			    break;
			case 8:
				
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