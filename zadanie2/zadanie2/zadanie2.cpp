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

double det(vector< vector<double> >	matrix)
{
	if (matrix.size() != matrix[0].size())
		return 0;

	if (matrix.size() == 1)
		return matrix[0][0];

	vector< vector<double> > tmp_matrix = matrix;
	double wynik = 0;

	for (int i = 0; i < matrix[0].size(); i++)
	{
		tmp_matrix.erase(tmp_matrix.begin());
		for (int j = 0; j < tmp_matrix.size(); j++)
			tmp_matrix[j].erase(tmp_matrix[j].begin() + i);
		wynik += ((i % 2) ? (-(matrix[0][i])) : (matrix[0][i])) * det(tmp_matrix);
		tmp_matrix = matrix;
	}
	return wynik;
}
bool readMatrix(vector< vector<double> > &a_matrix, vector<double> &b_matrix)
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
bool jacobiTest(vector< vector<double> > &a_matrix, vector<double> &b_matrix, vector<double> &x_matrix)
{
	vector< vector<double> > tmp_matrix = a_matrix;
	for (int i = 0; i < b_matrix.size(); i++)
		tmp_matrix[i].push_back(b_matrix[i]);

	for (int i = 0; i < tmp_matrix.size(); i++)		//szukanie wiersza z zerami
	{
		double sum = 0;
		for (int j = 0; j < tmp_matrix[i].size(); j++)
		{
			if (sum != 0)
				break;
			if (j == tmp_matrix[i].size() - 1 && tmp_matrix[i][j] != 0)
			{
				cout << "Uklad jest sprzeczny!\n";
				return false;
			}

			sum += tmp_matrix[i][j];
		}

		if (sum == 0)
		{
			tmp_matrix.erase(tmp_matrix.begin() + i);
			i--;
		}
	}

	// Szukanie powtorzonych (skalowanych) wierszy
	for (int i = 0; i < tmp_matrix.size(); i++)
	{
		for (int i2 = i + 1; i2 < tmp_matrix.size(); i2++)
		{
			double test = tmp_matrix[i][0] / tmp_matrix[i2][0];
			
			for (int j = 1; j < tmp_matrix[i].size(); j++)
			{
				if (j == tmp_matrix[i].size() - 1)
				{
					if (test != tmp_matrix[i][j] / tmp_matrix[i2][j])
					{
						cout << "Uklad sprzeczny\n";
						return false;
					}

					tmp_matrix.erase(tmp_matrix.begin() + i2);
					i2--;
				}

				if (test != tmp_matrix[i][j] / tmp_matrix[i2][j])
					break;
			}
		}
	}

	if (tmp_matrix.size() < tmp_matrix[0].size() - 1)
	{
		cout << "Uklad nieoznaczony!\n";
		return false;
	}

	a_matrix.clear();
	for (int i = 0; i < tmp_matrix.size(); i++)
	{
		vector<double> loop_vector;
		for (int j = 0; j < tmp_matrix[i].size()-1; j++)
			loop_vector.push_back(tmp_matrix[i][j]);

		a_matrix.push_back(loop_vector);
	}

	if (det(a_matrix) == 0)
	{
		cout << "Uklad sprzeczny!\n";
		return false;
	}

	b_matrix.clear();
	for (int i = 0; i < tmp_matrix.size(); i++)
		b_matrix.push_back(tmp_matrix[i].back());
		
	x_matrix.clear();
	x_matrix.assign(tmp_matrix[0].size() - 1, 0);

	return true;
}
bool isConvergence(vector< vector<double> > matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		double tmp = abs(matrix[i][i]);
		double sum = 0;

		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (j != i)
				sum += abs(matrix[i][j]);
		}

		if (sum > tmp)
			return false;
	}

	return true;
}
int main(array<System::String ^> ^args)
{
	if (!readMatrix(matrixA, matrixB))
	{
		cout << "Nie udalo sie otworzyc pliku!\n";
		system("pause");
		exit(1);
	}

	if (!jacobiTest(matrixA, matrixB, matrixX))
	{
		system("pause");
		exit(2);
	}

	if (!isConvergence(matrixA))
		cout << "Uklad nie jest zbiezny!\n";

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
