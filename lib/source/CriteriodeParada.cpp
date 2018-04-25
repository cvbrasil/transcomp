#include "CriteriodeParada.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

CriteriodeParada::CriteriodeParada(int TipodeCriterio,double CriterioDeParada,vector<double>TemperaturasAtuais, vector<double>TemperaturasAnteriores)
{
	if(CriterioDeParada>0&&TemperaturasAtuais.size()==TemperaturasAnteriores.size())
	{
		if(TipodeCriterio==1)
		{
			maxDiferencaSimples(CriterioDeParada,TemperaturasAtuais,TemperaturasAnteriores);
		}
		else
		{
			if(TipodeCriterio==2)
			{
				maxDiferencaRelativa(CriterioDeParada,TemperaturasAtuais,TemperaturasAnteriores);
			}
			else
			{
				if(TipodeCriterio==3)
				{
					DiferencasQuadradasSobreNVC(CriterioDeParada,TemperaturasAtuais,TemperaturasAnteriores);
				}
				else
				{
					if(TipodeCriterio==4)
					{
						ModulodasDiferencasSobreNVC(CriterioDeParada,TemperaturasAtuais,TemperaturasAnteriores);
					}
					else
					{
						if(TipodeCriterio==5)
						{
							ModulodasDiferencasRelativas(CriterioDeParada,TemperaturasAtuais,TemperaturasAnteriores);
						}
						else
						{
							if(TipodeCriterio==6)
							{
								cout<<endl<<endl<<"Para Criterio com Residuos, setar matriz e vetores na funcao correspondente."<<endl<<endl;
							}
							else
							{
								cout<<endl<<endl<<"Problema! Tipo de criterio escolhido invalido! Escolha entre criterio 1 e 6."<<endl<<endl;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		cout<<endl<<endl<<"Problema! Vetores de TemperaturasAnteriores e TemperaturasAtuais com tamanhos diferentes!"<<endl<<endl;
	}
}
bool CriteriodeParada::getFlagDeCriterioAtingido()
{
	return(this->FlagDeCriterioAtingido);
}
void CriteriodeParada::maxDiferencaSimples(double CriterioDeParada,vector<double>TemperaturasAtuais, vector<double>TemperaturasAnteriores)
{
	double ErroMax;
	ErroMax = fabs(TemperaturasAtuais[0]-TemperaturasAnteriores[0]);
	for(int i = 1; i<TemperaturasAnteriores.size(); i++)
	{
		if(ErroMax<fabs(TemperaturasAtuais[i]-TemperaturasAnteriores[i]))
		{
			ErroMax = fabs(TemperaturasAtuais[i]-TemperaturasAnteriores[i]);
		}
	}
	if(CriterioDeParada>ErroMax)
	{
		this->FlagDeCriterioAtingido=true;
		this->ErroDeParada = ErroMax;
	}
}
void CriteriodeParada::maxDiferencaRelativa(double CriterioDeParada,vector<double>TemperaturasAtuais, vector<double>TemperaturasAnteriores)
{
	double ErroMax;
	double Tmax;
	double Tmin;
	Tmax = ProcuraTmax(TemperaturasAtuais);
	Tmin = ProcuraTmin(TemperaturasAtuais);
	ErroMax = fabs(TemperaturasAtuais[0]-TemperaturasAnteriores[0])/(Tmax-Tmin);
	for(int i = 1; i<TemperaturasAnteriores.size(); i++)
	{
		if(ErroMax<fabs(TemperaturasAtuais[i]-TemperaturasAnteriores[i])/(Tmax-Tmin))
		{
			ErroMax = fabs(TemperaturasAtuais[i]-TemperaturasAnteriores[i])/(Tmax-Tmin);
		}
	}
	if(CriterioDeParada>ErroMax)
	{
		this->FlagDeCriterioAtingido=true;
		this->ErroDeParada = ErroMax;
	}
}
void CriteriodeParada::DiferencasQuadradasSobreNVC(double CriterioDeParada,vector<double>TemperaturasAtuais, vector<double>TemperaturasAnteriores)
{
	double Erro;
	double SomaDiferencasdeTemperatura = 0;
	int NVC = TemperaturasAtuais.size();
	for(int i = 0; i<TemperaturasAnteriores.size(); i++)
	{
		SomaDiferencasdeTemperatura = SomaDiferencasdeTemperatura + pow(TemperaturasAtuais[i]-TemperaturasAnteriores[i],2);
	}
	Erro = pow(SomaDiferencasdeTemperatura/NVC,0.5);
	if(CriterioDeParada>Erro)
	{
		this->FlagDeCriterioAtingido=true;
		this->ErroDeParada = Erro;
	}
}
void CriteriodeParada::ModulodasDiferencasSobreNVC(double CriterioDeParada,vector<double>TemperaturasAtuais, vector<double>TemperaturasAnteriores)
{
	double Erro;
	double SomaDiferencasdeTemperatura = 0;
	int NVC = TemperaturasAtuais.size();
	for(int i = 0; i<TemperaturasAnteriores.size(); i++)
	{
		SomaDiferencasdeTemperatura = SomaDiferencasdeTemperatura + fabs(TemperaturasAtuais[i]-TemperaturasAnteriores[i]);
	}
	Erro = SomaDiferencasdeTemperatura/NVC;
	if(CriterioDeParada>Erro)
	{
		this->FlagDeCriterioAtingido=true;
		this->ErroDeParada = Erro;
	}
}
void CriteriodeParada::ModulodasDiferencasRelativas(double CriterioDeParada,vector<double>TemperaturasAtuais, vector<double>TemperaturasAnteriores)
{
	double Erro;
	double Tmax;
	double Tmin;
	double SomaDiferencasdeTemperatura = 0;
	int NVC = TemperaturasAtuais.size();
	Tmax = ProcuraTmax(TemperaturasAtuais);
	Tmin = ProcuraTmin(TemperaturasAtuais);
	for(int i = 0; i<TemperaturasAnteriores.size(); i++)
	{
		SomaDiferencasdeTemperatura = SomaDiferencasdeTemperatura + fabs(TemperaturasAtuais[i]-TemperaturasAnteriores[i])/(Tmax-Tmin);
	}
	Erro = SomaDiferencasdeTemperatura/NVC;
	if(CriterioDeParada>Erro)
	{
		this->FlagDeCriterioAtingido=true;
		this->ErroDeParada = Erro;
	}
}
void CriteriodeParada::ResiduosQuadrados()
{

}
bool CriteriodeParada::getFlagDeCriterioAtingidoOscilante(double TemperaturasAtuais, double TemperaturasAnteriores1, double TemperaturasAnteriores2)
{
	bool Flag=0;
	Flag = CriterioAtingidoOscilante(TemperaturasAtuais,TemperaturasAnteriores1,TemperaturasAnteriores2);
	return(Flag);
}
bool CriteriodeParada::CriterioAtingidoOscilante(double TemperaturasAtuais,double TemperaturasAnteriores1,double TemperaturasAnteriores2)
{
	bool Flag = 0;
	if(TemperaturasAtuais-TemperaturasAnteriores1>0 && TemperaturasAnteriores1-TemperaturasAnteriores2<0)
	{
		Flag = 1;
	}
	if(TemperaturasAtuais-TemperaturasAnteriores1<0 && TemperaturasAnteriores1-TemperaturasAnteriores2>0)
	{
		Flag = 1;
	}
	return(Flag);
}
double CriteriodeParada::ProcuraTmax(vector<double> TemperaturasAtuais)
{
	double Tmax = TemperaturasAtuais[0];
	for(int i=1; i<TemperaturasAtuais.size(); i++)
	{
		if(TemperaturasAtuais[i]>Tmax)
		{
			Tmax = TemperaturasAtuais[i];
		}
	}
	return(Tmax);
}
double CriteriodeParada::ProcuraTmin(vector<double> TemperaturasAtuais)
{
	double Tmin = TemperaturasAtuais[0];
	for(int i=1; i<TemperaturasAtuais.size(); i++)
	{
		if(TemperaturasAtuais[i]<Tmin)
		{
			Tmin = TemperaturasAtuais[i];
		}
	}
	return(Tmin);
}
double CriteriodeParada::getErro()
{
	return(this->ErroDeParada);
}