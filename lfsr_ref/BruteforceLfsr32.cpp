#include "stdafx.h"
#include "BruteforceLfsr32.h"
#include <intrin.h>


BruteforceLfsr32::~BruteforceLfsr32()
{
}

uint32_t BruteforceLfsr32::GetNext32RandomBits()
{
	uint32_t s, out = 0;
	for (int i = 0; i < 32; i++) {
		s = _poly & state; //AND (multiply in GF(2) )
		int n = __popcnt(s);

		n = n & 0x1; //XOR all bits in n
		out |= (state & 0x1) << i;

		state >>= 1;
		state |= (n << 31); //feedback the new bit to Bit 31
	}

	return out;
}
