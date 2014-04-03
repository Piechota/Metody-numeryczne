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

void ParsX(string &Funkcja, double X)//Podmienia x
{
	size_t found = Funkcja.find('x');
	while (found != string::npos)
	{
		Funkcja.replace(found, 1, to_string(X));
		found = Funkcja.find('x');
	}
}

void ParsComma(string &Funkcja)//Zamienia przecinki na kropki
{
	size_t found = Funkcja.find(',');
	while (found != string::npos)
	{
		Funkcja.replace(found, 1, ".");
		found = Funkcja.find(',');
	}
}

void ParsSpace(string &Funkcja)//Usuwa spacje
{
	size_t found = Funkcja.find(' ');
	while (found != string::npos)
	{
		Funkcja.replace(found, 1, "");
		found = Funkcja.find(' ');
	}
}

void ParsBracket(string &Funkcja, double X)//Szuka nawiasow
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

void ParsSin(string &Funkcja, double X)//Oblicza sin'usa
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

void ParsCos(string &Funkcja, double X)//Oblicza cos'usa
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

void ParsTan(string &Funkcja, double X)//Oblicza tan'usa
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

void ParsPower(string &Funkcja, double X)//Oblicza potege
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

void ParsMD(string &Funkcja, double X)//Oblicza mnozenie i dzielenie
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

void ParsAS(string &Funkcja, double X)//Oblicza dodawanie i odejmowanie
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
	vector<double> tmp;

	int maxPower = 0;
	size_t tmp_found = 0;

	////////////				SZUKANIE NAJWIEKSZEJ POTEGI
	tmp_found = Funkcja.find('x');
	if (tmp_found == string::npos)
	{
		ParsMD(Funkcja, 1);
		ParsAS(Funkcja, 1);
		tmp.push_back(stod(Funkcja));
		return tmp;
	}

	maxPower = 1;

	tmp_found = Funkcja.find("x^");
	while (tmp_found != string::npos)
	{
		int trash;
		digit liczba = readRight(tmp_found + 2, Funkcja, trash);

		if (liczba.Integer > maxPower)
			maxPower = liczba.Integer;

		tmp_found = Funkcja.find("x^", tmp_found + 2);
	}

	tmp.assign(maxPower + 1, 0);
	////////////////////////////////////////////////////////////
	///////			Liczenie wspolczynnikow dla potegi > 0
	
	for (int i = maxPower; i > 0; i--)
	{
		string power = to_string(i);
		tmp_found = Funkcja.find("x^" + power);
		while (tmp_found != string::npos)
		{
			int tmp_begin = tmp_found;
			int tmp_end = tmp_found;
			digit liczba(1);

			//Szukanie z lewej
			if (tmp_found > 0 && Funkcja[tmp_found - 1] == '*')
				liczba *= readLeft(tmp_found - 2, Funkcja, tmp_begin);
			
			//Szukanie z prawej
			if (tmp_found < Funkcja.length() - 1)
			{
				readRight(tmp_found + 2, Funkcja, tmp_end);
				if (tmp_end < Funkcja.length() - 1 && Funkcja[tmp_end + 1] == '*')
					liczba *= readRight(tmp_end + 2, Funkcja, tmp_end);
			}

			if (tmp_begin > 0)
				tmp_begin--;
			if (tmp_found > 0 && Funkcja[tmp_found - 1] == '-')
				liczba.Integer *= -1;

			tmp[i] += liczba.Integer;

			Funkcja.erase(tmp_begin, tmp_end+1);

			tmp_found = Funkcja.find("x^" + power);
		}
	}

	//	Sprawdzane dla potegi = 1
	tmp_found = Funkcja.find('x');
	while (tmp_found != string::npos)
	{
		int tmp_begin = tmp_found;
		int tmp_end = tmp_found;
		digit liczba(1);

		//Szukanie z lewej
		if (tmp_found > 0 && Funkcja[tmp_found - 1] == '*')
			liczba *= readLeft(tmp_found - 1, Funkcja, tmp_begin);

		//Szukanie z prawej
		if (tmp_found < Funkcja.length() - 1)
		{
			if (Funkcja[tmp_found + 1] == '*')
				liczba *= readRight(tmp_found + 2, Funkcja, tmp_end);
		}

		if (tmp_begin > 0)
			tmp_begin--;
		if (Funkcja[tmp_found - 1] == '-')
			liczba.Integer *= -1;

		tmp[1] += liczba.Integer;

		Funkcja.erase(tmp_begin, tmp_end + 1);

		tmp_found = Funkcja.find('x');
	}

	//	Dla potegi = 0
	if (!Funkcja.empty())
	{
		ParsMD(Funkcja, 1);
		ParsAS(Funkcja, 1);
		tmp[0] = stod(Funkcja);
	}
	///////////////////////////////////////////////////////////

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