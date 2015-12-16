#include "vsfp_mantissa.h"

VSFP_MANTISSA::VSFP_MANTISSA(U16 size)
{
	mantissa = new U64[size];

	if (mantissa)
	{
		mantissa_size = size;
		zero();
	}
	else mantissa_size = 0;
}
VSFP_MANTISSA::VSFP_MANTISSA(U16 size, float arg)
{
	mantissa = new U64[size];

	if (mantissa)
	{
		mantissa_size = size;
		zero();
		mantissa[0] = static_cast<U64>((*reinterpret_cast<U32*>(&arg)) << 9) << 8*sizeof(float);
	}
	else mantissa_size = 0;
}
VSFP_MANTISSA::VSFP_MANTISSA(U16 size, double arg)
{
	mantissa = new U64[size];

	if (mantissa)
	{
		mantissa_size = size;
		zero();
		mantissa[0] = (*reinterpret_cast<U64*>(&arg)) << 12;
	}
	else mantissa_size = 0;
}
VSFP_MANTISSA::~VSFP_MANTISSA()
{
	delete[] mantissa;
}

void VSFP_MANTISSA::zero()
{
	for (U16 i = 0; i < mantissa_size; i++)
		mantissa[i] = 0;
	return;
}
bool VSFP_MANTISSA::change_size(U16 new_size)
{
	if (new_size == mantissa_size)
		return true;

	U64* new_mantissa = new U64[new_size];

	if (!new_mantissa)
		return false;

	U16 i = 0;
	if (new_size > mantissa_size)
	{
		for (; i < mantissa_size; i++)
			new_mantissa[i] = mantissa[i];
		for (; i < new_size; i++)
			new_mantissa[i] = 0;
	}
	else
	{
		for (; i < new_size; i++)
			new_mantissa[i] = mantissa[i];
	}

	mantissa_size = new_size;
	return true;
}

VSFP_MANTISSA& VSFP_MANTISSA::operator<< (U16 shift)
{
	if (shift)
	{
		U16 i = 0;
		if (shift/64)
		{
			for (; i+shift/64 < mantissa_size; i++)
				mantissa[i] = mantissa[i+shift/64];
			for (; i < mantissa_size; i++)
				mantissa[i] = 0;
			for (i = 0; i+shift/64 < mantissa_size; i++)
				mantissa[i] = (mantissa[i] << shift) | (mantissa[i+1] >> (64-shift%64));
		}
		else
		{
			for (; i+1 < mantissa_size; i++)
				mantissa[i] = (mantissa[i] << shift) | (mantissa[i+1] >> (64-shift));
			mantissa[i] <<= shift;
		}
	}

	return *this;
}
VSFP_MANTISSA& VSFP_MANTISSA::operator>> (U16 shift)
{
	/*
	if (shift)
	{
		U16 i = mantissa_size-1;
		if (shift/64)
		{
			for (;; i--)
			{
				mantissa[i] = mantissa[i-shift/64];
				mantissa[i] >>= shift%64;

				if (i == shift/64)
					break;
			}
			for (i--;;i--)
			{
				mantissa[i] = 0;

				if (!i)
					break;
			}
		}
		else
		{
			for (;; i--)
			{
				mantissa[i] = (mantissa[i] << shift) | (mantissa[i+1] >> (64-shift));

			}
			mantissa[i] <<= shift;
		}
	}*/

	return *this;
}