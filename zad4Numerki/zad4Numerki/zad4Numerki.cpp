// zad4Numerki.cpp : main project file.

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include "Zad4.h"

using namespace std;

int main(array<System::String ^> ^args)
{
	char wyb;
	int wezly;

	cout << "Podaj dokladnosc:\n";
	cin >> epsilon;

	cout << "\nPodaj ilosc wezlow (min 5):\n";
	cin >> wezly;
	wezly = (wezly < 5) ? 5 : wezly;

	cout << "\nZdefiniuj funkcje:\n";
	cout << "a) f(x) = x^3 + 5\n";
	cout << "b) f(x) = sin(x) + cos(x)\n";
	cout << "c) f(x) = 3^x\n";
	cin >> wyb;

	switch (wyb)
	{
	case 'a':
	case 'A':
		funkcja = wielomian;
		break;
	case 'b':
	case 'B':
		funkcja = trygono;
		break;
	case 'c':
	case 'C':
		funkcja = wykladnicze;
		break;
	}

	system("cls");

	cout << "\n\nCzebyszewa:\n";
	for (int i = 2; i <= wezly; i++)
	{
		cout << "Wezly: " << i << endl;
		cout << GaussaCzebyszewa(i) << endl;
		cout << "Iteracji: " << Iteration << endl << endl;
	}

	cout << "\n\n=============================\n\n";

	cout << "\n\nSimpson:\n";
	cout << simpson();
	cout << "\nIteracji: " << Iteration << endl << endl;

	cout << "\n\n=============================\n\n";

	cout << "Dokladnosc: " << epsilon;
	switch (wyb)
	{
	case 'a':
	case 'A':
		cout << "\nf(x) = x^3 + 5\n";
		break;
	case 'b':
	case 'B':
		cout << "\nf(x) = sin(x) + cos(x)\n";
		break;
	case 'c':
	case 'C':
		cout << "\nf(x) = 3^x\n";
		break;
	}

	system("pause");
	return 0;
}

