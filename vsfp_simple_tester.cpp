#include <iostream>
#include <iomanip>
using namespace std;

#include "vsfp_mantissa.h"

ostream& operator<<(ostream& ostr, const VSFP_MANTISSA& vm)
{
	ostr << hex;
	for (U16 i = 0; i < vm.size(); i++)
			ostr << setfill('0') << setw(16) << vm.mantissa[i] << " ";

	ostr << endl;
	return ostr;
}

int main()
{
	double f = 4.3f;
	cout << hex << *reinterpret_cast<U64*>(&f) << endl;
	VSFP_MANTISSA vp(3, f);
	cout << vp << endl;
	vp >> 128;
	cout << vp << endl;
	vp << 76;
	cout << vp << endl;

	cin.get();
	cin.ignore();
	return 0;
}