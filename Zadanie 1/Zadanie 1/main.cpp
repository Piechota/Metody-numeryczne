#include "gnuplot_i.hpp"
#include <cmath>
#include <string>
#include "parser.h"

using namespace std;

void menu(string &funkcja);
/*double wielomian(float x);	//funkcja obliczajaca 2x^3 + 4x^2 - 7
double trygonometria(float x); //funkcja obliczajaca sinx
double wykladnicza(float x);	//funkcja obliczajaca 5^x
double wielXtryg(float x);		//funkcja obliczajaca 2(sinx)^3 - 3x + 1
double trygXwykl(float x);		//funkcja obliczajaca 5^x + 7x*4^x
double wielXwykl(float x);		//funkcja obliczajaca sin (3^x)*/

string funk;		//pelna funkcja
double bisekcja(double A, double B, float n, bool iteracje, string &funkcja); //dolna granica przedzialu, gorna granica przedzialu, warunek zatrzymania, czy warunkiem zatrzymania jest ilosc iteracji
void rysuj_wykres(double a, double b, string &funkcja);

int main()
{
	/*double (*funkcje[6])(float);	//Tablica wskaznikow na funkcje
	funkcje[0] = wielomian;
	funkcje[1] = trygonometria;
	funkcje[2] = wykladnicza;
	funkcje[3] = wielXtryg;
	funkcje[4] = trygXwykl;
	funkcje[5] = wielXwykl;
	int wyb = menu();	//Wybieramy funkcje
	if (wyb == 7)
	{
		system("pause");
		exit(0);
	}
	system("cls");
	cout << "Wybrana funkcja dla arg x = 3:" << endl << funkcje[wyb - 1](3) << endl << endl;
	*/
	menu(funk);
	system("pause");
	return 0;
}



double bisekcja(double A, double B, float n, bool iteracje, string &funkcja)
{
	if (iteracje && n == 0)
	{
		cout << endl << "Koniec iteracji na przedziale: [" << A << ", " << B << "]" << endl;
		return 0;
	}

	if (wynikFunkcji((A + B) / 2, funkcja) == 0)
	{
		cout << endl << "Pierwiastek znaleziony w punkcie: " << (A + B) / 2 << endl;
		cout << "f(" << (A + B) / 2 << ") = 0 +- (9e-7)" << endl;
		return (A + B) / 2;
	}

	cout <<"Wartosc funkcji w polowie przedzialu: " << wynikFunkcji((A + B) / 2, funkcja) << endl;

	double zero1=0;
	double zero2=0;
	if (wynikFunkcji(A, funkcja)*wynikFunkcji((A + B) / 2, funkcja) < 0)
		zero1 = bisekcja(A, (A + B) / 2, n - 1, true, funkcja);
	if (wynikFunkcji(B, funkcja)*wynikFunkcji((A + B) / 2, funkcja) < 0)
		zero2 = bisekcja((A + B) / 2, B, n - 1, true, funkcja);

	if (zero1 > 0)
		return zero1;
	if (zero2 > 0)
		return zero2;

	return 0;
}

void menu(string &funkcja)
{
	int wyb;				//sposob obliczania miejsca zerowego
	char zatrzymanie;		//warunek zatrzymania
	float n;				//ilosc iteracji lub dokladnosc (zalezy od warunku zatrzymania)
	double a, b;			//przedzialy
	/*do
	{
		system("cls");
		cout << "1) 2x^3 + 4x^2 - 7 \n"
			<< "2) sinx \n"
			<< "3) 5^x \n"
			<< "4) 2(sinx)^3 - 3x + 1 \n"
			<< "5) 5^x + 7x*4^x \n"
			<< "6) sin (3^x) \n"
			<< "7) Wyjscie \n"
			<< "Wybierz funkcje: ";
		cin >> wyb;
	} while (wyb <1 || wyb >7);
	return wyb;*/
	do{
		system("cls");

		cout << "Wprowadz wzor funkcji:" << endl;
		cin.clear();
		cin.sync();
		getline(cin, funkcja);

		//zebranie informacji o metodzie liczenia miejsc zerowych
		cout << endl << "Wybierz metode:" << endl << "0. Wyjscie" << endl << "1. Bisekcja" << endl;
		cin >> wyb;
		//Jesli wybor to wyjscie, to po co mamy wybierac dalej ? :D
		if (wyb != 0)
		{
			cout << endl << "Podaj sposob zatrzymanai:" << endl << "b) Zadana liczba iteracji" << endl;
			cin >> zatrzymanie;
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

			cout << endl << "Podaj wartosc warunku konczacego:" << endl;
			cin >> n;

			switch (zatrzymanie)
			{
			case 'b':
				bisekcja(a, b, n, true, funkcja);
				break;
			}

			rysuj_wykres(a, b, funkcja);
			
		}
	} while (wyb != 0);
}

void rysuj_wykres(double a, double b, string &funkcja)
{
	Gnuplot::set_GNUPlotPath("E:/gnuplot/bin");

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
		system("pause");

		delete wykres;
	}
	catch (GnuplotException ge)
	{
		cout << ge.what() << endl;

		system("pause");
	}
}

/*
double wielomian(float x)
{
	return (2 * pow(x, 3) + 4 * pow(x, 2) - 7);
}

double trygonometria(float x)
{
	return sin(x);
}

double wykladnicza(float x)
{
	return pow(5, x);
}

double wielXtryg(float x)
{
	return (2 * pow(sin(x), 3) - 3 * x + 1);
}

double trygXwykl(float x)
{
	return (pow(5, x) + 7 * x*pow(4, x));
}

double wielXwykl(float x)
{
	return sin(pow(3, x));
}
*/