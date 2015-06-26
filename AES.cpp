/*
Implementation of the functions declared in AES.h
Author - bagarwa2
*/
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
	word roundkey_ind = 0;
	// cout<<"Original Text"<<endl;
	// print(ciphertext);

	KeyExpansion(key_schedule);
	AddRoundKey(&(key_schedule[roundkey_ind]), ciphertext);
	roundkey_ind +=16;
	// cout<<"After round 1"<<endl;
	// print(ciphertext);
	for(int i = 0; i < 9; i++)
	{
		SubBytes();
		// cout<<"After SubBytes"<<endl;
		// print(ciphertext);
		ShiftRows();
		// cout<<"ShiftRows"<<endl;
		// print(ciphertext);
		// MixColumns();
		MixColumns(ciphertext);
		// cout<<"After Mix Columns"<<endl;
		// print(ciphertext);
		AddRoundKey(&(key_schedule[roundkey_ind]), ciphertext);
		// cout<<"After AddRoundKey"<<endl;
		// print(ciphertext);
		roundkey_ind += 16;

	}
	// Final Round
	SubBytes();
	ShiftRows();
	AddRoundKey(&(key_schedule[roundkey_ind]), ciphertext);
	cout<<"Encryption Complete"<<endl;
	// print(ciphertext);
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
void AES::AddRoundKey(byte * currkey, byte * currtext)	//Done
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
		temp = ciphertext[4*0 + row];
		ciphertext[4*0 + row] = ciphertext[4*1 + row];
		ciphertext[4*1 + row] = ciphertext[4*2 + row];
		ciphertext[4*2 + row] = ciphertext[4*3 + row];
		ciphertext[4*3 + row] = temp;	
	}
}

//=======================================
void AES::MixColumns(byte * result)
{
	byte state[16];
	for(int i = 0; i<4; i++)
	{
		for(int j = 0; j<4; j++)
		{
			state[4*i + j] = result[4*i + j];
		}
	}
	for(int i = 0; i < 4; i++)
	{
		word ind = i*4;
		result[ind]   = Math(2, state[ind]) ^ Math(3, state[ind+1]) ^ state[ind+2] ^ state[ind+3];
		result[ind+1] = state[ind] ^ Math(2, state[ind+1]) ^ Math(3, state[ind+2]) ^ state[ind+3];
		result[ind+2] = state[ind] ^ state[ind+1] ^ Math(2, state[ind+2]) ^ Math(3, state[ind+3]);
		result[ind+3] = Math(3, state[ind]) ^ state[ind+1] ^ state[ind+2] ^ Math(2, state[ind+3]);
	}
}

byte AES::Math(word mul, byte val)
{
	if(mul <= 2)
		return xTime(val);
	else
		return Math(mul-1, val) ^ val;
}

byte AES::xTime(byte val)
{
	if(val & 0x80)
		return val << 1;
	else
		return ((val << 1) ^ 0x1b);
}

//=======================================
// A couple of helper functions
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


//========================================