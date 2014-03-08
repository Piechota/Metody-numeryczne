#include "gnuplot_i.hpp"
#include <cmath>
#include <string>

using namespace std;

int menu();
double wielomian(float x);	//funkcja obliczajaca 2x^3 + 4x^2 - 7
double trygonometria(float x); //funkcja obliczajaca sinx
double wykladnicza(float x);	//funkcja obliczajaca 5^x
double wielXtryg(float x);		//funkcja obliczajaca 2(sinx)^3 - 3x + 1
double trygXwykl(float x);		//funkcja obliczajaca 5^x + 7x*4^x
double wielXwykl(float x);		//funkcja obliczajaca sin (3^x)

string funk;		//pelna funkcja
double wynikFunkcji(double X, string funkcja);	//wartosc funkcji w X

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

	getline(cin, funk);
	cout << endl;
	cout << wynikFunkcji(1.0, funk) << endl;
	system("pause");
}

double wynikFunkcji(double X, string funkcja)
{
	string strFunkcji(funkcja);		//kopia lancucha funkcji

	//znalezienie wszystkich x i zastapienie ich wartoscia.
	size_t found = strFunkcji.find('x');
	while ( found != string::npos)
	{
		strFunkcji.replace(found, 1, to_string(X));
		found = strFunkcji.find('x');
	}

	found = strFunkcji.find(',');
	while (found != string::npos)
	{
		strFunkcji.replace(found, 1, ".");
		found = strFunkcji.find(',');
	}

	found = strFunkcji.find(' ');
	while (found != string::npos)
	{
		strFunkcji.replace(found, 1, "");
		found = strFunkcji.find(' ');
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	int otwNawias;
	int zamNawias;
	found = strFunkcji.find_last_of('(');
	while (found != string::npos)
	{
		size_t tmp = strFunkcji.find(')', found);
		if (tmp == string::npos)
		{
			cout << "zla funkcja!" << endl;
			system("pause");
			exit(0);
		}
		
		otwNawias = found;
		zamNawias = tmp+1;

		string newFunk(strFunkcji, otwNawias+1, (zamNawias-1)-(otwNawias+1));
		strFunkcji.replace(otwNawias, zamNawias - otwNawias, to_string(wynikFunkcji(X, newFunk)));
		found = strFunkcji.find_last_of('(');
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	//znalezienie wszystkich dzialan sinus oraz ich obliczenie
	found = strFunkcji.find("sin");
	while (found != string::npos)
	{
		string liczba; //liczba po prawo
		double wynik = 0;   //wynik operacji

		int beginOperation = found; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		int i = 3;

		while (found + i < strFunkcji.length() && (isdigit(strFunkcji[found + i]) || strFunkcji[found + i] == '.' || strFunkcji[found + i] == '-'))
		{
			liczba.insert(liczba.end(), strFunkcji[found + i]);
			i++;
		}
		endOperation = found + i - 1;

		wynik = sin(stod(liczba));

		strFunkcji.replace(beginOperation, endOperation - beginOperation, to_string(wynik));
		
		found = strFunkcji.find("sin");
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	//znalezienie wszystkich dzialan cosinus oraz ich obliczenie
	found = strFunkcji.find("cos");
	while (found != string::npos)
	{
		string liczba; //liczba po prawo
		double wynik = 0;   //wynik operacji

		int beginOperation = found; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		int i = 3;

		while (found + i < strFunkcji.length() && (isdigit(strFunkcji[found + i]) || strFunkcji[found + i] == '.' || strFunkcji[found + i] == '-'))
		{
			liczba.insert(liczba.end(), strFunkcji[found + i]);
			i++;
		}
		endOperation = found + i - 1;

		wynik = cos(stod(liczba));

		strFunkcji.replace(beginOperation, endOperation - beginOperation, to_string(wynik));
		
		found = strFunkcji.find("cos");
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	//znalezienie wszystkich dzialan tanges oraz ich obliczenie
	found = strFunkcji.find("tg");
	while (found != string::npos)
	{
		string liczba; //liczba po prawo
		double wynik = 0;   //wynik operacji

		int beginOperation = found; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		int i = 2;

		while (found + i < strFunkcji.length() && (isdigit(strFunkcji[found + i]) || strFunkcji[found + i] == '.' || strFunkcji[found + i] == '-'))
		{
			liczba.insert(liczba.end(), strFunkcji[found + i]);
			i++;
		}
		endOperation = found + i - 1;

		wynik = tan(stod(liczba));

		strFunkcji.replace(beginOperation, endOperation - beginOperation, to_string(wynik));
		
		found = strFunkcji.find("tg");
	}

///////////////////////////////////////////////////////////////////////////////////////////////

	//znalezienie wszystkich dzialan ^ oraz ich obliczenie
	found = strFunkcji.find_first_of("^", 1);
	while (found != string::npos)
	{
		string liczba1;	//liczba na lewo od znaku
		string liczba2; //liczba na prawo od znaku
		double wynik = 0;   //wynik operacji

		int beginOperation; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		int i = 1;

		while ((int)found - i >= 0 && (isdigit(strFunkcji[found - i]) || 
				strFunkcji[found - i] == '.' || 
				(strFunkcji[found - i] == '-' && ((int)found - i - 1 < 0 || !isdigit(strFunkcji[found - i - 1])))))		//wczytywanie liczby do liczba1
		{
			liczba1.insert(liczba1.begin(), strFunkcji[found - i]);
			i++;
		}
		beginOperation = found - i + 1; //zapisanie poczatku operacji

		i = 1;

		while (found + i < strFunkcji.length() && (isdigit(strFunkcji[found + i]) || strFunkcji[found + i] == '.' || strFunkcji[found + i] == '-'))
		{
			liczba2.insert(liczba2.end(), strFunkcji[found + i]);
			i++;
		}
		endOperation = found + i - 1;

		wynik = pow(stod(liczba1), stod(liczba2));

		strFunkcji.replace(beginOperation, endOperation - beginOperation, to_string(wynik));
		
		found = strFunkcji.find_first_of("^", 1);
	}

///////////////////////////////////////////////////////////////////////////////////////////////

	//znalezienie wszystkich dzialan * i / oraz ich obliczenie
	found = strFunkcji.find_first_of("*/", 1);
	while (found != string::npos)
	{
		string liczba1;	//liczba na lewo od znaku
		string liczba2; //liczba na prawo od znaku
		double wynik = 0;   //wynik operacji

		int beginOperation; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		int i = 1;

		while ((int)found - i >= 0 && (isdigit(strFunkcji[found - i]) || 
				strFunkcji[found - i] == '.' || 
				(strFunkcji[found - i] == '-' && ((int)found - i - 1 < 0 || !isdigit(strFunkcji[found - i - 1])))))		//wczytywanie liczby do liczba1
		{
			liczba1.insert(liczba1.begin(), strFunkcji[found - i]);
			i++;
		}
		beginOperation = found - i + 1; //zapisanie poczatku operacji

		i = 1;

		while (found + i < strFunkcji.length() && (isdigit(strFunkcji[found + i]) || strFunkcji[found + i] == '.' || strFunkcji[found + i] == '-'))
		{
			liczba2.insert(liczba2.end(), strFunkcji[found + i]);
			i++;
		}
		endOperation = found + i - 1;

		switch (strFunkcji[found])
		{
		case '*':
			wynik = stod(liczba1) * stod(liczba2);
			break;
		case '/':
			wynik = stod(liczba1) / stod(liczba2);
			break;
		}

		strFunkcji.replace(beginOperation, endOperation - beginOperation, to_string(wynik));
		
		found = strFunkcji.find_first_of("*/", 1);
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//znalezienie wszystkich dzialan + i - oraz ich obliczenie
	found = strFunkcji.find_first_of("+-", 1);
	while (found != string::npos)
	{
		string liczba1;	//liczba na lewo od znaku
		string liczba2; //liczba na prawo od znaku
		double wynik = 0;   //wynik operacji

		int beginOperation; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		int i = 1;

		while ((int)found - i >= 0 && (isdigit(strFunkcji[found - i]) ||
				strFunkcji[found - i] == '.' ||
				(strFunkcji[found - i] == '-' && ((int)found - i - 1 < 0 || !isdigit(strFunkcji[found - i - 1])))))		//wczytywanie liczby do liczba1
		{
			liczba1.insert(liczba1.begin(), strFunkcji[found - i]);
			i++;
		}
		beginOperation = found - i + 1; //zapisanie poczatku operacji

		i = 1;

		while (found + i < strFunkcji.length() && (isdigit(strFunkcji[found + i]) || strFunkcji[found + i] == '.' || strFunkcji[found + i] == '-'))
		{
			liczba2.insert(liczba2.end(), strFunkcji[found + i]);
			i++;
		}
		endOperation = found + i - 1;

		switch (strFunkcji[found])
		{
			case '+':
				wynik = stod(liczba1) + stod(liczba2);
				break;
			case '-':
				wynik = stod(liczba1) - stod(liczba2);
				break;
		}

		strFunkcji.replace(beginOperation, endOperation - beginOperation, to_string(wynik));
		
		found = strFunkcji.find_first_of("+-", 1);
	}
	return stod(strFunkcji);
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
