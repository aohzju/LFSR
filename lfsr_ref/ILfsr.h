#pragma once
#include <stdint.h>

class ILfsr
{
public:
	void Reseed(uint32_t seed) //set a new seed
	{
		state = seed;
	}

	virtual uint32_t GetNext32RandomBits() = 0;

protected:
	ILfsr() {

	}
	virtual ~ILfsr() {

	}

	uint32_t state;
};

