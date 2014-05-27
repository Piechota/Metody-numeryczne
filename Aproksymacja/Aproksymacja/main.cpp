#include <cstdlib>

#include "funkcjeMatematyczne.h"
#include "interfejs.h"
#include "gnuplot_i.hpp"

void rysuj(vector<double> x, vector<double> y, vector<double> xApr, vector<double> yApr, string tytul);

int main()
{
	vector<double> x;
	vector<double> y;
	vector<double> xApr;
	vector<double> yApr;
	komunikacja(x, y, xApr, yApr);
	rysuj(x, y, xApr, yApr, "Aproksymacja");
	return 0;
}

void rysuj(vector<double> x, vector<double> y, vector<double> xApr, vector<double> yApr, string tytul)
{
	if (!(Gnuplot::set_GNUPlotPath("E:/gnuplot/bin") || Gnuplot::set_GNUPlotPath("C:/gnuplot/bin")))
	{
		return;
	}

	Gnuplot* wykres = new Gnuplot;
	wykres->set_title(tytul);
	wykres->set_xlabel("X");
	wykres->set_ylabel("Y");
	wykres->set_style("lines");
	wykres->set_xrange(x[0], x[x.size() - 1]);
	double min = znajdzMin(y);
	double max = znajdzMax(y);
	wykres->set_yrange(min - (max - min) / y.size(), max + (max - min) / y.size());

	wykres->plot_xy(x, y, "Funkcja aproksymowana");
	wykres->plot_xy(xApr, yApr, "Funkcja aproksymujaca");

	system("pause");
	delete wykres;
}