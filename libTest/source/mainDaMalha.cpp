#include <vector>
#include <iostream>
#include <string>
#include <iomanip>

#include "Malha.h"
#include "PropriedadeTermica.h"
#include "CondicoesdeContorno.h"
#include "SolverLinear.h"
#include "GerenteVolumedeControle.h"

#define BOOST_TEST_MODULE TestModule

#include "Test.h"

TestCase( ummaterialtipo1 )
{
	vector<int> Nptoscadamat;
	Nptoscadamat.push_back(3);

	vector<double> LarguraMat;
	LarguraMat.push_back(1);

	Malha Malha1MatTipo1(Nptoscadamat,LarguraMat,1,1);

	checkClose(Malha1MatTipo1.getdelta_w(1),0.5,1e-5);

	checkClose(Malha1MatTipo1.getdelta_e(1),0.5,1e-5);

	checkClose(Malha1MatTipo1.getDelta_w_Menos(1),0.25,1e-5);

	checkClose(Malha1MatTipo1.getDelta_w_Mais(1),0.25,1e-5);

	checkClose(Malha1MatTipo1.getDelta_e_Menos(1),0.25,1e-5);

	checkClose(Malha1MatTipo1.getDelta_e_Mais(1),0.25,1e-5);
}
TestCase( ummaterialtipo2 )
{
	vector<int> Nptoscadamat;
	Nptoscadamat.push_back(3);

	vector<double> LarguraMat;
	LarguraMat.push_back(1);

	Malha Malha1MatTipo2(Nptoscadamat,LarguraMat,1,2);

	checkClose(Malha1MatTipo2.getdelta_w(1),0.3333333333,1e-5);

	checkClose(Malha1MatTipo2.getdelta_e(1),0.3333333333,1e-5);

	checkClose(Malha1MatTipo2.getDelta_w_Menos(1),0.166666666666,1e-5);

	checkClose(Malha1MatTipo2.getDelta_w_Mais(1),0.166666666666,1e-5);

	checkClose(Malha1MatTipo2.getDelta_e_Menos(1),0.166666666666,1e-5);

	checkClose(Malha1MatTipo2.getDelta_e_Mais(1),0.166666666666,1e-5);
}
TestCase( ummaterialtipo3 )
{
	vector<int> Nptoscadamat;
	Nptoscadamat.push_back(3);

	vector<double> LarguraMat;
	LarguraMat.push_back(1);

	Malha Malha1MatTipo2(Nptoscadamat,LarguraMat,1,3);

	checkClose(Malha1MatTipo2.getdelta_w(1),0.4,1e-5);

	checkClose(Malha1MatTipo2.getdelta_e(1),0.4,1e-5);

	checkClose(Malha1MatTipo2.getDelta_w_Menos(1),0.2,1e-5);

	checkClose(Malha1MatTipo2.getDelta_w_Mais(1),0.2,1e-5);

	checkClose(Malha1MatTipo2.getDelta_e_Menos(1),0.2,1e-5);

	checkClose(Malha1MatTipo2.getDelta_e_Mais(1),0.2,1e-5);
}
TestCase( ummaterialtipo4 )
{
	vector<int> Nptoscadamat;
	Nptoscadamat.push_back(3);

	vector<double> LarguraMat;
	LarguraMat.push_back(1);

	Malha Malha1MatTipo4(Nptoscadamat,LarguraMat,1,4);

	checkClose(Malha1MatTipo4.getdelta_w(1),0.4,1e-5);

	checkClose(Malha1MatTipo4.getdelta_e(1),0.4,1e-5);

	checkClose(Malha1MatTipo4.getDelta_w_Menos(1),0.2,1e-5);

	checkClose(Malha1MatTipo4.getDelta_w_Mais(1),0.2,1e-5);

	checkClose(Malha1MatTipo4.getDelta_e_Menos(1),0.2,1e-5);

	checkClose(Malha1MatTipo4.getDelta_e_Mais(1),0.2,1e-5);
}
TestCase( doismateriaistipo1 )
{
	vector<int> Nptoscadamat;
	Nptoscadamat.push_back(3);
	Nptoscadamat.push_back(3);

	vector<double> LarguraMat;
	LarguraMat.push_back(2);
	LarguraMat.push_back(1);

	Malha Malha2MatTipo1(Nptoscadamat,LarguraMat,2,1);

	checkClose(Malha2MatTipo1.getdelta_w(3),0.75,1e-5);

	checkClose(Malha2MatTipo1.getdelta_e(3),0.25,1e-5);

	checkClose(Malha2MatTipo1.getDelta_w_Menos(3),0.5,1e-5);

	checkClose(Malha2MatTipo1.getDelta_w_Mais(3),0.25,1e-5);

	checkClose(Malha2MatTipo1.getDelta_e_Menos(3),0.125,1e-5);

	checkClose(Malha2MatTipo1.getDelta_e_Mais(3),0.125,1e-5);
}
TestCase( doismateriaistipo2 )
{
	vector<int> Nptoscadamat;
	Nptoscadamat.push_back(3);
	Nptoscadamat.push_back(3);

	vector<double> LarguraMat;
	LarguraMat.push_back(2);
	LarguraMat.push_back(1);

	Malha Malha2MatTipo2(Nptoscadamat,LarguraMat,2,2);

	checkClose(Malha2MatTipo2.getdelta_w(2),0.6666666666666,1e-5);

	checkClose(Malha2MatTipo2.getdelta_e(2),0.5,1e-5);

	checkClose(Malha2MatTipo2.getDelta_w_Menos(2),0.33333333333,1e-5);

	checkClose(Malha2MatTipo2.getDelta_w_Mais(2),0.333333333333,1e-5);

	checkClose(Malha2MatTipo2.getDelta_e_Menos(2),0.33333333333,1e-5);

	checkClose(Malha2MatTipo2.getDelta_e_Mais(2),0.16666666666666,1e-5);
}
TestCase( doismateriaistipo4 )
{
	vector<int> Nptoscadamat;
	Nptoscadamat.push_back(3);
	Nptoscadamat.push_back(3);

	vector<double> LarguraMat;
	LarguraMat.push_back(2);
	LarguraMat.push_back(1);

	Malha Malha2MatTipo4(Nptoscadamat,LarguraMat,2,4);


	checkClose(Malha2MatTipo4.getdelta_w(2),0.4,1e-5);

	checkClose(Malha2MatTipo4.getdelta_e(2),0.6,1e-5);

	checkClose(Malha2MatTipo4.getDelta_w_Menos(2),0.2,1e-5);

	checkClose(Malha2MatTipo4.getDelta_w_Mais(2),0.2,1e-5);

	checkClose(Malha2MatTipo4.getDelta_e_Menos(2),0.4,1e-5);

	checkClose(Malha2MatTipo4.getDelta_e_Mais(2),0.2,1e-5);

	checkClose(Malha2MatTipo4.getLarguraTotal(),3,1e-5);
}
TestCase( TestePropriedadeTermica )
{
	vector<int> Nptoscadamat;
	Nptoscadamat.push_back(3);
	Nptoscadamat.push_back(5);
	Nptoscadamat.push_back(2);

	vector<double> kcadaMat;
	kcadaMat.push_back(1.89);
	kcadaMat.push_back(10.15);
	kcadaMat.push_back(401);

	PropriedadeTermica PropriedadeTermica1(kcadaMat,Nptoscadamat);

	for(int i=0; i<10; i++)
	{
		if(i<3)
		{
			checkClose(PropriedadeTermica1.getk(i),1.89,1e-5);
		}
		else
		{
			if(i<8)
			{
				checkClose(PropriedadeTermica1.getk(i),10.15,1e-5);
			}
			else
			{
				checkClose(PropriedadeTermica1.getk(i),401,1e-5);
			}
		}
	}
}
TestCase( CC1 )
{
	vector<double>Pre1;
	Pre1.push_back(300);

	vector<double>Pre2;
	Pre2.push_back(300);

	vector<int>Tipos;
	Tipos.push_back(1);
	Tipos.push_back(1);

	vector<double>aexterno;
	vector<double> ainterno;

	aexterno.push_back(10);
	ainterno.push_back(5);

	aexterno.push_back(10);
	ainterno.push_back(5);

	CondicoesdeContorno cc1(Pre1,Pre2,Tipos,1,aexterno,ainterno);

	checkClose(cc1.getPrimeiroTermodeEntrada(),1,1e-5);
	checkClose(cc1.getSegundoTermodeEntrada(),0,1e-5);
	checkClose(cc1.getTerceiroTermodeEntrada(),300,1e-5);

	checkClose(cc1.getPrimeiroTermodeSaida(),0,1e-5);
	checkClose(cc1.getSegundoTermodeSaida(),1,1e-5);
	checkClose(cc1.getTerceiroTermodeSaida(),300,1e-5);
}
TestCase( CC2 )
{
	vector<double>Pre1;
	Pre1.push_back(20);

	vector<double>Pre2;
	Pre2.push_back(20);

	vector<int>Tipos;
	Tipos.push_back(2);
	Tipos.push_back(2);

	vector<double> aexterno;
	vector<double> ainterno;

	aexterno.push_back(10);
	ainterno.push_back(5);

	aexterno.push_back(10);
	ainterno.push_back(5);

	CondicoesdeContorno cc1(Pre1,Pre2,Tipos,1,aexterno,ainterno);

	checkClose(cc1.getPrimeiroTermodeEntrada(),5,1e-5);
	checkClose(cc1.getSegundoTermodeEntrada(),-5,1e-5);
	checkClose(cc1.getTerceiroTermodeEntrada(),-20,1e-5);

	checkClose(cc1.getPrimeiroTermodeSaida(),-5,1e-5);
	checkClose(cc1.getSegundoTermodeSaida(),5,1e-5);
	checkClose(cc1.getTerceiroTermodeSaida(),20,1e-5);
}
TestCase( CC3 )
{
	vector<double>Pre1;
	Pre1.push_back(300);
	Pre1.push_back(20);

	vector<double>Pre2;
	Pre2.push_back(300);
	Pre2.push_back(20);

	vector<int>Tipos;
	Tipos.push_back(3);
	Tipos.push_back(3);

	vector<double> aexterno;
	vector<double> ainterno;

	aexterno.push_back(10);
	ainterno.push_back(5);

	aexterno.push_back(10);
	ainterno.push_back(5);

	CondicoesdeContorno cc1(Pre1,Pre2,Tipos,1,aexterno,ainterno);

	checkClose(cc1.getPrimeiroTermodeEntrada(),25,1e-5);
	checkClose(cc1.getSegundoTermodeEntrada(),-5,1e-5);
	checkClose(cc1.getTerceiroTermodeEntrada(),6000,1e-5);

	checkClose(cc1.getPrimeiroTermodeSaida(),-5,1e-5);
	checkClose(cc1.getSegundoTermodeSaida(),25,1e-5);
	checkClose(cc1.getTerceiroTermodeSaida(),6000,1e-5);
}
TestCase( CC4 )
{
	vector<double>Pre1;
	Pre1.push_back(300);

	vector<double>Pre2;
	Pre2.push_back(300);

	vector<int>Tipos;
	Tipos.push_back(1);
	Tipos.push_back(1);

	vector<double>aexterno;
	vector<double> ainterno;

	aexterno.push_back(10);
	ainterno.push_back(5);

	aexterno.push_back(10);
	ainterno.push_back(5);

	CondicoesdeContorno cc1(Pre1,Pre2,Tipos,2,aexterno,ainterno);

	checkClose(cc1.getPrimeiroTermodeEntrada(),15,1e-5);
	checkClose(cc1.getSegundoTermodeEntrada(),-5,1e-5);
	checkClose(cc1.getTerceiroTermodeEntrada(),3000,1e-5);

	checkClose(cc1.getPrimeiroTermodeSaida(),-5,1e-5);
	checkClose(cc1.getSegundoTermodeSaida(),15,1e-5);
	checkClose(cc1.getTerceiroTermodeSaida(),3000,1e-5);
}
TestCase( CC5 )
{
	vector<double>Pre1;
	Pre1.push_back(20);

	vector<double>Pre2;
	Pre2.push_back(20);

	vector<int>Tipos;
	Tipos.push_back(2);
	Tipos.push_back(2);

	vector<double> aexterno;
	vector<double> ainterno;

	aexterno.push_back(10);
	ainterno.push_back(5);

	aexterno.push_back(10);
	ainterno.push_back(5);

	CondicoesdeContorno cc1(Pre1,Pre2,Tipos,2,aexterno,ainterno);

	checkClose(cc1.getPrimeiroTermodeEntrada(),5,1e-5);
	checkClose(cc1.getSegundoTermodeEntrada(),-5,1e-5);
	checkClose(cc1.getTerceiroTermodeEntrada(),-20,1e-5);

	checkClose(cc1.getPrimeiroTermodeSaida(),-5,1e-5);
	checkClose(cc1.getSegundoTermodeSaida(),5,1e-5);
	checkClose(cc1.getTerceiroTermodeSaida(),20,1e-5);
}
TestCase( CC6 )
{
	vector<double>Pre1;
	Pre1.push_back(300);
	Pre1.push_back(20);

	vector<double>Pre2;
	Pre2.push_back(300);
	Pre2.push_back(20);

	vector<int>Tipos;
	Tipos.push_back(3);
	Tipos.push_back(3);

	vector<double> aexterno;
	vector<double> ainterno;

	aexterno.push_back(10);
	ainterno.push_back(5);

	aexterno.push_back(10);
	ainterno.push_back(5);

	CondicoesdeContorno cc1(Pre1,Pre2,Tipos,2,aexterno,ainterno);

	checkClose(cc1.getPrimeiroTermodeEntrada(),5.099502488,1e-5);
	checkClose(cc1.getSegundoTermodeEntrada(),-5,1e-5);
	checkClose(cc1.getTerceiroTermodeEntrada(),29.8507461,1e-5);

	checkClose(cc1.getPrimeiroTermodeSaida(),-5,1e-5);
	checkClose(cc1.getSegundoTermodeSaida(),5.099502488,1e-5);
	checkClose(cc1.getTerceiroTermodeSaida(),29.8507461,1e-5);
}
// TestCase( SL )
// {
// 	vector<vector<double> > A;
// 	vector<double> b;
// 	int n;
// 	vector<double> T;

// 	//GERA MATRIZ
// 	vector<double>aux;
// 	aux.push_back(1);
// 	aux.push_back(0);
// 	A.push_back(aux);
// 	aux[0] = 2;
// 	aux[1] = 1;
// 	A.push_back(aux);

// 	//GERA VETOR TERMOS INDEPENDENTES
// 	b.push_back(2);
// 	b.push_back(2);


// 	SolverLinear SL1(A,b,2);
// 	T = SL1.getCampodeTemperaturas();

// 	checkClose(T[0],2,1e-5);
// 	checkClose(T[1],-2,1e-5);
// }
TestCase( Ger_borda_Tpre_Conv )
{
	vector<double> Tgerente;

	vector<int> Nptoscadamat;
	Nptoscadamat.push_back(500);

	int Nmalhas = 1;

	vector<double> LarguraMat;
	LarguraMat.push_back(1);

	int TipoMalha = 1;

	vector<double>k;
	k.push_back(400);

	vector<double>Pre1;
	Pre1.push_back(300);

	vector<double>Pre2;
	Pre2.push_back(290);
	Pre2.push_back(10);

	vector<int> TiposPre;
	TiposPre.push_back(1);
	TiposPre.push_back(3);

	Malha Malhaaux(Nptoscadamat,LarguraMat,1,1);
	GerenteVolumedeControle GVC(Nptoscadamat,Nmalhas,LarguraMat,TipoMalha,k,Pre1,Pre2,TiposPre);

	Tgerente = GVC.getCampoDeTemperaturas();

	double Tanalitica;
	for(int i=0;i<500;i++)
	{
		Tanalitica = (Pre2[1]/k[0])*(Pre2[0]-(Pre2[1]/k[0]*LarguraMat[0]*Pre2[0]+Pre1[0])/(1+Pre2[1]*LarguraMat[0]/k[0]))*Malhaaux.getDistanciadaOrigemPosicional(i)+Pre1[0];
		checkClose(Tgerente[i],Tanalitica,1e-10);
	}
}