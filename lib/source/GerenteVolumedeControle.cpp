#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <math.h>

#include "Malha.h"
#include "PropriedadeTermica.h"
#include "CondicoesdeContorno.h"
#include "SolverLinear.h"
#include "GerenteVolumedeControle.h"
#include "CriteriodeParada.h"

using namespace std;

GerenteVolumedeControle::GerenteVolumedeControle(vector<int>Nptoscadamat,int Nmalhas,vector<double>LarguraMat,int TipoMalha,vector<double>k,int TipoDeKinterface,vector<double>Pre1,vector<double>Pre2,vector<int>TiposPre,bool DeltinhaTrueRealFalseMedio,bool kpolinomial):
malhaPolinomial(Nptoscadamat,LarguraMat,Nmalhas,TipoMalha),  propriedadetermicaPolinomial(k,Nptoscadamat)
{
	Malha malha1(Nptoscadamat,LarguraMat,Nmalhas,TipoMalha);
	this->DistanciaDaOrigem = malha1.getDistanciadaOrigem();

	int TotaldePontos;
	double LarguraTotal;
	LarguraTotal = ContaLarguraTotal(LarguraMat);
	TotaldePontos = ContaTotaldePontos(Nptoscadamat, Nmalhas);

	if( kpolinomial == false)
	{
		PropriedadeTermica propriedadetermica1(k,Nptoscadamat);
		SalvaTodok(propriedadetermica1, TotaldePontos);

		vector<vector<double> >A;
		vector<double>b;
		double kinterface1;
		
		vector<double> ksobredeltaexterno;
		ksobredeltaexterno=Montaksobredeltaexterno(malha1, propriedadetermica1, LarguraTotal, TotaldePontos);

		vector<double> ksobredeltamarginalinterno;

		ksobredeltamarginalinterno = Montaksobredeltamarginalinterno(malha1,propriedadetermica1,LarguraTotal,TotaldePontos,DeltinhaTrueRealFalseMedio,TipoDeKinterface);

		CondicoesdeContorno condicoesdecontorno1(Pre1,Pre2,TiposPre,TipoMalha,ksobredeltaexterno,ksobredeltamarginalinterno);

		A=MontaMatrizA(malha1,propriedadetermica1,condicoesdecontorno1,TotaldePontos,DeltinhaTrueRealFalseMedio,TipoDeKinterface);
		b=MontaVetorb(condicoesdecontorno1,TotaldePontos);
		
		SolverLinear solucionador(A,b,TotaldePontos);
		this->CampoDeTemperaturas = solucionador.getCampodeTemperaturas();
	}
	else
	{
		cout<<endl<<endl<<"Favor, setar kpolinomial, Temperaturas estimadas, limite de iterações e critério de parada em SetVariaveisPolinomiais."<<endl<<endl;

		this->LarguraTotal = LarguraTotal;
		this->TotaldePontos = TotaldePontos;
		this->DeltinhaTrueRealFalseMedio = DeltinhaTrueRealFalseMedio;
		this->TipoDeKinterface = TipoDeKinterface;
		this->Pre1 = Pre1;
		this->Pre2 = Pre2;
		this->TiposPre = TiposPre;
		this->TipoMalha = TipoMalha;
	}
}
int GerenteVolumedeControle::getNumerodeIteracoes()
{
	return(this->NumerodeIteracoes);
}
vector<double> GerenteVolumedeControle::getkEmTodosPontos()
{
	return(this->k_TodosPontos);
}
vector<double> GerenteVolumedeControle::getkinterface_TodosPontos()
{
	return(this->kinterface_TodosPontos);
}
void GerenteVolumedeControle::SalvaTodok(PropriedadeTermica propriedadetermica,int TotaldePontos)
{
	this->k_TodosPontos.resize(TotaldePontos);
	for(int i=0; i<TotaldePontos; i++)
	{
		this->k_TodosPontos[i]=propriedadetermica.getk(i);
	}
}
void GerenteVolumedeControle::SetVariaveisPolinomiais(vector<vector<double> >kpolinomial, vector<double>Tinicial, int iteracoesMax, double CriterioParada)
{
	this->CampoDeTemperaturas = Tinicial;
	this->propriedadetermicaPolinomial.setTemperaturas(Tinicial);
	this->propriedadetermicaPolinomial.setkPolinomial(kpolinomial);
	this->iteracoesMax = iteracoesMax;
	this->CriterioParada = CriterioParada;
	CalculaT();
	SalvaTodok(propriedadetermicaPolinomial,this->TotaldePontos);
}
void GerenteVolumedeControle::CalculaT()
{
	double ErroMax = this->CriterioParada+1;
	int NumerodeIteracoes = 0;
	vector<double> Tanterior = this->CampoDeTemperaturas;
	while(this->CriterioParada<ErroMax && this->iteracoesMax>NumerodeIteracoes)
	{
		vector<vector<double> >A;
		vector<double>b;
		double kinterface1;
		
		vector<double> ksobredeltaexterno;
		ksobredeltaexterno=Montaksobredeltaexterno(this->malhaPolinomial,this->propriedadetermicaPolinomial,this->LarguraTotal,this->TotaldePontos);

		vector<double> ksobredeltamarginalinterno;

		ksobredeltamarginalinterno = Montaksobredeltamarginalinterno(this->malhaPolinomial,this->propriedadetermicaPolinomial,this->LarguraTotal,this->TotaldePontos,this->DeltinhaTrueRealFalseMedio,this->TipoDeKinterface);

		CondicoesdeContorno condicoesdecontorno1(this->Pre1,this->Pre2,this->TiposPre,this->TipoMalha,ksobredeltaexterno,ksobredeltamarginalinterno);

		A=MontaMatrizA(this->malhaPolinomial,this->propriedadetermicaPolinomial,condicoesdecontorno1,this->TotaldePontos,this->DeltinhaTrueRealFalseMedio,this->TipoDeKinterface);
		b=MontaVetorb(condicoesdecontorno1,this->TotaldePontos);
		
		SolverLinear solucionador(A,b,this->TotaldePontos);
		this->CampoDeTemperaturas = solucionador.getCampodeTemperaturasTDMA();
		this->propriedadetermicaPolinomial.setTemperaturas(this->CampoDeTemperaturas);

		ErroMax = fabs(Tanterior[0]-CampoDeTemperaturas[0]);
		for(int i = 1; i<CampoDeTemperaturas.size(); i++)
		{
			if(ErroMax<fabs(Tanterior[i]-CampoDeTemperaturas[i]))
			{
				ErroMax = fabs(Tanterior[i]-CampoDeTemperaturas[i]); 
			}
		}
		NumerodeIteracoes++;
		Tanterior = this->CampoDeTemperaturas;

		// for(int i=0; i<this->TotaldePontos; i++)
		// {
		// 	cout<<endl<<"T["<<i<<"]="<<CampoDeTemperaturas[i]<<endl;
		// }
	}
	this->NumerodeIteracoes = NumerodeIteracoes;
}
void GerenteVolumedeControle::ImprimeMatriz(vector<vector<double> >A,vector<double>b, int TotaldePontos)
{
	cout<<endl<<endl<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
	for(int i=0; i<TotaldePontos; i++)
	{
		for(int j=0; j<TotaldePontos; j++)
		{
			cout<<A[i][j]<<"	";
		}
		cout<<"	|"<<b[i]<<endl;
	}
}
vector<vector<double> > GerenteVolumedeControle::MontaMatrizA(Malha malha1,PropriedadeTermica propriedadetermica1, CondicoesdeContorno condicoesdecontorno1, int TotaldePontos,bool DeltinhaTrueRealFalseMedio,int TipoDeKinterface)
{
	vector<vector<double> >A;
	A = CriaMatrizQuadradadeNulos(TotaldePontos);
	double kinterface1;
	double kinterface2;
	A[0][0] = condicoesdecontorno1.getPrimeiroTermodeEntrada();
	A[0][1] = condicoesdecontorno1.getSegundoTermodeEntrada();

	A[TotaldePontos-1][TotaldePontos-1-1] = condicoesdecontorno1.getPrimeiroTermodeSaida();
	A[TotaldePontos-1][TotaldePontos-1] = condicoesdecontorno1.getSegundoTermodeSaida();
	

	// cout<<endl<<endl<<"++++++++++++++++++++++++++++++MALHA+++++++++++++++++++++++++"<<endl;
	// cout<<A[0][0]<<"		"<<A[0][1]<<"		"<<b[0]<<endl;

	if(TotaldePontos>2)
	{
		for(int i=1; i<TotaldePontos-1;i++)
		{
			kinterface2 = getkInterface(malha1.getdelta_e(i),malha1.getDelta_e_Mais(i,DeltinhaTrueRealFalseMedio),malha1.getDelta_e_Menos(i,DeltinhaTrueRealFalseMedio),propriedadetermica1.getk(i+1),propriedadetermica1.getk(i),TipoDeKinterface);
			kinterface1 = getkInterface(malha1.getdelta_w(i),malha1.getDelta_w_Mais(i,DeltinhaTrueRealFalseMedio),malha1.getDelta_w_Menos(i,DeltinhaTrueRealFalseMedio),propriedadetermica1.getk(i),propriedadetermica1.getk(i-1),TipoDeKinterface);
			this->kinterface_TodosPontos.resize(TotaldePontos-1);
			this->kinterface_TodosPontos[i-1] = kinterface1;
			A[i][i-1] = -kinterface1/malha1.getdelta_w(i);
			A[i][i] = (kinterface1/malha1.getdelta_w(i)+kinterface2/malha1.getdelta_e(i));
			A[i][i+1] = -kinterface2/malha1.getdelta_e(i);
			// cout<<"------------------i="<<i<<"---------------"<<endl;
			// cout<<A[i][i-1]<<"		"<<A[i][i]<<"		"<<A[i][i-1]<<endl;
			// cout<<kinterface1<<"	"<<kinterface2<<endl;
			// cout<<malha1.getdelta_w(i)<<"	"<<malha1.getDelta_w_Mais(i,DeltinhaTrueRealFalseMedio)<<"	"<<malha1.getDelta_w_Menos(i,DeltinhaTrueRealFalseMedio)<<endl;
		}
		// cout<<A[TotaldePontos-1][TotaldePontos-2]<<"		"<<setprecision(10)<<A[TotaldePontos-1][TotaldePontos-1]<<"		"<<b[TotaldePontos-1]<<endl;
	}
	return(A);
}
vector<double> GerenteVolumedeControle::MontaVetorb(CondicoesdeContorno condicoesdecontorno1, int TotaldePontos)
{
	vector<double> b;
	b = CriaVetordeNulos(TotaldePontos);
	b[0] = condicoesdecontorno1.getTerceiroTermodeEntrada();
	b[TotaldePontos-1] = condicoesdecontorno1.getTerceiroTermodeSaida();
	return(b);
}
vector<double> GerenteVolumedeControle::Montaksobredeltaexterno(Malha malha1, PropriedadeTermica propriedadetermica1, double LarguraTotal, int TotaldePontos)
{
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
		ksobredeltaexterno[1] = propriedadetermica1.getk(TotaldePontos-1)/(LarguraTotal - malha1.getDistanciadaOrigemPosicional(TotaldePontos-1));
	}
	return(ksobredeltaexterno);
}
vector<double> GerenteVolumedeControle::Montaksobredeltamarginalinterno(Malha malha1, PropriedadeTermica propriedadetermica1, double LarguraTotal, int TotaldePontos, bool DeltinhaTrueRealFalseMedio, int TipoDeKinterface)
{
	double kinterface1;
	vector<double> ksobredeltamarginalinterno;
	ksobredeltamarginalinterno.resize(2);
	kinterface1 = getkInterface(malha1.getdelta_e(0),malha1.getDelta_e_Mais(0,DeltinhaTrueRealFalseMedio),malha1.getDelta_e_Menos(0,DeltinhaTrueRealFalseMedio),propriedadetermica1.getk(1),propriedadetermica1.getk(0),TipoDeKinterface);
	ksobredeltamarginalinterno[0] = kinterface1/malha1.getdelta_e(0);

	kinterface1 = getkInterface(malha1.getdelta_e(TotaldePontos-1-1),malha1.getDelta_e_Mais(TotaldePontos-1-1,DeltinhaTrueRealFalseMedio),malha1.getDelta_e_Menos(TotaldePontos-1-1,DeltinhaTrueRealFalseMedio),propriedadetermica1.getk(TotaldePontos-1),propriedadetermica1.getk(TotaldePontos-1-1),TipoDeKinterface);
	ksobredeltamarginalinterno[1] = kinterface1/malha1.getdelta_w(TotaldePontos-1);
	return (ksobredeltamarginalinterno);
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
vector<double> GerenteVolumedeControle::getDistanciaDaOrigem()
{
	return(this->DistanciaDaOrigem);
}
void GerenteVolumedeControle::SalvaCampoDeTemperaturascsv(string NomedoArquivo)
{
	ofstream myfile;
	myfile.open (NomedoArquivo.c_str());
	for(int i=0; i<this->CampoDeTemperaturas.size(); i++)
	{
			myfile<<this->CampoDeTemperaturas[i]<<setprecision(17)<<","<<this->DistanciaDaOrigem[i]<<setprecision(17)<<"\n";
	}
	myfile.close();
}
void GerenteVolumedeControle::SalvaDoisVetorescsv(string NomedoArquivo, vector<double> V1, vector<double> V2)
{
	if(V1.size()==V2.size())
	{
		ofstream myfile;
		myfile.open (NomedoArquivo.c_str());
		for(int i=0; i<V1.size(); i++)
		{
				myfile<<V1[i]<<setprecision(17)<<","<<V2[i]<<setprecision(17)<<"\n";
		}
		myfile.close();
	}
	else
	{
		cout<<endl<<endl<<"PROBLEMA! Vetores a serem salvos nao possuem mesma dimensao!"<<endl<<endl;
	}
}
int GerenteVolumedeControle::ContaTotaldePontos(vector<int> Nptoscadamat, int Nmalhas)
{
	int TotaldePontos=0;
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
double GerenteVolumedeControle::ContaLarguraTotal(vector<double>LarguraMat)
{
	double LarguraTotal=0;
	for(int i = 0; i<LarguraMat.size(); i++)
	{
		LarguraTotal = LarguraTotal + LarguraMat[i];
	}
	return(LarguraTotal);
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
	cout<<"Tipo Função k=k(T):"<<endl;
	cout<<"1-k=constantes"<<endl;
	cout<<"2-k=A1+A2T+A3T^2+...+AnT^(n-1) | ATENÇÃO! Neste caso, o vetor ou matriz (quando mais de um material) k deve ter k=[A1 A2 A3 ... An]"<<endl;
	cout<<"e ser setado pela funcao correspondente."<<endl<<endl;
	cout<<"Tipos de Prescricao"<<endl;
	cout<<"1-Temperatura Prescrita"<<endl;
	cout<<"2-Fluxo de Calor Prescrito"<<endl;
	cout<<"3-Temperatura do fluido e Coeficiente de Conveccao Prescritos"<<endl<<endl;
	cout<<"Ordens de Prescricao nos vetores Pre:"<<endl;
	cout<<"[Temperatura ou Fluxo,Coeficiente de Conveccao]"<<endl<<endl;
	cout<<"Alinhamento da malha com relação à interface de troca de materiais:"<<endl<<endl;
	cout<<"DeltinhaTrueRealFalseMedio=true:Alinhada"<<endl;
	cout<<"DeltinhaTrueRealFalseMedio=false: Desalinhada"<<endl<<endl;
	cout<<"Coeficiente de condução k como polinomio:"<<endl;
	cout<<"kpolinomial=true: Polinomio"<<endl;
	cout<<"kpolinomial=false: Constante"<<endl<<endl;
	cout<<"----------------------------------------------------------------------------------------"<<endl<<endl;
}