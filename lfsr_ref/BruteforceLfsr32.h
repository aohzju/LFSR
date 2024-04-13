#pragma once
#include <stdint.h>
#include "ILfsr.h"

class BruteforceLfsr32 : public ILfsr
{
public:
	BruteforceLfsr32(uint32_t poly, uint32_t seed = 0x1234ABCD)
	{
		_poly = poly;
		state = seed;
	}

	~BruteforceLfsr32();

	uint32_t GetNext32RandomBits() override;

private:
	uint32_t  _poly;
};

