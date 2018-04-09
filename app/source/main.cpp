#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <math.h>

#include "GerenteVolumedeControle.h"
#include "Malha.h"
#include "PropriedadeTermica.h"
#include "CondicoesdeContorno.h"
#include "SolverLinear.h"
#include "CriteriodeParada.h"

int main()
{
	vector<vector<double> > kpol;
	vector<double> k;
	vector<int> NumerodePontos;
	vector<double> Pre1;
	vector<double> Pre2;
	vector<int> TiposPre;
	vector<double> kporponto;
	vector<double> kinterfaces;

	TiposPre.push_back(1);
	TiposPre.push_back(1);

	bool Polinomial = true;
	bool DeltinhaTrueRealFalseMedio=true;
	Pre1.push_back(100);
	Pre2.push_back(20);
	int Nmalhas = 1;
	vector<double>LarguraMat;
	LarguraMat.push_back(0.1);
	int TipoMalha=1;

	//GERA VETOR NUM DE PTOS
	NumerodePontos.push_back(4);
	vector<int>NumeroDeVC;
	NumeroDeVC.resize(4);
	//GERA MATRIZ kpol
	vector<double> aux;
	aux.push_back(1.6);
	aux.push_back(-0.01);

	kpol.push_back(aux);
	string nomeArquivo;
	string TDC;
	string TDk;
	string NVC;

	vector<int>VecNumeroDeIteracoes;
	VecNumeroDeIteracoes.resize(4);
	for(int TipoDeCriterio=1; TipoDeCriterio<=2; TipoDeCriterio++)
	{
		cout<<"----------------------------------------------------------------------------------------"<<endl<<endl;
		cout<<endl<<endl<<endl<<"+++++++++++++++++++++++++++COMECA NOVO TIPO DE CRITERIODEPARADA ="<<TipoDeCriterio<<" +++++++++++++++++++++++++++++"<<endl;
		cout<<"----------------------------------------------------------------------------------------"<<endl<<endl;
		for(int TipoDeKinterface = 1; TipoDeKinterface<=2; TipoDeKinterface++)
		{
			cout<<endl<<endl<<endl<<"+++++++++++++++++++++++++++COMECA NOVO TIPO DE kInterface ="<<TipoDeKinterface<<" +++++++++++++++++++++++++++++"<<endl;
			cout<<"---------------------------------------------------------------------------"<<endl<<endl;
			for(int j=0; j<4; j++)
			{
				cout<<endl<<endl<<endl<<"+++++++++++++++++++++++++++COMECA NOVA MALHA+++++++++++++++++++++++++++++"<<endl;
				//CRIA MALHA AUXILIAR
				Malha Malhaaux(NumerodePontos,LarguraMat,Nmalhas,TipoMalha);
				//GERA VETOR To
				vector<double> To;
				for(int i=0; i<NumerodePontos[0]; i++)
				{
					To.push_back(-800*Malhaaux.getDistanciadaOrigemPosicional(i)+100);
				}
				
				GerenteVolumedeControle GerentePolinomial(NumerodePontos,Nmalhas,LarguraMat,TipoMalha,k,TipoDeKinterface,Pre1,Pre2,TiposPre,DeltinhaTrueRealFalseMedio,Polinomial,TipoDeCriterio);
				GerentePolinomial.SetVariaveisPolinomiais(kpol,To,200,1e-10);

				vector<double> CampodeT;
				CampodeT = GerentePolinomial.getCampoDeTemperaturas();
				kporponto=GerentePolinomial.getkEmTodosPontos();
				kinterfaces=GerentePolinomial.getkinterface_TodosPontos();

				vector<double> FluxoTermico;
				FluxoTermico=GerentePolinomial.getFluxoTermico();

				//TESTA VALORES
				vector<double>erro;
				erro.resize(NumerodePontos[0]);
				vector<double> Tanalitica;
				for(int i=0; i<NumerodePontos[0]; i++)
				{
					Tanalitica.push_back(160-pow(3600+160000*Malhaaux.getDistanciadaOrigemPosicional(i),0.5));
					cout<<endl<<"T["<<i<<"] = "<<setprecision(17)<<CampodeT[i]<<setprecision(17)<<"	k["<<i<<"]="<<kporponto[i];
					if(i<NumerodePontos[0]-1)
					{
						cout<<"	kinterf["<<i<<"] = "<<kinterfaces[i]<<setprecision(17)<<"	q="<<FluxoTermico[i]<<endl;
					}
				}
				//Salva Vetores de Simulacao
				TDC = GerentePolinomial.TransformaEmString(TipoDeCriterio);
				TDk = GerentePolinomial.TransformaEmString(TipoDeKinterface);
				NVC = GerentePolinomial.TransformaEmString(NumerodePontos[0]);
				nomeArquivo = "Trabalho2Criterio"+TDC+"kinterf"+TDk+"NVC"+NVC+".csv";
				GerentePolinomial.SalvaCampoDeTemperaturascsv(nomeArquivo);
				//Salva Erro
				if(NumerodePontos[0]==32||NumerodePontos[0]==4)
				{
					for(int i=0; i<NumerodePontos[0]; i++)
					{
						erro[i]=fabs(CampodeT[i]-Tanalitica[i])/Tanalitica[i];
					}
					nomeArquivo = "Trabalho2ERRORELATIVOCriterio"+TDC+"kinterf"+TDk+"NVC"+NVC+".csv";
					GerentePolinomial.SalvaDoisVetorescsv(nomeArquivo,erro,Malhaaux.getDistanciadaOrigem());
				}
				//Salva Tanalitica
				if(NumerodePontos[0]==4||NumerodePontos[0]==32)
				{
					string nomeArquivoAnalit = "Trabalho2TanalitNVC"+NVC+".csv";				
					GerentePolinomial.SalvaDoisVetorescsv(nomeArquivoAnalit, Tanalitica, Malhaaux.getDistanciadaOrigem());
					//Salva Fluxos TermicosxNVC
					nomeArquivo = "Trabalho2FLUXOTERMICOCriterio"+TDC+"kinterf"+TDk+"NVC"+NVC+".csv";
					vector<double> ContaInterfaces;
					ContaInterfaces.resize(NumerodePontos[0]-1);
					for(int f=0;f<NumerodePontos[0]-1;f++)
					{
						ContaInterfaces[f]=f;
					}
					GerentePolinomial.SalvaDoisVetorescsv(nomeArquivo,FluxoTermico,ContaInterfaces);
				}

				//Retira Numero de iteracoes
				int NumeroDeIteracoes;
				NumeroDeIteracoes = GerentePolinomial.getNumerodeIteracoes();
				cout<<endl<<endl<<"NumeroDeIteracoes="<<NumeroDeIteracoes<<"	NumeroDeVolumes="<<NumerodePontos[0]<<endl<<endl;
				//Salva Numero de Iteracoes x Numero de VC
				VecNumeroDeIteracoes[j]=NumeroDeIteracoes;
				NumeroDeVC[j] = NumerodePontos[0];
				if(j==3)
				{
					string nomeArquivoNVCiteracoes;
					nomeArquivoNVCiteracoes="Trabalho2NVCxITERACOESCriterio"+TDC+"kinterf"+TDk+".csv";
					GerentePolinomial.SalvaDoisVetoresDeintcsv(nomeArquivoNVCiteracoes,NumeroDeVC,VecNumeroDeIteracoes);
				}
				NumerodePontos[0]=NumerodePontos[0]*2;
			}
			NumerodePontos[0]=4;
		}
	}
	return 0;
}