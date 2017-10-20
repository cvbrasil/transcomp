#include <vector>
#include <iostream>
#include "Malha.h"

using namespace std;

Malha::Malha(vector<int>NumerodePontos,vector<double>LarguraporMaterial,int NumerodeMalhas,int TipodeMalha)
{
	setVariaveisdeMalha(NumerodePontos,LarguraporMaterial,NumerodeMalhas,TipodeMalha);
}
double Malha::getDistanciadaOrigemPosicional(int Position)
{
	return(this->DistanciadaOrigem[Position]);
}
double Malha::getLarguraTotal()
{
	return(this->LarguraTotal);
}
double Malha::getdelta_w(int position)
{
	if(position <= 0|| position>this->DistanciadaOrigem.size())
	{
		cout<<endl<<"Erro! Posição"<< position <<" não possui delta_w."<<endl<<endl;
		return(0);
	}
	else
	{
		double delta_w;
		delta_w = this->DistanciadaOrigem[position] - this->DistanciadaOrigem[position-1];
		return (delta_w);
	}
}
double Malha::getdelta_e(int position)
{
	if(position >= this->DistanciadaOrigem.size()-1 || position<0)
	{
		cout<<endl<<"Erro! Posição"<< position <<" não possui delta_e."<<endl<<endl;
		return(0);
	}
	else
	{
		double delta_e;
		delta_e = this->DistanciadaOrigem[position+1] - this->DistanciadaOrigem[position];
		return (delta_e);
	}
}
double Malha::getDelta_e_Mais(int position)
{
	if(position >= this->DistanciadaOrigem.size()-1 || position<0)
	{
		cout<<endl<<"Erro! Posição"<< position <<" não possui delta_e."<<endl<<endl;
		return(0);
	}
	else
	{
		double delta_e_Mais;
		int DefineMatPtoP=0;
		int DefineMatPtoE=0;
		for(int i=0;i<(this->DistanciadaOrigemMaterial.size());i++)
		{
			if(this->DistanciadaOrigem[position]>this->DistanciadaOrigemMaterial[i])
			{
				DefineMatPtoP = i+1;
			}
			if(this->DistanciadaOrigem[position+1]>this->DistanciadaOrigemMaterial[i])
			{
				DefineMatPtoE = i+1;
			}
		}
		if(DefineMatPtoE==DefineMatPtoP)
		{
			delta_e_Mais = (this->DistanciadaOrigem[position+1] - this->DistanciadaOrigem[position])/2;
		}
		else
		{
			delta_e_Mais = (this->DistanciadaOrigem[position+1]-this->DistanciadaOrigemMaterial[DefineMatPtoE-1]);
		}
		return (delta_e_Mais);
	}
}
double Malha::getDelta_e_Menos(int position)
{
	if(position >= this->DistanciadaOrigem.size()-1 || position<0)
	{
		cout<<endl<<"Erro! Posição"<< position <<" não possui delta_e."<<endl<<endl;
		return(0);
	}
	else
	{
		double delta_e_Menos;
		int DefineMatPtoP=0;
		int DefineMatPtoE=0;
		for(int i=0;i<(this->DistanciadaOrigemMaterial.size());i++)
		{
			if(this->DistanciadaOrigem[position]>this->DistanciadaOrigemMaterial[i])
			{
				DefineMatPtoP = i+1;
			}
			if(this->DistanciadaOrigem[position+1]>this->DistanciadaOrigemMaterial[i])
			{
				DefineMatPtoE = i+1;
			}
		}
		if(DefineMatPtoE==DefineMatPtoP)
		{
			delta_e_Menos = (this->DistanciadaOrigem[position+1] - this->DistanciadaOrigem[position])/2;
		}
		else
		{
			delta_e_Menos = (this->DistanciadaOrigemMaterial[DefineMatPtoE-1]-this->DistanciadaOrigem[position]);
		}
		return (delta_e_Menos);
	}
}
double Malha::getDelta_w_Mais(int position)
{
	if(position <= 0|| position>this->DistanciadaOrigem.size())
	{
		cout<<endl<<"Erro! Posição"<< position <<" não possui delta_w."<<endl<<endl;
		return(0);
	}
	else
	{
		double delta_w_Mais;
		int DefineMatPtoP=0;
		int DefineMatPtoW=0;
		for(int i=0;i<(this->DistanciadaOrigemMaterial.size());i++)
		{
			if(this->DistanciadaOrigem[position]>this->DistanciadaOrigemMaterial[i])
			{
				DefineMatPtoP = i+1;
			}
			if(this->DistanciadaOrigem[position-1]>this->DistanciadaOrigemMaterial[i])
			{
				DefineMatPtoW = i+1;
			}
		}
		if(DefineMatPtoP==DefineMatPtoW)
		{
			delta_w_Mais = (this->DistanciadaOrigem[position]-this->DistanciadaOrigem[position-1])/2;
		}
		else
		{
			delta_w_Mais = this->DistanciadaOrigem[position] - this->DistanciadaOrigemMaterial[DefineMatPtoP-1];
		}
		return (delta_w_Mais);
	}
}
double Malha::getDelta_w_Menos(int position)
{
	if(position <= 0|| position>this->DistanciadaOrigem.size())
	{
		cout<<endl<<"Erro! Posição"<< position <<" não possui delta_w."<<endl<<endl;
		return(0);
	}
	else
	{
		double delta_w_Menos;
		int DefineMatPtoP=0;
		int DefineMatPtoW=0;
		for(int i=0;i<(this->DistanciadaOrigemMaterial.size());i++)
		{
			if(this->DistanciadaOrigem[position]>this->DistanciadaOrigemMaterial[i])
			{
				DefineMatPtoP = i+1;
			}
			if(this->DistanciadaOrigem[position-1]>this->DistanciadaOrigemMaterial[i])
			{
				DefineMatPtoW = i+1;
			}
		}
		if(DefineMatPtoP==DefineMatPtoW)
		{
			delta_w_Menos = (this->DistanciadaOrigem[position]-this->DistanciadaOrigem[position-1])/2;
		}
		else
		{
			delta_w_Menos = this->DistanciadaOrigemMaterial[DefineMatPtoP-1] - this->DistanciadaOrigem[position-1];
		}
		return (delta_w_Menos);
	}
}
int Malha::getTipodeMalha()
{
	return(this->TipodeMalha);
}
vector<double> Malha::getDistanciadaOrigem()
{
	return(this->DistanciadaOrigem);
}
void Malha::setVariaveisdeMalha(vector<int>NumerodePontos,vector<double>LarguraporMaterial,int NumerodeMalhas,int TipodeMalha)
{
	if(NumerodePontos.size()==NumerodeMalhas)
	{
		if(LarguraporMaterial.size()==NumerodeMalhas)
		{
			vector<double> DeltaBase;
			vector<double> DeltasTransferencia;
			int PontosTotais = 0;
			int cont = 0;
			double DeltaInicial;

			DeltaBase = DefineDeltaBase(NumerodePontos,LarguraporMaterial,NumerodeMalhas,TipodeMalha);
			DeltaInicial = DefineDeltaBaseInicial(TipodeMalha,DeltaBase[0]);
			DeltasTransferencia = DefineDeltasdeTransferencia(DeltaBase[0],DeltaBase[NumerodeMalhas-1],TipodeMalha);

			this->TipodeMalha = TipodeMalha;

			this->DistanciadaOrigemMaterial.resize(NumerodeMalhas);

			for(int i=0;i<NumerodeMalhas;i++)
			{
				PontosTotais = PontosTotais + NumerodePontos[i];
			}
			this->DistanciadaOrigem.resize(PontosTotais);
			
			if(NumerodeMalhas==1)
			{
				this->DistanciadaOrigemMaterial[0]=LarguraporMaterial[0];
				this->LarguraTotal = LarguraporMaterial[0];
				for(int j=0;j<NumerodePontos[0];j++)
				{
					if(j==0)
					{
						this->DistanciadaOrigem[0] = DeltaInicial;
					}
					else
					{
						this->DistanciadaOrigem[cont] = this->DistanciadaOrigem[cont-1]+DeltaBase[0];
					}
					cont++;
				}
			}
			else
			{
				double acumulaLarguras = 0;
				for(int i=0;i<NumerodeMalhas;i++)
				{
					for(int j=0;j<NumerodePontos[i];j++)
					{
						if(j==0)
						{
							if(i==0)
							{
								this->DistanciadaOrigem[0] = DeltaInicial;
							}
							else
							{
								if(i==NumerodeMalhas-1)
								{
									this->DistanciadaOrigem[cont] = acumulaLarguras + DeltasTransferencia[1];
								}
								else
								{
									this->DistanciadaOrigem[cont] = acumulaLarguras + DeltaBase[i]/2;
								}
							}
						}
						else
						{
							if(j==NumerodePontos[i]-1)
							{
								if(i==0)
								{
									this->DistanciadaOrigem[cont] = this->DistanciadaOrigem[cont-1] + DeltasTransferencia[0];
								}
								else
								{
									this->DistanciadaOrigem[cont] = this->DistanciadaOrigem[cont-1] + DeltaBase[i];
								}
							}
							else
							{
								if(j==1)
								{
									if(i==NumerodeMalhas-1)
									{
										this->DistanciadaOrigem[cont] = this->DistanciadaOrigem[cont-1] + DeltasTransferencia[2];
									}
									else
									{
										this->DistanciadaOrigem[cont] = this->DistanciadaOrigem[cont-1] + DeltaBase[i];
									}
								}
								else
								{
									this->DistanciadaOrigem[cont] = this->DistanciadaOrigem[cont-1] + DeltaBase[i];
								}
							}
						}
						cont++;
					}
					this->DistanciadaOrigemMaterial[i] = acumulaLarguras;
					acumulaLarguras = acumulaLarguras + LarguraporMaterial[i];
				}
				this->LarguraTotal = acumulaLarguras;
			}
		}
		else
		{
			cout<<endl<<"PROBLEMA DETECTADO! Largura por Material != Numero de Malhas."<<endl<<endl;
		}
	}
	else
	{
		cout<<endl<<"PROBLEMA DETECTADO! Numero de pontos por malha ou Largura por Material != Numero de Malhas."<<endl<<endl;
	}
}

vector<double> Malha::DefineDeltaBase(vector<int>NumerodePontos,vector<double>LarguraporMaterial,int NumerodeMalhas,int TipodeMalha)
{
	vector<double> DeltaBase;
	DeltaBase.resize(NumerodeMalhas);
	//++++++++++++++++++++++++++TIPO1++++++++++++++++++++++++++++++++++++++++++++
	if(TipodeMalha==1)
	{
		DeltaBase[0] = LarguraporMaterial[0]/(NumerodePontos[0]-1);
		for(int i=1;i<NumerodeMalhas-1;i++)
		{
			DeltaBase[i] = LarguraporMaterial[i]/NumerodePontos[i];
		}
		DeltaBase[NumerodeMalhas-1] = LarguraporMaterial[NumerodeMalhas-1]/(NumerodePontos[NumerodeMalhas-1]-1);
	}
	//++++++++++++++++++++++++++TIPO2++++++++++++++++++++++++++++++++++++++++++++
	if(TipodeMalha==2)
	{
		for(int i=0;i<NumerodeMalhas;i++)
		{
			DeltaBase[i] = LarguraporMaterial[i]/NumerodePontos[i];
		}
	}
	//++++++++++++++++++++++++++TIPO3++++++++++++++++++++++++++++++++++++++++++++
	if(TipodeMalha==3)
	{
		DeltaBase[0] = LarguraporMaterial[0]/(NumerodePontos[0]-0.5);
		for(int i=1;i<NumerodeMalhas-1;i++)
		{
			DeltaBase[i] = LarguraporMaterial[i]/NumerodePontos[i];
		}
		DeltaBase[NumerodeMalhas-1] = LarguraporMaterial[NumerodeMalhas-1]/(NumerodePontos[NumerodeMalhas-1]-0.5);
	}
	//++++++++++++++++++++++++++TIPO4++++++++++++++++++++++++++++++++++++++++++++
	if(TipodeMalha==4)
	{
		DeltaBase[0] = LarguraporMaterial[0]/(NumerodePontos[0]-0.5);
		for(int i=1;i<NumerodeMalhas-1;i++)
		{
			DeltaBase[i] = LarguraporMaterial[i]/NumerodePontos[i];
		}
		DeltaBase[NumerodeMalhas-1] = LarguraporMaterial[NumerodeMalhas-1]/(NumerodePontos[NumerodeMalhas-1]-0.5);
	}
	return(DeltaBase);
}
double Malha::DefineDeltaBaseInicial(int TipodeMalha,double DeltaBaseMaterial1)
{
	double DeltaInicial;
	//++++++++++++++++++++++++++TIPO1++++++++++++++++++++++++++++++++++++++++++++
	if(TipodeMalha==1)
	{
		DeltaInicial = 0;
	}
	//++++++++++++++++++++++++++TIPO2++++++++++++++++++++++++++++++++++++++++++++
	if(TipodeMalha==2)
	{
		DeltaInicial = DeltaBaseMaterial1/2;
	}
	//++++++++++++++++++++++++++TIPO3++++++++++++++++++++++++++++++++++++++++++++
	if(TipodeMalha==3)
	{
		DeltaInicial = 0;
	}
	//++++++++++++++++++++++++++TIPO4++++++++++++++++++++++++++++++++++++++++++++
	if(TipodeMalha==4)
	{
		DeltaInicial = DeltaBaseMaterial1/2;
	}
	return(DeltaInicial);
}
vector<double> Malha::DefineDeltasdeTransferencia(double DeltaBaseMat1,double DeltaBaseMatUltimo,int TipodeMalha)
{
	vector<double> DeltasTransferencia;
	DeltasTransferencia.resize(3);
	//++++++++++++++++++++++++++TIPO1++++++++++++++++++++++++++++++++++++++++++++
	if(TipodeMalha==1)
	{
		DeltasTransferencia[0] = DeltaBaseMat1/2;
		DeltasTransferencia[1] = DeltaBaseMatUltimo/2;
		DeltasTransferencia[2] = DeltaBaseMatUltimo/2;
	}
	//++++++++++++++++++++++++++TIPO2++++++++++++++++++++++++++++++++++++++++++++
	if(TipodeMalha==2)
	{
		DeltasTransferencia[0] = DeltaBaseMat1;
		DeltasTransferencia[1] = DeltaBaseMatUltimo/2;
		DeltasTransferencia[2] = DeltaBaseMatUltimo;
	}
	//++++++++++++++++++++++++++TIPO3++++++++++++++++++++++++++++++++++++++++++++
	if(TipodeMalha==3)
	{
		DeltasTransferencia[0] = DeltaBaseMat1;
		DeltasTransferencia[1] = DeltaBaseMatUltimo/2;
		DeltasTransferencia[2] = DeltaBaseMatUltimo/2;
	}
	//++++++++++++++++++++++++++TIPO4++++++++++++++++++++++++++++++++++++++++++++
	if(TipodeMalha==4)
	{
		DeltasTransferencia[0] = DeltaBaseMat1/2;
		DeltasTransferencia[1] = DeltaBaseMatUltimo/2;
		DeltasTransferencia[2] = DeltaBaseMatUltimo;
	}
	return(DeltasTransferencia);
}