// zadanie2.cpp : main project file.

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#define PATH "matrix.txt"

using namespace std;

vector< vector<double> >	matrixA;
vector<double>				matrixB;
vector<double>				matrixX;

bool readMatrix(vector< vector<double> > &a_matrix, vector<double> &b_matrix, vector<double> &x_matrix)
{
	ifstream file(PATH);

	if (!file.is_open())
		return false;

	while (file.good())
	{
		string loop_string;
		double loop_double;
		vector<double> loop_vector;
		stringstream loop_line;

		getline(file, loop_string);
		loop_line.str(loop_string);
		while (loop_line.good())
		{
			loop_line >> loop_double;
			loop_vector.push_back(loop_double);
		}

		a_matrix.push_back(loop_vector);
	} 

	file.close();

	for (int i = 0; i < a_matrix.size(); i++)
	{
		b_matrix.push_back(a_matrix[i].back()); 
		a_matrix[i].pop_back();
	}

	x_matrix.assign(b_matrix.size(), 0);

	return true;
}
bool isRight(vector< vector<double> > &a_matrix, vector<double> &b_matrix, vector<double> &x_matrix, double round)
{
	double tmp;

	for (int i = 0; i < b_matrix.size(); i++)
	{
		tmp = 0;
		for (int j = 0; j < b_matrix.size(); j++)
		{
			tmp += a_matrix[i][j] * x_matrix[j];
		}
		if (abs(tmp - b_matrix[i]) > round)
			return false;
	}

	return true;
}
void jacobiMethod(vector< vector<double> > &a_matrix, vector<double> &b_matrix, vector<double> &x_matrix, int maxIteration, double round)
{
	vector<double> loop_x;
	loop_x.assign(x_matrix.size(), 0);

	for (int k = 0; k < maxIteration; k++)
	{
		for (int i = 0; i < a_matrix.size(); i++)
		{
			double sigma = b_matrix[i];
			for (int j = 0; j < a_matrix.size(); j++)
			{
				if (i != j)
					sigma -= a_matrix[i][j] * loop_x[j];
			}
			x_matrix[i] = sigma / ((a_matrix[i][i] != 0) ? (a_matrix[i][i]) : 1);
		}

		loop_x = x_matrix;
		if (isRight(a_matrix, b_matrix, x_matrix, round))
		{
			cout << "Rozwiazanie (+-" << round << ") znaleziono dla:\n";
			for (int i = 0; i < x_matrix.size(); i++)
				cout << 'x' << i + 1 << ": " << x_matrix[i] << endl;
			return;
		}
	}

	cout << "Koniec iteracji, obliczenia zatrzymaly sie na:\n";
	for (int i = 0; i < x_matrix.size(); i++)
		cout << 'x' << i + 1 << ": " << x_matrix[i] << endl;
}
bool jacobiTest(vector< vector<double> > &a_matrix, vector<double> &b_matrix)
{
	vector< vector<double> > tmp_matrix = a_matrix;
	for (int i = 0; i < b_matrix.size(); i++)
		tmp_matrix[i].push_back(b_matrix[i]);

	for (int i = 0; i < tmp_matrix.size(); i++)
	{
		for (int i2 = i + 1; i2 < tmp_matrix.size(); i2++)
		{
			double tmp = tmp_matrix[i][0] / tmp_matrix[i2][0];
			for (int k = 1; k < tmp_matrix[0].size(); k++)
			{
				if (k == tmp_matrix[0].size() - 1)
				{
					if (tmp_matrix[i][k] / tmp_matrix[i2][k] != tmp)
						cout << "Rownania sprzeczne!\n";
					else
						cout << "Rownania nieoznaczone!\n";

					return false;
				}

				if (tmp_matrix[i][k] / tmp_matrix[i2][k] != tmp)
					break;
			}
		}
	}

	return true;
}
int main(array<System::String ^> ^args)
{
	if (!readMatrix(matrixA, matrixB, matrixX))
	{
		cout << "Nie udalo sie otworzyc pliku!\n";
		system("pause");
		exit(1);
	}

	if (!jacobiTest(matrixA, matrixB))
	{
		system("pause");
		exit(2);
	}
	int i;
	double r;
	cout << "Podaj ilosc iteracji: ";
	cin >> i;
	cout << "Podaj przyblizenie: ";
	cin >> r;

	jacobiMethod(matrixA, matrixB, matrixX, i, r);

	system("pause");
    return 0;
}
