#include "CondicoesdeContorno.h"
#include <vector>
#include <iostream>

using namespace std;

CondicoesdeContorno::CondicoesdeContorno(vector<double>Pre1,vector<double>Pre2,vector<int>Tipos,int TipodeMalha,vector<double>aexterno,vector<double>ainterno)
{
	setCondicoesdeContorno(Pre1,Pre2,Tipos,TipodeMalha,aexterno,ainterno);
}
double CondicoesdeContorno::getPrimeiroTermodeEntrada()
{
	return(this->TermodeEntrada[0]);
}
double CondicoesdeContorno::getSegundoTermodeEntrada()
{
	return(this->TermodeEntrada[1]);
}
double CondicoesdeContorno::getTerceiroTermodeEntrada()
{
	return(this->TermodeEntrada[2]);
}
double CondicoesdeContorno::getPrimeiroTermodeSaida()
{
	return(this->TermodeSaida[0]);
}
double CondicoesdeContorno::getSegundoTermodeSaida()
{
	return(this->TermodeSaida[1]);
}
double CondicoesdeContorno::getTerceiroTermodeSaida()
{
	return(this->TermodeSaida[2]);
}
void CondicoesdeContorno::setCondicoesdeContorno(vector<double>Pre1,vector<double>Pre2,vector<int>Tipos,int TipodeMalha,vector<double>aexterno,vector<double>ainterno)
{
	if(Tipos.size()==2)
	{
		this->TermodeEntrada.resize(3);
		if(Tipos[0]==1&&Pre1.size()==1)
		{
			if(TipodeMalha == 1||TipodeMalha==3)
			{
				this->TermodeEntrada[0] = 1;
				this->TermodeEntrada[1] = 0;
				this->TermodeEntrada[2] = Pre1[0];
			}
			else
			{
				if(TipodeMalha == 2||TipodeMalha==4)
				{
					this->TermodeEntrada[0] = aexterno[0]+ainterno[0];
					this->TermodeEntrada[1] = -ainterno[0];
					this->TermodeEntrada[2] = Pre1[0]*aexterno[0];
				}
				else
				{
					cout<<endl<<"Problema! Tipo de Malha nao correspondente!"<<endl;
					this->TermodeEntrada[0] = 0;
					this->TermodeEntrada[1] = 0;
					this->TermodeEntrada[2] = 0;
				}
			}
		}
		else
		{
			if(Tipos[0]==2&&Pre1.size()==1)
			{
				if(TipodeMalha == 1||TipodeMalha==3)
				{
					this->TermodeEntrada[0] = ainterno[0];
					this->TermodeEntrada[1] = -ainterno[0];
					this->TermodeEntrada[2] = Pre1[0];
				}
				else
				{
					if(TipodeMalha == 2||TipodeMalha==4)
					{
						this->TermodeEntrada[0] = ainterno[0];
						this->TermodeEntrada[1] = -ainterno[0];
						this->TermodeEntrada[2] = Pre1[0];
					}
					else
					{
						cout<<endl<<"Problema! Tipo de Malha nao correspondente!"<<endl;
						this->TermodeEntrada[0] = 0;
						this->TermodeEntrada[1] = 0;
						this->TermodeEntrada[2] = 0;
					}
				}
			}
			else
			{
				if(Tipos[0]==3&&Pre1.size()==2)
				{
					if(TipodeMalha == 1||TipodeMalha==3)
					{
						this->TermodeEntrada[0] = ainterno[0]+Pre1[1];
						this->TermodeEntrada[1] = -ainterno[0];
						this->TermodeEntrada[2] = Pre1[0]*Pre1[1];
					}
					else
					{
						if(TipodeMalha == 2||TipodeMalha==4)
						{
							this->TermodeEntrada[0] = ainterno[0]+1/(1/Pre1[1]+1/aexterno[0]);
							this->TermodeEntrada[1] = -ainterno[0];
							this->TermodeEntrada[2] = Pre1[0]/(1/Pre1[1]+1/aexterno[0]);
						}
						else
						{
							this->TermodeEntrada[0] = 0;
							this->TermodeEntrada[1] = 0;
							this->TermodeEntrada[2] = 0;
							cout<<endl<<"Problema! Tipo de Malha nao correspondente!"<<endl;
						}
					}
				}
				else
				{
					cout<<endl<<"Problema! Codigo nao coerente na Prescricao1!"<<endl;
					this->TermodeEntrada[0] = 0;
					this->TermodeEntrada[1] = 0;
					this->TermodeEntrada[2] = 0;
				}
			}
		}
		this->TermodeSaida.resize(3);
		if(Tipos[1]==1&&Pre2.size()==1)
		{
			if(TipodeMalha == 1||TipodeMalha==4)
			{
				this->TermodeSaida[0] = 0;
				this->TermodeSaida[1] = 1;
				this->TermodeSaida[2] = Pre2[0];
			}
			else
			{
				if(TipodeMalha == 2||TipodeMalha==3)
				{
					this->TermodeSaida[0] = -ainterno[1];
					this->TermodeSaida[1] = aexterno[1]+ainterno[1];
					this->TermodeSaida[2] = Pre2[0]*aexterno[1];
				}
				else
				{
					this->TermodeSaida[0] = 0;
					this->TermodeSaida[1] = 0;
					this->TermodeSaida[2] = 0;
					cout<<endl<<"Problema! Tipo de Malha nao correspondente!"<<endl;
				}
			}
		}
		else
		{
			if(Tipos[1]==2&&Pre2.size()==1)
			{
				if(TipodeMalha == 1||TipodeMalha==4)
				{
					this->TermodeSaida[0] = -ainterno[1];
					this->TermodeSaida[1] = ainterno[1];
					this->TermodeSaida[2] = Pre2[0];
				}
				else
				{
					if(TipodeMalha == 2||TipodeMalha==3)
					{	
						this->TermodeSaida[0] = -ainterno[1];
						this->TermodeSaida[1] = ainterno[1];
						this->TermodeSaida[2] = Pre2[0];
					}
					else
					{
						this->TermodeSaida[0] = 0;
						this->TermodeSaida[1] = 0;
						this->TermodeSaida[2] = 0;
						cout<<endl<<"Problema! Tipo de Malha nao correspondente!"<<endl;
					}
				}
			}
			else
			{
				if(Tipos[1]==3&&Pre2.size()==2)
				{
					if(TipodeMalha == 1||TipodeMalha==4)
					{
						this->TermodeSaida[0] = -ainterno[1];
						this->TermodeSaida[1] = ainterno[1]+Pre2[1];
						this->TermodeSaida[2] = Pre2[0]*Pre2[1];
					}
					else
					{
						if(TipodeMalha == 2||TipodeMalha==3)
						{
							this->TermodeSaida[0] = -ainterno[1];
							this->TermodeSaida[1] = ainterno[1]+1/(1/Pre2[1]+1/aexterno[1]);
							this->TermodeSaida[2] = Pre2[0]/(1/Pre2[1]+1/aexterno[1]);
						}
						else
						{
							cout<<endl<<"Problema! Tipo de Malha nao correspondente!"<<endl;
							this->TermodeSaida[0] = 0;
							this->TermodeSaida[1] = 0;
							this->TermodeSaida[2] = 0;
						}
					}
				}
				else
				{
					cout<<endl<<"Problema! Codigo nao coerente na Prescricao2!"<<endl;
					this->TermodeSaida[0] = 0;
					this->TermodeSaida[1] = 0;
					this->TermodeSaida[2] = 0;
				}
			}
		}
	}
	else
	{
		cout<<endl<<"Problema! Nao ha dois tipos de Condicao de Contorno!"<<endl;
		this->TermodeSaida[0] = 0;
		this->TermodeSaida[1] = 0;
		this->TermodeSaida[2] = 0;
	}
}
