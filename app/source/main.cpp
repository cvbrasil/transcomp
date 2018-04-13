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

double getcsi(double Bi, double xo, double crit)
{
	double x;
	int cont = 0;
	int iteracaomaxima=100;
	double erro = 1;
	while(crit<erro && iteracaomaxima>cont)
	{
		cont++;
		x = xo-(Bi-xo*tan(xo))/(-(tan(xo)+xo*pow(1/cos(xo),2)));
		erro = fabs(x - xo);
		xo = x;
	}
	return (x);
}
double getCn(double csi)
{
	double Cn=(4*sin(csi)/(2*csi+sin(2*csi)));
	return(Cn);
}
double getSolucaoAnalitica(double Bi, double Fo, double xc, double crit)
{
	double pi = 3.14159265359;
	double theta = 0;
	int cont = 0;
	int iteracaomaxima=100;
	double soma = crit+1;
	double xo=1;
	double Cn;
	double csi;
	while((crit<soma || soma<-crit) && iteracaomaxima>cont)
	{
		csi = getcsi(Bi, xo, crit);
		Cn = getCn(csi);
		soma = Cn*exp(-(pow(csi,2)*Fo))*cos(csi*xc);
		//cout<<endl<<endl<<"	"<<soma<<"	"<<cont<<endl<<endl;
		theta = theta + soma;
		cont ++;
		xo = cont*pi;
	}
	return (theta);
}
int main()
{
	vector<double> csi;
	vector<double> Cn;
	vector<double> kvec;
	double Bi = 1.15;
	double crit = 1e-13;
	double k = 0.7;
	double cp = 700;
	double L = 0.4;
	double ro = 2000;
	double To = 20;
	double Tinf = 100;
	double h = Bi*k/L;
	double DELTAt=911020;
	double alpha;
	vector<int>NumerodePontos;
	NumerodePontos.push_back(4);
	vector<double>LarguraporMaterial;
	LarguraporMaterial.push_back(0.4);
	int NumerodeMalhas = 1;
	int TipodeMalha = 1;
	kvec.push_back(k);

	for(int i=0; i<1; i++)
	{
		vector<double> Tinicial;
		NumerodePontos[0] = NumerodePontos[0]*(i+1);
		cout<<endl<<endl<<endl<<"+++++++++++++++++++++++++++++++++ "<<NumerodePontos[0]<<"VC +++++++++++++++++++++++++++++++++++++"<<endl<<endl;
		double PassodeTempo;
		if(i==0)
		{
			PassodeTempo = 4444;
			DELTAt = 911020;
		}
		if(i==1)
		{
			PassodeTempo = 816;
			DELTAt = 283152;
		}
		//Solucao Analitica
		vector<double>thetas;
		thetas.resize(NumerodePontos[0]);
		vector<double> Tanalit;
		Tanalit.resize(NumerodePontos[0]);
		vector<double>DistanciaX;
		Malha malhaaux(NumerodePontos,LarguraporMaterial,NumerodeMalhas,TipodeMalha);
		DistanciaX =  malhaaux.getDistanciadaOrigem();
		alpha = k/(ro*cp);
		double Fo = alpha*DELTAt/pow(LarguraporMaterial[0],2);

		for(int u=0; u<NumerodePontos[0]; u++)
		{
			Tinicial.push_back(To);
			thetas[u] = getSolucaoAnalitica(Bi, Fo, DistanciaX[u]/LarguraporMaterial[0], crit);
			Tanalit[u] = thetas[u]*(To-Tinf)+Tinf;
			cout<<endl<<"theta["<<u<<"]="<<thetas[u]<<"	Tanalit["<<u<<"]="<<Tanalit[u]<<endl;
		}

		//Solucao Simulada
		int TipoDeKinterface = 1;
		vector<double> Pre1;
		Pre1.push_back(0);
		vector<double> Pre2;
		Pre2.push_back(100);
		Pre2.push_back(h);
		vector<int> TiposPre;
		TiposPre.push_back(2);
		TiposPre.push_back(3);
		int Caso = 2;
		int TipoDeCriterio = 1;
		int iteracoesMax = 1600;
		double CriteriodeParada = 1e-2;
		double f = 0;
		vector<double> CampodeT;
		vector<vector<double> > CampodeTporDt;
		int NumeroDeIteracoes;
		int TempoAteConvergencia;
		GerenteVolumedeControle gerente(NumerodePontos,NumerodeMalhas,LarguraporMaterial,TipodeMalha,kvec,TipoDeKinterface,Pre1,Pre2,TiposPre,true,Caso,TipoDeCriterio);
		gerente.SetVariaveisTransiente(ro,cp,Tinicial,iteracoesMax,CriteriodeParada,PassodeTempo,f);
		CampodeT=gerente.getCampoDeTemperaturas(); //PEGA A ULTIMA TEMPERATURA
		CampodeTporDt=gerente.getTemperaturasTransiente();
		NumeroDeIteracoes=gerente.getNumerodeIteracoes();
		TempoAteConvergencia = NumeroDeIteracoes*PassodeTempo;

		cout<<endl<<endl<<"MATRIZ CAMPO DE T"<<endl<<endl;
		for(int j=0; j<NumeroDeIteracoes; j++)
		{
			for(int k=0; k<NumerodePontos[0]; k++)
			{
				cout<<CampodeTporDt[j][k]<<"\t";
			}
			cout<<endl;
		}
		cout<<endl<<endl<<"iteracoes="<<NumeroDeIteracoes<<"	tempo ate convergir="<<TempoAteConvergencia<<endl<<endl;
		//Salva dados
		gerente.SalvaCampoDeTemperaturascsv("Trab3_1600it_8VC.csv");
		
		//Teste
		for(int i=0; i<NumerodePontos[0]; i++)
		{
			if(fabs(Tanalit[i]-CampodeT[i])/Tanalit[i]>1e-1)
			{
				cout<<endl<<endl<<"Teste Errado pois Tanalit["<<i<<"]="<<Tanalit[i]<<" e Tsimul="<<CampodeT[i]<<endl<<endl;
			}
			else
			{
				cout<<endl<<endl<<"Teste Certo pois Tanalit["<<i<<"]="<<Tanalit[i]<<" e Tsimul="<<CampodeT[i]<<endl<<endl;
			}
		}
	}
	return 0;
}