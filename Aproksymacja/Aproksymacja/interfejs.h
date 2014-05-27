#include <iostream>
#include <string>
#include <vector>

using namespace std;

void komunikacja(vector<double> &x, vector<double> &y, vector<double> &xApr, vector<double> &yApr);
int wybierzFunkcje();

double liczWartoscFunkcji(double (*fun)(double), double x);
double podaj(string co);

void szukajStopnia(double lewyKraniec, double prawyKraniec, double(*fun)(double), vector<double> &x, vector<double> &y, vector<double> &xApr, vector<double> &yApr);