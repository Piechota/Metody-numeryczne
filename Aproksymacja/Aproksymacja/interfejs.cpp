#include "interfejs.h"
#include "funkcjeMatematyczne.h"

void komunikacja(vector<double> &x, vector<double> &y, vector<double> &xApr, vector<double> &yApr)
{
	system("cls");
	cout << "1. Podany stopien aproksymacji" << endl
		<< "2. Podany oczekiwany blad aproksymacji" << endl
		<< "3. Wyjdz" << endl;
	int wybor;
	cin >> wybor;
	if (wybor == 3)
	{
		cout << "Pa pa" << endl;
		system("pause");
		exit(0);
	}
	cout << "Aproksymacja oparta o wielomiany Czebyszewa\n\n\n";
	int wyborFunkcji = wybierzFunkcje();
	if (wyborFunkcji == -1)
	{
		cout << "Nie ma takiej funkcji :)" << endl;
		system("pause");
		exit(0);
	}
	double(*fun)(double) = wielomian;
	switch (wyborFunkcji)
	{
	case 1:
		fun = wielomian;
		break;
	case 2:
		fun = liniowa;
		break;
	case 3:
		fun = modul;
		break;
	case 4:
		fun = trygonometryczna;
		break;
	case 5:
		fun = wieltryg;
		break;
	case 6:
		fun = wielmodul;
		break;
	}
	cout << "Przy przedziale aproksymacji trzeba pamietac, ze dla wielomianow Czebyszewa wzor Simspona mnozy sie przez wage "
		<< "1/sqrt(1-x^2) wiec przedzial powinien zawierac sie w przedziale [-1,1]" << endl;
	double lewyKraniec = podaj("Podaj lewy kraniec przedzialu aproksymacji: ");
	double prawyKraniec = podaj("Podaj prawy kraniec przedzialu aproksymacji: ");
	vector<vector<double>> wielomianyAproksymacji;
	int stopien;
	switch (wybor)
	{
	case 1:
		system("cls");
		stopien = (int)podaj("Podaj stopien wielomianu aproksymacji: ");
		wielomianyAproksymacji = wielomiany(stopien);
		wyznaczFunkcjeAproksymujaca(lewyKraniec, prawyKraniec, xApr, yApr, wielomianyAproksymacji, stopien, fun);
		wyznaczWartosciFunkcji(lewyKraniec, prawyKraniec, x, y, fun);
		cout << "Blad aproksymacji: " << bladAproksymacji(y, yApr) << endl;
		break;
	case 2:
		szukajStopnia(lewyKraniec, prawyKraniec, fun, x, y, xApr, yApr);
		break;
	default:
		cout << "Sa tylko 3 opcje" << endl;
		break;
	}
}

double liczWartoscFunkcji(double (*fun)(double), double x)
{
	return fun(x);
}

double podaj(string co)
{
	cout << co << endl;
	double toreturn;
	cin >> toreturn;
	return toreturn;
}

int wybierzFunkcje()
{
	cout << "1. 2x^3-7x^2+x-3" << endl
		<< "2. 7x-3" << endl
		<< "3. |x|" << endl
		<< "4. cos(x)" << endl
		<< "5. 2cos^4(x) - 3cos^3(x) + 5cos(x) - 1" << endl
		<< "6. 3|x|^3 - 4|x| + 2" << endl;
	int wybor;
	cin >> wybor;
	if (wybor < 1 || wybor > 6)
	{
		return -1;
	}
	return wybor;
}

void szukajStopnia(double lewyKraniec, double prawyKraniec, double(*fun)(double), vector<double> &x, vector<double> &y, vector<double> &xApr, vector<double> &yApr)
{
	double oczekiwanyBlad = podaj("Podaj oczekiwany blad: ");
	int stopien = 0;
	double blad = oczekiwanyBlad;
	vector<vector<double>> wielomianyAproksymacji;
	do
	{
		stopien++;
		wielomianyAproksymacji = wielomiany(stopien);
		xApr.clear();
		yApr.clear();
		x.clear();
		y.clear();
		wyznaczFunkcjeAproksymujaca(lewyKraniec, prawyKraniec, xApr, yApr, wielomianyAproksymacji, stopien, fun);
		wyznaczWartosciFunkcji(lewyKraniec, prawyKraniec, x, y, fun);
		blad = bladAproksymacji(y, yApr);
	} while (blad > oczekiwanyBlad);
	cout << "Oczekiwany blad (" << oczekiwanyBlad << ") osiagnieto dla aproksymacji stopnia " << stopien << endl
		<< "Dokladny blad = " << blad << endl;
}