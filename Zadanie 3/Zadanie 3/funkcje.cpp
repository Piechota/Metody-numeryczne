#include "funkcje.h"

double liniowa(double x)
{
	double wynik;
	wynik = 2 * x - 4;
	return wynik;
}

double modul(double x)
{
	double wynik = x;
	if (wynik < 0)
	{
		wynik = -wynik;
	}
	return wynik;
}

double wielomian(double x)
{
	double wynik;
	double wsp[4] = { 5, 3, -7, 3 };
	wynik = Horner(wsp, x, 3);
	return wynik;
}

double sinus(double x)
{
	double wynik = sin(x);
	return wynik;
}

double liniowaSinus(double x)
{
	double wynik = 2 * sin(x);
	wynik -= 5;
	return wynik;
}

double modulSinusWykladnicza(double x)
{
	double wynik = 2 * abs(x);
	wynik -= 3 * sin(x);
	wynik -= poteguj(x, 2);
	return wynik;
}

double poteguj(double podstawa, int potega)
{
	double wynik = 1.0;
	for (int i = 1; i <= potega; i++)
	{
		wynik *= podstawa;
	}
	return wynik;
}

double Horner(double wsp[], double x, int stopien)
{
	/*
	//Schemat Hornera rekurencyjnie
	if (stopien == 0)
	{
	return wsp[0];
	}

	return x*Horner(wsp, x, stopien - 1) + wsp[stopien];*/

	//Schemat Horenera iteracyjnie
	double wynik = wsp[0];
	for (int i = 1; i <= stopien; i++)
	{
		wynik *= x;
		wynik += wsp[i];
	}
	return wynik;
}
