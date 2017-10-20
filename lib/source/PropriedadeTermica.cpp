#include "PropriedadeTermica.h"
#include <vector>
#include <iostream>

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
		cout<<endl<<"Problema! Posicao"<< position <<"nao existe!"<<endl<<endl;
		return(0);
	}
}
void PropriedadeTermica::setk(vector<double>kcadaMat,vector<int>NumerodePontos)
{
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
	}
	else
	{
		cout<<endl<<"Problema encontrado! Vetores de k e de pontos com tamanhos diferentes!"<<endl<<endl;
	}
}