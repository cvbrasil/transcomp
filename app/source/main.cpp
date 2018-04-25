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
	vector<double> csi;
	vector<double> Cn;
	vector<double> kvec;
	double crit = 1e-13;
	double k = 230;
	double cp = 900;
	double L = 0.005;
	double RaioInterno = 0.05;
	double ro = 2700;
	double To = 80;
	double Tinf = 80;
	double h = 20000;
	double DELTAt=0;
	double DeslocaY = 150;
	double Amplitude = 50;
	double Frequencia = 50;
	double DeslocaX = 0;
	int QualExtremo = 1;
	vector<int>NumerodePontos;
	NumerodePontos.push_back(4);
	vector<double>LarguraporMaterial;
	LarguraporMaterial.push_back(L);
	int NumerodeMalhas = 1;
	int TipodeMalha = 1;
	kvec.push_back(k);
	int iteracoesMax = 1000;
	int TipoDeKinterface = 1;
	vector<double> Pre1;
	Pre1.push_back(0);
	vector<double> Pre2;
	Pre2.push_back(Tinf);
	Pre2.push_back(h);
	vector<int> TiposPre;
	TiposPre.push_back(1);
	TiposPre.push_back(3);
	int Caso = 2;
	int TipoDeCriterio = 1;
	double CriteriodeParada = 1e-10;
	double f = 1;
	double PassodeTempo = 0.002;
	vector<double>Tinicial;
	for(int i=0; i++; i<NumerodePontos[0])
	{
		Tinicial.push_back(To);
	}
	vector<vector<<double> > CampodeTtransiente;
	GerenteVolumedeControle gerenteTrab4Teste(NumerodePontos,NumerodeMalhas,LarguraporMaterial,TipodeMalha,kvec,TipoDeKinterface,Pre1,Pre2,TiposPre,true,Caso,TipoDeCriterio);
	gerenteTrab4Teste.setVariaveisCilindricas(RaioInterno);
	gerenteTrab4Teste.setCoeficientesCosTpreTransiente(DeslocaY,Amplitude,Frequencia,DeslocaX,QualExtremo);
	gerenteTrab4Teste.SetVariaveisTransiente(ro,cp,Tinicial,iteracoesMax,CriteriodeParada,PassodeTempo,f);
	CampodeTtransiente=gerenteTrab4Teste.getTemperaturasTransiente();

	cout<<endl<<endl<<endl<<"+++++++++++++++++++++++++++CAMPO DE T TRANSIENTE+++++++++++++++++++++++++++++++++"<<endl<<endl;
	for(int i=0; i++; i<NumerodePontos[0])
	{
		for(int j=0; j++; j<CampodeTtransiente.size())
		{
			cout<<CampodeTtransiente[i][j]<<"\t";
		}
		cout<<endl;
	}
	return 0;
}