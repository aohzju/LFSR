#include "stdafx.h"
#include "MatrixLfsr32.h"
#include <intrin.h>


MatrixLfsr32::~MatrixLfsr32()
{
}

uint32_t MatrixLfsr32::GetNext32RandomBits()
{
	uint32_t nxt;
	nxt = state;

	state = Gf2MatrixVecMul(state_trans_matrix_p32, state);

	return nxt;
}

void MatrixLfsr32::ConstructStateTransMatrix()
{
	for(int i=0; i<31; i++)
		state_trans_matrix[i] = 0x2 << i;
	state_trans_matrix[31] = _poly;
}

void MatrixLfsr32::CalStateTransMatrixP32()
{
	uint32_t tmp[32];
	memcpy(state_trans_matrix_p32, state_trans_matrix, sizeof(uint32_t) * 32);
	for (int i = 0; i < 31; i++) {
		memcpy(tmp, state_trans_matrix_p32, sizeof(uint32_t) * 32);
		Gf2MatrixMul(state_trans_matrix, tmp, state_trans_matrix_p32);
	}
}

void MatrixLfsr32::Gf2MatrixMul(const uint32_t A[], const uint32_t B[], uint32_t C[])
{
	uint32_t col_vector;
	memset(C, 0, sizeof(uint32_t) * 32);
	for (int i = 0; i < 32; i++) { //column i
		col_vector = GetBitMatrixColumn(B, i);
		uint32_t m = Gf2MatrixVecMul(A, col_vector);
		for (int r = 0; r < 32; r++)
			C[r] |= ((m >> r) & 0x1) << i;
	}
}

uint32_t MatrixLfsr32::GetBitMatrixColumn(const uint32_t A[], int col)
{
	uint32_t v = 0;
	for (int i = 0; i < 32; i++) {
		uint32_t bv;
		bv = (A[i] >> col) & 0x1;
		v |= bv << i;
	}

	return v;
}

uint32_t MatrixLfsr32::Gf2MatrixVecMul(const uint32_t A[], const uint32_t v)
{
	uint32_t r = 0;
	for (int i = 0; i < 32; i++) {
		uint32_t b = A[i] & v;
		uint32_t bv = __popcnt(b) & 0x1;
		r |= bv << i;
	}

	return r;
}