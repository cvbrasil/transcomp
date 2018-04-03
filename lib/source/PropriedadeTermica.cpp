#include "PropriedadeTermica.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PropriedadeTermica::PropriedadeTermica(vector<double>kcadaMat,vector<int>NumerodePontos)
{
	setk(kcadaMat,NumerodePontos);
}
double PropriedadeTermica::getk(int position)
{
	if(position>=0&&position<this->k.size())
	{
		return(this->k[position]);
	}
	else
	{
		cout<<endl<<"Problema! Posicao "<< position <<" nao existe!"<<endl<<endl;
		return(0);
	}
}
void PropriedadeTermica::setk(vector<double>kcadaMat,vector<int>NumerodePontos)
{
	this->NumerodePontos=NumerodePontos;
	if(kcadaMat.size()==NumerodePontos.size())
	{
		int cont = 0;
		for(int i=0; i<NumerodePontos.size(); i++)
		{
			for(int j=0; j<NumerodePontos[i]; j++)
			{
				this->k.push_back(kcadaMat[i]);
				cont++;
			}
		}
		this->TotaldePontos=cont;
	}
	else
	{
		cout<<endl<<"Problema encontrado! Vetores de k e de pontos com tamanhos diferentes! Para polinomio, use as funcoes set correspondentes."<<endl<<endl;
		int cont = 0;
		for(int i=0; i<NumerodePontos.size(); i++)
		{
			for(int j=0; j<NumerodePontos[i]; j++)
			{
				cont++;
			}
		}
		this->TotaldePontos=cont;
	}
}
void PropriedadeTermica::setkPolinomial(vector<vector<double> >kpolinomial)
{
	if(kpolinomial.size()==this->NumerodePontos.size())
	{
		this->kpolinomial=kpolinomial;
		if(this->TemperaturasPorPontoSalvo==1)
		{
			CalculakPolinomial();
		}
		this->kpolinomialSalvo=1;
	}	
	else
	{
		cout<<endl<<"Problema encontrado! Matriz de k e vetor de pontos com tamanhos diferentes!"<<endl<<endl;
	}
}
void PropriedadeTermica::setTemperaturas(vector<double> TemperaturasPorPonto)
{
	if(TemperaturasPorPonto.size()==this->TotaldePontos)
	{
		this->TemperaturasPorPonto=TemperaturasPorPonto;
		if(this->kpolinomialSalvo==1)
		{
			CalculakPolinomial();
		}
		this->TemperaturasPorPontoSalvo=1;
	}
	else
	{
		cout<<endl<<"Problema encontrado! Quantidade de temperaturas e numero de pontos com tamanhos diferentes!"<<endl<<endl;
	}
}
void PropriedadeTermica::CalculakPolinomial()
{
	vector<double> k;
	int cont=0;

	k.resize(this->TotaldePontos);
	for(int i=0;i<this->NumerodePontos.size();i++)
	{
		for(int j=0;j<this->NumerodePontos[i];j++)
		{
			k[cont]=0;
			for(int w=0;w<this->kpolinomial[i].size();w++)
			{
				k[cont]=k[cont]+pow(this->TemperaturasPorPonto[cont],w)*kpolinomial[i][w];
			}
			cout<<endl<<endl<<"k["<<cont<<"]="<<k[cont]<<endl<<endl;
			cont++;
		}
	}
	this->k=k;
}