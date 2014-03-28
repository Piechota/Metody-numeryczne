#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "gnuplot_i.hpp"

#define ERROR "W powyzszym wypadku wylaczam program\n"
#define MAT_2PI 2*3.14159
#define MAT_PI 3.14159

using namespace std;

//Zmienne globalne
double(*funkcja)(double) = NULL;
vector<double> x;
vector<double> y;
vector<double> xInterpolowane;
vector<double> yInterpolowane;
vector<double> xWezly;
vector<double> yWezly;

//Funkcje matematyczne, obliczeniowe
double liniowa(double x);
double modul(double x);
double wielomian(double x);
double sinus(double x);
double liniowaSinus(double x);
double modulSinusWykladnicza(double x);
double poteguj(double podstawa, int potega);
double Horner(double wsp[], double x, int stopien);

//Funkcja interpolujaca i rysujaca wykres oraz uzupelniajace wektory
void interpoluj(double A, double B, int N);
void rysuj_wykres(double A, double B);
void uzupelnijWektorXY(double A, double B);
void uzupelnijWektorInterpolowany(double A, double B);
void uzupelnijWektorWezlow(double A, double B, int N);

int main()
{
	cout << "Wybierz funkcje: " << endl
		<< "1. 2*x - 4" << endl
		<< "2. |x|" << endl
		<< "3. 5*x^3 + 3*x^2 - 7*x + 3" << endl
		<< "4. sin(x)" << endl
		<< "5. 2*sin(x) - 5" << endl
		<< "6. 2*|x| - 3*sin(x) - x^2" << endl
		<< "7. Zamknij program" << endl;
	int wyborFunkcji;
	cin >> wyborFunkcji;

	system("cls");
	try
	{
		switch (wyborFunkcji)
		{
		case 1:
			funkcja = liniowa;
			break;
		case 2:
			funkcja = modul;
			break;
		case 3:
			funkcja = wielomian;
			break;
		case 4:
			funkcja = sinus;
			break;
		case 5:
			funkcja = liniowaSinus;
			break;
		case 6:
			funkcja = modulSinusWykladnicza;
			break;
		case 7:
			exit(0);
			break;
		default:
			string txt = "Nieznana komenda";
			throw txt;
			break;
		}
	}
	catch (string co)
	{
		cout << co << endl;
		cout << ERROR;
		system("pause");
		exit(1);
	}

	cout << "Podaj przedzial interpolacji: " << endl
		<< "A: ";
	double A;
	cin >> A;
	cout << "B: ";
	double B;
	cin >> B;

	cout << "Podaj liczbe wezlow interpolacji: " << endl;
	int N;
	cin >> N;
	
	interpoluj(A, B, N);
	uzupelnijWektorXY(A, B);
	rysuj_wykres(A, B);

	return 0;
}

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

void interpoluj(double A, double B, int N)
{

	uzupelnijWektorInterpolowany(A, B);
	uzupelnijWektorWezlow(A, B, N - 1);
}

void rysuj_wykres(double A, double B)
{
	if (x.empty() || y.empty() || xInterpolowane.empty() || yInterpolowane.empty() || xWezly.empty() || yWezly.empty())
	{
		cout << "Jeden z wektorow jest pusty, nie uzupelniono ich" << endl;
		system("pause");
		return;
	}
	if (!(Gnuplot::set_GNUPlotPath("E:/gnuplot/bin") || Gnuplot::set_GNUPlotPath("C:/gnuplot/bin")))
	{
		string path;
		do{
			path.clear();
			cout << endl << "Plik folder nie znaleziony!" << endl;
			cout << "Prosze podac sciezke do gnuplot/bin" << endl;
			getline(cin, path);
		} while (!Gnuplot::set_GNUPlotPath(path));
	}

	try
	{
		Gnuplot* wykres = new Gnuplot;
		wykres->set_title("Wykres wybranej funkcji z zaznaczeniem wezlow interpolacji oraz wielomianu interpolacji");
		wykres->set_style("lines");
		wykres->set_xlabel("X");
		wykres->set_ylabel("Y");
		wykres->set_grid();
		wykres->plot_xy(x, y, "Funkcja");
		wykres->plot_xy(xInterpolowane, yInterpolowane, "Wielomian interpolowany");
		wykres->set_style("points");
		wykres->set_pointsize(2.0);
		wykres->plot_xy(xWezly, yWezly, "Wezly interpolacji");
		system("pause");
	}
	catch (GnuplotException ge)
	{
		cout << ge.what() << endl;

		system("pause");
	}
}

void uzupelnijWektorXY(double A, double B)
{
	for (double i = A; i <= B; i += 0.1)
	{
		x.push_back(i);
		y.push_back(funkcja(i));
	}
}

void uzupelnijWektorInterpolowany(double A, double B)
{
	for (double i = A; i <= B; i += 0.1)
	{
		xInterpolowane.push_back(i);
		yInterpolowane.push_back(funkcja(i));
	}
}

void uzupelnijWektorWezlow(double A, double B, int N)
{
	for (int n = 1; n <= N + 1; n++)
	{
		double arg = ((N + 1 + 0.5 - n) / (N + 1)) * MAT_PI;
		double wynik =cos(arg);
		wynik *= (B - A);
		wynik += A + B;
		wynik *= 0.5;
		xWezly.push_back(wynik);
		yWezly.push_back(funkcja(wynik));
	}
	cout << "Ilosc x w wezlach: " << xWezly.size() << endl;
}