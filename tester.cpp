#include <iostream>
using namespace std;

#include "vsfp.h"

int main()
{
	MATRIX<double> a(3,3);
	MATRIX<double> v(4,1);

	cout << "podaj macierz a" << endl;
	cin >> a;

	try
	{
		cout << MATRIX_SoLE<double>::matrix_inverse(a) << endl;
	}
	catch (std::logic_error err)
	{
		cout << err.what();
	}

	cin.get();
	cin.ignore();
	return 0;
}