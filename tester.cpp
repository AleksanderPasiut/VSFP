#include <iostream>
using namespace std;

#include "vsfp.h"

int main()
{
	MATRIX<double> a(4,4);
	MATRIX<double> v(4,1);

	cout << "podaj macierz a" << endl;
	cin >> a;
	cout << "podaj wektor v" << endl;
	cin >> v;

	cout << endl;
	try { cout << MATRIX_SoLE<double>::matrix_inverse(a) << endl;	}			catch(std::logic_error err)	{	cout << "matrix inversion error: " << err.what() << endl;	}
	try { cout << MATRIX_SoLE<double>::compute_determinant(a) << endl; }		catch(std::logic_error err)	{	cout << "determinant computation error: " << err.what() << endl;	}
	try { cout << MATRIX_SoLE<double>::jacoby_solver(a, v, 0.01) << endl; }		catch(std::logic_error err)	{	cout << "jacoby solver error: " << err.what() << endl;	}
	try { cout << MATRIX_SoLE<double>::gauss_seidl_solver(a, v, 0.01) << endl; }catch(std::logic_error err)	{	cout << "gauss seidl solver error: " << err.what() << endl;	}
	try { cout << MATRIX_SoLE<double>::gauss_solver(a, v) << endl; }			catch(std::logic_error err)	{	cout << "gauss solver error: " << err.what() << endl;	}
	try { cout << MATRIX_SoLE<double>::jordan_solver(a, v) << endl; }			catch(std::logic_error err)	{	cout << "jordan solver error: " << err.what() << endl;	}
	
	cout << MATRIX_SoLE<double>::shuffle_for_diagonal_domination(a,v) << endl;
	cout << v;
	cin.get();
	cin.ignore();
	return 0;
}