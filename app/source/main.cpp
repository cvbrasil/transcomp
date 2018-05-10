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
std::stringstream sstm;
double NewtonRaphsonParaTerL(double m,double eta,double crit, int itmax)
{
	double Lo=2;
	double L;
	double diferenca = crit+1;
	int cont=0;
	while(itmax>cont&&crit<diferenca)
	{
		L=Lo-(tanh(m*Lo)/(eta*m*Lo)-1)/((m/cosh(m*Lo)/cosh(m*Lo)-eta*m*tanh(m*Lo))/(eta*m*Lo*Lo));
		diferenca=fabs(L-Lo);
		Lo=L;
		cont++;
	}
	return(L);
}
int main()
{
	vector<double> kvec;
	double k = 230;
	double Tinf = 20;
	double Tb = 100;
	double h = 200;
	double LH=1;
	double LV=0.012;
	double eta=0.6;
	double crit=1e-10;
	double itmax=200;
	double m = pow(h*(2*LV+2)/(k*LV),0.5);
	LH=NewtonRaphsonParaTerL(m,eta,crit,itmax);
	cout<<endl<<endl<<"LH="<<LH<<"	m="<<m<<endl<<endl;
	vector<int>NumerodePontosH;
	NumerodePontosH.push_back(5);
	vector<double>LarguraporMaterialH;
	LarguraporMaterialH.push_back(LH);
	int NumerodeMalhasH = 1;
	int NumerodeMalhasV = 1;
	int TipodeMalhaH = 4;
	vector<int>NumerodePontosV;
	NumerodePontosV.push_back(2);
	vector<double>LarguraporMaterialV;
	LarguraporMaterialV.push_back(LV);
	int TipodeMalhaV = 1;
	kvec.push_back(k);
	int TipoDeKinterface = 1;
	vector<double> Pre1;
	Pre1.push_back(Tb);
	vector<double> Pre2;
	Pre2.push_back(0);
	vector<int> TiposPreH;
	TiposPreH.push_back(1);
	TiposPreH.push_back(2);
	vector<double>Pre3;
	Pre3.push_back(0);
	vector<double> Pre4;
	Pre4.push_back(Tinf);
	Pre4.push_back(h);
	vector<int>TiposPreV;
	TiposPreV.push_back(2);
	TiposPreV.push_back(3);
	int Caso = 3;
	int TipoDeCriterio=1;

	//REFINA MALHA
	for(int i=0; i<3; i++)
	{
		Malha malhaVertical(NumerodePontosV,LarguraporMaterialV,NumerodeMalhasV,TipodeMalhaV);
		Malha malhaHorizontal(NumerodePontosH,LarguraporMaterialH,NumerodeMalhasH,TipodeMalhaH);
		PropriedadeTermica propriedadetermicaV(kvec,NumerodePontosV);
		GerenteVolumedeControle gerenteTrab5(NumerodePontosH,NumerodeMalhasH,LarguraporMaterialH,TipodeMalhaH,kvec,TipoDeKinterface,Pre1,Pre2,TiposPreH,true,Caso,TipoDeCriterio);
		gerenteTrab5.SetVariaveisBidimensionais(malhaVertical,propriedadetermicaV,Pre3,Pre4,TiposPreV,LV,NumerodePontosV[0],TipodeMalhaV);
		vector<vector<double> >A;
		A=gerenteTrab5.getMatrizA();
		vector<double> b;
		b=gerenteTrab5.getVetorb();
		string NomeMatriz;
		string NomeVetor;
		int NH=NumerodePontosH[0];
		int NV=NumerodePontosV[0];
		NomeMatriz="MatrizAHOR"+std::to_string(NH)+"VERT"+std::to_string(NV)+".csv";
		NomeVetor="VetorbHOR"+std::to_string(NH)+"VERT"+std::to_string(NV)+".csv";
		gerenteTrab5.SalvaMatrizcsv(NomeMatriz,A);
		gerenteTrab5.SalvaVetorcsv(NomeVetor,b);
		//Salva pontos de malha
		vector<double> VETORMALHAHORIZONTAL;
		vector<double> VETORMALHAVERTICAL;
		VETORMALHAHORIZONTAL=malhaHorizontal.getDistanciadaOrigem();
		VETORMALHAVERTICAL=malhaVertical.getDistanciadaOrigem();
 		string NomeVetorHorizontal="VetorMalhaHorizontal"+std::to_string(NumerodePontosH[0])+".csv";
 		string NomeVetorVertical="VetorMalhaVertical"+std::to_string(NumerodePontosV[0])+".csv";
		gerenteTrab5.SalvaDoisVetorescsv(NomeVetorHorizontal, VETORMALHAHORIZONTAL,VETORMALHAHORIZONTAL);
		gerenteTrab5.SalvaDoisVetorescsv(NomeVetorVertical, VETORMALHAVERTICAL,VETORMALHAVERTICAL);
		NumerodePontosH[0]=NumerodePontosH[0]*2;
		NumerodePontosV[0]=NumerodePontosV[0]*2;
	}
	return 0;
}