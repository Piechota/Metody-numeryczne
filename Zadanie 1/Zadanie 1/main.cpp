#include "gnuplot_i.hpp"
#include <cmath>
#include <string>
#include "parser.h"

using namespace std;

void menu(string &funkcja);
string funk;		//pelna funkcja
bool bisekcja(double A, double B, float n, bool iteracje, string &funkcja); //dolna granica przedzialu, gorna granica przedzialu, warunek zatrzymania, czy warunkiem zatrzymania jest ilosc iteracji
void rysuj_wykres(double a, double b, string &funkcja);
double X, Y; //pierwiastek
bool pierw; //czy znaleziono
bool pierwS;	//czy znaleziono pierwiastek w siecznych
double XS, YS;	//pierwiastki
bool sieczne(double A, double B, float n, bool iteracje, string &funkcja, bool zmiana);

int main()
{
	menu(funk);
	system("pause");
	return 0;
}



bool bisekcja(double A, double B, float n, bool iteracje, string &funkcja)
{
	if (iteracje && n == 0)
	{
		cout << endl << "Koniec iteracji na przedziale: [" << A << ", " << B << "]" << endl;
		return false;
	}

	if (wynikFunkcji((A + B) / 2, funkcja) == 0)
	{
		cout << endl << "Pierwiastek znaleziony w punkcie: " << (A + B) / 2 << endl;
		cout << "f(" << (A + B) / 2 << ") = 0 +- (9e-7)" << endl;

		X = (A + B) / 2;
		Y = 0.0f;

		return true;
	}

	if ((!iteracje) && (abs(wynikFunkcji((A + B) / 2, funkcja)) < n))
	{
		cout << endl << "Koniec iteracji na przedziale: [" << A << ", " << B << "]" << endl;
		return false;
	}

	if (iteracje)
	{
		n -= 1;
	}

	if (wynikFunkcji(A, funkcja)*wynikFunkcji((A + B) / 2, funkcja) < 0)
		bisekcja(A, (A + B) / 2, n, iteracje, funkcja);
	if (wynikFunkcji(B, funkcja)*wynikFunkcji((A + B) / 2, funkcja) < 0)
		bisekcja((A + B) / 2, B, n, iteracje, funkcja);


	return false;
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
		pierw = bisekcja(a, b, n, false, funkcja);
		pierwS = sieczne(a, b, n, false, funkcja, false);
		break;
	case 'b':
		pierw = bisekcja(a, b, n, true, funkcja);
		pierwS = sieczne(a, b, n, true, funkcja, false);
		break;
	}
	if (pierw)
	{
		cout << "znaleziono pierwiastek w bisekcji" << endl;
	}
	if (pierwS)
	{
		cout << "znaleziono pierwiastek w siecznych" << endl;
	}

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
		//funkcja plot_equation nie pozwala na rysowanie cotangensa oraz funkcji napisanych w postaci 5^x, x^4 itp.
		//dlatego jest tutaj ten if, jesli jest to inna funkcja niz wymienione to niech sobie sam rysuje
		//w przypadku wystapienia takiej funkcji rysujemy recznie
		if (funkcja.find('^') == string::npos && funkcja.find("ctg") == string::npos && funkcja.find("ctan") == string::npos)
		{
			wykres->set_xrange(a, b);
			wykres->plot_equation(funkcja);
		}
		else
		{
			vector<double> x;
			vector<double> y;
			for (double i = a; i <= b; i += 0.1)
			{
				x.push_back(i);
				y.push_back(wynikFunkcji(i, funkcja));
			}
			wykres->plot_xy(x, y, funkcja);
		}

		if (pierw || pierwS)
		{
			vector<double> x;
			vector<double> y;
			if (pierw)
			{
				x.push_back(X);
				y.push_back(Y);
			}
			if (pierwS)
			{
				x.push_back(XS);
				y.push_back(YS);
			}
			wykres->set_style("points");
			wykres->set_pointsize(2.0);

			wykres->plot_xy(x, y, "Pierwiastek");
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

bool sieczne(double A, double B, float n, bool iteracje, string &funkcja, bool zmiana)
{
	if (iteracje && n == 0)
	{
		cout << endl << "Koniec iteracji na przedziale: [" << A << ", " << B << "]" << endl;
		return false;
	}
	double x1 = A;
	double x2 = B;
	double y1 = wynikFunkcji(x1, funkcja);
	double y2 = wynikFunkcji(x2, funkcja);
	double a = (y1 - y2) / (x1 - x2);
	double b = y1 - a*x1;
	double x0 = -b / a;
	if (wynikFunkcji(x0, funkcja) == 0)
	{
		cout << endl << "Pierwiastek znaleziony w punkcie: " << (A + B) / 2 << endl;
		cout << "f(" << (A + B) / 2 << ") = 0 +- (9e-7)" << endl;

		XS = (A + B) / 2;
		YS = 0.0f;

		return true;
	}

	if ((!iteracje) && (abs(wynikFunkcji((A + B) / 2, funkcja)) < n))
	{
		cout << endl << "Koniec iteracji na przedziale: [" << A << ", " << B << "]" << endl;
		return false;
	}
	if (zmiana)
	{
		sieczne(A, x0, n, iteracje, funkcja, false);
	}
	else
	{
		sieczne(x0, B, n, iteracje, funkcja, true);
	}

	return false;
}