#include "AES.h"
#include "tables.h"


AES::AES(byte * text, byte * newkey)
{
	for(int i = 0; i<16; i++)
	{
		plaintext[i] = text[i];
		key[i] = newkey[i];
		ciphertext[i] = text[i];
	}
}

void AES::encrypt()	//TODO
{
	//int rounds = (keysize-128)/32 + 10;
	byte key_schedule[16*11];
	unsigned int roundkey_ind = 0;
	print(ciphertext);

	KeyExpansion(key_schedule);
	AddRoundKey(&(key_schedule[roundkey_ind]), ciphertext);
	roundkey_ind +=16;
	print(ciphertext);
	for(int i = 0; i < 9; i++)
	{
		SubBytes();
		print(ciphertext);
		ShiftRows();
		print(ciphertext);
		MixColumns();
		// MixColumns(ciphertext);
		print(ciphertext);
		AddRoundKey(&(key_schedule[roundkey_ind]), ciphertext);
		print(ciphertext);
		roundkey_ind += 16;

	}
	// Final Round
	SubBytes();
	ShiftRows();
	AddRoundKey(&(key_schedule[roundkey_ind]), ciphertext);
	cout<<"Encryption Complete"<<endl;
	print(ciphertext);
}

//=======================================
void AES::KeyExpansion(byte * key_schedule)	// Function Done
{
	for(int i = 0; i<4; i++)
	{
		for(int j = 0; j<4; j++)
		{
			key_schedule[4*i + j] = key[4*i + j];	
		}
	}

	int i = 4;


	while( i < (4 * 11))
	{
		word prev = 0;
		for(int j = 0; j < 4; j++)
		{
			prev = prev << 8;
			prev += key_schedule[(4*(i-1)) + j ];
		}
		// cout<<"Printing Word"<<endl;
		// printword(prev);
		word t = prev;

		if(i % 4 == 0)
		{
			t = RotateWord(t);

			byte a[4];
			for(int j = 0; j<4; j++)
			{
				a[j] = s[(byte)(t & 0xff)];
				t = t>>8;
				//printf("%02x ", a[j]);
			}
			//cout<<endl;
			a[3] = a[3] ^ Rcon[(i/4)];
			// cout << (int)Rcon[(i/4)] << "Rcon val"<<endl;
			// printf("%02x ", a[3]);
			// cout<<endl;

			t = 0;
			for(int j = 3; j>=0; j--)
			{
				t = t<<8;
				t = t + a[j];
			}
		}
		// if(i == 8)
		// {
		// 	printword(t);
		// 	cout<< " Checking value" <<endl;
		// }
			

		word temp = 0;
		for(int j = 0 ; j<4; j++)
		{
			temp = temp<<8;
			temp += key_schedule[4*(i-4) + j];
		}
		word result = t ^ temp;

		for(int j = 0; j<4; j++)
		{
			key_schedule[4*i + j] = (result >> 24) & 0xff;
			result = result << 8;
		}
		// if(i % 4 == 3)
		// 	print(&key_schedule[4*i]);

		i++;
		// break;
	}
	// cout<<"KeyExpansion Printing"<<endl;
	// print(key_schedule);
	// print(&key_schedule[16]);
}

word AES::RotateWord(word u)
{
	return ((u<<8) | (u>>24));
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
	byte temp[16];
	for(int i = 0; i<4; i++)
	{
		for(int j = 0; j<4; j++)
		{
			temp[4*i + j] = ciphertext[4*i + j]; //= s[ciphertext[i*4 + j]];
		}
	}
	for(int i = 0; i<4; i++)
	{
		for(int j = 0; j<4; j++)
		{
			ciphertext[4*i + j] = s[temp[i*4 + j]];
		}
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



void AES::print(byte * data)
{
	for(int i = 0; i < 16; i++)
	{
		if(i % 4 == 0)
			cout<<endl;
		printf("%02x ", data[i]);
	}
	cout<<endl;
}
void AES::printword(word u)
{
	for(int i = 0; i<4; i++)
	{
		printf("%02x ", (byte)((u>>24)&0xff));
		u = u<<8;		
	}
	cout<<endl;
}

byte * AES::plain()
{
	return plaintext;
}

byte * AES::cipher()
{
	return ciphertext;
}


//=======================================
// void AES::MixColumns(byte * result)
// {
// 	byte state[16];
// 	for(int i = 0; i<4; i++)
// 	{
// 		for(int j = 0; j<4; j++)
// 		{
// 			state[4*i + j] = result[4*i + j]; //= s[ciphertext[i*4 + j]];
// 		}
// 	}
// 	for(int i = 0; i < 4; i++)
// 	{
// 		int ind = (i*4);
// 		result[ind]   = weirdMath(2, state[ind]) ^ weirdMath(3, state[ind+1]) ^ state[ind+2] ^ state[ind+3];
// 		result[ind+1] = state[ind] ^ weirdMath(2, state[ind+1]) ^ weirdMath(3, state[ind+2]) ^ state[ind+3];
// 		result[ind+2] = state[ind] ^ state[ind+1] ^ weirdMath(2, state[ind+2]) ^ weirdMath(3, state[ind+3]);
// 		result[ind+3] = weirdMath(3, state[ind]) ^ state[ind+1] ^ state[ind+2] ^ weirdMath(2, state[ind+3]);
// 	}
// }

// unsigned char AES::weirdMath(int mul, unsigned char val)
// {
// 	if(mul <= 2)
// 		return xTime(val);
// 	else
// 		return weirdMath(mul-1, val) ^ val;
// }

// unsigned char AES::xTime(unsigned char val)
// {
// 	if(val & 0x80) {
// 		return val << 1;
// 	} else {
// 		return ((val << 1) ^ 0x1b);
// 	}
// }

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


