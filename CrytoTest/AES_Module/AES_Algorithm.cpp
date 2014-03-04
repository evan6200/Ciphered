/*
******************************************************************
**       Advanced Encryption Standard implementation in C.      **
**       By Niyaz PK                                            **
**       E-mail: niyazlife@gmail.com                            **
**       Downloaded from Website: www.hoozi.com                 **
******************************************************************
This is the source code for encryption using the latest AES algorithm.
AES algorithm is also called Rijndael algorithm. AES algorithm is 
recommended for non-classified by the National Institute of Standards 
and Technology(NIST), USA. Now-a-days AES is being used for almost 
all encryption applications all around the world.

THE MAIN FEATURE OF THIS AES ENCRYPTION PROGRAM IS NOT EFFICIENCY; IT
IS SIMPLICITY AND READABILITY. THIS SOURCE CODE IS PROVIDED FOR ALL
TO UNDERSTAND THE AES ALGORITHM.

Comments are provided as needed to understand the program. But the 
user must read some AES documentation to understand the underlying 
theory correctly.

It is not possible to describe the complete AES algorithm in detail 
here. For the complete description of the algorithm, point your 
browser to:
http://www.csrc.nist.gov/publications/fips/fips197/fips-197.pdf

Find the Wikipedia page of AES at:
http://en.wikipedia.org/wiki/Advanced_Encryption_Standard
******************************************************************
*/

// Include stdio.h for standard input/output.
// Used for giving output to the screen.
#include "stdafx.h"
#include "AES_Algorithm.h"
#include <string.h>


const unsigned char sbox[256] = {
	//0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 }; //F

const unsigned char rsbox[256] = {
	  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb
	, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb
	, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e
	, 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25
	, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92
	, 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84
	, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06
	, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b
	, 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73
	, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e
	, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b
	, 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4
	, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f
	, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef
	, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61
	, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

// The round constant word array, Rcon[i], contains the values given by 
// x to th e power (i-1) being powers of x (x is denoted as {02}) in the field GF(2^8)
// Note that i starts at 1, not 0).
const unsigned char Rcon[255] = {
	0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 
	0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 
	0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 
	0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 
	0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 
	0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 
	0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 
	0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 
	0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 
	0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 
	0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 
	0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 
	0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 
	0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 
	0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 
	0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb  };


// The number of columns comprising a state in AES. This is a constant in AES. Value=4
#define Nb 4

// The number of rounds in AES Cipher. It is simply initiated to zero. The actual value is recieved in the program.
#define Nr 10

// in - it is the array that holds the plain text to be encrypted.
// out - it is the array that holds the key for encryption.
// state - the array that holds the intermediate results during encryption.
unsigned char state[4][4];

// The array that stores the round keys.
//unsigned char RoundKey[240];
unsigned char RoundKey[176];

unsigned char IV[16];


void Xor(unsigned char* buff, unsigned char* chain)
{
	int i;

	for (i = 0; i < 16; i++)
	{
		*(buff++) ^= *(chain++);
	}
}

void AES_SetIV(unsigned char *pIV)
{
	memcpy(IV, pIV, 16);
}


// This function produces Nb(Nr+1) round keys. The round keys are used in each round to encrypt the states.
// The length of Key is fixed to 128 bits
void AES_SetKey(unsigned char *pAESKey)
{
	// The number of 32 bit words in the key. It is simply initiated to zero. The actual value is recieved in the program.
	int Nk;
	int i, j;
	unsigned char temp[4], k;

	Nk = 128 / 32;
	//Nr = Nk + 6;

	//memset(RoundKey, 0, sizeof(RoundKey));
	// The first round key is the key itself.
	memcpy(RoundKey, pAESKey, 128 / 8);
	/*for (i = 0; i < Nk; i++)
	{
		RoundKey[i*4]   = pAESKey[i*4];
		RoundKey[i*4+1] = pAESKey[i*4+1];
		RoundKey[i*4+2] = pAESKey[i*4+2];
		RoundKey[i*4+3] = pAESKey[i*4+3];
	}*/

	i = Nk;
	// All other round keys are found from the previous round keys.
	while (i < (Nb * (Nr + 1)))
	{
		for (j = 0; j < 4; j++)
		{
			temp[j] = RoundKey[(i - 1) * 4 + j];
		}

		if (i % Nk == 0)
		{
			// This function rotates the 4 bytes in a word to the left once.
			// [a0,a1,a2,a3] becomes [a1,a2,a3,a0]

			// Function RotWord()
			{
				k = temp[0];
				temp[0] = temp[1];
				temp[1] = temp[2];
				temp[2] = temp[3];
				temp[3] = k;
			}

			// SubWord() is a function that takes a four-byte input word and 
			// applies the S-box to each of the four bytes to produce an output word.

			// Function Subword()
			{
				temp[0] = sbox[temp[0]];
				temp[1] = sbox[temp[1]];
				temp[2] = sbox[temp[2]];
				temp[3] = sbox[temp[3]];
			}

			temp[0] =  temp[0] ^ Rcon[i/Nk];
		}
		else if (Nk > 6 && i % Nk == 4)
		{
			// Function Subword()
			{
				temp[0]=sbox[temp[0]];
				temp[1]=sbox[temp[1]];
				temp[2]=sbox[temp[2]];
				temp[3]=sbox[temp[3]];
			}
		}

		RoundKey[i*4+0] = RoundKey[(i-Nk)*4+0] ^ temp[0];
		RoundKey[i*4+1] = RoundKey[(i-Nk)*4+1] ^ temp[1];
		RoundKey[i*4+2] = RoundKey[(i-Nk)*4+2] ^ temp[2];
		RoundKey[i*4+3] = RoundKey[(i-Nk)*4+3] ^ temp[3];
		i++;
	}
}

// This function adds the round key to state.
// The round key is added to the state by an XOR function.
void AddRoundKey(int round) 
{
	unsigned char i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			state[j][i] ^= RoundKey[round * Nb * 4 + i * Nb + j];
		}
	}
}

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
void SubBytes()
{
	unsigned char i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			state[i][j] = sbox[state[i][j]];
		}
	}
}

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
void InvSubBytes()
{
	int i,j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			state[i][j] = rsbox[state[i][j]];

		}
	}
}

// The ShiftRows() function shifts the rows in the state to the left.
// Each row is shifted with different offset.
// Offset = Row number. So the first row is not shifted.
void ShiftRows()
{
	unsigned char temp;

	// Rotate first row 1 columns to left	
	temp        = state[1][0];
	state[1][0] = state[1][1];
	state[1][1] = state[1][2];
	state[1][2] = state[1][3];
	state[1][3] = temp;

	// Rotate second row 2 columns to left	
	temp        = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = temp;

	temp        = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = temp;

	// Rotate third row 3 columns to left
	temp        = state[3][0];
	state[3][0] = state[3][3];
	state[3][3] = state[3][2];
	state[3][2] = state[3][1];
	state[3][1] = temp;
}

// The ShiftRows() function shifts the rows in the state to the left.
// Each row is shifted with different offset.
// Offset = Row number. So the first row is not shifted.
void InvShiftRows()
{
	unsigned char temp;

	// Rotate first row 1 columns to right	
	temp		= state[1][3];
	state[1][3] = state[1][2];
	state[1][2] = state[1][1];
	state[1][1] = state[1][0];
	state[1][0] = temp;

	// Rotate second row 2 columns to right	
	temp		= state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = temp;

	temp		= state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = temp;

	// Rotate third row 3 columns to right
	temp		= state[3][0];
	state[3][0] = state[3][1];
	state[3][1] = state[3][2];
	state[3][2] = state[3][3];
	state[3][3] = temp;
}

// xtime is a macro that finds the product of {02} and the argument to xtime modulo {1b}  
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

// Multiplty is a macro used to multiply numbers in the field GF(2^8)
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))


// MixColumns function mixes the columns of the state matrix
void MixColumns()
{
	unsigned char i;
	unsigned char Tmp, Tm, t;

	for (i = 0; i < 4; i++)
	{	
		t = state[0][i];
		Tmp = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
		Tm  = state[0][i] ^ state[1][i]; Tm = xtime(Tm); state[0][i] ^= Tm ^ Tmp;
		Tm  = state[1][i] ^ state[2][i]; Tm = xtime(Tm); state[1][i] ^= Tm ^ Tmp;
		Tm  = state[2][i] ^ state[3][i]; Tm = xtime(Tm); state[2][i] ^= Tm ^ Tmp;
		Tm  = state[3][i] ^ t;			 Tm = xtime(Tm); state[3][i] ^= Tm ^ Tmp;
	}
}

// MixColumns function mixes the columns of the state matrix.
// The method used to multiply may be difficult to understand for the inexperienced.
// Please use the references to gain more information.
void InvMixColumns()
{
	unsigned char i;
	unsigned char a, b, c, d;

	for (i = 0; i < 4; i++)
	{
		a = state[0][i];
		b = state[1][i];
		c = state[2][i];
		d = state[3][i];
		
		state[0][i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
		state[1][i] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
		state[2][i] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
		state[3][i] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
	}
}
// Cipher is the main function that encrypts the PlainText.
void AES_CipherBlock(unsigned char *pPlainText, unsigned char *pCiphered)
{
	int i, j, round = 0;

	//Copy the input PlainText to state array.
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			state[j][i] = pPlainText[i * 4 + j];
		}
	}

	// Add the First round key to the state before starting the rounds.
	AddRoundKey(0); 
	
	// There will be Nr rounds.
	// The first Nr-1 rounds are identical.
	// These Nr-1 rounds are executed in the loop below.
	for (round = 1; round < Nr; round++)
	{
		SubBytes();
		ShiftRows();
		MixColumns();
		AddRoundKey(round);
	}
	
	// The last round is given below.
	// The MixColumns function is not here in the last round.
	SubBytes();
	ShiftRows();
	AddRoundKey(Nr);

	// The encryption process is over.
	// Copy the state array to output array.
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			pCiphered[i * 4 + j] = state[j][i];
		}
	}
}

// InvCipher is the main function that decrypts the CipherText.
void AES_DeCipherBlock(unsigned char *pCiphered, unsigned char *pPlainText)
{
	int i, j, round = 0;

	//Copy the input CipherText to state array.
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			state[j][i] = pCiphered[i * 4 + j];
		}
	}

	// Add the First round key to the state before starting the rounds.
	AddRoundKey(Nr); 

	// There will be Nr rounds.
	// The first Nr-1 rounds are identical.
	// These Nr-1 rounds are executed in the loop below.
	for (round = Nr - 1; round > 0; round--)
	{
		InvShiftRows();
		InvSubBytes();
		AddRoundKey(round);
		InvMixColumns();
	}

	// The last round is given below.
	// The MixColumns function is not here in the last round.
	InvShiftRows();
	InvSubBytes();
	AddRoundKey(0);

	// The decryption process is over.
	// Copy the state array to output array.
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			pPlainText[i * 4 + j] = state[j][i];
		}
	}
}

size_t AES_Encrypt(unsigned char* in, size_t inn, unsigned char* result, size_t outn, bool bChaining, int iMode)
{
	//n should be > 0 and multiple of m_blockSize
	size_t	n, totaln;
	unsigned char* pin = in;
	unsigned char* presult = result;
	unsigned char  m_chain[16], m_pin[16];

	totaln = inn / 16;
	totaln += inn % 16 ? 1 : 0;
	totaln *= 16;
	if (outn < totaln)
		return 0;

	if (!bChaining)
		memcpy(m_chain, IV, 16);

	while (inn)
	{
		n = inn > 16 ? 16 : inn;
		if (n != 16)
			memset(m_pin, 0, 16);
		memcpy(m_pin, pin, n);

		switch (iMode)
		{
		case CBC:	//CBC mode, using the Chain
			Xor(m_chain, m_pin);
			AES_CipherBlock(m_chain, presult);
			memcpy(m_chain, presult, 16);
			break;

		case CFB:	//CFB mode, using the Chain
			AES_CipherBlock(m_chain, presult);
			Xor(presult, m_pin);
			memcpy(m_chain, presult, 16);
			break;

		default: //ECB mode, not using the Chain
			AES_CipherBlock(m_pin, presult);
		}

		pin += n;
		presult += 16;
		inn -= n;
	}

	return totaln;
}

void AES_Decrypt(unsigned char* in, unsigned char* result, size_t n, bool bChaining, int iMode)
{
	//n should be > 0 and multiple of m_blockSize
	unsigned int i;
	unsigned char* pin = in;
	unsigned char* presult = result;
	unsigned char  m_chain[16], m_pin[16];

	if (!bChaining)
		memcpy(m_chain, IV, 16);

	n = n / 16;

	for (i = 0; i < n; i++)
	{
		memcpy(m_pin, pin, 16);

		switch (iMode)
		{
		case CBC: //CBC mode, using the Chain
			AES_DeCipherBlock(m_pin, presult);
			Xor(presult, m_chain);
			memcpy(m_chain, m_pin, 16);				
			break;
		case CFB: //CFB mode, using the Chain, not using Decrypt()
			AES_CipherBlock(m_chain, presult);
			//memcpy(presult, pin, 16);
			Xor(presult, m_pin);
			memcpy(m_chain, m_pin, 16);
			break;
		default: //ECB mode, not using the Chain
			AES_DeCipherBlock(m_pin, presult);
		}

		pin += 16;
		presult += 16;
	}
}
