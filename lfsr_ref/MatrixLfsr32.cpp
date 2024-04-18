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
	//memcpy(state_trans_matrix_p32, state_trans_matrix, sizeof(uint32_t) * 32);
	for (int i = 0; i < 32; i++) {
		tmp[i] = GetBitMatrixColumn(state_trans_matrix, i); //transpose state_trans_matrix, such that tmp is column-major
	}
	for (int i = 0; i < 31; i++) {
		Gf2MatrixMul(state_trans_matrix, tmp, state_trans_matrix_p32);
		memcpy(tmp, state_trans_matrix_p32, sizeof(uint32_t) * 32);
	}
	for (int i = 0; i < 32; i++) {
		state_trans_matrix_p32[i] = GetBitMatrixColumn(tmp, i); //back to row-column
	}
}

//Matrix multiplication in GF(2) field
//A: row-major 32x32 bit matrix
//B: column-major 32x32 bit matrix
//C: C = A*B, column-major 32x32 matrix
void MatrixLfsr32::Gf2MatrixMul(const uint32_t A[], const uint32_t B[], uint32_t C[])
{
	for (int i = 0; i < 32; i++) {
		C[i] = Gf2MatrixVecMul(A, B[i]);
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