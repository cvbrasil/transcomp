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
	int numerodetermos = 10;
	double k = 0.7;
	double cp = 700;
	double L = 0.4;
	double ro = 2000;
	double To = 20;
	double Tinf = 100;
	double h = Bi*k/L;
	double DELTAt=6000;
	double alpha;
	vector<int>NumerodePontos;
	NumerodePontos.push_back(4);
	vector<double>LarguraporMaterial;
	LarguraporMaterial.push_back(0.4);
	int NumerodeMalhas = 1;
	int TipodeMalha = 1;
	kvec.push_back(k);
	vector<double> Tinicial;

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

	for(int i=0; i<NumerodePontos[0]; i++)
	{
		Tinicial.push_back(To);
		thetas[i] = getSolucaoAnalitica(Bi, Fo, DistanciaX[i]/LarguraporMaterial[0], crit);
		Tanalit[i] = thetas[i]*(To-Tinf)+Tinf;
		cout<<endl<<"theta["<<i<<"]="<<thetas[i]<<"	Tanalit["<<i<<"]="<<Tanalit[i]<<endl;
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
	int iteracoesMax = 100;
	double CriteriodeParada = 1e-5;
	double f = 0;
	double PassodeTempo = 60;
	vector<double> CampodeT;
	GerenteVolumedeControle gerente(NumerodePontos,NumerodeMalhas,LarguraporMaterial,TipodeMalha,kvec,TipoDeKinterface,Pre1,Pre2,TiposPre,true,Caso,TipoDeCriterio);
	gerente.SetVariaveisTransiente(ro,cp,Tinicial,iteracoesMax,CriteriodeParada,PassodeTempo,f);
	CampodeT=gerente.getCampoDeTemperaturas(); //PEGA A ULTIMA TEMPERATURA
	//Teste
	for(int i=0; i<NumerodePontos[0]; i++)
	{
		if(fabs(Tanalit[i]-CampodeT[i])/Tanalit[i]>1e-4)
		{
			cout<<endl<<endl<<"Teste Errado pois Tanalit["<<i<<"]="<<Tanalit[i]<<" e Tsimul="<<CampodeT[i]<<endl<<endl;
		}
		else
		{
			cout<<endl<<endl<<"Teste Certo pois Tanalit["<<i<<"]="<<Tanalit[i]<<" e Tsimul="<<CampodeT[i]<<endl<<endl;
		}
	}
	return 0;
}