#include "funkcje.h"
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

//Funkcja interpolujaca i rysujaca wykres oraz uzupelniajace wektory
void interpoluj(double A, double B, int N);
void rysuj_wykres(double A, double B);
void uzupelnijWektorXY(double A, double B);
void uzupelnijWektorWielomianu(double A, double B, int N);
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

void interpoluj(double A, double B, int N)
{
	uzupelnijWektorWezlow(A, B, N - 1);
	//TODO
	//wyliczyc wspolczynniki b_i
	//znalezc sposob na obliczenie wartosci wielomianu interpolowanego
	uzupelnijWektorWielomianu(A, B, N);
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

void uzupelnijWektorWielomianu(double A, double B, int N)
{
	//TODO
}

void uzupelnijWektorWezlow(double A, double B, int N)
{
	for (int n = 1; n <= N + 1; n++)
	{
		/*WYKLADOWY WZOR 1/2((B-A)cos((2n+1)*PI/(2N+1))+A+B)
		//Pokazuje tylko pare wezlow
		double arg = (2 * n + 1) / (2 * N + 1);
		arg *= MAT_PI;
		double wynik = cos(arg);
		wynik *= (B - A);
		wynik += (A + B);
		wynik *= 0.5;*/

		//WZOR ZNALEZIONY NA http://www3.nd.edu/~jjwteach/441/PdfNotes/lecture8.pdf
		double arg = ((N + 1 + 0.5 - n) / (N + 1)) * MAT_PI;
		double wynik =cos(arg);
		wynik *= (B - A);
		wynik += A + B;
		wynik *= 0.5;
		xWezly.push_back(wynik);
		yWezly.push_back(funkcja(wynik));
	}
}