#include "gnuplot_i.hpp"
#include <cmath>
#include <string>
#include "parser.h"
#include <ctime>

using namespace std;

void menu(string &funkcja);
string funk;		//pelna funkcja
bool bisekcja(double A, double B, float n, bool iteracje, string &funkcja, int &iteracja); //dolna granica przedzialu, gorna granica przedzialu, warunek zatrzymania, czy warunkiem zatrzymania jest ilosc iteracji
void rysuj_wykres(double a, double b, string &funkcja);
double X, Y; //pierwiastek
bool pierw; //czy znaleziono
bool pierwS;	//czy znaleziono pierwiastek w siecznych
double XS, YS;	//pierwiastki
bool sieczne(double A, double B, float n, bool iteracje, string &funkcja, bool zmiana, int &iteracja);
int iteracjaB = 0, iteracjaS = 0;
int poteguj(int podstawa, int potega);

int main()
{
	menu(funk);
	system("pause");
	return 0;
}



bool bisekcja(double A, double B, float n, bool iteracje, string &funkcja, int &iteracja)
{
	//Przerobiona bisekcja na iteracyjne
	/*if (iteracje && n == 0)
	{
		cout << endl << "Koniec iteracji na przedziale: [" << A << ", " << B << "]" << endl;
		iteracja++;
		return false;
	}

	long double wynik = wynikFunkcji((A + B) / 2, funkcja);

	if (wynik == 0)
	{
		cout << endl << "Pierwiastek znaleziony w punkcie: " << (A + B) / 2 << endl;
		cout << "f(" << (A + B) / 2 << ") = 0 +- (9e-7)" << endl;

		X = (A + B) / 2;
		Y = 0.0f;

		iteracja++;
		return true;
	}

	if ((!iteracje) && (abs(wynik) < n))
	{
		cout << endl << "Koniec iteracji na przedziale: [" << A << ", " << B << "]" << endl;
		iteracja++;
		return false;
	}

	if (iteracje)
	{
		n -= 1;
	}

	if (wynikFunkcji(A, funkcja)*wynik < 0)
	{
		iteracja++;
		return bisekcja(A, (A + B) / 2, n, iteracje, funkcja, iteracja);
	}
	if (wynikFunkcji(B, funkcja)*wynik < 0)
	{
		iteracja++;
		return bisekcja((A + B) / 2, B, n, iteracje, funkcja, iteracja);
	}


	iteracja++;
	return false;*/
	if (iteracje)
	{
		for (int i = 0; i < n; i++)
		{
			iteracja++;
			long double wynik = wynikFunkcji((A + B) / 2, funkcja);
			if (wynik == 0)
			{
				cout << endl << "Pierwiastek znaleziony w punkcie: " << (A + B) / 2 << endl;
				cout << "f(" << (A + B) / 2 << ") = 0 +- (9e-7)" << endl;

				X = (A + B) / 2;
				Y = 0.0f;

				return true;
			}
			if (wynikFunkcji(A, funkcja)*wynik < 0)
			{
				B = (A + B) / 2;
			}
			if (wynikFunkcji(B, funkcja)*wynik < 0)
			{
				A = (A + B) / 2;
			}
		}
		cout << "Koniec iteracji na przedziale [" << A << ", " << B << "]" << endl;
		return false;
	}
	else
	{
		for (int i = 0; /* brak warunku konczacego */ ; i++)
		{
			iteracja++;
			long double wynik = wynikFunkcji((A + B) / 2, funkcja);
			if (wynik == 0)
			{
				cout << endl << "Pierwiastek znaleziony w punkcie: " << (A + B) / 2 << endl;
				cout << "f(" << (A + B) / 2 << ") = 0 +- (9e-7)" << endl;

				X = (A + B) / 2;
				Y = 0.0f;

				return true;
			}
			else if (abs(wynik) < n)
			{
				cout << endl << "Pierwiastek znaleziony w punkcie: " << (A + B) / 2 << endl;
				cout << "f(" << (A + B) / 2 << ") = 0 +- ((9e-7)+" << n << ")" << endl;
				return true;
			}
			if (wynikFunkcji(A, funkcja)*wynik < 0)
			{
				B = (A + B) / 2;
			}
			if (wynikFunkcji(B, funkcja)*wynik < 0)
			{
				A = (A + B) / 2;
			}
		}
	}
}

void menu(string &funkcja)
{
	char zatrzymanie;		//warunek zatrzymania
	float n;				//ilosc iteracji lub dokladnosc (zalezy od warunku zatrzymania)
	double a, b;			//przedzialy
	system("cls");

	cout << "Wprowadz wzor funkcji:" << endl;
	cin.clear();
	cin.sync();
	getline(cin, funkcja);
	cout << endl << "Podaj przedzial (pamietaj, ze wartosc funkcji na jego krancach musi miec rozne znaki):" << endl << "A: ";
	cin >> a;
	cout << endl << "B: ";
	cin >> b;
	while (wynikFunkcji(a, funkcja)*wynikFunkcji(b, funkcja) >= 0)
	{
		cout << endl << "Znaki przedzialu sa takie same!" << endl;
		if (wynikFunkcji((a + b) / 2, funkcja) == 0)
			cout << "ale srodek przedzialu jest miejscem zerowym!" << endl;

		cout << endl << "Podaj przedzial (pamietaj, ze wartosc funkcji na jego krancach musi miec rozne znaki):" << endl << "A: ";
		cin >> a;
		cout << endl << "B: ";
		cin >> b;
	}
	cout << endl << "Podaj sposob zatrzymanai:" << endl << "a) Dokladnosc" << endl << "b) Zadana liczba iteracji" << endl;
	cin >> zatrzymanie;
	cout << endl << "Podaj wartosc warunku konczacego:" << endl;
	cin >> n;

	switch (zatrzymanie)
	{
	case 'a':
		pierw = bisekcja(a, b, n, false, funkcja, iteracjaB);
		pierwS = sieczne(a, b, n, false, funkcja, false, iteracjaS);
		break;
	case 'b':
		pierw = bisekcja(a, b, n, true, funkcja, iteracjaB);
		pierwS = sieczne(a, b, n, true, funkcja, false, iteracjaS);
		break;
	}
	if (pierw)
	{
		cout << "Znaleziono pierwiastek w bisekcji" << endl;
	}
	else
	{
		cout << "Nie znaleziono pierwiastka w bisekcji" << endl;
	}
	if (pierwS)
	{
		cout << "Znaleziono pierwiastek w siecznych" << endl;
	}
	else
	{
		cout << "Nie znaleziono pierwiastka w siecznych" << endl;
	}

	cout << endl << "Iteracji przy bisekcji: " << iteracjaB << endl << "Iteracja przy siecznych: " << iteracjaS << endl;

	rysuj_wykres(a, b, funkcja);
}

void rysuj_wykres(double a, double b, string &funkcja)
{
	if (!(Gnuplot::set_GNUPlotPath("E:/gnuplot/bin") || Gnuplot::set_GNUPlotPath("C:/gnuplot/bin")))
	{
		string path;
		do{
			path.clear();
			cout << endl << "Plik folder nie znaleziony!" << endl;
			cout << "Prosze podac sciezke do gnuplot/bin" << endl;
			getline(cin, path);
		}while(!Gnuplot::set_GNUPlotPath(path));
	}

	try
	{
		Gnuplot* wykres = new Gnuplot;
		wykres->set_title("Wykres funkcji " + funkcja + " na przedziale <" + to_string(a) + ", " + to_string(b) + ">");
		wykres->set_style("lines");
		wykres->set_xlabel("X");
		wykres->set_ylabel("Y");
		wykres->set_grid();
		vector<double> x;
		vector<double> y;
		for (double i = a; i <= b; i += 0.1)
		{
			x.push_back(i);
			y.push_back(wynikFunkcji(i, funkcja));
		}
		wykres->plot_xy(x, y, funkcja);

		if (pierw || pierwS)
		{
			vector<double> x;
			vector<double> y;
			vector<double> xS;
			vector<double> yS;
			if (pierw)
			{
				x.push_back(X);
				y.push_back(Y);
			}
			if (pierwS)
			{
				xS.push_back(XS);
				yS.push_back(YS);
			}
			wykres->set_style("points");
			wykres->set_pointsize(2.0);
			wykres->plot_xy(x, y, "Pierwiastek metod¹ bisekcji");

			wykres->plot_xy(xS, yS, "Pierwiastek metod¹ siecznych");
		}

		system("pause");

		delete wykres;
	}
	catch (GnuplotException ge)
	{
		cout << ge.what() << endl;

		system("pause");
	}
}

bool sieczne(double A, double B, float n, bool iteracje, string &funkcja, bool zmiana, int &iteracja)
{
	//Zmiana z rekurencji na iteracje
	/*if (iteracje && n == 0)
	{
		cout << endl << "Koniec iteracji na przedziale: [" << A << ", " << B << "]" << endl;
		iteracja++;
		return false;
	}
	double x1 = A;
	double x2 = B;
	double y1 = wynikFunkcji(x1, funkcja);
	double y2 = wynikFunkcji(x2, funkcja);
	double a = (y1 - y2) / (x1 - x2);
	double b = y1 - a*x1;
	double x0 = -b / a;
	if (A < B)
	{
		if (x0<A || x0>B)
		{
			cout << "Wyszlo za przedzial" << endl;
			return false;
		}
	}
	else
	{
		if (x0>A || x0<B)
		{
			cout << "Wyszlo za przedzial" << endl;
			return false;
		}
	}
	if (wynikFunkcji(x0, funkcja) == 0)
	{
		cout << endl << "Pierwiastek znaleziony w punkcie: " << (A + B) / 2 << endl;
		cout << "f(" << (A + B) / 2 << ") = 0 +- (9e-7)" << endl;

		XS = (A + B) / 2;
		YS = 0.0f;

		iteracja++;
		return true;
	}

	if ((!iteracje) && (abs(wynikFunkcji(x0, funkcja)) < n))
	{
		cout << endl << "Koniec iteracji na przedziale: [" << A << ", " << B << "]" << endl;
		iteracja++;
		return false;
	}
	if (zmiana)
	{
		iteracja++;
		return sieczne(A, x0, n, iteracje, funkcja, false, iteracja);
	}
	else
	{
		iteracja++;
		return sieczne(x0, B, n, iteracje, funkcja, true, iteracja);
	}
	iteracja++;
	return false;*/
	if (iteracje)
	{
		for (int i = 0; i < n; i++)
		{
			iteracja++;
			double x1 = A;
			double x2 = B;
			double y1 = wynikFunkcji(x1, funkcja);
			double y2 = wynikFunkcji(x2, funkcja);
			double a = (y1 - y2) / (x1 - x2);
			double b = y1 - a*x1;
			double x0 = -b / a;
			long double wynik = wynikFunkcji(x0, funkcja);
			if (A < B)
			{
				if (!(x0>A&&x0<B))
				{
					cout << "Wyszlo za przedzial" << endl;
					return false;
				}
			}
			else
			{
				if (!(x0>B&&x0<A))
				{
					cout << "Wyszlo za przedzial" << endl;
					return false;
				}
			}
			if (wynik == 0)
			{
				cout << endl << "Pierwiastek znaleziony w punkcie: " << (A + B) / 2 << endl;
				cout << "f(" << (A + B) / 2 << ") = 0 +- (9e-7)" << endl;

				XS = (A + B) / 2;
				YS = 0.0f;

				return true;
			}
			if (zmiana)
			{
				B = x0;
			}
			else
			{
				A = x0;
			}
			zmiana = !zmiana;
		}
	}
	else
	{
		for (int i = 0; /* brak warunku konczacego */ ; i++)
		{
			iteracja++;
			double x1 = A;
			double x2 = B;
			double y1 = wynikFunkcji(x1, funkcja);
			double y2 = wynikFunkcji(x2, funkcja);
			double a = (y1 - y2) / (x1 - x2);
			double b = y1 - a*x1;
			double x0 = -b / a;
			long double wynik = wynikFunkcji(x0, funkcja);
			if (A < B)
			{
				if (!(x0>A&&x0<B))
				{
					cout << "Wyszlo za przedzial" << endl;
					return false;
				}
			}
			else
			{
				if (!(x0>B&&x0<A))
				{
					cout << "Wyszlo za przedzial" << endl;
					return false;
				}
			}
			if (wynik == 0)
			{
				cout << endl << "Pierwiastek znaleziony w punkcie: " << (A + B) / 2 << endl;
				cout << "f(" << (A + B) / 2 << ") = 0 +- (9e-7)" << endl;

				XS = (A + B) / 2;
				YS = 0.0f;

				return true;
			}
			else if (abs(wynik) < n)
			{
				cout << endl << "Pierwiastek znaleziony w punkcie: " << (A + B) / 2 << endl;
				cout << "f(" << (A + B) / 2 << ") = 0 +- ((9e-7) + " << n << ")" << endl;

				XS = (A + B) / 2;
				YS = 0.0f;

				return true;
			}
			if (zmiana)
			{
				B = x0;
			}
			else
			{
				A = x0;
			}
			zmiana = !zmiana;
		}
	}
	return false;
}