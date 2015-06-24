#include "AES.h"
#include "tables.h"

AES::AES(byte * text, byte * newkey)
{
	for(int i = 0; i<16; i++)
		plaintext[i] = text[i];
	for(int i = 0; i<16; i++)
		key[i] = newkey[i];
}

void AES::encrypt()	//TODO
{
	//int rounds = (keysize-128)/32 + 10;
	byte key_schedule[16*11];
	unsigned int roundkey_ind = 0;

	KeyExpansion(key_schedule);
	AddRoundKey(&(key_schedule[roundkey_ind]), key);
	roundkey_ind +=16;

	for(int i = 0; i < 9; i++)
	{
		SubBytes();
		ShiftRows();
		MixColumns();
		AddRoundKey(&(key_schedule[roundkey_ind]), ciphertext);
		roundkey_ind += 16;

	}
	// Final Round
	SubBytes();
	ShiftRows();
	AddRoundKey(&(key_schedule[roundkey_ind]), ciphertext);
	cout<<"Encryption Complete"<<endl;
}

//=======================================
void AES::KeyExpansion(byte * key_schedule)
{


}

//=======================================
void AES::AddRoundKey(byte * currkey, byte * currtext)	//TODO
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			int idx = (i * 4) + j;
			ciphertext[idx] = currtext[idx] ^ currkey[idx];
		}
	}
}

//====================================
void AES::SubBytes()	//Done
{
	for(int i = 0; i<16; i++)
	{
		int col = ciphertext[i] & 0x0f;
		int row = ciphertext[i] & 0xf0;
		ciphertext[i] = s[row*4 + col];
	}
}

//=====================================
// Left Shifting the no. of times as the row number
void AES::ShiftRows()	//Done
{
	for(int i = 0; i<4; i++)	// Row variable
	{
		leftShift(i);
	}
}

void AES::leftShift(int row)	//Done
{
	byte temp; 
	for(int i = 0; i<row; i++)
	{
		temp = ciphertext[4*row + 0];
		ciphertext[4*row + 0] = ciphertext[4*row + 1];
		ciphertext[4*row + 1] = ciphertext[4*row + 2];
		ciphertext[4*row + 2] = ciphertext[4*row + 3];
		ciphertext[4*row + 3] = temp;	
	}
}

//=======================================
void AES::MixColumns()	// Done
{
	for(int i = 0; i<4; i++)
	{
		gmix_column(i);
	}
}

void AES::gmix_column(int col) // Done
{
	byte a[4];
	byte b[4];
	byte temp;
	for(int i =0; i<4; i++)
	{
	    a[i] = ciphertext[4*i + col];
	    temp = (byte)((signed char)ciphertext[i] >> 7); // arithmetic right shift, thus shifting in either zeros or ones
	    b[i] = ciphertext[4*i + col] << 1; // implicitly removes high bit because b[c] is an 8-bit char, so we xor by 0x1b and not 0x11b in the next line
	    b[i] ^= 0x1B & temp; // Rijndael's Galois field
	}
	ciphertext[4*0 + col] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
	ciphertext[4*1 + col] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
	ciphertext[4*2 + col] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];        
	ciphertext[4*3 + col] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
}

void AES::printdetails()
{
	for(int i = 0; i < 16; i++)
	{
		if(i % 4 == 0)
			cout<<endl;
		printf("%02x ", ciphertext[i]);
	}
	cout<<endl;
}



//========================================
// CODE DUMP
//Removed Dynamic Memory Allocation for variable keysize

/*
AES::AES(byte (&text)[16], byte * newkey, int keysize)
{
	if(keysize != 128 || keysize != 192 || keysize != 256)
	{
		cout<<"Invalid keysize"<<endl;
		key = NULL;
		return;
	}
	else
	{
		for(int i = 0; i<16; i++)
			plaintext[i] = text[i];
		
		key = new byte((keysize%8))
		for(int i = 0; i<keysize%8; i++)
		{
			key[i] = newkey[i];
		}
	}
}
AES::~AES()
{
	clear();
}


void AES::clear()
{
	if(key != NULL)
	{
		for(int i = 0; i<(keysize%8); i++)
			delete key[i];
	}
	key = NULL;
	keysize = 0;
}
*/


