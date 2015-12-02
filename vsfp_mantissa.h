#pragma once

#include "vsfp_nbtn.h"

class VSFP_MANTISSA
{
public:	// tymczasowo
	U64* mantissa;
	U16 mantissa_size;

public:
	VSFP_MANTISSA(U16 size = 2);
	VSFP_MANTISSA(U16 size, float arg);
	VSFP_MANTISSA(U16 size, double arg);
	~VSFP_MANTISSA();

	void zero();								// zerowanie mantysy
	bool change_size(U16 new_size);				// zmiana rozmiaru
	U16 size() const { return mantissa_size; }	// zwrócenie rozmiaru

	VSFP_MANTISSA& operator<< (U16 shift); // przesuniêcie bitowe w lewo
	VSFP_MANTISSA& operator>> (U16 shift); // przesuniêcie bitowe w prawo

	U8 add(const VSFP_MANTISSA&); // dodawanie
	U8 sub(const VSFP_MANTISSA&); // odejmowanie
	U8 mul(const VSFP_MANTISSA&); // mnozenie
	U8 div(const VSFP_MANTISSA&); // dzielenie
};