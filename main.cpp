/*
Testing 128 bit AES encryption
using a sample message and key
*/


#include "AES.h"

int main()
{
	byte key[16] = {0x00, 0x01, 0x02, 0x03,
					0x04, 0x05, 0x06, 0x07,
					0x08, 0x09, 0x0a, 0x0b,
					0x0c, 0x0d, 0x0e, 0x0f };
	
	byte message[16] = {0xec, 0xe2, 0x98, 0xdc,
						0xec, 0xe2, 0x98, 0xdc,
						0xec, 0xe2, 0x98, 0xdc,
						0xec, 0xe2, 0x98, 0xdc };
	// Bug Finding - Testing All Functions Individually
	// AES bug(message, key);
	// bug.SubBytes();
	// bug.ShiftRows();
	// bug.print(bug.cipher());

	byte expected_res[16] = {
						0xda, 0xec, 0x30, 0x55,
						0xdf, 0x05, 0x8e, 0x1c, 
						0x39, 0xe8, 0x14, 0xea, 
						0x76, 0xf6, 0x74, 0x7e };

	AES test(message, key);
	test.encrypt();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j< 4; j++)
		{
			if((test.cipher())[4*i + j] != expected_res[4*i + j])
			{				
				cout<<"Incorrect Encryption"<<endl;
				return 0;			
			}
		}
	}
	test.print(test.cipher());
	cout<<"Correct Encryption"<<endl;
}