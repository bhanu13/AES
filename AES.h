// A simple program that implements AES encryption and decryption

// 128 bit - 16 bytes
/*
Constant Block Size of 16 bytes
Variable Key Size of 128, 192 or 256 bits
10, 12 and 14 cycles respectively

I am only implementing 128 bit AES
No need for constructor - destructor
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
	void encrypt();
	void decrypt();
	void print(byte * data);
   byte * plain();
   byte * cipher();

//private:
	byte plaintext[16];
	byte ciphertext[16];
	byte key[16];
	//int keysize;	// Possible vaues - 128, 192, 256 bits   // Chosen to be 128 only
	void SubBytes();
	void ShiftRows();
	void MixColumns();
	void AddRoundKey(byte * currkey, byte * currtext);
   void KeyExpansion(byte * key_schedule);
   //void clear();
	void leftShift(int row);
   void gmix_column(int col);
   word RotateWord(word u);
   void printword(word u);
   //===============Testing
   // void MixColumns(byte * result);
   // unsigned char weirdMath(int mul, unsigned char val);
   // unsigned char xTime(unsigned char val);




};


#endif
