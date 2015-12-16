#pragma once

template<typename T>
MATRIX<T>& MATRIX_SoLE<T>::diagonal(MATRIX<T>& matrix)
{
	for (unsigned i = 0; i < matrix.rows(); i++)
		for (unsigned j = 0; j < matrix.cols(); j++)
			if (i != j)
				matrix.field(i,j) = 0;
	return matrix;
}

template<typename T>
MATRIX<T>& MATRIX_SoLE<T>::nondiagonal(MATRIX<T>& matrix)
{
	for (unsigned i = 0; i < matrix.rows(); i++)
		for (unsigned j = 0; j < matrix.cols(); j++)
			if (i == j)
				matrix.field(i,j) = 0;
	return matrix;
}

template<typename T>
MATRIX<T>& MATRIX_SoLE<T>::upper(MATRIX<T>& matrix)
{
	for (unsigned i = 0; i < matrix.rows(); i++)
		for (unsigned j = 0; j < matrix.cols(); j++)
			if (i >= j)
				matrix.field(i,j) = 0;
	return matrix;
}

template<typename T>
MATRIX<T>& MATRIX_SoLE<T>::nonupper(MATRIX<T>& matrix)
{
	for (unsigned i = 0; i < matrix.rows(); i++)
		for (unsigned j = 0; j < matrix.cols(); j++)
			if (i < j)
				matrix.field(i,j) = 0;
	return matrix;
}

template <typename T>
MATRIX<T>& MATRIX_SoLE<T>::row_echelon_form(MATRIX<T>& matrix)
{
	for (unsigned i = 0; i+1 < matrix.rows() && i < matrix.cols(); i++)
	{
		if (matrix.field(i,i) == 0)
			for (unsigned j = i+1; j < matrix.rows(); j++)
				if (matrix.field(j,i) != 0)
					for (unsigned k = 0; k < matrix.cols(); k++)
					{	T tmp = matrix.field(i,k);
						matrix.field(i,k) = matrix.field(j,k);
						matrix.field(j,k) = tmp;	}

		if (matrix.field(i,i) != 0)
			for (unsigned j = i+1; j < matrix.rows(); j++)
			{
				T multiplier = matrix.field(j,i)/matrix.field(i,i);

				for (unsigned k = i; k < matrix.cols(); k++)
					matrix.field(j,k) -= matrix.field(i,k)*multiplier;
			}
	}
	return matrix;
}

template <typename T>
MATRIX<T>& MATRIX_SoLE<T>::jordan_elimination(MATRIX<T>& matrix)
{
	row_echelon_form(matrix);

	for (unsigned i = min(matrix.rows(), matrix.cols())-1; i > 0; i--)
	{
		unsigned w = i;
		while (matrix.field(w,i) == 0)
		{
			if (!w)
				break;

			w--;
		}

		if (matrix.field(w,i) != 0 && w)
			for (unsigned j = w-1; ;j--)
			{
				T multiplier = matrix.field(j,i)/matrix.field(w,i);

				for (unsigned k = i; k < matrix.cols(); k++)
					matrix.field(j,k) -= multiplier*matrix.field(w,k);

				if (!j)
					break;
			}
	}
	return matrix;
}

template<typename T>
MATRIX<T>& MATRIX_SoLE<T>::diagonal_matrix_inverse(MATRIX<T>& matrix)
{
	if (matrix.rows() != matrix.cols())
		throw std::logic_error("Matrix is not square.");

	for (unsigned i = 0; i < matrix.rows(); i++)
		if (matrix.field(i,i) == 0)
			throw std::logic_error("Matrix is not invertible.");

	for (unsigned i = 0; i < matrix.rows(); i++)
		matrix.field(i,i) = 1/matrix.field(i,i);

	return matrix;
}

template<typename T>
MATRIX<T> MATRIX_SoLE<T>::lower_triangular_matrix_inverse(const MATRIX<T>& matrix)
{
	if (matrix.rows() != matrix.cols())
		throw std::logic_error("Matrix is not square.");

	if (diagonal_elements_product(matrix) == 0)
		throw std::logic_error("Matrix is not invertible.");

	MATRIX<T> ret(matrix.rows(), matrix.cols());
	ret.identity();

	for (unsigned i = 0; i < matrix.rows(); i++)
		ret.field(i,i) /= matrix.field(i,i);

	for (unsigned i = 0; i < matrix.cols(); i++)
		for (unsigned j = i+1; j < matrix.rows(); j++)
		{
			T factor = matrix.field(j,i)/matrix.field(j,j);
			for (unsigned k = 0; k < j; k++)
				ret.field(j,k) -= ret.field(i,k)*factor;
		}

	return ret;
}

template <typename T>
T MATRIX_SoLE<T>::diagonal_elements_product(const MATRIX<T>& matrix)
{
	T ret = 1;
	for (unsigned i = 0; i < min(matrix.rows(), matrix.cols()); i++)
		ret *= matrix.field(i,i);

	return ret;
}
