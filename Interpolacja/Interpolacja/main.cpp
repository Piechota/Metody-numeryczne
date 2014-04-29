#include <iostream>
#include <vector>

#include "gnuplot_i.hpp"

#define M_PI 3.1415926535

using namespace std;

#pragma region FUNKCJE MATEMAYCZNE

	double Horner(double x, double* wsp, int stopien);
	double Horner(vector<double> tab, double x);
	double potega(double x, int n);
	double modul(double x);
	double wielomian(double x);
	double trygonometria(double x);
	double skladana(double x);

#pragma endregion

#pragma region ZMIENNE GLOBALNE

	vector<double> x;
	vector<double> y;
	vector<double> xWezly;
	vector<double> yWezly;
	vector<double> xWielomian;
	vector<double> yWielomian;

#pragma endregion

#pragma region FUNKCJE

	void uzupelnijWektorFunkcji(double A, double B, double (*funkcja)(double));
	void uzupelnijWektorWezlow(double A, double B, int N, double(*funkcja)(double));
	void uzupelnijWektorInterpolowany(int N, double A, double B);
	double obliczIlorazRoznicowy(double x1, double y1, double x2, double y2);
	vector<double> mnozWielomiany(vector<double> wielomian1, vector<double> wielomian2);
	vector<double> sumujWielomiany(vector<double> wielomian1, vector<double> wielomian2);
	bool sprawdzWielomian(double xw, double yw, vector<double> wsp);
	void rysujWykres();

#pragma endregion

int main()
{
	double(*funkcje[])(double) = { modul, wielomian, trygonometria, skladana };
	cout << "Wybierz funkcje:\n"
		<< "1. |x|\n"
		<< "2. 2 * x^7 - 3 * x^5 + x^4 - x^3 + 8 * x^2 - 4 * x + 2\n"
		<< "3. cos^3(x) - 2 * cos(x)\n"
		<< "4. sin^2(x) + 4 * sin(x) - 3 + x^3 - 2 * x^2 + 3 * x\n";
	int wybor;
	do{
		cin.clear();
		cin.sync();
		cin >> wybor;
	} while (wybor<1 || wybor>4);

	double(*funkcja)(double) = funkcje[wybor - 1];

	system("cls");
	cout << "Podaj przedzial:\n"
		<< "A: ";
	double A;
	cin >> A;
	cout << "B: ";
	double B;
	do
	{
		cin >> B;
	} while (B <= A);

	system("cls");
	cout << "Podaj liczbe wezlow: ";
	int N;
	do
	{
		cin >> N;
	} while (N <= 0);

	uzupelnijWektorFunkcji(A, B, funkcja);
	uzupelnijWektorWezlow(A, B, N, funkcja);
	uzupelnijWektorInterpolowany(N, A, B);
	rysujWykres();

	return 0;
}

#pragma region DEFINICJE FUNKCJI MATEMATYCZNYCH

	double Horner(double x, double* wsp, int stopien)
	{
		double wynik = wsp[0];
		for (int i = 1; i <= stopien; i++)
		{
			wynik *= x;
			wynik += wsp[i];
		}
		return wynik;
	}

	double Horner(vector<double> tab, double x)
	{
		double wartosc = tab[0];
		for (unsigned int i = 1; i < tab.size(); i += 1)
		{
			wartosc = wartosc * x + tab[i];
		}
		return wartosc;
	}

	double potega(double x, int n)
	{
		double wynik = 1;
		for (int i = 1; i < n; i++)
		{
			wynik *= x;
		}
		return wynik;
	}

	double modul(double x)
	{
		if (x >= 0)
		{
			return x;
		}
		else
		{
			return -x;
		}
	}

	double wielomian(double x)
	{
		//2*x^7 - 3*x^5 + x^4 - x^3 + 8*x^2 - 4*x + 2
		double wsp[] = { 2, 0, -3, 1, -1, 8, -4, 2 };
		return Horner(x, wsp, 7);
	}

	double trygonometria(double x)
	{
		//cos(x)^3 - 2cos(x)
		double wsp[] = { 1, 0, -2, 0 };
		return Horner(cos(x), wsp, 3);
	}

	double skladana(double x)
	{
		//f(x) = sin^2(x) + 4 * sin(x) - 3 + x^3 - 2*x^2 + 3*x
		// dziele funkcje na dwie:
		// g(x) = sin^2(x) + 4 * sin(x) - 3 | czesc trygonometryczna
		// h(x) = x^3 - 2*x^2 + 3*x	| czesc wielomianowa
		// tym sposobem mam f(x) = g(x) + h(x)

		double wsptryg[] = { 1, 4, -3 };
		double czesc_trygonometryczna = Horner(sin(x), wsptryg, 2);
		double wspwielomian[] = { 1, -2, 3, 0 };
		double czesc_wielomianowa = Horner(x, wspwielomian, 3);

		return (czesc_trygonometryczna + czesc_wielomianowa);
	}

#pragma endregion

#pragma region DEFINICJE FUNKCJI

	void uzupelnijWektorFunkcji(double A, double B, double(*funkcja)(double))
	{
		for (double i = A; i <= B; i+=0.1)
		{
			x.push_back(i);
			y.push_back(funkcja(i));
		}
	}

	void uzupelnijWektorWezlow(double A, double B, int N, double(*funkcja)(double))
	{
		for (int i = 0; i < N; i++)
		{
			double x_w = cos(((2 * i + 1) * M_PI) / (2 * N + 1));
			x_w *= (B - A);
			x_w += (A + B);
			x_w *= 0.5;
			xWezly.push_back(x_w);
			yWezly.push_back(funkcja(x_w));
		}
	}

	void uzupelnijWektorInterpolowany(int N, double A, double B)
	{
		// wyznaczenie ilorazow roznicowych
		vector<double> *ilorazyRoznicowe = new vector<double>[yWezly.size()];
		ilorazyRoznicowe[0] = yWezly;

		for (unsigned int i = 1; i < yWezly.size(); i++)
		{
			for (unsigned int j = 0; j < yWezly.size() - i; j++)
			{
				ilorazyRoznicowe[i].push_back(obliczIlorazRoznicowy(xWezly.at(j), ilorazyRoznicowe[i - 1].at(j), xWezly.at(j + i), ilorazyRoznicowe[i - 1].at(j + 1)));
			}
		}

		// wymnozenie wszystkich czynnikow (x-xi) wielomianu interpolujacego
		// i zsumowanie ich w jeden wielomian w postaci an*x^n+a_n-1*x^(n-1)+...+a1*x+a0
		// w wektorze wsp_wielomianu zostaja wspolczynniki wielomianu powyzej
		vector<double> wsp_wielomianu;
		for (unsigned int i = 0; i < yWezly.size(); i += 1)
		{
			wsp_wielomianu.push_back(0);
		}

		for (unsigned int i = 0; i < yWezly.size(); i += 1)
		{
			vector<double> fi;
			fi.push_back(ilorazyRoznicowe[i].at(0));
			for (unsigned int j = 0; j < i; j += 1)
			{
				vector<double> tmp;
				tmp.push_back(1);
				tmp.push_back(-xWezly.at(j));
				fi = mnozWielomiany(fi, tmp);
			}

			wsp_wielomianu = sumujWielomiany(wsp_wielomianu, fi);
		}

		// uzupelnienie wektorow wielomianu interpolacyjnego
		// na calym zadanym przedziale w celu narysowania wielomianu
		for (double i = A; i <= B; i += 0.1)
		{
			xWielomian.push_back(i);
		}

		/*for (vector<double>::iterator it = xWielomian.begin(); it != xWielomian.end(); it += 1)
		{
			yWielomian.push_back(Horner(wsp_wielomianu, *it));
		}*/

		for (unsigned int i = 0; i < xWielomian.size(); i++)
		{
			yWielomian.push_back(Horner(wsp_wielomianu, xWielomian.at(i)));
		}

		for (unsigned i = 0; i < xWezly.size(); i++)
		{
			if (!sprawdzWielomian(xWezly.at(i), yWezly.at(i), wsp_wielomianu))
			{
				cout << "Wartosc wielomianu w wezle x = " << xWezly.at(i) << " wyznaczona z wielomianu interpolacyjnego (w_n(x_n)) "
					<< "nie pokrywa sie z f(x_n)\n";
			}
		}

		delete[] ilorazyRoznicowe;
	}

	double obliczIlorazRoznicowy(double x1, double y1, double x2, double y2)
	{
		return (y2 - y1) / (x2 - x1);
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
				wynikowy.at(i+j) += wielomian1.at(i) * wielomian2.at(j);
			}
		}

		return wynikowy;
	}

	vector<double> sumujWielomiany(vector<double> wielomian1, vector<double> wielomian2)
	{
		vector<double> wynikowy;
	
		if (wielomian1.size() > wielomian2.size())
		{
			wynikowy = wielomian1;
			vector<double>::reverse_iterator rwynikowy = wynikowy.rbegin();
			for (vector<double>::reverse_iterator rwielomian = wielomian2.rbegin(); rwielomian != wielomian2.rend(); rwielomian++, rwynikowy++)
			{
				*rwynikowy += *rwielomian;
			}
		}
		else
		{
			wynikowy = wielomian2;
			vector<double>::reverse_iterator rwynikowy = wynikowy.rbegin();
			for (vector<double>::reverse_iterator rwielomian = wielomian1.rbegin(); rwielomian != wielomian1.rend(); rwielomian++, rwynikowy++)
			{
				*rwynikowy += *rwielomian;
			}
		}

		return wynikowy;
	}

	bool sprawdzWielomian(double xw, double yw, vector<double> wsp)
	{
		// sprawdzenie czy wartosci w wezlach sa rowne (warunek interpolacji)
		// wn(xn) = yn
		// uwzglednienie dokladnosci 0.0001
		if (abs(Horner(wsp, xw) - yw) < 0.0001)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void rysujWykres()
	{
		if (!Gnuplot::set_GNUPlotPath("E:/gnuplot/bin"))
		{
			return;
		}

		Gnuplot* wykres = new Gnuplot;
		wykres->set_title("Interpolacja Newtona na wezlach Czebyszewa");
		wykres->set_xlabel("X");
		wykres->set_ylabel("Y");

		if (!xWezly.empty() && !yWezly.empty())
		{
			wykres->set_style("points");
			wykres->set_pointsize(2.0);
			wykres->plot_xy(xWezly, yWezly, "Wezly Czebyszewa");
		}
		else
		{
			cout << "Nie wyznaczono wezlow Czebyszewa" << endl;
		}

		if (!x.empty() && !y.empty())
		{
			wykres->set_style("lines");
			wykres->plot_xy(x, y, "Funkcja");
		}
		else
		{
			cout << "Nie zdefiniowano funkcji" << endl;
		}

		if (!xWielomian.empty() && !yWielomian.empty())
		{
			wykres->set_style("lines");
			wykres->plot_xy(xWielomian, yWielomian, "Wielomian");
		}
		else
		{
			cout << "Nie wyznaczono wielomianu interpolacyjnego" << endl;
		}

		system("pause");
		delete wykres;
	}

#pragma endregion
