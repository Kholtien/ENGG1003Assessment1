#ifndef SUBSCIPHER_H_
#define SUBSCIPHER_H_


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


#endif //SUBSCIPHER_H_