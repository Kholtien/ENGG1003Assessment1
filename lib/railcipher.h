#ifndef RAILCIPHER_H_
#define RAILCIPHER_H_

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <math.h>


//encrypts the string toEncrypt. The encrypted string will at the pointer encrypted
void railFenceEncrypt(char* toEncrypt,char* encrypted, int key);

//pads message so it will complete the zig zag
void padMessageRail(char* message,int key);

//decrypts the string toDecrypt and the decrypted string will be the decrypted string
void railFenceDecrypt(char* toDecrypt,char* decrypted, int key);

//runs the railFenceDecrypt function through key = 2 to key = keyMAX
int railFenceDecryptTry(char* toDecrypt,char* decrypted, int keyMAX);

#endif //RAILCYPHER_H_