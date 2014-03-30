#include <string>
#include <vector>

using namespace std;

struct digit
{
	int Integer;
	double Double;
	bool isInteger;

	digit()
	{
		Integer = 0;
		Double = 0.0;
		isInteger = true;
	}
	digit(int x)
	{
		Integer = x;
		Double = 0.0;
		isInteger = true;
	}
	digit(double x)
	{
		Integer = 0;
		Double = x;
		isInteger = false;
	}
	void operator*=(digit x)
	{
		if (x.isInteger)
			isInteger ? (Integer *= x.Integer) : (Double *= x.Integer);
		else
		{
			isInteger ? (Double = Integer * x.Double) : (Double *= x.Double);
			isInteger = false;
			Integer = 0;
		}
	}
};

long double wynikFunkcji(long double X, string funkcja);
digit readLeft(int found, string strFunkcji, int &beginOperation);
digit readRight(int found, string strFunkcji, int &endOperation);

void ParsX(string &Funkcja, double X)
{
	size_t found = Funkcja.find('x');
	while (found != string::npos)
	{
		Funkcja.replace(found, 1, to_string(X));
		found = Funkcja.find('x');
	}
}
void ParsComma(string &Funkcja)
{
	size_t found = Funkcja.find(',');
	while (found != string::npos)
	{
		Funkcja.replace(found, 1, ".");
		found = Funkcja.find(',');
	}
}
void ParsSpace(string &Funkcja)
{
	size_t found = Funkcja.find(' ');
	while (found != string::npos)
	{
		Funkcja.replace(found, 1, "");
		found = Funkcja.find(' ');
	}
}
void ParsBracket(string &Funkcja, double X)
{
	int otwNawias;
	int zamNawias;
	size_t found = Funkcja.find_last_of('(');
	while (found != string::npos)
	{
		size_t tmp = Funkcja.find(')', found);
		if (tmp == string::npos)
		{
			cout << "zla funkcja!" << endl;
			system("pause");
			exit(0);
		}

		otwNawias = found;
		zamNawias = tmp + 1;

		string newFunk(Funkcja, otwNawias + 1, (zamNawias - 1) - (otwNawias + 1));
		Funkcja.replace(otwNawias, zamNawias - otwNawias, to_string(wynikFunkcji(X, newFunk)));
		found = Funkcja.find_last_of('(');
	}
}
void ParsSin(string &Funkcja, double X)
{
	//znalezienie wszystkich dzialan sinus oraz ich obliczenie
	size_t found = Funkcja.find("sin");
	while (found != string::npos)
	{
		//string liczba; //liczba po prawo
		long double wynik = 0;   //wynik operacji

		int beginOperation = found; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		digit liczba;

		int i = 3;

		liczba = readRight(found + i, Funkcja, endOperation);

		wynik = sin(liczba.isInteger ? liczba.Integer : liczba.Double);

		Funkcja.replace(beginOperation, endOperation - beginOperation, to_string(wynik));

		found = Funkcja.find("sin");
	}
}
void ParsCos(string &Funkcja, double X)
{
	//znalezienie wszystkich dzialan cosinus oraz ich obliczenie
	size_t found = Funkcja.find("cos");
	while (found != string::npos)
	{
		//string liczba; //liczba po prawo
		long double wynik = 0;   //wynik operacji

		int beginOperation = found; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		digit liczba;

		int i = 3;

		liczba = readRight(found + i, Funkcja, endOperation);

		wynik = cos(liczba.isInteger ? liczba.Integer : liczba.Double);

		Funkcja.replace(beginOperation, endOperation - beginOperation, to_string(wynik));

		found = Funkcja.find("cos");
	}
}
void ParsTan(string &Funkcja, double X)
{
	//znalezienie wszystkich dzialan tanges oraz ich obliczenie
	size_t found = Funkcja.find("tan");
	while (found != string::npos)
	{
		//string liczba; //liczba po prawo
		long double wynik = 0;   //wynik operacji

		int beginOperation = found; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		digit liczba;

		int i = 2;

		liczba = readRight(found + i, Funkcja, endOperation);

		wynik = tan(liczba.isInteger ? liczba.Integer : liczba.Double);

		Funkcja.replace(beginOperation, endOperation - beginOperation, to_string(wynik));

		found = Funkcja.find("tan");
	}
}
void ParsPower(string &Funkcja, double X)
{
	//znalezienie wszystkich dzialan ^ oraz ich obliczenie
	size_t found = Funkcja.find_first_of("^", 1);
	while (found != string::npos)
	{
		long double wynik = 0;   //wynik operacji

		int beginOperation; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		digit liczba1;
		digit liczba2;

		int i = 1;

		liczba1 = readLeft(found - i, Funkcja, beginOperation);
		liczba2 = readRight(found + i, Funkcja, endOperation);

		wynik = pow((liczba1.isInteger ? liczba1.Integer : liczba1.Double), (liczba2.isInteger ? liczba2.Integer : liczba2.Double));

		Funkcja.replace(beginOperation, endOperation - beginOperation, to_string(wynik));

		found = Funkcja.find_first_of("^", 1);
	}
}
void ParsMD(string &Funkcja, double X)
{
	//znalezienie wszystkich dzialan * i / oraz ich obliczenie
	size_t found = Funkcja.find_first_of("*/", 1);
	while (found != string::npos)
	{
		long double wynik = 0;   //wynik operacji

		int beginOperation; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		digit liczba1;
		digit liczba2;

		int i = 1;

		liczba1 = readLeft(found - i, Funkcja, beginOperation);
		liczba2 = readRight(found + i, Funkcja, endOperation);

		switch (Funkcja[found])
		{
		case '*':
			wynik = (liczba1.isInteger ? liczba1.Integer : liczba1.Double) * (liczba2.isInteger ? liczba2.Integer : liczba2.Double);
			break;
		case '/':
			wynik = (liczba1.isInteger ? liczba1.Integer : liczba1.Double) / (liczba2.isInteger ? liczba2.Integer : liczba2.Double);
			break;
		}

		Funkcja.replace(beginOperation, endOperation - beginOperation, to_string(wynik));

		found = Funkcja.find_first_of("*/", 1);
	}
}
void ParsAS(string &Funkcja, double X)
{
	//znalezienie wszystkich dzialan + i - oraz ich obliczenie
	size_t found = Funkcja.find_first_of("+-", 1);
	while (found != string::npos)
	{
		long double wynik = 0;   //wynik operacji

		int beginOperation; //poczatek operacji (pierwsza cyfra lewej liczby w stringu)
		int endOperation;   //koniec operacji (ostatnia cyfra prawej liczby w stringu)
		///\/\ zostanie zastapione przez wynik /\/\

		digit liczba1;
		digit liczba2;

		int i = 1;

		liczba1 = readLeft(found - i, Funkcja, beginOperation);
		liczba2 = readRight(found + i, Funkcja, endOperation);

		switch (Funkcja[found])
		{
		case '+':
			wynik = (liczba1.isInteger ? liczba1.Integer : liczba1.Double) + (liczba2.isInteger ? liczba2.Integer : liczba2.Double);
			break;
		case '-':
			wynik = (liczba1.isInteger ? liczba1.Integer : liczba1.Double) - (liczba2.isInteger ? liczba2.Integer : liczba2.Double);
			break;
		}

		Funkcja.replace(beginOperation, endOperation - beginOperation, to_string(wynik));

		found = Funkcja.find_first_of("+-", 1);
	}
}

double horner(vector<double> wsp, double x)
{
	double wynik = wsp[wsp.size()-1];
	for (int i = wsp.size() - 2; i >= 0; i--)
		wynik = wynik*x + wsp[i];

	return wynik;
}
bool isHornerPoly(string Funkcja)
{
	bool returned = true;
	if (Funkcja.find("sin") != string::npos || Funkcja.find("cos") != string::npos || Funkcja.find("tan") != string::npos)	 //Jesli funkcja zawiera fun trygonometryczne
		return false;														 //nie jest wielomianem

	digit liczba;
	size_t find = Funkcja.find('^'); 
	int tmp;
	while (find != string::npos)
	{
		liczba = readRight(find + 1, Funkcja, tmp);
		if (!liczba.isInteger || liczba.Integer < 0)	//Jesli wykladnik potegi nie jest calkowity
			return false;								//wielomian nie nadaje sie do algorytmu horner'a

		find = Funkcja.find('^', find+1);
	}

	return returned;
}
vector<double> hornerPoly(string Funkcja)
{
	int trash;

	vector<double> tmp;
	int maxPotega = 0;
	size_t found = Funkcja.find('x'); 
	if (found != string::npos)		//jesli znaleziono 'x'
		maxPotega = 1;				//istnieje potega 1 stopnia

	found = Funkcja.find("x^");
	while (found != string::npos)	//szukanie najwyzszej potegi
	{
		maxPotega = (maxPotega < readRight(found + 2, Funkcja, trash).Integer) ? readRight(found + 2, Funkcja, trash).Integer : maxPotega; 
		found = Funkcja.find("x^", trash);
	}

	tmp.assign(maxPotega + 1, 0);	//utworzenie ilosci elementow rownych ilosci poteg, wypelnienie ich zerami

	for (int i = maxPotega; i > 0; i--)	//petla liczaca wspolczynniki przy potegach
	{
		string power;
		digit liczba;

		int trash_begin = 0;	//przechowuje poczatek lewego wspolczynnika
		int trash_end = 0;		//przechowuje koniec prawego wspolczynnika

		power = to_string(i);
		size_t tmp_found = Funkcja.find("x^" + power);	//szukanie aktualnej potegi
		
		if (tmp_found == string::npos && i == 1)	//jesli potegi nie ma, sprawdzenie czy nie jest rowna 1 (x^1 = x)
			tmp_found = Funkcja.find('x');

		while (tmp_found != string::npos)
		{
			digit tmp_liczba(1);
			trash_begin = tmp_found;

			if ((tmp_found != 0) && (Funkcja[tmp_found - 1] == '*'))	//obliczenie wspolczynnika po lewej stronie (jesli istnieje)
			{
				tmp_liczba *= readLeft(tmp_found - 2, Funkcja, trash_begin);	//odczytanie lewego wspolczynnika
				if (Funkcja[tmp_found - trash_begin - 1] == '-')	//jesli znak jest ujemny
					tmp_liczba.isInteger ? (tmp_liczba.Integer *= -1) : (tmp_liczba.Double *= -1);
			}

			if ((trash_begin != 0) && !isdigit(Funkcja[trash_begin - 1]))
				trash_begin--;

			liczba = readRight((Funkcja[tmp_found+1] == '^') ? (tmp_found + 2) : (tmp_found+1), Funkcja, trash_end);//odczytanie wspolczynnika z prawej strony
			if (trash_end + 1 != Funkcja.length() && Funkcja[trash_end + 1] == '*')
			{
				tmp_liczba *= readRight(trash_end + 2, Funkcja, trash_end);
			}

			tmp_found = Funkcja.find("x^" + power, tmp_found+2);	//szukanie aktualnej potegi

			if (tmp_found == string::npos && i == 1)	//jesli potegi nie ma, sprawdzenie czy nie jest rowna 1 (x^1 = x)
				tmp_found = Funkcja.find('x', tmp_found+1);

			if (tmp_liczba.isInteger && tmp_liczba.Integer == 1 && Funkcja[trash_begin] == '-')
				tmp_liczba.Integer *= -1;

			tmp[i] += (tmp_liczba.isInteger ? tmp_liczba.Integer : tmp_liczba.Double);
		}

		if (trash_begin != trash_end)
			Funkcja.erase(trash_begin, trash_end - trash_begin + 1);
		tmp_found = Funkcja.find("x^" + power);
	}

	if (!Funkcja.empty()) //jesli nie pusta, jej wynik to wartosc wspolczynnika dla x^0 
	{
		ParsMD(Funkcja, 1);
		ParsAS(Funkcja, 1);

		tmp[0] += stod(Funkcja);
	}
	
	return tmp;
}

digit readLeft(int found, string strFunkcji, int &beginOperation)
{
	digit tmp;
	string liczba;

	while (found >= 0 && (isdigit(strFunkcji[found]) ||
		strFunkcji[found] == '.' ||
		(strFunkcji[found] == '-' && (found - 1 < 0 || !isdigit(strFunkcji[found - 1])))))		//wczytywanie liczby do liczba1
	{
		if (strFunkcji[found] == '.')
			tmp.Double = 1.0;

		if ((isdigit(strFunkcji[found]) && strFunkcji[found] != '0') && tmp.Double == 1.0)
			tmp.isInteger = false;
		
		liczba.insert(liczba.begin(), strFunkcji[found]);
		found--;
	}
	beginOperation = found + 1; //zapisanie poczatku operacji
	
	tmp.isInteger ? tmp.Integer = stoi(liczba) : tmp.Double = stod(liczba);

	return tmp;
}
digit readRight(int found, string strFunkcji, int &endOperation)
{
	string liczba;
	digit tmp;
	while (found < strFunkcji.length() && (isdigit(strFunkcji[found]) || strFunkcji[found] == '.' || (liczba.empty() && strFunkcji[found] == '-')))
	{
		if (strFunkcji[found] == '.')
			tmp.Double = 1.0;

		if ((isdigit(strFunkcji[found]) && strFunkcji[found] != '0') && tmp.Double == 1.0)
			tmp.isInteger = false;

		liczba.insert(liczba.end(), strFunkcji[found]);
		found++;
	}
	endOperation = found - 1;

	tmp.isInteger ? (tmp.Integer = stoi(liczba)) : (tmp.Double = stod(liczba));

	return tmp;
}

long double wynikFunkcji(long double X, string funkcja)
{
	string strFunkcji(funkcja);		//kopia lancucha funkcji

	ParsComma(strFunkcji);
	ParsSpace(strFunkcji);
	ParsBracket(strFunkcji, X);

	if (isHornerPoly(strFunkcji))
	{
		vector<double> tmp;
		tmp = hornerPoly(strFunkcji);
		
		return horner(tmp, X);
	}

	ParsX(strFunkcji, X);

	ParsSin(strFunkcji, X);
	ParsCos(strFunkcji, X);
	ParsTan(strFunkcji, X);

	ParsPower(strFunkcji, X);
	ParsMD(strFunkcji, X);
	ParsAS(strFunkcji, X);

	long double rounded = stold(strFunkcji);
	if (abs(rounded - round(rounded)) < 0.0000009)
		rounded = round(rounded);

	return rounded;
}

