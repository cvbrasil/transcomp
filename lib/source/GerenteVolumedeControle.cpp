#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstring>

#include "Malha.h"
#include "PropriedadeTermica.h"
#include "CondicoesdeContorno.h"
#include "SolverLinear.h"
#include "GerenteVolumedeControle.h"

using namespace std;

GerenteVolumedeControle::GerenteVolumedeControle(vector<int>Nptoscadamat,int Nmalhas,vector<double>LarguraMat,int TipoMalha,vector<double>k,int TipoDeKinterface,vector<double>Pre1,vector<double>Pre2,vector<int>TiposPre)
{
	Malha malha1(Nptoscadamat,LarguraMat,Nmalhas,TipoMalha);
	PropriedadeTermica propriedadetermica1(k,Nptoscadamat);

	int TotaldePontos;
	vector<vector<double> >A;
	vector<double>b;
	double kinterface1;
	double kinterface2;

	double delta_e;
	double delta_e_Menos;
	double delta_e_Mais;
	double kmais_e;
	double kmenos_e;

	double delta_w;
	double delta_w_Menos;
	double delta_w_Mais;
	double kmais_w;
	double kmenos_w;

	TotaldePontos = ContaTotaldePontos(Nptoscadamat, Nmalhas);

	b = CriaVetordeNulos(TotaldePontos);
	A = CriaMatrizQuadradadeNulos(TotaldePontos);
	
	vector<double> ksobredeltaexterno;
	ksobredeltaexterno.resize(2);
	if(malha1.getDistanciadaOrigemPosicional(0)==0)
	{
		ksobredeltaexterno[0] = 0;
	}
	else
	{
		ksobredeltaexterno[0] = propriedadetermica1.getk(0)/malha1.getDistanciadaOrigemPosicional(0);
	}
	if(malha1.getDistanciadaOrigemPosicional(TotaldePontos-1)==0)
	{
		ksobredeltaexterno[1] = 0;
	}
	else
	{
		ksobredeltaexterno[1] = propriedadetermica1.getk(TotaldePontos-1)/malha1.getDistanciadaOrigemPosicional(TotaldePontos-1);
	}
	

	vector<double> ksobredeltamarginalinterno;
	ksobredeltamarginalinterno.resize(2);
	kinterface1 = getkInterface(malha1.getdelta_e(0),malha1.getDelta_e_Mais(0),malha1.getDelta_e_Menos(0),propriedadetermica1.getk(1),propriedadetermica1.getk(0),TipoDeKinterface);
	ksobredeltamarginalinterno[0] = kinterface1/malha1.getdelta_e(0);

	kinterface1 = getkInterface(malha1.getdelta_e(TotaldePontos-1-1),malha1.getDelta_e_Mais(TotaldePontos-1-1),malha1.getDelta_e_Menos(TotaldePontos-1-1),propriedadetermica1.getk(TotaldePontos-1),propriedadetermica1.getk(TotaldePontos-1-1),TipoDeKinterface);
	ksobredeltamarginalinterno[1] = kinterface1/malha1.getdelta_w(TotaldePontos-1);

	CondicoesdeContorno condicoesdecontorno1(Pre1,Pre2,TiposPre,TipoMalha,ksobredeltaexterno,ksobredeltamarginalinterno);

	A[0][0] = condicoesdecontorno1.getPrimeiroTermodeEntrada();
	A[0][1] = condicoesdecontorno1.getSegundoTermodeEntrada();
	b[0] = condicoesdecontorno1.getTerceiroTermodeEntrada();

	A[TotaldePontos-1][TotaldePontos-1-1] = condicoesdecontorno1.getPrimeiroTermodeSaida();
	A[TotaldePontos-1][TotaldePontos-1] = condicoesdecontorno1.getSegundoTermodeSaida();
	b[TotaldePontos-1] = condicoesdecontorno1.getTerceiroTermodeSaida();

	if(TotaldePontos>2)
	{
		for(int i=1; i<TotaldePontos-1;i++)
		{
			kinterface2 = getkInterface(malha1.getdelta_e(i),malha1.getDelta_e_Mais(i),malha1.getDelta_e_Menos(i),propriedadetermica1.getk(i+1),propriedadetermica1.getk(i),TipoDeKinterface);
			kinterface1 = getkInterface(malha1.getdelta_w(i),malha1.getDelta_w_Mais(i),malha1.getDelta_w_Menos(i),propriedadetermica1.getk(i),propriedadetermica1.getk(i-1),TipoDeKinterface);
			A[i][i-1] = -kinterface1/malha1.getdelta_e(i);
			A[i][i] = (kinterface1/malha1.getdelta_e(i)+kinterface2/malha1.getdelta_w(i));
			A[i][i+1] = -kinterface2/malha1.getdelta_w(i);
		}
	}
	

	SolverLinear solucionador(A,b,TotaldePontos);
	this->CampoDeTemperaturas = solucionador.getCampodeTemperaturas();
}
double GerenteVolumedeControle::getkInterface(double delta, double delta_Mais, double delta_Menos, double kmais, double kmenos, int TipoDeKinterface)
{
	if(TipoDeKinterface==1)
	{
		return(delta/(delta_Mais/kmais+delta_Menos/kmenos));
	}
	else
	{
		if(TipoDeKinterface==2)
		{
			return((kmenos*delta_Menos+kmais*delta_Mais)/delta);
		}
		else
		{
			cout<<endl<<"Problema! Tipo de K da Interface inexistente. 1-Resistencia equivalente; 2-Interpolacao Linear"<<endl<<endl;
		}
	}
}
vector<double> GerenteVolumedeControle::getCampoDeTemperaturas()
{
	return(this->CampoDeTemperaturas);
}
void GerenteVolumedeControle::SalvaCampoDeTemperaturascsv(string NomedoArquivo)
{
	char NomedoArquivoChar[NomedoArquivo.length()+1];
	strcpy(NomedoArquivoChar,NomedoArquivo.c_str());
	ofstream myfile;
	myfile.open (NomedoArquivoChar);
	for(int i=0; i<this->CampoDeTemperaturas.size(); i++)
	{
			myfile<<this->CampoDeTemperaturas[i]<<endl;
	}
	myfile.close();
}
int GerenteVolumedeControle::ContaTotaldePontos(vector<int> Nptoscadamat, int Nmalhas)
{
	int TotaldePontos;
	for(int i=0;i<Nmalhas;i++)
	{
		TotaldePontos = TotaldePontos + Nptoscadamat[i];
	}
	return(TotaldePontos);
}
vector<double> GerenteVolumedeControle::CriaVetordeNulos(int NumerodePontos)
{
	vector<double> b;
	b.resize(NumerodePontos);
	for(int i=0;i<NumerodePontos;i++)
	{
		b[i] = 0;
	}
	return(b);
}
vector<vector<double> > GerenteVolumedeControle::CriaMatrizQuadradadeNulos(int NumerodePontos)
{
	vector<vector<double> >A;
	A.resize(NumerodePontos);
	for(int i=0;i<NumerodePontos;i++)
	{
		A[i].resize(NumerodePontos);
		for(int j=0;j<NumerodePontos;j++)
		{
			A[i][j] = 0;
		}
	}
	return(A);
}
void GerenteVolumedeControle::MostraTiposdeConfiguracao()
{
	cout<<endl<<"----------------------------------------------------------------------------------------"<<endl;
	cout<<"-------------------------------------Como Configurar------------------------------------"<<endl;
	cout<<"----------------------------------------------------------------------------------------"<<endl<<endl;
	cout<<"Tipo de Malha:"<<endl;
	cout<<"1-Pontos iniciais e finais nas bordas dos Volumes de Controle"<<endl;
	cout<<"2-Pontos centrados nos Volumes de Controle"<<endl;
	cout<<"3-Ponto inicial na borda e final no centro"<<endl;
	cout<<"4-Ponto inicial no centro e final da borda"<<endl<<endl;
	cout<<"Tipo de k da Interface:"<<endl;
	cout<<"1-Pela Resistencia Equivalente"<<endl;
	cout<<"2-Pela Interpolacao Linear"<<endl<<endl;
	cout<<"Tipos de Prescricao"<<endl;
	cout<<"1-Temperatura Prescrita"<<endl;
	cout<<"2-Fluxo de Calor Prescrito"<<endl;
	cout<<"3-Temperatura do fluido e Coeficiente de Conveccao Prescritos"<<endl<<endl;
	cout<<"Ordens de Prescricao nos vetores Pre:"<<endl;
	cout<<"[Temperatura/Fluxo,Coeficiente de Conveccao"<<endl<<endl;
}