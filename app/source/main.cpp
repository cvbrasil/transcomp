#include <vector>
#include <iostream>
#include <string>

#include "GerenteVolumedeControle.h"
#include "Malha.h"
#include "PropriedadeTermica.h"
#include "CondicoesdeContorno.h"
#include "SolverLinear.h"
#include "CriteriodeParada.h"

int main()
{
	vector<double> TemperaturasAtuais1;
	vector<double> TemperaturasAtuais2;
	vector<double> TemperaturasAnteriores;
	double criterio = 1;

	TemperaturasAtuais1.push_back(300);
	TemperaturasAtuais1.push_back(301);
	TemperaturasAtuais1.push_back(302);
	TemperaturasAtuais1.push_back(303);

	TemperaturasAtuais2.push_back(304.5);
	TemperaturasAtuais2.push_back(305.6);
	TemperaturasAtuais2.push_back(307.2);
	TemperaturasAtuais2.push_back(307.7);

	TemperaturasAnteriores.push_back(305);
	TemperaturasAnteriores.push_back(306);
	TemperaturasAnteriores.push_back(307);
	TemperaturasAnteriores.push_back(308);

	for(int i=1; i<=5; i++)
	{
		bool FlagCerto;
		bool FlagErrado;
		CriteriodeParada criterioTesteCerto(i,criterio,TemperaturasAtuais2, TemperaturasAnteriores);
		CriteriodeParada criterioTesteErrado(i,criterio,TemperaturasAtuais1, TemperaturasAnteriores);
		FlagCerto = criterioTesteCerto.getFlagDeCriterioAtingido();
		if(FlagCerto==true)
		{
			cout<<endl<<"FLAG CERTO DEU CERTO"<<endl<<endl;
		}
		else
		{
			cout<<endl<<"FLAG CERTO DEU ERRADO"<<endl<<endl;
		}
		FlagErrado = criterioTesteErrado.getFlagDeCriterioAtingido();
		if(FlagErrado==false)
		{
			cout<<endl<<"FLAG ERRADO DEU CERTO"<<endl<<endl;
		}
		else
		{
			cout<<endl<<"FLAG ERRADO DEU ERRADO"<<endl<<endl;
		}
	}
	return 0;
}