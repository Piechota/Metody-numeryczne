#include "gnuplotFunc.h"
#include "gnuplot_i.hpp"

void rysuj(vector<double> x, vector<double>* y, string tytul)
{
	if (!(Gnuplot::set_GNUPlotPath("E:/gnuplot/bin") || Gnuplot::set_GNUPlotPath("C:/gnuplot/bin")))
	{
		return;
	}

	Gnuplot* wykres = new Gnuplot;
	wykres->set_title(tytul);
	wykres->set_xlabel("t");
	wykres->set_ylabel("Y");
	wykres->set_style("lines");
	wykres->set_xrange(x[0], x[x.size() - 1]);
	//wykres->set_yrange(min - (max - min) / y.size(), max + (max - min) / y.size());

	wykres->plot_xy(x, y[0], "Funkcja alfa");
	wykres->plot_xy(x, y[1], "Funkcja omega");
	wykres->plot_xy(x, y[2], "Funkcja i");

	system("pause");
	delete wykres;
}