#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

#define M_PI 3.14159

using namespace std;

double wielomian(double x);
double liniowa(double x);
double modul(double x);
double trygonometryczna(double x);
double wieltryg(double x);
double wielmodul(double x);

//Funkcje pomocnicze do obliczania
double Horner(double x, double* wsp, int stopien);
double Horner(vector<double> tab, double x);
double potega(double x, int wykladnik);
double znajdzMin(vector<double> tab);
double znajdzMax(vector<double> tab);

//Aproksymacja
vector<vector<double>> wielomiany(int stopien);
vector<double> wezlyCzebyszewa(double A, double B, int iloscWezlow);
vector<double> mnozWielomiany(vector<double> wielomian1, vector<double> wielomian2);
vector<double> sumujWielomiany(vector<double> wielomian1, vector<double> wielomian2);
double calka(double A, double B, vector<double> wielomian, double(*fun)(double), double epsilon);
void wyznaczFunkcjeAproksymujaca(double A, double B, vector<double> &xApr, vector<double> &yApr,
								 vector<vector<double>> wielomiany, int stopien, double(*fun)(double));
void wyznaczWartosciFunkcji(double A, double B, vector<double> &x, vector<double> &y, double (*fun)(double));
double waga(double x);
double iloczynFunkcji(double(*fun)(double), vector<double> wielomian, double x);
double bladAproksymacji(vector<double> yFunkcji, vector<double> yApr);