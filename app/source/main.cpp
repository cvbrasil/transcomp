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
	vector<double> kvec;
	double k = 230;
	double Tinf = 20;
	double Tb = 100;
	double h = 200;
	double LH=;
	double LV=;
	vector<int>NumerodePontosH;
	NumerodePontosH.push_back(12);
	vector<double>LarguraporMaterialH;
	LarguraporMaterial.push_back(LH);
	int NumerodeMalhas = 1;
	int TipodeMalhaH = 4;
	vector<int>NumerodePontosV;
	NumerodePontosV.push_back(4);
	vector<double>LarguraporMaterialV;
	LarguraporMaterial.push_back(LV);
	int TipodeMalhaV = 1;
	kvec.push_back(k);
	int TipoDeKinterface = 1;
	vector<double> Pre1;
	Pre1.push_back(Tb);
	vector<double> Pre2;
	Pre2.push_back(0);
	vector<int> TiposPreH;
	TiposPre.push_back(1);
	TiposPre.push_back(2);
	vector<double> Pre3;
	Pre3.push_back(Tinf);
	Pre3.push_back(h);
	vector<double>Pre4;
	Pre4.push_back(0);
	vector<double>TiposPreV;
	TiposPreV.push_back(2);
	TiposPreV.push_back(3);
	int Caso = 3;
	int TipoDeCriterio = 1;
	double CriteriodeParada = 1e-5;
	Malha malhaVertical(NumerodePontosV,LarguraporMaterialV,NumerodeMalhas,TipodeMalhaV);
	GerenteVolumedeControle gerenteTrab5(NumerodePontosH,NumerodeMalhasH,LarguraporMaterialH,TipodeMalhaH,kvec,TipoDeKinterface,Pre1,Pre2,TiposPreH,true,Caso,TipoDeCriterio);
	gerenteTrab5.SetVariaveisBidimensionais(malhaVertical,Pre3,Pre4,TiposPreV);
	return 0;
}