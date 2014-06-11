#include <cstdlib>
#include <iostream>
#include <string>
#include "MathFunc.h"
#include "gnuplotFunc.h"

int n = 0;
int main()
{
	char wyb;
	cout << "Podaj ilosc krokow (sugerowane 512):\n";
	cin >> n;

	cout << "\na)Rungego-Kutty\nb)Ralstona:\n";
	cin >> wyb;

	vector<double> X;
	vector<double>* Y;

	switch (wyb)
	{
	case 'a':
		X = podajX();
		Y = RK4();
		rysuj(X, Y, "Rungego-Kutty " + to_string(n));
		delete[] Y;
		break;
	case 'b':
		X = podajX();
		Y = RK4_Ralston();
		rysuj(X, Y, "Ralston " + to_string(n));
		delete[] Y;
		break;
	}
	return 0;
}