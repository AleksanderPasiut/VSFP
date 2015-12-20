// This file provides MATRIX template class which is used to represent matrix with 
// scalars of variable type. It also provides basic operations such as addition,
// multiplication, size changing, combining, etc.

#pragma once

template<typename T>
class MATRIX
{
protected:
	T** table;
	unsigned rows_amount;
	unsigned cols_amount;

public:
	MATRIX(unsigned rows = 1, unsigned cols = 1);
	MATRIX(const MATRIX<T>&);
	~MATRIX();

	MATRIX<T>& operator= (const MATRIX<T>&);

	MATRIX<T>& operator+= (const MATRIX<T>&);
	MATRIX<T>& operator-= (const MATRIX<T>&);
	MATRIX<T>& operator*= (const MATRIX<T>&);

	MATRIX<T> operator+ (const MATRIX<T>&) const;
	MATRIX<T> operator- (const MATRIX<T>&) const;
	MATRIX<T> operator* (const MATRIX<T>&) const;

	MATRIX<T>& operator+= (const T&);
	MATRIX<T>& operator-= (const T&);
	MATRIX<T>& operator*= (const T&);

	MATRIX<T> operator+ (const T&) const;
	MATRIX<T> operator- (const T&) const;
	MATRIX<T> operator* (const T&) const;

	T& field(unsigned row, unsigned col);
	const T& field(unsigned row, unsigned col) const;

	MATRIX<T>& change_size(unsigned rows, unsigned cols);

	MATRIX<T>& row_combine(const MATRIX<T>& arg);
	MATRIX<T>& col_combine(const MATRIX<T>& arg);

	MATRIX<T>& zero();
	MATRIX<T>& identity();

	unsigned rows() const { return rows_amount; }
	unsigned cols() const { return cols_amount; }
};

#include "matrix_methods.h"