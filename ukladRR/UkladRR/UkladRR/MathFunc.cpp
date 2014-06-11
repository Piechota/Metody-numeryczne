#include "MathFunc.h"

#define A 0
#define W 1
#define I 2

#pragma region STALE
double beta = 0.5;
double w_0		= 3.;
double a_max	= 1.;
double a_0		= 0.15*a_max;
double i_max	= 4.;
double R_0		= 100;
double E_m		= 220*sqrt(2.);
double w		= 100 * M_PI;
double L_0		= 100. / w;
double fi		= M_PI / 3.;
double c[] = {
	1. / 6.,
	0.17476028,
	-0.55148053,
	1.20553547,
	0.17118478
};

double alfa_0 = 1. / 2.;
double alfa_1 = 0.4;
double alfa_2 = (7. / 8.) - ((3./16.)*sqrt(5.));
double C1 = (a_max*(a_0 + a_max))*(i_max*i_max);

double t_p = 0.;
double t_k = 2.;
#pragma endregion STALE

/**
x - argument
wsp - tablica wspolczynnikow
stopien - stopien wielomianu
*/
long double Horner(double x, double* wsp, int stopien)
{
	long double wynik = wsp[0];
	for (int i = 1; i <= stopien; i++)
	{
		wynik *= x;
		wynik += wsp[i];
	}
	return wynik;
}

double funkcja_alfa(double t, double alfa, double omega, double i)
{
	if (!t)
		return 0.;
	return omega;
}
double funkcja_omega(double t, double alfa, double omega, double i)
{
	if (!t)
		return 0.;

	double x1 = -2.*beta*w_0*omega;
	double x2 = -1.*w_0*w_0*alfa;
	double x3 = C1*w_0*w_0*((i*i)/(a_0+alfa));
	return x1 + x2 + x3;
}
double funkcja_i(double t, double alfa, double omega, double i)
{
	if (!t)
		return 0.;

	double x0 = 1. / L_0;
	double x1 = -1.*R_0*i;
	double x2 = E_m*sin(w*t+fi);
	return x0*(x1+x2);
}

vector<double>* RK4()
{
	double h = (t_k - t_p) / n;

	double K_alfa[4];
	double K_omega[4];
	double K_i[4];

	double alfa_n = 0.;
	double omega_n = 0.;
	double i_n = 0.;

	vector<double>* Y = new vector<double>[3];

	for (double t_n = t_p; t_n <= t_k; t_n += h)
	{
		Y[A].push_back(alfa_n);
		Y[W].push_back(omega_n);
		Y[I].push_back(i_n);

		K_alfa[0]	= funkcja_alfa(t_n, alfa_n, omega_n, i_n);
		K_omega[0]	= funkcja_omega(t_n, alfa_n, omega_n, i_n);
		K_i[0]		= funkcja_i(t_n, alfa_n, omega_n, i_n);

		K_alfa[1]	= funkcja_alfa(	t_n + alfa_0*h, alfa_n + alfa_0*h*K_alfa[0], omega_n + alfa_0*h*K_omega[0], i_n + alfa_0*h*K_i[0]);
		K_omega[1]	= funkcja_omega(t_n + alfa_0*h, alfa_n + alfa_0*h*K_alfa[0], omega_n + alfa_0*h*K_omega[0], i_n + alfa_0*h*K_i[0]);
		K_i[1]		= funkcja_i(	t_n + alfa_0*h, alfa_n + alfa_0*h*K_alfa[0], omega_n + alfa_0*h*K_omega[0], i_n + alfa_0*h*K_i[0]);

		K_alfa[2]	= funkcja_alfa(	t_n + alfa_0*h, alfa_n + alfa_0*h*K_alfa[1], omega_n + alfa_0*h*K_omega[1], i_n + alfa_0*h*K_i[1]);
		K_omega[2]	= funkcja_omega(t_n + alfa_0*h, alfa_n + alfa_0*h*K_alfa[1], omega_n + alfa_0*h*K_omega[1], i_n + alfa_0*h*K_i[1]);
		K_i[2]		= funkcja_i(	t_n + alfa_0*h, alfa_n + alfa_0*h*K_alfa[1], omega_n + alfa_0*h*K_omega[1], i_n + alfa_0*h*K_i[1]);

		K_alfa[3]	= funkcja_alfa(	t_n + h, alfa_n + h*K_alfa[2], omega_n + h*K_omega[2], i_n + h*K_i[2]);
		K_omega[3]	= funkcja_omega(t_n + h, alfa_n + h*K_alfa[2], omega_n + h*K_omega[2], i_n + h*K_i[2]);
		K_i[3]		= funkcja_i(	t_n + h, alfa_n + h*K_alfa[2], omega_n + h*K_omega[2], i_n + h*K_i[2]);

		alfa_n	+= c[0] * h*(K_alfa[0]	+ 2 * K_alfa[1]		+ 2 * K_alfa[2]		+ K_alfa[3]);
		omega_n += c[0] * h*(K_omega[0] + 2 * K_omega[1]	+ 2 * K_omega[2]	+ K_omega[3]);
		i_n		+= c[0] * h*(K_i[0]		+ 2 * K_i[1]		+ 2 * K_i[2]		+ K_i[3]);
	}
	return Y;
}

vector<double>* RK4_Ralston()
{
	double h = (t_k - t_p) / n;

	double K_alfa[4];
	double K_omega[4];
	double K_i[4];

	double alfa_n = 0.;
	double omega_n = 0.;
	double i_n = 0.;

	vector<double>* Y = new vector<double>[3];

	for (double t_n = t_p; t_n <= t_k; t_n += h)
	{
		Y[A].push_back(alfa_n);
		Y[W].push_back(omega_n);
		Y[I].push_back(i_n);

		K_alfa[0]	= funkcja_alfa(	t_n, alfa_n, omega_n, i_n);
		K_omega[0]	= funkcja_omega(t_n, alfa_n, omega_n, i_n);
		K_i[0]		= funkcja_i(	t_n, alfa_n, omega_n, i_n);

		K_alfa[1]	= funkcja_alfa(	t_n + 0.4*h, alfa_n + 0.4*h*K_alfa[0], omega_n + 0.4*h*K_omega[0], i_n + 0.4*h*K_i[0]);
		K_omega[1]	= funkcja_omega(t_n + 0.4*h, alfa_n + 0.4*h*K_alfa[0], omega_n + 0.4*h*K_omega[0], i_n + 0.4*h*K_i[0]);
		K_i[1]		= funkcja_i(	t_n + 0.4*h, alfa_n + 0.4*h*K_alfa[0], omega_n + 0.4*h*K_omega[0], i_n + 0.4*h*K_i[0]);


		K_alfa[2]	= funkcja_alfa(	t_n + 0.45573726*h,
									alfa_n + 0.2969776*h*K_alfa[0] + 0.15875966*h*K_alfa[1],
									omega_n + 0.2969776*h*K_omega[0] + 0.15875966*h*K_omega[1],
									i_n + 0.2969776*h*K_i[0] + 0.15875966*h*K_i[1]);

		K_omega[2]	= funkcja_omega(t_n + 0.45573726*h,
									alfa_n + 0.2969776*h*K_alfa[0] + 0.15875966*h*K_alfa[1],
									omega_n + 0.2969776*h*K_omega[0] + 0.15875966*h*K_omega[1],
									i_n + 0.2969776*h*K_i[0] + 0.15875966*h*K_i[1]);

		K_i[2]		= funkcja_i(	t_n + 0.45573726*h,
									alfa_n + 0.2969776*h*K_alfa[0] + 0.15875966*h*K_alfa[1],
									omega_n + 0.2969776*h*K_omega[0] + 0.15875966*h*K_omega[1],
									i_n + 0.2969776*h*K_i[0] + 0.15875966*h*K_i[1]);



		K_alfa[3]	= funkcja_alfa(	t_n + h, 
									alfa_n + 0.21810038*h*K_alfa[0] - 3.0509647*h*K_alfa[1] + 3.83286432*h*K_alfa[2], 
									omega_n + 0.21810038*h*K_omega[0] - 3.0509647*h*K_omega[1] + 3.83286432*h*K_omega[2],
									i_n + 0.21810038*h*K_i[0] - 3.0509647*h*K_i[1] + 3.83286432*h*K_i[2]);

		K_omega[3]	= funkcja_omega(t_n + h,
									alfa_n + 0.21810038*h*K_alfa[0] - 3.0509647*h*K_alfa[1] + 3.83286432*h*K_alfa[2],
									omega_n + 0.21810038*h*K_omega[0] - 3.0509647*h*K_omega[1] + 3.83286432*h*K_omega[2],
									i_n + 0.21810038*h*K_i[0] - 3.0509647*h*K_i[1] + 3.83286432*h*K_i[2]);

		K_i[3]		= funkcja_i(	t_n + h,
									alfa_n + 0.21810038*h*K_alfa[0] - 3.0509647*h*K_alfa[1] + 3.83286432*h*K_alfa[2],
									omega_n + 0.21810038*h*K_omega[0] - 3.0509647*h*K_omega[1] + 3.83286432*h*K_omega[2],
									i_n + 0.21810038*h*K_i[0] - 3.0509647*h*K_i[1] + 3.83286432*h*K_i[2]);

		alfa_n	+= h*(0.17476028*K_alfa[0]	- 0.55148053 * K_alfa[1]	+ 1.20553547 * K_alfa[2]	+ 0.17118478 * K_alfa[3]);
		omega_n += h*(0.17476028*K_omega[0] - 0.55148053 * K_omega[1]	+ 1.20553547 * K_omega[2]	+ 0.17118478 * K_omega[3]);
		i_n		+= h*(0.17476028*K_i[0]		- 0.55148053 * K_i[1]		+ 1.20553547 * K_i[2]		+ 0.17118478 * K_i[3]);
	}
	return Y;
}

vector<double> podajX()
{
	double h = (t_k - t_p) / n;

	vector<double> X;
	for (double t_n = t_p; t_n <= t_k; t_n += h)
		X.push_back(t_n);

	return X;
}