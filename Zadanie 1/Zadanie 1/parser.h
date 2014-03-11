#include <string>

using namespace std;

long double wynikFunkcji(long double X, string funkcja)
{
	string strFunkcji(funkcja);		//kopia lancucha funkcji

	//znalezienie wszystkich x i zastapienie ich wartoscia.
	size_t found = strFunkcji.find('x');
	while (found != string::npos)
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
		zamNawias = tmp + 1;

		string newFunk(strFunkcji, otwNawias + 1, (zamNawias - 1) - (otwNawias + 1));
		strFunkcji.replace(otwNawias, zamNawias - otwNawias, to_string(wynikFunkcji(X, newFunk)));
		found = strFunkcji.find_last_of('(');
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	//znalezienie wszystkich dzialan sinus oraz ich obliczenie
	found = strFunkcji.find("sin");
	while (found != string::npos)
	{
		string liczba; //liczba po prawo
		long double wynik = 0;   //wynik operacji

		int beginOperation = found; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		int i = 3;

		while (found + i < strFunkcji.length() && (isdigit(strFunkcji[found + i]) || strFunkcji[found + i] == '.' || ( i == 3 && strFunkcji[found + i] == '-')))
		{
			liczba.insert(liczba.end(), strFunkcji[found + i]);
			i++;
		}
		endOperation = found + i - 1;

		long double digit = stold(liczba);

		wynik = sin(digit);

		strFunkcji.replace(beginOperation, endOperation - beginOperation, to_string(wynik));

		found = strFunkcji.find("sin");
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	//znalezienie wszystkich dzialan cosinus oraz ich obliczenie
	found = strFunkcji.find("cos");
	while (found != string::npos)
	{
		string liczba; //liczba po prawo
		long double wynik = 0;   //wynik operacji

		int beginOperation = found; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		int i = 3;

		while (found + i < strFunkcji.length() && (isdigit(strFunkcji[found + i]) || strFunkcji[found + i] == '.' || (i == 3 && strFunkcji[found + i] == '-')))
		{
			liczba.insert(liczba.end(), strFunkcji[found + i]);
			i++;
		}
		endOperation = found + i - 1;

		long double digit = stold(liczba);

		wynik = cos(digit);

		strFunkcji.replace(beginOperation, endOperation - beginOperation, to_string(wynik));

		found = strFunkcji.find("cos");
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	//znalezienie wszystkich dzialan tanges oraz ich obliczenie
	found = strFunkcji.find("tan");
	while (found != string::npos)
	{
		string liczba; //liczba po prawo
		long double wynik = 0;   //wynik operacji

		int beginOperation = found; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		int i = 2;

		while (found + i < strFunkcji.length() && (isdigit(strFunkcji[found + i]) || strFunkcji[found + i] == '.' || (i == 2 && strFunkcji[found + i] == '-')))
		{
			liczba.insert(liczba.end(), strFunkcji[found + i]);
			i++;
		}
		endOperation = found + i - 1;

		long double digit = stold(liczba);

		wynik = tan(digit);

		strFunkcji.replace(beginOperation, endOperation - beginOperation, to_string(wynik));

		found = strFunkcji.find("tan");
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	//znalezienie wszystkich dzialan ^ oraz ich obliczenie
	found = strFunkcji.find_first_of("^", 1);
	while (found != string::npos)
	{
		string liczba1;	//liczba na lewo od znaku
		string liczba2; //liczba na prawo od znaku
		long double wynik = 0;   //wynik operacji

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

		while (found + i < strFunkcji.length() && (isdigit(strFunkcji[found + i]) || strFunkcji[found + i] == '.' || (i == 1 && strFunkcji[found + i] == '-')))
		{
			liczba2.insert(liczba2.end(), strFunkcji[found + i]);
			i++;
		}
		endOperation = found + i - 1;

		long double digit1 = stold(liczba1);

		long double digit2 = stold(liczba2);

		wynik = pow(digit1, digit2);

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
		long double wynik = 0;   //wynik operacji

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

		while (found + i < strFunkcji.length() && (isdigit(strFunkcji[found + i]) || strFunkcji[found + i] == '.' || (i == 1 && strFunkcji[found + i] == '-')))
		{
			liczba2.insert(liczba2.end(), strFunkcji[found + i]);
			i++;
		}
		endOperation = found + i - 1;

		long double digit1 = stold(liczba1);

		long double digit2 = stold(liczba2);

		switch (strFunkcji[found])
		{
		case '*':
			wynik = digit1 * digit2;
			break;
		case '/':
			wynik = digit1 / digit2;
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
		long double wynik = 0;   //wynik operacji

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

		while (found + i < strFunkcji.length() && (isdigit(strFunkcji[found + i]) || strFunkcji[found + i] == '.' || (i == 1 && strFunkcji[found + i] == '-')))
		{
			liczba2.insert(liczba2.end(), strFunkcji[found + i]);
			i++;
		}
		endOperation = found + i - 1;

		long double digit1 = stold(liczba1);

		long double digit2 = stold(liczba2);

		switch (strFunkcji[found])
		{
		case '+':
			wynik = digit1 + digit2;
			break;
		case '-':
			wynik = digit1 - digit2;
			break;
		}

		strFunkcji.replace(beginOperation, endOperation - beginOperation, to_string(wynik));

		found = strFunkcji.find_first_of("+-", 1);
	}

	long double rounded = stold(strFunkcji);
	if (abs(rounded - round(rounded)) < 0.0000009)
		rounded = round(rounded);

	return rounded;
}