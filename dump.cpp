
// CODE DUMP
/*
Removed Dynamic Memory Allocation for variable keysize

Some functions that have now been implemented differently
*/
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
	    temp = (byte)((signed char)ciphertext[i] >> 7);
	    b[i] = ciphertext[4*i + col] << 1;
	    b[i] ^= 0x1B & temp;
	}
	ciphertext[4*0 + col] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
	ciphertext[4*1 + col] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
	ciphertext[4*2 + col] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];        
	ciphertext[4*3 + col] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
}

*/


