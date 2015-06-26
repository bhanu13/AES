/* 
A C++ program that implements AES encryption and decryption with the help of an AES class.

User Accessible Functions - 
encrypt, decrypt, print, plain, cipher - Look below

Constant Block Size of 16 bytes
Variable Key Size of 128, 192 or 256 bits
10, 12 and 14 cycles respectively
Only implementing 128 bit AES | 128 bit - 16 bytes
No need for destructor - No dynamic memory allocation

Author - bagarwa2
*/

#ifndef _AES_H
#define _AES_H

#include <iostream>
#include <stdint.h>

typedef uint32_t word;
typedef unsigned char byte;

using namespace std;


class AES
{
public:
	// AES(byte & plaintext, byte & key, int keysize);
   AES(byte * text, byte * newkey);
	// ~AES();
	void encrypt();  // Applies the entire encryption algorithm
	void decrypt();
	void print(byte * data);  // Print function used to print any 16 byte array - 
   //Used for printing the encoded and decoded messages
   byte * plain();   // Returns a pointer to the plaintext private variable
   byte * cipher();  // Returns a pointer to the cipihertext private variable

private:
	byte plaintext[16];    // Contains the decoded message
	byte ciphertext[16];   // Contains the encoded message
	byte key[16];
	//int keysize;	// Possible vaues - 128, 192, 256 bits   // Chosen to be 128 only
	void SubBytes();
	void ShiftRows();
	// void MixColumns();
	void AddRoundKey(byte * currkey, byte * currtext);
   void KeyExpansion(byte * key_schedule);
   //void clear();
   void MixColumns(byte * result);
   
   //============Helper functions============//
   byte Math(word mul, byte val);
   byte xTime(byte val);
	void leftShift(int row);
   // void gmix_column(int col);
   word RotateWord(word u);
   void printword(word u);

};


#endif
