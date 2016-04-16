#include <iostream>
using namespace std;

#include "vsfp.h"

#include <cmath>
double f(const double& x)
{
	return exp(x)-x-2;
}
double fp(const double& x)
{
	return exp(x)-1;
}

int main()
{
	cout.precision(20);

	if (true)
	{
		MATRIX<double> a(5,5);
		cout << "podaj macierz" << endl;
		cin >> a;
		
		a.remove_rows(1, 2);
		cout << a << endl;
		a.remove_cols(2, 2);
		cout << a << endl;
	}

	if (false)
	{
		MATRIX<double> a(5,5);
		MATRIX<double> v(5,1);

		cout << "podaj macierz a" << endl;
		cin >> a;
		cout << "podaj wektor v" << endl;
		cin >> v;

		cout << endl;
		cout << "matrix inverse: " << endl;
		try { cout << MATRIX_SoLE<double>::matrix_inverse(a) << endl;	}			catch(std::logic_error err)	{	cout << "matrix inversion error: " << err.what() << endl;	}
		cout << "determinant: " << endl;
		try { cout << MATRIX_SoLE<double>::compute_determinant(a) << endl << endl; }catch(std::logic_error err)	{	cout << "determinant computation error: " << err.what() << endl;	}
		cout << "Gauss solver: " << endl;
		try { cout << MATRIX_SoLE<double>::gauss_solver(a, v) << endl; }			catch(std::logic_error err)	{	cout << "Gauss solver error: " << err.what() << endl;	}
		cout << "Jordan solver: " << endl;
		try { cout << MATRIX_SoLE<double>::jordan_solver(a, v) << endl; }			catch(std::logic_error err)	{	cout << "Jordan solver error: " << err.what() << endl;	}
		cout << "Jacoby solver: " << endl;
		try { cout << MATRIX_SoLE<double>::jacoby_solver(a, v, 0.01) << endl; }		catch(std::logic_error err)	{	cout << "Jacoby solver error: " << err.what() << endl;	}
		cout << "Gauss-Seidl solver: " << endl;
		try { cout << MATRIX_SoLE<double>::gauss_seidl_solver(a, v, 0.01) << endl; }catch(std::logic_error err)	{	cout << "Gauss-Seidl solver error: " << err.what() << endl;	}
	}

	if (false)
	{
		VSFP_MANTISSA m(3,0.72);
		m.mantissa[1] = 0x5555555555;
		m.mantissa[2] = 0x123123123123;
		cout << m;

		m >> 72;

		cout << m;
	}

	if (false)
	{
		double root;
		unsigned counter;

		
		cout << "bisection solver" << endl;
		try
		{
			root = NLES<double>::bisection_solver(f, 0, 2, 0.00000000001, 100, &counter);
			cout << "root = " << root << endl;
			cout << "f(root) = " << f(root) << endl;
			cout << "iterations = " << counter << endl;
		}
		catch(logic_error err)	{ cout << err.what() << endl; }
		cout << endl;
		cout << "tangent solver" << endl;
		try
		{
			root = NLES<double>::tangent_solver(f, fp, 2, 0.00000000001, 100, &counter);
			cout << "root = " << root << endl;
			cout << "f(root) = " << f(root) << endl;
			cout << "iterations = " << counter << endl;
		}
		catch(logic_error err)	{ cout << err.what() << endl; }
		cout << endl;
		cout << "regula falsi solver" << endl;
		try
		{
			root = NLES<double>::regula_falsi_solver(f, 0, 2, 0.00000000001, 100, &counter);
			cout << "root = " << root << endl;
			cout << "f(root) = " << f(root) << endl;
			cout << "iterations = " << counter << endl;
		}
		catch(logic_error err)	{ cout << err.what() << endl; }
		cout << endl;
		cout << "secant solver" << endl;
		try
		{
			root = NLES<double>::secant_solver(f, 2, 0, 0.00000000001, 100, &counter);
			cout << "root = " << root << endl;
			cout << "f(root) = " << f(root) << endl;
			cout << "iterations = " << counter << endl;
		}
		catch(logic_error err)	{ cout << err.what() << endl; }

	}
	
	cin.get();
	cin.ignore();
	return 0;
}