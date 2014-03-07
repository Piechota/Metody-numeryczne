#include "gnuplot_i.hpp"
#include "cmath"

using namespace std;

int menu();
double wielomian(float x);	//funkcja obliczajaca 2x^3 + 4x^2 - 7
double trygonometria(float x); //funkcja obliczajaca sinx
double wykladnicza(float x);	//funkcja obliczajaca 5^x
double wielXtryg(float x);		//funkcja obliczajaca 2(sinx)^3 - 3x + 1
double trygXwykl(float x);		//funkcja obliczajaca 5^x + 7x*4^x
double wielXwykl(float x);		//funkcja obliczajaca sin (3^x)

int main()
{
	double (*tab_wsk_do_funkcji[6])(float);	//Tablica wskaznikow na funkcje
	tab_wsk_do_funkcji[0] = wielomian;
	tab_wsk_do_funkcji[1] = trygonometria;
	tab_wsk_do_funkcji[2] = wykladnicza;
	tab_wsk_do_funkcji[3] = wielXtryg;
	tab_wsk_do_funkcji[4] = trygXwykl;
	tab_wsk_do_funkcji[5] = wielXwykl;
	int wyb = menu();	//Wybieramy funkcje
	if (wyb == 7)
	{
		system("pause");
		exit(0);
	}
	wyb--;	//numerowanie od 0 do 5, zamiast od 1 do 6
	double (*funkcja)(float) = tab_wsk_do_funkcji[wyb];	//przypisujemy funkcje do wskaznika
	system("cls");
	cout << funkcja(3) << endl;
	system("pause");
}

int menu()
{
	int wyb;
	do
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
	return wyb;
}

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
