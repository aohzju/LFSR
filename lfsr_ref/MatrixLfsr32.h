#pragma once
#include <stdint.h>
#include "ILfsr.h"

class MatrixLfsr32 : public ILfsr
{
public:
	MatrixLfsr32(uint32_t poly, uint32_t seed = 0x1234ABCD)
	{
		_poly = poly;
		state = seed;

		ConstructStateTransMatrix();
		CalStateTransMatrixP32();
	}
	~MatrixLfsr32();

	uint32_t GetNext32RandomBits() override;

private:
	uint32_t _poly;
	uint32_t state_trans_matrix[32]; //A
	uint32_t state_trans_matrix_p32[32]; //A**32

	void ConstructStateTransMatrix();
	void CalStateTransMatrixP32();
	void Gf2MatrixMul(const uint32_t A[], const uint32_t B[], uint32_t C[]); //A, B, C: 32x32 bit matrix
	uint32_t Gf2MatrixVecMul(const uint32_t A[], const uint32_t v); //A: 32x32, v: Nx1 vector

	uint32_t GetBitMatrixColumn(const uint32_t A[], int col);
};

