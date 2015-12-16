// This file provides VSFP_MANTISSA class which is used to represent
// mantissa in VSFP format.

#pragma once

#include "..\vsfp_nbtn.h"

class VSFP_MANTISSA
{
public:	// temporarily
	U64* mantissa;
	U16 mantissa_size;

public:
	VSFP_MANTISSA(U16 size = 2);
	VSFP_MANTISSA(U16 size, float arg);
	VSFP_MANTISSA(U16 size, double arg);
	~VSFP_MANTISSA();

	void zero();
	bool change_size(U16 new_size);
	U16 size() const { return mantissa_size; }

	VSFP_MANTISSA& operator<< (U16 shift);
	VSFP_MANTISSA& operator>> (U16 shift);

	U8 add(const VSFP_MANTISSA&);
	U8 sub(const VSFP_MANTISSA&);
	U8 mul(const VSFP_MANTISSA&);
	U8 div(const VSFP_MANTISSA&);
};