// lfsr_ref.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "BruteforceLfsr32.h"
#include "MatrixLfsr32.h"

int main()
{
	uint32_t poly = 0x400007;
	uint32_t seed = 0x3A9C1506;

	ILfsr  *bruteforce_lfsr, *matrix_lsfr;

	bruteforce_lfsr = new BruteforceLfsr32(poly, seed);
	matrix_lsfr = new MatrixLfsr32(poly, seed);

	//Generate 1000 32-bit chunks and compare:
	int err = 0;
	for (int i = 0; i < 0x7FFFFFFF; i++) {
		uint32_t a, b;
		a = bruteforce_lfsr->GetNext32RandomBits();
		b = matrix_lsfr->GetNext32RandomBits();
		if (a != b) {
			printf("Wrong at %d: Expected 0x%08X, Actual 0x%08X\n", i, a, b);
			err++;
		}
	}
	if (err == 0)
		printf("Test passed!\n");

	system("pause");
    return 0;
}

