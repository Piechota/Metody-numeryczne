#include "funkcjeMatematyczne.h"

double Horner(vector<double> tab, double x)
{
	double wartosc = tab[0];
	for (unsigned int i = 1; i < tab.size(); i += 1)
	{
		wartosc = wartosc * x + tab[i];
	}
	return wartosc;
}

double Horner(double x, double* wsp, int stopien)
{
	double wynik = wsp[0];

	for (int i = 1; i <= stopien; i++)
	{
		wynik = wynik*x + wsp[i];
	}

	return wynik;
}

double potega(double x, int wykladnik)
{
	if (wykladnik < 0)
	{
		return potega(1 / x, -wykladnik);
	}
	double wynik = 1;
	for (int i = 1; i <= wykladnik; i++)
	{
		wynik *= x;
	}
	return wynik;
}

double wielomian(double x)
{
	//2x^3-7x^2+x-3
	double wsp[] = { 2, -7, 1, -3 };
	return Horner(x, wsp, 3);
}

double liniowa(double x)
{
	//7x-3
	double wsp[] = { 7, -3 };
	return Horner(x, wsp, 1);
}

double modul(double x)
{
	//|x|
	return x < 0 ? -x : x;
}

double trygonometryczna(double x)
{
	//cos(x)
	return cos(x);
}

double wieltryg(double x)
{
	//2cos^4(x) - 3cos^3(x) + 5cos(x) - 1
	double wsp[] = { 2, -3, 0, 5, -1 };
	return Horner(cos(x), wsp, 4);
}

double wielmodul(double x)
{
	//3|x|^3 - 4|x| + 2
	double wsp[] = { 3, 0, -4, 2 };
	return Horner(x < 0 ? -x : x, wsp, 3);
}

vector<vector<double>> wielomiany(int stopien)
{
	vector<vector<double>> wspolczynniki;
	for (int i = 0; i <= stopien; i++)
	{
		wspolczynniki.push_back(vector<double>());
	}
	//T0(x) = 1
	wspolczynniki[0].push_back(1);

	//T1(x) = x
	wspolczynniki[1].push_back(1);
	wspolczynniki[1].push_back(0);

	//Tn=2xTk(x) - Tk-1(x)
	for (int i = 2; i <= stopien; i++)
	{
		for (int j = 0; j < i; j++)
		{
			wspolczynniki[i].push_back(wspolczynniki[i - 1][j] * 2);
		}
		wspolczynniki[i].push_back(0);

		vector<double> tmp;
		for (int j = 0; j < i - 1; j++)
		{
			tmp.push_back(-(wspolczynniki[i - 2][j]));
		}
		wspolczynniki[i] = sumujWielomiany(wspolczynniki[i], tmp);
	}
	return wspolczynniki;
}

/*
Okazaly sie niepotrzebne
vector<double> wezlyCzebyszewa(double A, double B, int iloscWezlow)
{
	vector<double> wezly;
	for (int i = 0; i <= iloscWezlow; i++)
	{
		double x_w = cos(((2 * i + 1) * M_PI) / (2 * iloscWezlow + 1));
		x_w *= (B - A);
		x_w += (A + B);
		x_w *= 0.5;
		wezly.push_back(x_w);
	}
	return wezly;
}

vector<double> mnozWielomiany(vector<double> wielomian1, vector<double> wielomian2)
{
	vector<double> wynikowy;

	for (unsigned int i = 0; i < (wielomian1.size() + wielomian2.size() - 1); i++)
	{
		wynikowy.push_back(0);
	}

	for (unsigned int i = 0; i < wielomian1.size(); i++)
	{
		for (unsigned int j = 0; j < wielomian2.size(); j++)
		{
			wynikowy.at(i + j) += wielomian1.at(i) * wielomian2.at(j);
		}
	}

	return wynikowy;
}*/

vector<double> sumujWielomiany(vector<double> wielomian1, vector<double> wielomian2)
{
	if (wielomian1.size() < wielomian2.size())
	{
		return sumujWielomiany(wielomian2, wielomian1);
	}
	vector<double> wynikowy;

	wynikowy = wielomian1;
	vector<double>::reverse_iterator rwynikowy = wynikowy.rbegin();
	for (vector<double>::reverse_iterator rwielomian = wielomian2.rbegin(); rwielomian != wielomian2.rend(); rwielomian++, rwynikowy++)
	{
		*rwynikowy += *rwielomian;
	}

	return wynikowy;
}

double calka(double A, double B, vector<double> wielomian, double(*fun)(double), double epsilon)
{
	vector<double> wyniki;
	double n = 2.0;
	int iteracje = 0;
	double roznica;
	do
	{
		double wynik = 0.0;
		double h = (B - A) / n;
		double xa = A;
		for (int i = 0; i < n/2; i++)
		{
			wynik = wynik + (h / 3.0)*(iloczynFunkcji(fun, wielomian, xa) + 4 * iloczynFunkcji(fun, wielomian, xa + h) + iloczynFunkcji(fun, wielomian, xa + h + h));
			xa = xa + h + h;
		}

		wyniki.push_back(wynik);

		if (iteracje == 0)
		{
			roznica = wynik;
		}
		else
		{
			roznica = wynik - wyniki[iteracje - 1];
		}

		if (abs(roznica) < epsilon)
		{
			break;
		}

		n *= 2.0;
		iteracje += 1;
	} while (true);

	return wyniki[wyniki.size() - 1];
}

void wyznaczFunkcjeAproksymujaca(double A, double B, vector<double> &xApr, vector<double> &yApr, 
								 vector<vector<double>> wielomiany, int stopien, double(*fun)(double))
{
	vector<double> wspolczynniki;
	system("cls");
	cout << "Prosze czekac (0%)...";
	for (int i = 0; i <= stopien; i++)
	{
		double wsp = 2.0 / M_PI;
		wsp *= calka(-0.99999, 0.99999, wielomiany[i], fun, 0.001);
		wspolczynniki.push_back(wsp);
		system("cls");
		cout << "Prosze czekac (" << ((i+1) * 100 / (stopien + 1)) << "%)...";
	}

	cout << endl;

	for (double x = A; x <= B; x += 0.1)
	{
		xApr.push_back(x);
		double y = 0;
		y += wspolczynniki[0] / 2 * Horner(wielomiany[0], x);
		for (int j = 1; j <= stopien; j++)
		{
			y += wspolczynniki[j] * Horner(wielomiany[j], x);
		}
		yApr.push_back(y);
	}
}

void wyznaczWartosciFunkcji(double A, double B, vector<double> &x, vector<double> &y, double(*fun)(double))
{
	for (double i = A; i <= B; i += 0.1)
	{
		x.push_back(i);
		y.push_back(fun(i));
	}
}

double waga(double x)
{
	double y = 1.0;
	double pierw = sqrt(1.0 - potega(x, 2));
	y /= pierw;
	return y;
}

double iloczynFunkcji(double(*fun)(double), vector<double> wielomian, double x)
{
	return fun(x) * Horner(wielomian, x) * waga(x);
}

double bladAproksymacji(vector<double> yFunkcji, vector<double> yApr)
{
	double max = 0.0;
	for (int i = 0; i < yFunkcji.size(); i++)
	{
		double tmp = abs(yFunkcji[i] - yApr[i]);
		if (tmp > max)
		{
			max = tmp;
		}
	}
	return max;
}

double znajdzMin(vector<double> tab)
{
	double min = tab[0];
	for (int i = 1; i < tab.size(); i++)
	{
		if (tab[i] < min)
		{
			min = tab[i];
		}
	}
	return min;
}

double znajdzMax(vector<double> tab)
{
	double max = tab[0];
	for (int i = 1; i < tab.size(); i++)
	{
		if (tab[i] > max)
		{
			max = tab[i];
		}
	}
	return max;
}