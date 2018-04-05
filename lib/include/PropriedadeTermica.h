#ifndef PROPRIEDADE_TEMICA_H
#define PROPRIEDADE_TEMICA_H

#include <vector>
#include <iostream>

using namespace std;

class PropriedadeTermica
{
	public:
		PropriedadeTermica(vector<double>kcadaMat,vector<int>NumerodePontosCadaMat);

		double getk(int P);
		void setkPolinomial(vector<vector<double> >kpolinomial);
		void setTemperaturas(vector<double> TemperaturasPorPonto);
	private:
		void setk(vector<double>kcadaMat, vector<int>NumerodePontosCadaMat);
		void CalculakPolinomial();

		vector<vector<double> >kpolinomial;

		vector<double>k;
		vector<double>TemperaturasPorPonto;

		int TotaldePontos;
		vector<int> NumerodePontos;

		bool TemperaturasPorPontoSalvo=0;
		bool kpolinomialSalvo=0;
};

#endif