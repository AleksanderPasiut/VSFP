#include <iostream>

#include "vsfp.h"

void f(
	const MATRIX<double>& v,
	const MATRIX<double>& B,
	MATRIX<double>& x,
	double& deltaV,
	double x_min,
	double x_max,
	double Tc,
	double Tp)
{
    const unsigned& n = B.rows();
    const unsigned& m = B.cols();
    
    // przygotowanie wektora wspó³czynników
    MATRIX<double> vector(m);
    for (unsigned i = 0; i < m; i++)
    {
        vector.field(i) = 0;
        
        for (unsigned j = 0; j < n; j++)
            vector.field(i) += B.field(j, i)*v.field(j);
    }
    
    // przygotowanie macierzy
    MATRIX<double> matrix(m, m);
    for (unsigned i = 0; i < m; i++)
        for (unsigned j = 0; j < m; j++)
        {
            matrix.field(i, j) = 0;
            
            for (unsigned k = 0; k < n; k++)
                matrix.field(i, j) += B.field(k, i)*B.field(k, j);
        }
    
    // odwrócenie macierzy
    matrix = MATRIX_SoLE<double>::matrix_inverse(matrix);
    
	// wstepne obliczenie wektora x
    x = matrix*vector;

	// obliczenie sta³ej s i przeskalowanie wektora x
	double tmp = 0;
	for (unsigned i = 0; i < m; i++)
		tmp += x.field(i);
	double s = (Tc-m*Tp)/tmp;
	x *= s;

	// uwzglêdnienie ograniczeñ
	for (unsigned i = 0; i < x.rows(); i++)
	{
		if (x.field(i) < x_min)
			x.field(i) = x_min;
		if (x.field(i) > x_max)
			x.field(i) = x_max;
	}

	// obliczenie b³êdu
	MATRIX<double> dv = B*x-v*s;
	cout << dv << endl;
	deltaV = 0;
	for (unsigned i = 0; i < dv.rows(); i++)
		deltaV += dv.field(i)*dv.field(i);
	deltaV = sqrt(deltaV);
}

int main()
{
	MATRIX<double> v(18);
	for(unsigned i = 0; i < 18; i++)
		v.field(i) = 20;

	MATRIX<double> B(18, 4);
	switch(3)
	{
		case 0:
			B.field(0, 0) = B.field(1, 0) = B.field(5, 0) = B.field(6, 0) = B.field(12, 0) = B.field(13, 0) = B.field(16, 0) = B.field(17, 0) = 1;
			B.field(2, 1) = B.field(7, 1) = B.field(12, 1) = B.field(16, 1) = 1;
			B.field(3, 2) = B.field(4, 2) = B.field(8, 2) = B.field(9, 2) = B.field(10, 2) = B.field(11, 2) = B.field(14, 2) = B.field(15, 2) = 1;
			B.field(4, 3) = B.field(9, 3) = B.field(10, 3) = B.field(14, 3) = 1;
			break;
		case 1:
			B.field(0, 0) = B.field(1, 0) = B.field(2, 0) = B.field(12, 0) = B.field(16, 0) = B.field(17, 0) = 1;
			B.field(5, 1) = B.field(6, 1) = B.field(7, 1) = B.field(12, 1) = B.field(13, 1) = B.field(16, 1) = 1;
			B.field(3, 2) = B.field(4, 2) = B.field(8, 2) = B.field(9, 2) = B.field(10, 2) = B.field(11, 2) = B.field(14, 2) = B.field(15, 2) = 1;
			B.field(4, 3) = B.field(9, 3) = B.field(10, 3) = B.field(14, 3) = 1;
			break;
		case 2:
			B.field(0, 0) = B.field(1, 0) = B.field(5, 0) = B.field(6, 0) = B.field(12, 0) = B.field(13, 0) = B.field(16, 0) = B.field(17, 0) = 1;
			B.field(2, 1) = B.field(7, 1) = B.field(12, 1) = B.field(16, 1) = 1;
			B.field(3, 2) = B.field(4, 2) = B.field(10, 2) = B.field(11, 2) = B.field(13, 2) = B.field(14, 2) = B.field(16, 2) = 1;
			B.field(8, 3) = B.field(9, 3) = B.field(10, 3) = B.field(12, 3) = B.field(14, 3) = B.field(15, 3) = B.field(17, 3) = 1;
			break;
		case 3:
			B.field(0, 0) = B.field(1, 0) = B.field(2, 0) = B.field(11, 0) = B.field(12, 0) = B.field(14, 0) = B.field(16, 0) = 1;
			B.field(3, 1) = B.field(4, 1) = B.field(10, 1) = B.field(13, 1) = B.field(14, 1) = B.field(16, 1) = 1;
			B.field(5, 2) = B.field(6, 2) = B.field(7, 2) = B.field(9, 2) = B.field(10, 2) = B.field(12, 2) = B.field(15, 2) = B.field(16, 2) = 1;
			B.field(8, 3) = B.field(9, 3) = B.field(10, 3) = B.field(12, 3) = B.field(14, 3) = B.field(17, 3) = 1;
			break;
	}

	MATRIX<double> x(4);
	double deltaV;

	f(v, B, x, deltaV, 5, 25, 60, 3);

	cout << v << endl;
	cout << B << endl;
	cout << x << endl;
	cout << deltaV;

	cin.get();
	cin.ignore();
	return 0;
}