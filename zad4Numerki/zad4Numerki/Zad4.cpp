#include "stdafx.h"
#include "Zad4.h"


double(*funkcja)(double x);
double A = -1.;
double B = 1.;
double epsilon = 0.;
long int Iteration = 0;

/**
x - argument
wsp - tablica wspolczynnikow
stopien - stopien wielomianu
*/
long double Horner(double x, double* wsp, int stopien)
{
	long double wynik = wsp[0];
	for (int i = 1; i <= stopien; i++)
	{
		wynik *= x;
		wynik += wsp[i];
	}
	return wynik;
}

/**
wezly Czebyszewa
*/
double czebyszew(double a, double b, double i, double N)
{
		double x_w = cos(((2*i + 1)/(2*N + 1))*M_PI);
		x_w *= (b - a);
		x_w += (a + b);
		x_w *= 0.5;

		return x_w;
}

/**
(a+b)/2
*/
double d(double a, double b)
{
	return (a + b) / 2.;
}

/**
w(x) = 1/(sqrt(1-x^2))
*/
double waga(double x)
{
	double wsp[] = { -1., 0., 1. };
	double h = Horner(x, wsp, 2.);
	double m = sqrt(h);
	return (m == 0) ? 0 : (1. / (sqrt(h)));
}

/**
f(x) = x^3 + 5
*/
double wielomian(double x)
{
	double wsp[] = { 1., 0., 0., 5. };
	return Horner(x, wsp, 3);
}

/**
f(x) = sin(x) + cos(x)
*/
double trygono(double x)
{
	return sin(x) + cos(x);
}

/**
f(x) = 3^x
*/
double wykladnicze(double x)
{
	return pow(3., x);
}

/**
wzor Simpsona o zadanej dokladnosci
*/
double simpson()
{
	double W = 0.;
	double c = 0.; //Wynik calki

	Iteration = 0;

	for (int n = 1;; n++)
	{
		Iteration++;
		W = (B - A) / n;
		double c1 = 0.;

		for (int i = n; i--;)
		{
			double a = A + (W*i);
			double b = A + (W*(i + 1.));
			double m = (a + b) / 2.;
			double h = m - a;
			c1 += (h / 3.)*(f(a) + (4*f(m)) + f(b));
		}

		if (abs(c - c1) <= epsilon)
			return c1;

		c = c1;
	}
}

/**
kwadratura Gaussa-Czebyszewa
t - ilosc wezlow (2-5)
*/
double GaussaCzebyszewa(int t)
{
	double c = 0.;

	long int m = 1;
	double a = 0.;
	double b = 0.;
	double w = M_PI / t;

	Iteration = 0;

	for (;;)
	{
		Iteration++;

		m *= 2;
		a = b;
		b = a + (1. / m);

		double c1 = 0.;
		double c2 = 0.;

		for (int i = 1; i != t; i++)
		{
			double plusX = czebyszew(a, b, i, t);
			double minusX = czebyszew(-b, -a, i, t);
			double x1 = (d(-a, b) * plusX) + d(a, b);
			double x2 = (d(b, -a) * plusX) + d(-a, -b);
			c1 += funkcja(x1);
			c2 += funkcja(x2);
		}
		
		c1 *= w * d(-a, b);
		c2 *= w * d(b, -a);
		c += c1 + c2;
		if (abs(c1) <= epsilon && abs(c2) <= epsilon)
			return c;
	}
}

/**
g(x) = w(x)*f(x)
*/
double f(double x)
{
	return waga(x)*funkcja(x);
}