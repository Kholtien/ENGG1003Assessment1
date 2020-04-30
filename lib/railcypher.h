#ifndef RAILCYPHER_H_
#define RAILCYPHER_H_


//encrypts the string toEncrypt. The encrypted string will at the pointer encrypted
void railFenceEncrypt(char* toEncrypt,char* encrypted, int key);

//pads message so it will complete the zig zag
void padMessageRail(char* message,int key);

//decrypts the string toDecrypt and the decrypted string will be the decrypted string
void railFenceDecrypt(char* toDecrypt,char* decrypted, int key);

//runs the railFenceDecrypt function through key = 2 to key = keyMAX
int railFenceDecryptTry(char* toDecrypt,char* decrypted, int keyMAX);

//int main()
//{
//    int i, len, rails;
//    char str[1000];
//    char encryptedStr[1000];
//
//    char message[] = "Wow, this is a really cool message";
//    len = strlen(message);
//    rails = 4;
//    for (i = 0; i < len; i++){
//        str[i] = message[i];
//    }
//    str[i] = 0;
//
//    //printf("Enter a Secret Message (one line only)\n");
//    //scanf("%[^\n]%*c", str);
//    
//    //printf("Enter number of rails\n");
//    //scanf("%d", &rails);
//
//    railFenceEncrypt(str,encryptedStr,rails);
//
//    printf("%s\n%s\n",str,encryptedStr);
//
//    railFenceDecrypt(encryptedStr,str,rails);
//
//    printf("%s\n%s\n",str,encryptedStr);
//
//    railFenceDecryptTry(encryptedStr,str,10);
//
//    return 0;
//}


#endif //RAILCYPHER_H_