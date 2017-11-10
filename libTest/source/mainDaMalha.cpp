#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <petscksp.h>

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

	checkClose(Malha1MatTipo1.getDelta_w_Menos(1,true),0.25,1e-5);

	checkClose(Malha1MatTipo1.getDelta_w_Mais(1,true),0.25,1e-5);

	checkClose(Malha1MatTipo1.getDelta_e_Menos(1,true),0.25,1e-5);

	checkClose(Malha1MatTipo1.getDelta_e_Mais(1,true),0.25,1e-5);
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

	checkClose(Malha1MatTipo2.getDelta_w_Menos(1,true),0.166666666666,1e-5);

	checkClose(Malha1MatTipo2.getDelta_w_Mais(1,true),0.166666666666,1e-5);

	checkClose(Malha1MatTipo2.getDelta_e_Menos(1,true),0.166666666666,1e-5);

	checkClose(Malha1MatTipo2.getDelta_e_Mais(1,true),0.166666666666,1e-5);
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

	checkClose(Malha1MatTipo2.getDelta_w_Menos(1,true),0.2,1e-5);

	checkClose(Malha1MatTipo2.getDelta_w_Mais(1,true),0.2,1e-5);

	checkClose(Malha1MatTipo2.getDelta_e_Menos(1,true),0.2,1e-5);

	checkClose(Malha1MatTipo2.getDelta_e_Mais(1,true),0.2,1e-5);
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

	checkClose(Malha1MatTipo4.getDelta_w_Menos(1,true),0.2,1e-5);

	checkClose(Malha1MatTipo4.getDelta_w_Mais(1,true),0.2,1e-5);

	checkClose(Malha1MatTipo4.getDelta_e_Menos(1,true),0.2,1e-5);

	checkClose(Malha1MatTipo4.getDelta_e_Mais(1,true),0.2,1e-5);
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

	checkClose(Malha2MatTipo1.getDelta_w_Menos(3,true),0.5,1e-5);

	checkClose(Malha2MatTipo1.getDelta_w_Mais(3,true),0.25,1e-5);

	checkClose(Malha2MatTipo1.getDelta_e_Menos(3,true),0.125,1e-5);

	checkClose(Malha2MatTipo1.getDelta_e_Mais(3,true),0.125,1e-5);
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

	checkClose(Malha2MatTipo2.getDelta_w_Menos(2,true),0.33333333333,1e-5);

	checkClose(Malha2MatTipo2.getDelta_w_Mais(2,true),0.333333333333,1e-5);

	checkClose(Malha2MatTipo2.getDelta_e_Menos(2,true),0.33333333333,1e-5);

	checkClose(Malha2MatTipo2.getDelta_e_Mais(2,true),0.16666666666666,1e-5);
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

	checkClose(Malha2MatTipo4.getDelta_w_Menos(2,true),0.2,1e-5);

	checkClose(Malha2MatTipo4.getDelta_w_Mais(2,true),0.2,1e-5);

	checkClose(Malha2MatTipo4.getDelta_e_Menos(2,true),0.4,1e-5);

	checkClose(Malha2MatTipo4.getDelta_e_Mais(2,true),0.2,1e-5);

	checkClose(Malha2MatTipo4.getLarguraTotal(),3,1e-5);
}
TestCase( doismateriaistipo2MALHA_IGUALMENTE_ESPACADA )
{
	vector<int> Nptoscadamat;
	Nptoscadamat.push_back(3);
	Nptoscadamat.push_back(6);

	vector<double> LarguraMat;
	LarguraMat.push_back(2);
	LarguraMat.push_back(2);

	Malha Malha2MatTipo2(Nptoscadamat,LarguraMat,2,2);

	checkClose(Malha2MatTipo2.getdelta_e(0),0.6666666666666,1e-5);

	checkClose(Malha2MatTipo2.getdelta_e(1),0.6666666666666,1e-5);

	checkClose(Malha2MatTipo2.getdelta_e(2),0.5,1e-5);

	checkClose(Malha2MatTipo2.getdelta_e(3),0.3333333333333,1e-5);

	checkClose(Malha2MatTipo2.getdelta_e(4),0.3333333333333,1e-5);

	checkClose(Malha2MatTipo2.getdelta_e(5),0.3333333333333,1e-5);

	checkClose(Malha2MatTipo2.getdelta_e(6),0.3333333333333,1e-5);

	checkClose(Malha2MatTipo2.getdelta_e(7),0.3333333333333,1e-5);
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
// TestCase( CC5 )
// {
// 	vector<double>Pre1;
// 	Pre1.push_back(20);

// 	vector<double>Pre2;
// 	Pre2.push_back(20);

// 	vector<int>Tipos;
// 	Tipos.push_back(2);
// 	Tipos.push_back(2);

// 	vector<double> aexterno;
// 	vector<double> ainterno;

// 	aexterno.push_back(10);
// 	ainterno.push_back(5);

// 	aexterno.push_back(10);
// 	ainterno.push_back(5);

// 	CondicoesdeContorno cc1(Pre1,Pre2,Tipos,2,aexterno,ainterno);

// 	checkClose(cc1.getPrimeiroTermodeEntrada(),5,1e-5);
// 	checkClose(cc1.getSegundoTermodeEntrada(),-5,1e-5);
// 	checkClose(cc1.getTerceiroTermodeEntrada(),-20,1e-5);

// 	checkClose(cc1.getPrimeiroTermodeSaida(),-5,1e-5);
// 	checkClose(cc1.getSegundoTermodeSaida(),5,1e-5);
// 	checkClose(cc1.getTerceiroTermodeSaida(),20,1e-5);
// }
// TestCase( CC6 )
// {
// 	vector<double>Pre1;
// 	Pre1.push_back(300);
// 	Pre1.push_back(20);

// 	vector<double>Pre2;
// 	Pre2.push_back(300);
// 	Pre2.push_back(20);

// 	vector<int>Tipos;
// 	Tipos.push_back(3);
// 	Tipos.push_back(3);

// 	vector<double> aexterno;
// 	vector<double> ainterno;

// 	aexterno.push_back(10);
// 	ainterno.push_back(5);

// 	aexterno.push_back(10);
// 	ainterno.push_back(5);

// 	CondicoesdeContorno cc1(Pre1,Pre2,Tipos,2,aexterno,ainterno);

// 	checkClose(cc1.getPrimeiroTermodeEntrada(),5.099502488,1e-5);
// 	checkClose(cc1.getSegundoTermodeEntrada(),-5,1e-5);
// 	checkClose(cc1.getTerceiroTermodeEntrada(),29.8507461,1e-5);

// 	checkClose(cc1.getPrimeiroTermodeSaida(),-5,1e-5);
// 	checkClose(cc1.getSegundoTermodeSaida(),5.099502488,1e-5);
// 	checkClose(cc1.getTerceiroTermodeSaida(),29.8507461,1e-5);
// }
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
// TestCase( Ger_borda_Tpre_Conv_Erro )
// {
// 	PetscInitialize(0,0,0,0);

// 	vector<int> Nptoscadamat;
// 	Nptoscadamat.push_back(4);

// 	int Nmalhas=1;

// 	int Ntestes = 6;
// 	vector<double> ErroMax;
// 	ErroMax.resize(Ntestes);
// 	for(int i=0;i<ErroMax.size();i++)
// 	{
// 		ErroMax[i] = 0;
// 	}

// 	vector<double> LarguraMat;
// 	LarguraMat.push_back(1);

// 	int TipoMalha = 1;

// 	vector<double>k;
// 	k.push_back(400);

// 	vector<double>Pre1;
// 	Pre1.push_back(300);

// 	vector<double>Pre2;
// 	Pre2.push_back(290);
// 	Pre2.push_back(10);

// 	vector<int> TiposPre;
// 	TiposPre.push_back(1);
// 	TiposPre.push_back(3);

// 	//Escopo para 4 volumes
// 	{
// 		vector<double> Tgerente;
// 		vector<double> Tanalitica;
// 		Malha Malhaaux(Nptoscadamat,LarguraMat,1,1);
// 		GerenteVolumedeControle GVC(Nptoscadamat,Nmalhas,LarguraMat,TipoMalha,k,1,Pre1,Pre2,TiposPre,true);

// 		Tgerente = GVC.getCampoDeTemperaturas();


// 		Tanalitica.resize(Tgerente.size());
// 		vector<double> DistanciaDaOrigem;

// 		DistanciaDaOrigem = GVC.getDistanciaDaOrigem();

// 		string NomedoArquivo = "TabelasTrab4Analit1mat.csv";
// 		char NomedoArquivoChar[NomedoArquivo.length()+1];
// 		strcpy(NomedoArquivoChar,NomedoArquivo.c_str());
// 		ofstream myfile;
// 		myfile.open (NomedoArquivoChar);

// 		for(int i=0;i<Tgerente.size();i++)
// 		{
// 			Tanalitica[i] = (Pre2[1]/k[0])*(Pre2[0]-(Pre2[1]/k[0]*LarguraMat[0]*Pre2[0]+Pre1[0])/(1+Pre2[1]*LarguraMat[0]/k[0]))*Malhaaux.getDistanciadaOrigemPosicional(i)+Pre1[0];
// 			checkClose(Tgerente[i],Tanalitica[i],1e-10);
// 			myfile<<Tanalitica[i]<<setprecision(17)<<","<<DistanciaDaOrigem[i]<<setprecision(17)<<"\n";
// 		}
// 		myfile.close();
// 		string Nome = "TabelasTrab4Simul1mat.csv";
// 		GVC.SalvaCampoDeTemperaturascsv(Nome);
// 	}
// 	string NomedoArquivo2 = "TabelasTrab4erroMAX1mat.csv";
// 	char NomedoArquivoChar2[NomedoArquivo2.length()+1];
// 	strcpy(NomedoArquivoChar2,NomedoArquivo2.c_str());
// 	ofstream myfile2;
// 	myfile2.open (NomedoArquivoChar2);
// 	for(int j=0;j<Ntestes;j++)
// 	{
// 		vector<double> Tgerente;
// 		vector<double> Tanalitica;

// 		Malha Malhaaux(Nptoscadamat,LarguraMat,1,1);
// 		GerenteVolumedeControle GVC(Nptoscadamat,Nmalhas,LarguraMat,TipoMalha,k,1,Pre1,Pre2,TiposPre,true);
// 		Tgerente = GVC.getCampoDeTemperaturas();
// 		Tanalitica.resize(Tgerente.size());

// 		vector<double>erro;
// 		erro.resize(Tgerente.size());
// 		for(int i=0;i<Tgerente.size();i++)
// 		{
// 			Tanalitica[i] = (Pre2[1]/k[0])*(Pre2[0]-(Pre2[1]/k[0]*LarguraMat[0]*Pre2[0]+Pre1[0])/(1+Pre2[1]*LarguraMat[0]/k[0]))*Malhaaux.getDistanciadaOrigemPosicional(i)+Pre1[0];
// 			erro[i] = fabs(Tanalitica[i]-Tgerente[i])/Tgerente[i];
// 			if(ErroMax[j]<erro[i])
// 			{
// 				ErroMax[j]=erro[i];
// 			}
// 		}
// 		myfile2<<ErroMax[j]<<setprecision(17)<<","<<Nptoscadamat[0]<<setprecision(17)<<"\n";
// 		Nptoscadamat[0]=Nptoscadamat[0]*2;
// 	}
// 	myfile2.close();

// 	{
// 		Pre1[0]=300;
// 		vector<double> Tgerente;
// 		vector<double> Tanalitica;
// 		Nptoscadamat[0]=4;
// 		Nptoscadamat.push_back(4);

// 		Nmalhas=2;
// 		LarguraMat.push_back(0.5);
// 		TipoMalha = 2;
// 		k[0]=400;
// 		k.push_back(200);

// 		Malha Malhaaux2Mat(Nptoscadamat,LarguraMat,2,2);

// 		// GerenteVolumedeControle DoisMatTpreConvInterpDesalinhado(Nptoscadamat,Nmalhas,LarguraMat,TipoMalha,k,2,Pre1,Pre2,TiposPre,false);

// 		// GerenteVolumedeControle DoisMatTpreConvResistDesalinhado(Nptoscadamat,Nmalhas,LarguraMat,TipoMalha,k,1,Pre1,Pre2,TiposPre,false);

// 		// GerenteVolumedeControle DoisMatTpreConvInterpAlinhado(Nptoscadamat,Nmalhas,LarguraMat,TipoMalha,k,2,Pre1,Pre2,TiposPre,true);

// 		GerenteVolumedeControle DoisMatTpreConvResistAlinhado(Nptoscadamat,Nmalhas,LarguraMat,TipoMalha,k,1,Pre1,Pre2,TiposPre,true);

// 		Tgerente = DoisMatTpreConvResistAlinhado.getCampoDeTemperaturas();

// 		double Tx1;
// 		double Tx2;

// 		int cont = 0;
// 	//	Tx1=Pre1[0]-Pre2[1]/k[0]*((Pre1[0]+Pre2[0]*Pre2[1]*(LarguraMat[0]/k[0]+(LarguraMat[1])/k[1]))/(Pre2[1]*((LarguraMat[1])/k[1]+LarguraMat[0]/k[0]+1/Pre2[1]))-Pre2[0])*LarguraMat[0];
// 		Tx2=(Pre1[0]+Pre2[0]*Pre2[1]*(LarguraMat[0]/k[0]+LarguraMat[1]/k[1]))/(Pre2[1]*(LarguraMat[1]/k[1]+LarguraMat[0]/k[0]+1/Pre2[1]));
// 		// cout<<endl<<"Tx2="<<setprecision(10)<<Tx2<<endl<<endl;
// 		for(int j=0;j<Nmalhas;j++)
// 		{
// 			for(int i=0;i<Nptoscadamat[j];i++)
// 			{
// 				if(j<1)
// 				{
// 					Tanalitica.push_back(Pre1[0]-Pre2[1]/k[0]*(Tx2-Pre2[0])*Malhaaux2Mat.getDistanciadaOrigemPosicional(cont));
// 					checkClose(Tgerente[cont],Tanalitica[cont],1e-10);
// 				}
// 				else
// 				{
// 					Tanalitica.push_back(Pre1[0]-Pre2[1]*(Tx2-Pre2[0])*(LarguraMat[0]/k[0]-LarguraMat[0]/k[1]+Malhaaux2Mat.getDistanciadaOrigemPosicional(cont)/k[1]));
// 					checkClose(Tgerente[cont],Tanalitica[cont],1e-10);
// 				}
// 				// cout<<endl<<fabs(Tanalitica[cont]-Tgerente[cont])<<"	"<<Malhaaux2Mat.getDistanciadaOrigemPosicional(cont)<<endl;
// 				// cont ++;
// 			}
// 		}
// 	}

// 	PetscFinalize();
	
// }
TestCase( Ger_borda_Tpre_Tpre_1Mat )
{
	PetscInitialize(0,0,0,0);

	vector<int> Nptoscadamat;
	Nptoscadamat.push_back(4);

	int Nmalhas=1;

	int Ntestes = 6;
	vector<double> ErroMax;
	ErroMax.resize(Ntestes);
	for(int i=0;i<ErroMax.size();i++)
	{
		ErroMax[i] = 0;
	}

	vector<double> LarguraMat;
	LarguraMat.push_back(0.1);

	int TipoMalha = 1;

	vector<double>k;
	k.push_back(400);

	vector<double>Pre1;
	Pre1.push_back(373);

	vector<double>Pre2;
	Pre2.push_back(293);

	vector<int> TiposPre;
	TiposPre.push_back(1);
	TiposPre.push_back(1);

	//Escopo para 4 volumes
	{
		vector<double> Tgerente;
		vector<double> Tanalitica;
		Malha Malhaaux(Nptoscadamat,LarguraMat,1,1);
		GerenteVolumedeControle GVC(Nptoscadamat,Nmalhas,LarguraMat,TipoMalha,k,1,Pre1,Pre2,TiposPre,true);

		Tgerente = GVC.getCampoDeTemperaturas();


		Tanalitica.resize(Tgerente.size());
		vector<double> DistanciaDaOrigem;

		DistanciaDaOrigem = GVC.getDistanciaDaOrigem();

		string NomedoArquivo = "TabelasTrab4Analit1mat.csv";
		char NomedoArquivoChar[NomedoArquivo.length()+1];
		strcpy(NomedoArquivoChar,NomedoArquivo.c_str());
		ofstream myfile;
		myfile.open (NomedoArquivoChar);

		for(int i=0;i<Tgerente.size();i++)
		{
			Tanalitica[i] = (Pre2[0]-Pre1[0])*Malhaaux.getDistanciadaOrigemPosicional(i)/LarguraMat[0]+Pre1[0];
			checkClose(Tgerente[i],Tanalitica[i],1e-10);
			myfile<<Tanalitica[i]<<setprecision(17)<<","<<DistanciaDaOrigem[i]<<setprecision(17)<<"\n";
		}
		myfile.close();
		string Nome = "TabelasTrab4Simul1mat.csv";
		GVC.SalvaCampoDeTemperaturascsv(Nome);
	}
	string NomedoArquivo2 = "TabelasTrab4erroMAX1mat.csv";
	char NomedoArquivoChar2[NomedoArquivo2.length()+1];
	strcpy(NomedoArquivoChar2,NomedoArquivo2.c_str());
	ofstream myfile2;
	myfile2.open (NomedoArquivoChar2);
	for(int j=0;j<Ntestes;j++)
	{
		vector<double> Tgerente;
		vector<double> Tanalitica;

		Malha Malhaaux(Nptoscadamat,LarguraMat,1,1);
		GerenteVolumedeControle GVC(Nptoscadamat,Nmalhas,LarguraMat,TipoMalha,k,1,Pre1,Pre2,TiposPre,true);
		Tgerente = GVC.getCampoDeTemperaturas();
		Tanalitica.resize(Tgerente.size());

		vector<double>erro;
		erro.resize(Tgerente.size());
		for(int i=0;i<Tgerente.size();i++)
		{
			Tanalitica[i] = (Pre2[0]-Pre1[0])*Malhaaux.getDistanciadaOrigemPosicional(i)/LarguraMat[0]+Pre1[0];
			erro[i] = fabs(Tanalitica[i]-Tgerente[i])/Tgerente[i];
			if(ErroMax[j]<erro[i])
			{
				ErroMax[j]=erro[i];
			}
		}
		myfile2<<ErroMax[j]<<setprecision(17)<<","<<Nptoscadamat[0]<<setprecision(17)<<"\n";
		Nptoscadamat[0]=Nptoscadamat[0]*2;
	}
	myfile2.close();
}

TestCase( Ger_central_Qpre_Conv_Erro )
{
	PetscInitialize(0,0,0,0);
	vector<int> Nptoscadamat;
	Nptoscadamat.push_back(4);
	Nptoscadamat.push_back(4);

	int TotaldePontos=0;
	for(int i=0; i<Nptoscadamat.size(); i++)
	{
		TotaldePontos=TotaldePontos+Nptoscadamat[i];
	}

	int Nmalhas=2;

	int Ntestes = 6;
	vector<double> ErroMax;
	ErroMax.resize(Ntestes);
	for(int i=0;i<ErroMax.size();i++)
	{
		ErroMax[i] = 0;
	}

	vector<double> LarguraMat;
	LarguraMat.push_back(1);
	LarguraMat.push_back(0.5);

	int TipoMalha = 2;

	vector<double>k;
	k.push_back(400);
	k.push_back(200);

	vector<double>Pre1;
	Pre1.push_back(100);

	vector<double>Pre2;
	Pre2.push_back(290);
	Pre2.push_back(10);

	vector<int> TiposPre;
	TiposPre.push_back(2);
	TiposPre.push_back(3);

	vector<double>Tanalitica;
	Tanalitica.resize(TotaldePontos);

	Malha Malhaaux(Nptoscadamat,LarguraMat,Nmalhas,TipoMalha);


	double Ts2;
	double Ts0;
	Ts2=Pre1[0]/Pre2[1]+Pre2[0];
	Ts0=Pre1[0]*(LarguraMat[1]/k[1]+LarguraMat[0]/k[0])+Ts2;

	for(int i=0; i<TotaldePontos; i++)
	{
		if(i<Nptoscadamat[0])
		{
			Tanalitica[i]=Ts0-Pre1[0]*Malhaaux.getDistanciadaOrigemPosicional(i)/k[0];
		}
		else
		{
			Tanalitica[i]=Ts0+LarguraMat[0]*Pre1[0]*(1/k[1]-1/k[0])-Malhaaux.getDistanciadaOrigemPosicional(i)*Pre1[0]/k[1];
		}
	}
	//GRÁFICO DO CAMPO DE T Solução Analítica
	{
		string NomedoArquivo2 = "SolucaoAnalitica2Mat.csv";
		char NomedoArquivoChar2[NomedoArquivo2.length()+1];
		strcpy(NomedoArquivoChar2,NomedoArquivo2.c_str());
		ofstream myfile2;
		myfile2.open (NomedoArquivoChar2);
		for(int i=0; i<TotaldePontos; i++)
		{
			myfile2<<Tanalitica[i]<<setprecision(17)<<","<<Malhaaux.getDistanciadaOrigemPosicional(i)<<setprecision(17)<<"\n";
		}
		myfile2.close();
	}
	{
		GerenteVolumedeControle DoisMatQpreConvInterpDesalinhada(Nptoscadamat,Nmalhas,LarguraMat,TipoMalha,k,2,Pre1,Pre2,TiposPre,false);
		vector<double>Tsimulacao;
		Tsimulacao = DoisMatQpreConvInterpDesalinhada.getCampoDeTemperaturas();
		for(int i=0; i<TotaldePontos; i++)
		{
			checkClose(Tanalitica[i],Tsimulacao[i],1e-12);
		}
		//GRÁFICO DO CAMPO DE T DoisMatQpreConvInterpDesalinhada
		{
			string NomedoArquivo2 = "DoisMatQpreConvInterpDesalinhada.csv";
			char NomedoArquivoChar2[NomedoArquivo2.length()+1];
			strcpy(NomedoArquivoChar2,NomedoArquivo2.c_str());
			ofstream myfile2;
			myfile2.open (NomedoArquivoChar2);
			for(int i=0; i<TotaldePontos; i++)
			{
				myfile2<<Tsimulacao[i]<<setprecision(17)<<","<<Malhaaux.getDistanciadaOrigemPosicional(i)<<setprecision(17)<<"\n";
			}
			myfile2.close();
		}
	}
	{
		GerenteVolumedeControle DoisMatQpreConvResistDesalinhada(Nptoscadamat,Nmalhas,LarguraMat,TipoMalha,k,1,Pre1,Pre2,TiposPre,false);
		vector<double>Tsimulacao;
		Tsimulacao = DoisMatQpreConvResistDesalinhada.getCampoDeTemperaturas();
		for(int i=0; i<TotaldePontos; i++)
		{
			checkClose(Tanalitica[i],Tsimulacao[i],1e-2);
		}
		//GRÁFICO DE CAMPO DE T DoisMatQpreConvResistDesalinhada
		{
			string NomedoArquivo2 = "DoisMatQpreConvResistDesalinhada.csv";
			char NomedoArquivoChar2[NomedoArquivo2.length()+1];
			strcpy(NomedoArquivoChar2,NomedoArquivo2.c_str());
			ofstream myfile2;
			myfile2.open (NomedoArquivoChar2);
			for(int i=0; i<TotaldePontos; i++)
			{
				myfile2<<Tsimulacao[i]<<setprecision(17)<<","<<Malhaaux.getDistanciadaOrigemPosicional(i)<<setprecision(17)<<"\n";
			}
			myfile2.close();
		}
	}
	{
		GerenteVolumedeControle DoisMatQpreConvInterpAlinhada(Nptoscadamat,Nmalhas,LarguraMat,TipoMalha,k,2,Pre1,Pre2,TiposPre,true);
		vector<double>Tsimulacao;
		Tsimulacao = DoisMatQpreConvInterpAlinhada.getCampoDeTemperaturas();
		for(int i=0; i<TotaldePontos; i++)
		{
			checkClose(Tanalitica[i],Tsimulacao[i],1e-2);
		}
		//GRÁFICO DE Erro DE T DoisMatQpreConvInterpAlinhada
		{
			string NomedoArquivo2 = "ErroDoisMatQpreConvInterpAlinhada.csv";
			char NomedoArquivoChar2[NomedoArquivo2.length()+1];
			strcpy(NomedoArquivoChar2,NomedoArquivo2.c_str());
			ofstream myfile2;
			myfile2.open (NomedoArquivoChar2);
			for(int i=0; i<TotaldePontos; i++)
			{
				myfile2<<fabs((Tsimulacao[i]-Tanalitica[i])/Tanalitica[i])<<setprecision(17)<<","<<Malhaaux.getDistanciadaOrigemPosicional(i)<<setprecision(17)<<"\n";
			}
			myfile2.close();
		}
	}
	{
		GerenteVolumedeControle DoisMatQpreConvResistAlinhada(Nptoscadamat,Nmalhas,LarguraMat,TipoMalha,k,1,Pre1,Pre2,TiposPre,true);
		vector<double>Tsimulacao;
		Tsimulacao = DoisMatQpreConvResistAlinhada.getCampoDeTemperaturas();
		for(int i=0; i<TotaldePontos; i++)
		{
			checkClose(Tanalitica[i],Tsimulacao[i],1e-12);
		}
		//GRÁFICO DE ERRO DE T DoisMatQpreConvResistAlinhada
		{
			string NomedoArquivo2 = "ErroDoisMatQpreConvResistAlinhada.csv";
			char NomedoArquivoChar2[NomedoArquivo2.length()+1];
			strcpy(NomedoArquivoChar2,NomedoArquivo2.c_str());
			ofstream myfile2;
			myfile2.open (NomedoArquivoChar2);
			for(int i=0; i<TotaldePontos; i++)
			{
				myfile2<<fabs((Tsimulacao[i]-Tanalitica[i])/Tanalitica[i])<<setprecision(17)<<","<<Malhaaux.getDistanciadaOrigemPosicional(i)<<setprecision(17)<<"\n";
			}
			myfile2.close();
		}
	}
	{
		int NumeroDeTestes = 6;
		vector<double>TanaliticaVariavel;
		TanaliticaVariavel.resize(TotaldePontos);
		double ErroInterp;
		double ErroResist;
		vector<double> ErroMaxInterp;
		vector<double> ErroMaxResist;
		vector<double> NumeroDeVolumes;

		ErroMaxResist.resize(NumeroDeTestes);
		ErroMaxInterp.resize(NumeroDeTestes);
		NumeroDeVolumes.resize(NumeroDeTestes);

		for(int i=0;i<NumeroDeTestes;i++)
		{
			ErroMaxResist[i]=0;
			ErroMaxInterp[i]=0;
		}

		double Ts2;
		double Ts0;
		Ts2=Pre1[0]/Pre2[1]+Pre2[0];
		Ts0=Pre1[0]*(LarguraMat[1]/k[1]+LarguraMat[0]/k[0])+Ts2;

		vector<int>NptoscadamatVariavel;
		NptoscadamatVariavel.push_back(2);
		NptoscadamatVariavel.push_back(2);

		for(int i=0; i<NumeroDeTestes; i++)
		{	
			NptoscadamatVariavel[0] = NptoscadamatVariavel[0]*2;
			NptoscadamatVariavel[1] = NptoscadamatVariavel[1]*2;

			NumeroDeVolumes[i] = NptoscadamatVariavel[0];

			GerenteVolumedeControle DoisMatQpreConvInterpAlinhada(NptoscadamatVariavel,Nmalhas,LarguraMat,TipoMalha,k,2,Pre1,Pre2,TiposPre,true);
			vector<double>TsimulacaoInterp;
			TsimulacaoInterp = DoisMatQpreConvInterpAlinhada.getCampoDeTemperaturas();

			GerenteVolumedeControle DoisMatQpreConvResistAlinhada(NptoscadamatVariavel,Nmalhas,LarguraMat,TipoMalha,k,1,Pre1,Pre2,TiposPre,true);
			vector<double>TsimulacaoResist;
			TsimulacaoResist = DoisMatQpreConvResistAlinhada.getCampoDeTemperaturas();


			Malha MalhaauxVariavel(NptoscadamatVariavel,LarguraMat,Nmalhas,TipoMalha);
			for(int j=0; j<NptoscadamatVariavel[0]+NptoscadamatVariavel[1];j++)
			{
				if(i<NptoscadamatVariavel[0])
				{
					TanaliticaVariavel[i]=Ts0-Pre1[0]*MalhaauxVariavel.getDistanciadaOrigemPosicional(i)/k[0];
				}
				else
				{
					TanaliticaVariavel[i]=Ts0+LarguraMat[0]*Pre1[0]*(1/k[1]-1/k[0])-MalhaauxVariavel.getDistanciadaOrigemPosicional(i)*Pre1[0]/k[1];
				}
			}
			ErroInterp = fabs((TanaliticaVariavel[i]-TsimulacaoInterp[i])/TanaliticaVariavel[i]);
			ErroResist = fabs((TanaliticaVariavel[i]-TsimulacaoResist[i])/TanaliticaVariavel[i]);
			if(ErroInterp>ErroMaxInterp[i])
			{
				ErroMaxInterp[i]=ErroInterp;
			}
			if(ErroResist>ErroMaxResist[i])
			{
				ErroMaxResist[i]=ErroResist;
			}
		}
		{
			string NomedoArquivo2 = "ErroMaxDoisMatQpreConvInterpAlinhada.csv";
			char NomedoArquivoChar2[NomedoArquivo2.length()+1];
			strcpy(NomedoArquivoChar2,NomedoArquivo2.c_str());
			ofstream myfile2;
			myfile2.open (NomedoArquivoChar2);
			for(int i=0; i<NumeroDeTestes; i++)
			{
				myfile2<<ErroMaxInterp[i]<<setprecision(17)<<","<<NumeroDeVolumes[i]<<setprecision(17)<<"\n";
			}
			myfile2.close();
		}
		{
			string NomedoArquivo2 = "ErroMaxDoisMatQpreConvResistAlinhada.csv";
			char NomedoArquivoChar2[NomedoArquivo2.length()+1];
			strcpy(NomedoArquivoChar2,NomedoArquivo2.c_str());
			ofstream myfile2;
			myfile2.open (NomedoArquivoChar2);
			for(int i=0; i<NumeroDeTestes; i++)
			{
				myfile2<<ErroMaxResist[i]<<setprecision(17)<<","<<NumeroDeVolumes[i]<<setprecision(17)<<"\n";
			}
			myfile2.close();
		}
	}
	PetscFinalize();
}