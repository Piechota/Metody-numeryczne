#include "funkcje.h"
#include "gnuplot_i.hpp"

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
	/*bool flag = false;
	double A;
	double B;
	int wyborFunkcji;
	int N;

	while (!flag)
	{
		system("cls");
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

		try
		{
			flag = true;
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
				throw string("Nie znam takiej komendy");
				break;
			}
		}
		catch (string co)
		{
			cin.clear();
			cin.sync();
			flag = false;
			cout << co << endl;
			system("pause");
		}
	}

	flag = false;
	while (!flag)
	{
		try
		{
			flag = true;
			system("cls");
			cout << "Podaj przedzial interpolacji: " << endl
				<< "A: ";
			cin >> A;
			cout << "B: ";
			cin >> B;
			if (abs(A) == abs(B))
			{
				throw string("Srodek przedzialu wystepuje w punkcie 0");
			}
			else if (A > B)
			{
				throw string("Lewy kraniec przedzialu nie moze byc wiekszy od prawego kranca");
			}
		}
		catch (string what)
		{
			cin.clear();
			cin.sync();
			flag = false;
			cout << what << endl;
			system("pause");
		}
	}

	flag = false;
	while (!flag)
	{
		try
		{
			flag = true;
			system("cls");
			cout << "Podaj liczbe wezlow interpolacji: " << endl;
			cin >> N;
			if (N<=0)
			{
				throw string("Liczba wezlow nie moze byc mniejsza od 0 ;)");
			}
		}
		catch (string what)
		{
			cin.clear();
			cin.sync();
			flag = false;
			cout << what << endl;
			system("pause");
		}
	}
	
	interpoluj(A, B, N);
	uzupelnijWektorXY(A, B);
	rysuj_wykres(A, B);*/
uzupelnijWektorWielomianu(-10, 10, 10);
	return 0;
}

void interpoluj(double A, double B, int N)
{
	uzupelnijWektorWezlow(A, B, N - 1);
	uzupelnijWektorWielomianu(A, B, N);
}

void rysuj_wykres(double A, double B)
{
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

		if (x.empty() || y.empty() || xInterpolowane.empty() || yInterpolowane.empty() || xWezly.empty() || yWezly.empty())
		{
			string txt = "Jeden z wektorow jest pusty, nie uzupelniono ich\n";
			throw txt;
		}
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
	catch (string ex)
	{
		cout << ex;
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
	double ** tmp = new double*[N+1];
	for (int i = 0; i < N+1; i++)
	{
		tmp[i] = new double[N];
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N + 1; j++)
		{
			tmp[i][j] = 0;
		}
	}

	for (int i = 0; i < N + 1; i++)
	{
		delete[] tmp[i];
	}
	delete[] tmp;
}

void uzupelnijWektorWezlow(double A, double B, int N)
{
	for (int n = 0; n <= N; n++)
	{
		double xWezla;
		double arg = (2 * n + 1) / (2 * N + 1);
		arg *= MAT_PI;
		xWezla = cos(arg);
		xWezla *= (B - A);
		xWezla += (A + B);
		xWezla *= 0.5;
		xWezly.push_back(xWezla);
		yWezly.push_back(funkcja(xWezla));
	}
}