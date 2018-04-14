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
	double DELTAt=0;
	double alpha;
	vector<int>NumerodePontos;
	NumerodePontos.push_back(4);
	vector<double>LarguraporMaterial;
	LarguraporMaterial.push_back(0.4);
	int NumerodeMalhas = 1;
	int TipodeMalha = 1;
	kvec.push_back(k);
	int iteracoesMax = 500; //CORRIGIR!!!!! T EM 6a ITERÇÂO != T EM j==5----------------6it=j5

	for(int i=1; i<2; i++)
	{
		vector<double> Tinicial;
		NumerodePontos[0] = NumerodePontos[0]*(i+1);
		cout<<endl<<endl<<endl<<"+++++++++++++++++++++++++++++++++ "<<NumerodePontos[0]<<"VC +++++++++++++++++++++++++++++++++++++"<<endl<<endl;
		double PassodeTempo;
		if(i==0)
		{
			PassodeTempo = 12851;
		}
		if(i==1)
		{
			PassodeTempo = 2804;
		}
		//PassodeTempo = 2804;
		//PassodeTempo = 12851;

		//Solucao Analitica
		vector<double>thetas;
		vector<double> Tanalit;
		vector<vector<double> >CampodeTporDtAnalitico;
		vector<double>DistanciaX;

		Malha malhaaux(NumerodePontos,LarguraporMaterial,NumerodeMalhas,TipodeMalha);
		DistanciaX =  malhaaux.getDistanciadaOrigem();
		for(int j=0;j<iteracoesMax;j++)
		{
			DELTAt = DELTAt + PassodeTempo;
			
			thetas.resize(NumerodePontos[0]);
			Tanalit.resize(NumerodePontos[0]);
			alpha = k/(ro*cp);
			double Fo = alpha*DELTAt/pow(LarguraporMaterial[0],2);

			for(int u=0; u<NumerodePontos[0]; u++)
			{
				Tinicial.push_back(To);
				thetas[u] = getSolucaoAnalitica(Bi, Fo, DistanciaX[u]/LarguraporMaterial[0], crit);
				Tanalit[u] = thetas[u]*(To-Tinf)+Tinf;

				//cout<<endl<<"theta["<<u<<"]="<<thetas[u]<<"	Tanalit["<<u<<"]="<<Tanalit[u]<<endl;
			}
			if(j==24||j==49||j==99||j==199||j==299||j==499)
			{
				CampodeTporDtAnalitico.push_back(Tanalit);
			}
			// if(j==4||j==14||j==29||j==59||j==89||j==119)
			// {
			// 	CampodeTporDtAnalitico.push_back(Tanalit);
			// }
		}
		DELTAt=0;
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
		double CriteriodeParada = 1e-10;
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

		// for(int j=0; j<CampodeT.size(); j++)
		// {
		// 	cout<<endl<<endl<<"T["<<j<<"]="<<CampodeT[j]<<" Tanalit="<<CampodeTporDtAnalitico[0][j]<<endl<<endl;
		// }

		// cout<<endl<<endl<<"MATRIZ CAMPO DE T"<<endl<<endl;
		// for(int j=0; j<NumeroDeIteracoes; j++)
		// {
		// 	for(int k=0; k<NumerodePontos[0]; k++)
		// 	{
		// 		cout<<CampodeTporDt[j][k]<<"\t";
		// 	}
		// 	cout<<endl;
		// }
		cout<<endl<<endl<<"iteracoes="<<NumeroDeIteracoes<<"	tempo ate convergir="<<TempoAteConvergencia<<endl<<endl;
		//Salva dados
		//gerente.SalvaCampoDeTemperaturascsv("Trab3_25it_8VC_teste.csv");
		//gerente.SalvaMatrizcsv("Trab3_5it_4VC_dt20000.csv",CampodeTporDt);
		//gerente.SalvaMatrizcsv("Trab3_Analit_4VC_dt12851.csv",CampodeTporDtAnalitico);
		gerente.SalvaMatrizcsv("Trab3_Analit_8VC_dt2804.csv",CampodeTporDtAnalitico);


		//Erro
		vector<vector<double> >CampodeTErro;
		vector<double> Iter;

		Iter.resize(6);
		CampodeTErro.resize(6);

		CampodeTErro[0]=(CampodeTporDt[24]); Iter[0]=25;
		CampodeTErro[1]=(CampodeTporDt[49]);Iter[1]=50;
		CampodeTErro[2]=(CampodeTporDt[99]);Iter[2]=100;
		CampodeTErro[3]=(CampodeTporDt[199]);Iter[3]=200;
		CampodeTErro[4]=(CampodeTporDt[299]);Iter[4]=300;
		CampodeTErro[5]=(CampodeTporDt[499]);Iter[5]=500;

		// CampodeTErro[0]=CampodeTporDt[4];Iter[0]=5;
		// CampodeTErro[1]=CampodeTporDt[14];Iter[1]=15;
		// CampodeTErro[2]=CampodeTporDt[29];Iter[2]=30;
		// CampodeTErro[3]=CampodeTporDt[59];Iter[3]=60;
		// CampodeTErro[4]=CampodeTporDt[89];Iter[4]=90;
		// CampodeTErro[5]=CampodeTporDt[119];Iter[5]=120;

		// for(int j=0; j<CampodeTErro.size(); j++)
		// {
		// 	for(int k=0; k<CampodeTErro[j].size(); k++)
		// 	{
		// 		cout<<CampodeTErro[j][k]<<"\t";
		// 	}
		// 	cout<<endl;
		// }

		vector<double> Erromax;
		Erromax.resize(6);
		double Erro;
		
		//gerente.SalvaMatrizcsv("Trab3_Analit_8VC_dt2804.csv",CampodeTErro);

		// for(int j=0; j<CampodeTporDtAnalitico.size(); j++)
		// {
		// 	//Erromax[j]=fabs(CampodeTErro[j][0]-CampodeTporDtAnalitico[j][0])/CampodeTporDtAnalitico[j][0];
		// 	Erromax[j]=fabs(CampodeTErro[j][0]-CampodeTporDtAnalitico[j][0]);
		// 	//cout<<endl<<endl<<"Terro["<<j<<"]="<<CampodeTErro[j][0]<<"-TAnalitico"<<CampodeTporDtAnalitico[j][0]<<"="<<Erromax[j]<<endl<<endl;
		// 	for(int k=1; k<CampodeTporDtAnalitico[j].size(); k++)
		// 	{
		// 		//Erro = fabs(CampodeTErro[j][k]-CampodeTporDtAnalitico[j][k])/CampodeTporDtAnalitico[j][k];
		// 		Erro = fabs(CampodeTErro[j][k]-CampodeTporDtAnalitico[j][k]);
		// 		//cout<<endl<<endl<<"Terro["<<j<<"]="<<CampodeTErro[j][k]<<"-TAnalitico="<<CampodeTporDtAnalitico[j][k]<<"="<<Erro<<endl<<endl;
		// 		if(Erro>Erromax[j])
		// 		{
		// 			Erromax[j]=Erro;
		// 		}
		// 	}
		// 	cout<<endl<<endl<<"Erromax["<<j<<"]="<<Erromax[j]<<endl<<endl;
		// }
		// gerente.SalvaDoisVetorescsv("Trab3_Analit_8VC_ErromaxNasIts.csv", Iter, Erromax);

		//Teste
		
		// for(int i=0; i<NumerodePontos[0]; i++)
		// {
		// 	if(fabs(Tanalit[i]-CampodeT[i])/Tanalit[i]>1e-1)
		// 	{
		// 		cout<<endl<<endl<<"Teste Errado pois Tanalit["<<i<<"]="<<Tanalit[i]<<" e Tsimul="<<CampodeT[i]<<endl<<endl;
		// 	}
		// 	else
		// 	{
		// 		cout<<endl<<endl<<"Teste Certo pois Tanalit["<<i<<"]="<<Tanalit[i]<<" e Tsimul="<<CampodeT[i]<<endl<<endl;
		// 	}
		// }
	}
	return 0;
}