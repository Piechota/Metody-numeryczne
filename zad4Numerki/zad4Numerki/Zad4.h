long double Horner(double x, double* wsp, int stopien);
double czebyszew(double A, double B, double i, double N);
double d(double a, double b);
double waga(double x);
double wielomian(double x);
double trygono(double x);
double wykladnicze(double x);
double stala(double x);

double simpson();
double GaussaCzebyszewa(int t);

extern double(*funkcja)(double x);
extern double A;
extern double B ;
extern double epsilon;
extern long int Iteration;

double f(double x);
