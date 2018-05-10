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

GerenteVolumedeControle::GerenteVolumedeControle(vector<int>Nptoscadamat,int Nmalhas,vector<double>LarguraMat,int TipoMalha,vector<double>k,int TipoDeKinterface,vector<double>Pre1,vector<double>Pre2,vector<int>TiposPre,bool DeltinhaTrueRealFalseMedio,int caso,int TipoDeCriterio):
malhaPolinomial(Nptoscadamat,LarguraMat,Nmalhas,TipoMalha),  propriedadetermicaPolinomial(k,Nptoscadamat)
{
	Malha malha1(Nptoscadamat,LarguraMat,Nmalhas,TipoMalha);
	this->DistanciaDaOrigem = malha1.getDistanciadaOrigem();

	int TotaldePontos;
	double LarguraTotal;
	LarguraTotal = ContaLarguraTotal(LarguraMat);
	TotaldePontos = ContaTotaldePontos(Nptoscadamat, Nmalhas);

	if( caso == 0)
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
		this->LarguraTotal = LarguraTotal;
		this->TotaldePontos = TotaldePontos;
		this->DeltinhaTrueRealFalseMedio = DeltinhaTrueRealFalseMedio;
		this->TipoDeKinterface = TipoDeKinterface;
		this->Pre1 = Pre1;
		this->Pre2 = Pre2;
		this->TiposPre = TiposPre;
		this->TipoMalha = TipoMalha;
		this->TipoDeCriterio = TipoDeCriterio;
		if(caso == 1)
		{
			cout<<endl<<endl<<"Favor, setar kpolinomial, Temperaturas estimadas, limite de iterações e critério de parada em SetVariaveisPolinomiais."<<endl<<endl;		
		}
		else
		{
			if(caso == 2)
			{
				cout<<endl<<endl<<"Favor, setar ro, Cp, Temperaturas iniciais, limite de iteracoes e critério de parada em SetVariaveisTransiente."<<endl<<endl;
			}
			else
			{
				if(caso == 3)
				{
					cout<<endl<<endl<<"Favor, setar objetos Malha em SetVariaveisBidimensionais."<<endl<<endl;
				}
			}
		}
	}
}
vector<double> GerenteVolumedeControle::getFluxoTermico()
{
	vector<double> FluxoTermico;
	FluxoTermico.resize(TotaldePontos-1);
	for(int i=0;i<this->TotaldePontos-1;i++)
	{
		FluxoTermico[i]=-kinterface_TodosPontos[i]*(CampoDeTemperaturas[i+1]-CampoDeTemperaturas[i])/(malhaPolinomial.getdelta_e(i));
	}
	this->kinterface_TodosPontos;
	this->CampoDeTemperaturas;
	return(FluxoTermico);
}
double GerenteVolumedeControle::getErroIterativo()
{
	return(this->ErroDeParada);
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
vector<vector<double> > GerenteVolumedeControle::getTemperaturasTransiente()
{
	return(this->CampoDeTemperaturasTransiente);
}
void GerenteVolumedeControle::SalvaTodok(PropriedadeTermica propriedadetermica,int TotaldePontos)
{
	this->k_TodosPontos.resize(TotaldePontos);
	for(int i=0; i<TotaldePontos; i++)
	{
		this->k_TodosPontos[i]=propriedadetermica.getk(i);
	}
}
void GerenteVolumedeControle::SetVariaveisBidimensionais(Malha malhaVertical,PropriedadeTermica propriedadetermicaV,vector<double> Pre1V,vector<double> Pre2V,vector<int> TiposPreV,double LarguraTotalV,double TotaldePontosV,int TipoMalhaV)
{
	this->Pre1V = Pre1V;
	this->Pre2V = Pre2V;
	this->TiposPreV = TiposPreV;
	this->LarguraTotalV = LarguraTotalV;
	this->TotaldePontosV = TotaldePontosV;
	this->TipoMalhaV = TipoMalhaV;
	CalculaTBidimensional(malhaVertical,propriedadetermicaV);
}
void GerenteVolumedeControle::SetVariaveisPolinomiais(vector<vector<double> >kpolinomial, vector<double>Tinicial, int iteracoesMax, double CriterioParada)
{
	this->CampoDeTemperaturas = Tinicial;
	this->propriedadetermicaPolinomial.setTemperaturas(Tinicial);
	this->propriedadetermicaPolinomial.setkPolinomial(kpolinomial);
	this->iteracoesMax = iteracoesMax;
	this->CriterioParada = CriterioParada;
	CalculaTpolinomial();
	SalvaTodok(propriedadetermicaPolinomial,this->TotaldePontos);
}
void GerenteVolumedeControle::SetVariaveisTransiente(double ro, double Cp, vector<double>Tinicial, int iteracoesMax, double CriterioParada, double PassoDeTempo, double f)
{
	this->Tinicial = Tinicial;
	this->iteracoesMax = iteracoesMax;
	this->CriterioParada = CriterioParada;
	this->ro = ro;
	this->Cp = Cp;
	this->PassoDeTempo = PassoDeTempo;
	if(f==0)
	{
		CalculaTtransienteExplicito();
	}
	if(f>=1-1e-13)
	{
		CalculaTtransienteImplicito();
	}
}
void GerenteVolumedeControle::setCoeficientesCosTpreTransiente(double DeslocaY, double Amplitude, double Frequencia, double DeslocaX, int QualExtremo)
{
	if(QualExtremo==1)
	{
		this->DeslocaY1 = DeslocaY;
		this->Amplitude1 = Amplitude;
		this->Frequencia1 = Frequencia;
		this->DeslocaX1 = DeslocaX;
		this->FlagCoefCosSetado1 = true;
	}
	if(QualExtremo==2)
	{
		this->DeslocaY2 = DeslocaY;
		this->Amplitude2 = Amplitude;
		this->Frequencia2 = Frequencia;
		this->DeslocaX2 = DeslocaX;
		this->FlagCoefCosSetado2 = true;
	}
}
void GerenteVolumedeControle::setVariaveisCilindricas(double RaioInterno)
{
	this->RaioInterno = RaioInterno;
	this->IndicaCoordenadaCilindrica = 1;
}
void GerenteVolumedeControle::CalculaTBidimensional(Malha malhaVertical,PropriedadeTermica propriedadetermicaV)
{	
	vector<vector<double> >AH;
	vector<double>bH;
	vector<vector<double> >AV;
	vector<double>bV;
	vector<vector<double> >A;
	vector<double> b;
	double kinterface1;
	//HORIZONTAL
	vector<double> ksobredeltaexterno;
	ksobredeltaexterno=Montaksobredeltaexterno(this->malhaPolinomial,this->propriedadetermicaPolinomial,this->LarguraTotal,this->TotaldePontos);
	vector<double> ksobredeltamarginalinterno;
	ksobredeltamarginalinterno = Montaksobredeltamarginalinterno(this->malhaPolinomial,this->propriedadetermicaPolinomial,this->LarguraTotal,this->TotaldePontos,this->DeltinhaTrueRealFalseMedio,this->TipoDeKinterface);
	CondicoesdeContorno condicoesdecontornoH(this->Pre1,this->Pre2,this->TiposPre,this->TipoMalha,ksobredeltaexterno,ksobredeltamarginalinterno);
	//VERTICAL
	ksobredeltaexterno=Montaksobredeltaexterno(malhaVertical,propriedadetermicaV,this->LarguraTotalV,this->TotaldePontosV);
	ksobredeltamarginalinterno = Montaksobredeltamarginalinterno(malhaVertical,propriedadetermicaV,this->LarguraTotalV,this->TotaldePontosV,this->DeltinhaTrueRealFalseMedio,this->TipoDeKinterface);
	CondicoesdeContorno condicoesdecontornoV(this->Pre1V,this->Pre2V,this->TiposPreV,this->TipoMalhaV,ksobredeltaexterno,ksobredeltamarginalinterno);

	AH=MontaMatrizA(this->malhaPolinomial,this->propriedadetermicaPolinomial,condicoesdecontornoH,this->TotaldePontos,this->DeltinhaTrueRealFalseMedio,this->TipoDeKinterface);
	bH=MontaVetorb(condicoesdecontornoH,this->TotaldePontos);

	// cout<<endl<<endl<<endl<<"++++++++++++++++++++++++++++++MATRIZH+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
	// for(int i=0; i<this->TotaldePontos; i++)
	// {
	// 	for(int j=0; j<this->TotaldePontos; j++)
	// 	{
	// 		cout<<AH[i][j]<<setw(9);
	// 	}
	// 	cout<<"|"<<bH[i]<<endl;
	// }

	AV=MontaMatrizA(malhaVertical,propriedadetermicaV,condicoesdecontornoV,this->TotaldePontosV,this->DeltinhaTrueRealFalseMedio,this->TipoDeKinterface);
	bV=MontaVetorb(condicoesdecontornoV,this->TotaldePontosV);

	// cout<<endl<<endl<<endl<<"++++++++++++++++++++++++++++++MATRIZV+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
	// for(int i=0; i<TotaldePontosV; i++)
	// {
	// 	for(int j=0; j<TotaldePontosV; j++)
	// 	{
	// 		cout<<AV[i][j]<<setw(9);
	// 	}
	// 	cout<<"|"<<bV[i]<<endl;
	// }
	A=MontaMatrizBidimensional(AH,AV,malhaVertical);
	b=MontaVetorBidimensional(bH,bV,malhaVertical);

	int TotaldePontosBidimensionais = this->TotaldePontos*this->TotaldePontosV;

	cout<<endl<<endl<<endl<<"++++++++++++++++++++++++++++++MATRIZ+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
	for(int i=0; i<TotaldePontosBidimensionais; i++)
	{
		for(int j=0; j<TotaldePontosBidimensionais; j++)
		{
			cout<<A[i][j]<<setw(9);
		}
		cout<<"|"<<b[i]<<endl;
	}

	//SolverLinear SolverBidimensional(A,b,TotaldePontosBidimensionais);
	//CampoDeTemperaturasBidimensional=SolverBidimensional.getCampodeTemperaturas();
}
vector<vector<double> > GerenteVolumedeControle::MontaMatrizBidimensional(vector<vector<double> > AH,vector<vector<double> > AV,Malha malhaVertical)
{
	double DELTAX;
	double DELTAY;
	vector<vector<double> >AHW;
	vector<vector<double> >AHP;
	vector<vector<double> >AHE;
	vector<vector<double> >AVS;
	vector<vector<double> >AVP;
	vector<vector<double> >AVN;
	for(int i=0; i<this->TotaldePontosV; i++)
	{
		DELTAY = malhaVertical.getDELTAVC(i,this->DeltinhaTrueRealFalseMedio);
		vector<double>AHWaux;
		vector<double>AHPaux;
		vector<double>AHEaux;
		AHWaux.push_back(0);
		AHPaux.push_back(AH[0][0]*DELTAY);
		AHEaux.push_back(AH[0][1]*DELTAY);
		for(int j=1; j<this->TotaldePontos-1; j++)
		{
			AHWaux.push_back(AH[j][j-1]*DELTAY);
			AHPaux.push_back(AH[j][j]*DELTAY);
			AHEaux.push_back(AH[j][j+1]*DELTAY);
		}
		AHWaux.push_back(AH[this->TotaldePontos-1][this->TotaldePontos-2]*DELTAY);
		AHPaux.push_back(AH[this->TotaldePontos-1][this->TotaldePontos-1]*DELTAY);
		AHEaux.push_back(0);

		AHW.push_back(AHWaux);
		AHP.push_back(AHPaux);
		AHE.push_back(AHEaux);
	}
	for(int i=0; i<this->TotaldePontos; i++)
	{
		DELTAX = this->malhaPolinomial.getDELTAVC(i,this->DeltinhaTrueRealFalseMedio);
		vector<double>AVSaux;
		vector<double>AVPaux;
		vector<double>AVNaux;
		AVSaux.push_back(0);
		AVPaux.push_back(AV[0][0]*DELTAX);
		AVNaux.push_back(AV[0][1]*DELTAX);
		for(int j=1; j<this->TotaldePontosV-1; j++)
		{
			AVSaux.push_back(AV[j][j-1]*DELTAX);
			AVPaux.push_back(AV[j][j]*DELTAX);
			AVNaux.push_back(AV[j][j+1]*DELTAX);
		}
		AVSaux.push_back(AV[this->TotaldePontosV-1][this->TotaldePontosV-2]*DELTAX);
		AVPaux.push_back(AV[this->TotaldePontosV-1][this->TotaldePontosV-1]*DELTAX);
		AVNaux.push_back(0);
		AVS.push_back(AVSaux);
		AVP.push_back(AVPaux);
		AVN.push_back(AVNaux);
	}
	// cout<<endl<<"DELTAVC"<<endl;
	// for(int i=0; i<this->TotaldePontos; i++)
	// {
	// 	cout<<malhaPolinomial.getDELTAVC(i,1)<<endl;
	// }
	// cout<<endl<<endl<<endl<<"++++++++++++++++++++++++++++++MATRIZAVS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
	// for(int i=0; i<this->TotaldePontos; i++)
	// {
	// 	for(int j=0; j<this->TotaldePontosV; j++)
	// 	{
	// 		cout<<AVS[i][j]<<setw(9);
	// 	}
	// 	cout<<endl;
	// }
	// cout<<endl<<endl<<endl<<"++++++++++++++++++++++++++++++MATRIZAVP+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
	// for(int i=0; i<this->TotaldePontos; i++)
	// {
	// 	for(int j=0; j<this->TotaldePontosV; j++)
	// 	{
	// 		cout<<AVP[i][j]<<setw(9);
	// 	}
	// 	cout<<endl;
	// }
	// 	cout<<endl<<endl<<endl<<"++++++++++++++++++++++++++++++MATRIZAVN+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
	// for(int i=0; i<this->TotaldePontos; i++)
	// {
	// 	for(int j=0; j<this->TotaldePontosV; j++)
	// 	{
	// 		cout<<AVN[i][j]<<setw(9);
	// 	}
	// 	cout<<endl;
	// }
	AVS=TransposicionaMatriz(AVS);
	AVP=TransposicionaMatriz(AVP);
	AVN=TransposicionaMatriz(AVN);
	// 	cout<<endl<<endl<<endl<<"++++++++++++++++++++++++++++++MATRIZAVS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
	// for(int i=0; i<this->TotaldePontos; i++)
	// {
	// 	for(int j=0; j<this->TotaldePontosV; j++)
	// 	{
	// 		cout<<AVS[i][j]<<setw(9);
	// 	}
	// 	cout<<endl;
	// }
	// cout<<endl<<endl<<endl<<"++++++++++++++++++++++++++++++MATRIZAVP+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
	// for(int i=0; i<this->TotaldePontos; i++)
	// {
	// 	for(int j=0; j<this->TotaldePontosV; j++)
	// 	{
	// 		cout<<AVP[i][j]<<setw(9);
	// 	}
	// 	cout<<endl;
	// }
	// 	cout<<endl<<endl<<endl<<"++++++++++++++++++++++++++++++MATRIZAVN+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
	// for(int i=0; i<this->TotaldePontos; i++)
	// {
	// 	for(int j=0; j<this->TotaldePontosV; j++)
	// 	{
	// 		cout<<AVN[i][j]<<setw(9);
	// 	}
	// 	cout<<endl;
	// }
	vector<vector<double> >A;
	A=MontaMatrizBidimensionalTermoATermo(AHW,AHP,AHE,AVS,AVP,AVN);
	return(A);
}
vector<vector<double> > GerenteVolumedeControle::MontaMatrizBidimensionalTermoATermo(vector<vector<double> >AHW,vector<vector<double> >AHP,vector<vector<double> >AHE,vector<vector<double> >AVS,vector<vector<double> >AVP,vector<vector<double> >AVN)
{
	vector<vector<double> > A;
	int TotaldePontosBidimensionais = this->TotaldePontos*this->TotaldePontosV;
	A = CriaMatrizQuadradadeNulos(TotaldePontosBidimensionais);
	int cont = 0;
	for(int i=0; i<this->TotaldePontos; i++)
	{
		for(int j=0; j<this->TotaldePontosV; j++)
		{
			if(cont>0)
			{
				A[cont][cont-1]=AHW[i][j];
			}
			A[cont][cont] = AHP[i][j] + AVP[i][j];
			if(cont<TotaldePontosBidimensionais-1)
			{
				A[cont][cont+1]=AHE[i][j];
			}
			if(cont>this->TotaldePontos-1)
			{
				A[cont][cont-this->TotaldePontos]=AVS[i][j];
			}
			if(cont<TotaldePontosBidimensionais-this->TotaldePontosV)
			{
				A[cont][cont+this->TotaldePontos]=AVN[i][j];
			}
			cont++;
		}
	}
	return(A);
}
vector<double> GerenteVolumedeControle::MontaVetorBidimensional(vector<double>bH,vector<double>bV,Malha malhaVertical)
{
	double DELTAX;
	double DELTAY;
	vector<double>bHW;
	vector<double>bHE;
	vector<double>bVS;
	vector<double>bVN;
	for(int i=0; i<this->TotaldePontosV; i++)
	{
		DELTAY = malhaVertical.getDELTAVC(i,this->DeltinhaTrueRealFalseMedio);
		bHW.push_back(bH[0]*DELTAY);
		bHE.push_back(bH[this->TotaldePontos-1]*DELTAY); 
	}
	for(int i=0; i<this->TotaldePontos; i++)
	{
		DELTAX = this->malhaPolinomial.getDELTAVC(i,this->DeltinhaTrueRealFalseMedio);
		bVS.push_back(bV[0]*DELTAX);
		bVN.push_back(bV[this->TotaldePontosV-1]*DELTAX);
	}
	vector<double>b;
	b=MontaVetorBidimensionalTermoATermo(bHW,bHE,bVS,bVN);
	return(b);
}
vector<double> GerenteVolumedeControle::MontaVetorBidimensionalTermoATermo(vector<double>bHW,vector<double>bHE,vector<double>bVS,vector<double>bVN)
{
	vector<double>b;
	int TotaldePontosBidimensionais = this->TotaldePontos*this->TotaldePontosV;
	b=CriaVetordeNulos(TotaldePontosBidimensionais);
	for(int i=0;i<this->TotaldePontos;i++)
	{
		b[i]=b[i]+bVS[i];
	}
	int cont=0;
	for(int i=TotaldePontosBidimensionais-this->TotaldePontos;i<TotaldePontosBidimensionais;i++)
	{
		b[i]=b[i]+bVN[cont];
		cont++;
	}
	cont=0;
	for(int i=0;i<TotaldePontosBidimensionais;i=i+this->TotaldePontos)
	{
		b[i]=b[i]+bHW[cont];
		cont++;
	}
	cont=0;
	for(int i=this->TotaldePontos-1;i<TotaldePontosBidimensionais;i=i+this->TotaldePontos)
	{
		b[i]=b[i]+bHE[cont];
		cont++;
	}
	return(b);
}
void GerenteVolumedeControle::CalculaTtransienteImplicito()
{
	vector<vector<double> >A;
	vector<double>b;
	double kinterface1;
	
	vector<double> ksobredeltaexterno;
	ksobredeltaexterno=Montaksobredeltaexterno(this->malhaPolinomial, this->propriedadetermicaPolinomial, this->LarguraTotal, this->TotaldePontos);

	vector<double> ksobredeltamarginalinterno;

	ksobredeltamarginalinterno = Montaksobredeltamarginalinterno(this->malhaPolinomial,this->propriedadetermicaPolinomial,this->LarguraTotal,this->TotaldePontos,this->DeltinhaTrueRealFalseMedio,this->TipoDeKinterface);
	bool FlagDeCriterioAtingido=false;
	bool FlagDeCriterioOscilanteAtingido = false;
	int cont=0;
	double tAcumulado = 0;
	double CritComparacao = (DeslocaY1+Pre2[0])/2;
	vector<double>T1;
	vector<double>T2;
	for(int i=0; i<this->TotaldePontos; i++)
	{
		T1.push_back(-99999);
		T2.push_back(-99999);
	}
	while(FlagDeCriterioAtingido==false && this->iteracoesMax>cont && FlagDeCriterioOscilanteAtingido==false)
	{
		tAcumulado = tAcumulado + this->PassoDeTempo;
		AjustaTpreSeVariavel(tAcumulado);

		CondicoesdeContorno condicoesdecontorno1(this->Pre1,this->Pre2,this->TiposPre,this->TipoMalha,ksobredeltaexterno,ksobredeltamarginalinterno);

		A=MontaMatrizA(this->malhaPolinomial,this->propriedadetermicaPolinomial,condicoesdecontorno1,this->TotaldePontos,this->DeltinhaTrueRealFalseMedio,this->TipoDeKinterface);
		A=SomaCoeficientesTransienteNaMatriz(A);

		b=MontaVetorb(condicoesdecontorno1,this->TotaldePontos);
		b=SomaCoeficientesTransienteNoVetor(b);

		// cout<<endl<<endl;
		// for(int i=0; i<this->TotaldePontos; i++)
		// {
		// 	for(int j=0; j<this->TotaldePontos; j++)
		// 	{
		// 		cout<<A[i][j]<<"\t";
		// 	}
		// 	cout<<"|"<<b[i]<<endl<<endl;
		// }

		SolverLinear solver(A,b,this->TotaldePontos);
		this->CampoDeTemperaturas = solver.getCampodeTemperaturasTDMA();
		this->CampoDeTemperaturasTransiente.push_back(this->CampoDeTemperaturas);

		CriteriodeParada criteriodeparada(this->TipoDeCriterio,this->CriterioParada,this->CampoDeTemperaturas,this->Tinicial);
		FlagDeCriterioAtingido=criteriodeparada.getFlagDeCriterioAtingido();
		this->Tinicial = this->CampoDeTemperaturas;
		if(this->FlagCoefCosSetado1==true||this->FlagCoefCosSetado2==true)
		{
			double IteracoesPorPeriodo1 = 2/this->Frequencia1/this->PassoDeTempo;
			double IteracoesPorPeriodo2 = 2/this->Frequencia2/this->PassoDeTempo;
			int FatorDeCiclo1 = cont/IteracoesPorPeriodo1;
			int FatorDeCiclo2 = cont/IteracoesPorPeriodo2;
			cout<<endl<<endl<<"IteracoesPorPeriodo "<<IteracoesPorPeriodo1<<"\t"<<IteracoesPorPeriodo2<<endl<<endl;
			if(IteracoesPorPeriodo1*FatorDeCiclo1+1e-12>cont&&IteracoesPorPeriodo1*FatorDeCiclo1-1e-12<cont||IteracoesPorPeriodo2*FatorDeCiclo2+1e-12>cont&&IteracoesPorPeriodo2*FatorDeCiclo2-1e-12<cont)
			{
				cout<<endl<<endl<<endl<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ENTROUAQUI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<cont<<endl<<endl<<endl;
				T1=CampoDeTemperaturasTransiente[cont];
				CriteriodeParada criteriooscilante(1,this->CriterioParada,T1,T2);
				FlagDeCriterioOscilanteAtingido=criteriooscilante.getFlagDeCriterioAtingido();
				T2=T1;
			}
		}
		// if(cont>3)
		// {
		// 	double TmedAtual=0;
		// 	double TmedAnterior1=0;
		// 	double TmedAnterior2=0;
		// 	for(int i=0; i<this->TotaldePontos; i++)
		// 	{
		// 		TmedAtual = TmedAtual+CampoDeTemperaturasTransiente[cont][i];
		// 		TmedAnterior1 = TmedAnterior1+CampoDeTemperaturasTransiente[cont-1][i];
		// 		TmedAnterior2 = TmedAnterior2+CampoDeTemperaturasTransiente[cont-2][i];
		// 	}
		// 	TmedAtual = TmedAtual/this->TotaldePontos;
		// 	TmedAnterior1 = TmedAnterior1/this->TotaldePontos;
		// 	TmedAnterior2 = TmedAnterior2/this->TotaldePontos;
		// 	if(TmedAtual>=150 & TmedAnterior1>150 & TmedAnterior2>150)
		// 	{
		// 		FlagDeCriterioOscilanteAtingido=true;
		// 	}
		// }
		cont ++;
	}
}
void GerenteVolumedeControle::AjustaTpreSeVariavel(double tAcumulado)
{
	double Pi = 3.14159265359;
	if(TiposPre[0]==1)
	{
		if(FlagCoefCosSetado1==true)
		{
			this->Pre1[0]=this->DeslocaY1+this->Amplitude1*cos(this->Frequencia1*Pi*tAcumulado+DeslocaX1);
		}
	}
	if(TiposPre[1]==1)
	{
		if(FlagCoefCosSetado2==true)
		{
			this->Pre2[0]=this->DeslocaY2+this->Amplitude2*cos(this->Frequencia2*Pi*tAcumulado+DeslocaX2);
		}
	}
}
vector<vector<double> > GerenteVolumedeControle::SomaCoeficientesTransienteNaMatriz(vector<vector<double> >A)
{
	double Pi = 3.14159265359;
	double apo;
	double rp;
	double rw;
	double re;
	if(this->IndicaCoordenadaCilindrica==1)
	{
		if(this->TiposPre[0]==2)
		{
			apo = (this->malhaPolinomial.getDelta_e_Menos(0,this->DeltinhaTrueRealFalseMedio))*(this->RaioInterno)*this->ro*this->Cp*2*Pi/this->PassoDeTempo;
			A[0][1]=A[0][1]*(this->RaioInterno+this->malhaPolinomial.getDelta_e_Menos(0,this->DeltinhaTrueRealFalseMedio))*2*Pi;
			A[0][0]=-A[0][1]+apo;
		}
		if(this->TiposPre[0]==3)
		{
			apo = (this->malhaPolinomial.getDelta_e_Menos(0,this->DeltinhaTrueRealFalseMedio))*(this->RaioInterno)*this->ro*this->Cp*2*Pi/this->PassoDeTempo;
			A[0][1]=A[0][1]*(this->RaioInterno+this->malhaPolinomial.getdelta_e(0))*2*Pi;
			A[0][0]=-A[0][1]+apo-this->Pre1[1]*2*Pi*(this->RaioInterno);
		}
		for(int i=1; i<this->TotaldePontos-1; i++)
		{
			rw = this->RaioInterno+this->malhaPolinomial.getDistanciadaOrigemPosicional(i)-this->malhaPolinomial.getDelta_w_Mais(i,this->DeltinhaTrueRealFalseMedio);
			rp = this->RaioInterno+this->malhaPolinomial.getDistanciadaOrigemPosicional(i);
			re = this->RaioInterno+this->malhaPolinomial.getDistanciadaOrigemPosicional(i)+this->malhaPolinomial.getDelta_e_Menos(i,this->DeltinhaTrueRealFalseMedio);
			apo = (this->malhaPolinomial.getDelta_e_Menos(i,this->DeltinhaTrueRealFalseMedio)+this->malhaPolinomial.getDelta_w_Mais(i,this->DeltinhaTrueRealFalseMedio))*(rp)*this->ro*this->Cp/this->PassoDeTempo*2*Pi;
			A[i][i-1]=A[i][i-1]*(rw)*2*Pi;
			A[i][i+1]=A[i][i+1]*(re)*2*Pi;
			A[i][i]=-A[i][i+1]-A[i][i-1]+apo;
		}
		if(this->TiposPre[1]==2)
		{
			rw = this->RaioInterno+this->malhaPolinomial.getDistanciadaOrigemPosicional(this->TotaldePontos-1)-this->malhaPolinomial.getDelta_w_Mais(this->TotaldePontos-1,this->DeltinhaTrueRealFalseMedio);
			rp = this->RaioInterno+this->malhaPolinomial.getDistanciadaOrigemPosicional(this->TotaldePontos-1);
			apo = (this->malhaPolinomial.getDelta_w_Mais(this->TotaldePontos-1,this->DeltinhaTrueRealFalseMedio))*(rp)*this->ro*this->Cp/this->PassoDeTempo*2*Pi;
			A[this->TotaldePontos-1][this->TotaldePontos-2]= A[this->TotaldePontos-1][this->TotaldePontos-2]*(rw)*2*Pi;
			A[this->TotaldePontos-1][this->TotaldePontos-1]=-A[this->TotaldePontos-1][this->TotaldePontos-2]+apo;
		}
		if(this->TiposPre[1]==3)
		{
			rw = this->RaioInterno+this->malhaPolinomial.getDistanciadaOrigemPosicional(this->TotaldePontos-1)-this->malhaPolinomial.getDelta_w_Mais(this->TotaldePontos-1,this->DeltinhaTrueRealFalseMedio);
			rp = this->RaioInterno+this->malhaPolinomial.getDistanciadaOrigemPosicional(this->TotaldePontos-1);
			apo = (this->malhaPolinomial.getDelta_w_Mais(this->TotaldePontos-1,this->DeltinhaTrueRealFalseMedio))*(rp)*this->ro*this->Cp/this->PassoDeTempo*2*Pi;
			A[this->TotaldePontos-1][this->TotaldePontos-2]= A[this->TotaldePontos-1][this->TotaldePontos-2]*(rw)*2*Pi;
			A[this->TotaldePontos-1][this->TotaldePontos-1] =-A[this->TotaldePontos-1][this->TotaldePontos-2]+apo+this->Pre2[1]*(rp)*2*Pi;
		}
		return(A);
	}
	else
	{
		if(this->TiposPre[0]==2)
		{
			apo = (this->malhaPolinomial.getDelta_e_Menos(0,this->DeltinhaTrueRealFalseMedio))*this->ro*this->Cp/this->PassoDeTempo;
			A[0][0]=-A[0][1]+apo;
		}
		if(this->TiposPre[0]==3)
		{
			apo = (this->malhaPolinomial.getDelta_e_Menos(0,this->DeltinhaTrueRealFalseMedio))*this->ro*this->Cp/this->PassoDeTempo;
			A[0][0]=-A[0][1]+apo+this->Pre1[1];
		}
		for(int i=1; i<this->TotaldePontos-1; i++)
		{
			apo = (this->malhaPolinomial.getDelta_e_Menos(i,this->DeltinhaTrueRealFalseMedio)+this->malhaPolinomial.getDelta_w_Mais(i,this->DeltinhaTrueRealFalseMedio))*this->ro*this->Cp/this->PassoDeTempo;
			A[i][i] =-A[i][i+1]-A[i][i-1]+apo;
		}
		if(this->TiposPre[1]==2)
		{
			apo = (this->malhaPolinomial.getDelta_w_Mais(this->TotaldePontos-1,this->DeltinhaTrueRealFalseMedio))*this->ro*this->Cp/this->PassoDeTempo;
			A[this->TotaldePontos-1][this->TotaldePontos-1] = -A[this->TotaldePontos-1][this->TotaldePontos-2]+apo;
		}
		if(this->TiposPre[1]==3)
		{
			apo = (this->malhaPolinomial.getDelta_w_Mais(this->TotaldePontos-1,this->DeltinhaTrueRealFalseMedio))*this->ro*this->Cp/this->PassoDeTempo;
			A[this->TotaldePontos-1][this->TotaldePontos-1] = -A[this->TotaldePontos-1][this->TotaldePontos-2]+apo+this->Pre2[1];
		}
		return(A);
	}
}
vector<double> GerenteVolumedeControle::SomaCoeficientesTransienteNoVetor(vector<double>b)
{
	double Pi = 3.14159265359;
	double apo;
	double rp;
	double rw;
	double re;
	if(this->IndicaCoordenadaCilindrica==1)
	{
		if(this->TiposPre[0]==2)
		{
			apo = (this->malhaPolinomial.getDelta_e_Menos(0,this->DeltinhaTrueRealFalseMedio))*(this->RaioInterno)*this->ro*this->Cp*2*Pi/this->PassoDeTempo;
			b[0]=b[0]+apo*this->Tinicial[0];
		}
		if(this->TiposPre[0]==3)
		{
			apo = (this->malhaPolinomial.getDelta_e_Menos(0,this->DeltinhaTrueRealFalseMedio))*(this->RaioInterno)*this->ro*this->Cp*2*Pi/this->PassoDeTempo;
			b[0]=this->Pre1[0]*this->Pre1[1]*2*Pi*this->RaioInterno+apo*this->Tinicial[0];
		}
		for(int i=1; i<this->TotaldePontos-1; i++)
		{
			rp = this->RaioInterno+this->malhaPolinomial.getDistanciadaOrigemPosicional(i);
			apo = (this->malhaPolinomial.getDelta_e_Menos(i,this->DeltinhaTrueRealFalseMedio)+this->malhaPolinomial.getDelta_w_Mais(i,this->DeltinhaTrueRealFalseMedio))*(rp)*this->ro*this->Cp/this->PassoDeTempo*2*Pi;
			b[i] = apo*this->Tinicial[i];
		}
		if(this->TiposPre[1]==2)
		{
			rp = this->RaioInterno+this->malhaPolinomial.getDistanciadaOrigemPosicional(this->TotaldePontos-1);
			apo = (this->malhaPolinomial.getDelta_w_Mais(this->TotaldePontos-1,this->DeltinhaTrueRealFalseMedio))*(rp)*this->ro*this->Cp/this->PassoDeTempo*2*Pi;
			b[this->TotaldePontos-1]=b[this->TotaldePontos-1]+apo*this->Tinicial[this->TotaldePontos-1];
		}
		if(this->TiposPre[1]==3)
		{
			rp = this->RaioInterno+this->malhaPolinomial.getDistanciadaOrigemPosicional(this->TotaldePontos-1);
			apo = (this->malhaPolinomial.getDelta_w_Mais(this->TotaldePontos-1,this->DeltinhaTrueRealFalseMedio))*(rp)*this->ro*this->Cp/this->PassoDeTempo*2*Pi;
			b[this->TotaldePontos-1]=this->Pre2[0]*this->Pre2[1]*2*Pi*rp+apo*this->Tinicial[this->TotaldePontos-1];
		}
		return(b);
	}
	else
	{
		if(this->TiposPre[0]==2||this->TiposPre[0]==3)
		{
			apo = (this->malhaPolinomial.getDelta_e_Menos(0,this->DeltinhaTrueRealFalseMedio))*this->ro*this->Cp/this->PassoDeTempo;
			b[0]=b[0]+apo*this->Tinicial[0];
		}
		for(int i=1; i<this->TotaldePontos-1; i++)
		{
			apo = (this->malhaPolinomial.getDelta_e_Menos(i,this->DeltinhaTrueRealFalseMedio)+this->malhaPolinomial.getDelta_w_Mais(i,this->DeltinhaTrueRealFalseMedio))*this->ro*this->Cp/this->PassoDeTempo;
			b[i] = apo*this->Tinicial[i];
		}
		if(this->TiposPre[1]==2||this->TiposPre[1]==3)
		{
			apo = (this->malhaPolinomial.getDelta_w_Mais(this->TotaldePontos-1,this->DeltinhaTrueRealFalseMedio))*this->ro*this->Cp/this->PassoDeTempo;
			b[this->TotaldePontos-1] = b[this->TotaldePontos-1]+apo;
		}
		return(b);
	}
}
void GerenteVolumedeControle::CalculaTtransienteExplicito()
{
	TestaConvergenciaTransienteExplicito();

	vector<vector<double> >A;
	
	vector<double> ksobredeltaexterno;
	ksobredeltaexterno=Montaksobredeltaexterno(this->malhaPolinomial,this->propriedadetermicaPolinomial,this->LarguraTotal,this->TotaldePontos);

	vector<double> ksobredeltamarginalinterno;

	ksobredeltamarginalinterno = Montaksobredeltamarginalinterno(this->malhaPolinomial,this->propriedadetermicaPolinomial,this->LarguraTotal,this->TotaldePontos,this->DeltinhaTrueRealFalseMedio,this->TipoDeKinterface);

	this->CampoDeTemperaturas.resize(this->TotaldePontos);

	int cont = 0;
	bool FlagDeCriterioAtingido=false;
	while(this->iteracoesMax>cont && FlagDeCriterioAtingido==false)
	{
		CalculaUmPassoNoTempoExplicito();
		CriteriodeParada criteriodeparada(this->TipoDeCriterio,this->CriterioParada,this->CampoDeTemperaturas,this->Tinicial);
		FlagDeCriterioAtingido = criteriodeparada.getFlagDeCriterioAtingido();
		cont++;
		this->Tinicial=this->CampoDeTemperaturas;
		A.push_back(this->CampoDeTemperaturas);
	}
	this->NumerodeIteracoes=cont;
	this->CampoDeTemperaturasTransiente = A;
}
void GerenteVolumedeControle::CalculaUmPassoNoTempoExplicito()
{	
	double ae;
	double aw;
	double apo;
	double kinterface1;
	double kinterface2;
	kinterface2 = getkInterface(this->malhaPolinomial.getdelta_e(0),this->malhaPolinomial.getDelta_e_Mais(0,DeltinhaTrueRealFalseMedio),this->malhaPolinomial.getDelta_e_Menos(0,DeltinhaTrueRealFalseMedio),this->propriedadetermicaPolinomial.getk(1),this->propriedadetermicaPolinomial.getk(0),TipoDeKinterface);
	ae = kinterface2/this->malhaPolinomial.getdelta_e(0);
	apo = (this->malhaPolinomial.getDelta_e_Menos(0,DeltinhaTrueRealFalseMedio))*this->ro*this->Cp/this->PassoDeTempo;
	this->CampoDeTemperaturas[0] = (CondicaoDeContornoEntradaExplicito(ae,apo)+this->Tinicial[1]*ae)/apo;
	// cout<<endl<<endl<<"aw="<<aw<<"	ae="<<ae<<"	apo="<<apo<<endl<<endl;
	
	for(int i=1; i<TotaldePontos-1;i++)
	{
		kinterface2 = getkInterface(this->malhaPolinomial.getdelta_e(i),this->malhaPolinomial.getDelta_e_Mais(i,DeltinhaTrueRealFalseMedio),this->malhaPolinomial.getDelta_e_Menos(i,DeltinhaTrueRealFalseMedio),this->propriedadetermicaPolinomial.getk(i+1),this->propriedadetermicaPolinomial.getk(i),TipoDeKinterface);
		kinterface1 = getkInterface(this->malhaPolinomial.getdelta_w(i),this->malhaPolinomial.getDelta_w_Mais(i,DeltinhaTrueRealFalseMedio),this->malhaPolinomial.getDelta_w_Menos(i,DeltinhaTrueRealFalseMedio),this->propriedadetermicaPolinomial.getk(i),this->propriedadetermicaPolinomial.getk(i-1),TipoDeKinterface);
		aw = kinterface1/this->malhaPolinomial.getdelta_w(i);
		ae = kinterface2/this->malhaPolinomial.getdelta_e(i);
		apo = (this->malhaPolinomial.getDelta_e_Menos(i,DeltinhaTrueRealFalseMedio)+this->malhaPolinomial.getDelta_w_Mais(i,DeltinhaTrueRealFalseMedio))*this->ro*this->Cp/this->PassoDeTempo;
		this->CampoDeTemperaturas[i] = (this->Tinicial[i]*(-ae-aw+apo)+this->Tinicial[i+1]*(ae)+this->Tinicial[i-1]*(aw))/apo;
		// cout<<endl<<endl<<"aw="<<aw<<"	ae="<<ae<<"	apo="<<apo<<endl<<endl;
	
	}
	kinterface1 = getkInterface(this->malhaPolinomial.getdelta_w(this->TotaldePontos-1),this->malhaPolinomial.getDelta_w_Mais(this->TotaldePontos-1,DeltinhaTrueRealFalseMedio),this->malhaPolinomial.getDelta_w_Menos(this->TotaldePontos-1,DeltinhaTrueRealFalseMedio),this->propriedadetermicaPolinomial.getk(this->TotaldePontos-1),this->propriedadetermicaPolinomial.getk(this->TotaldePontos-2),TipoDeKinterface);
	aw = kinterface1/this->malhaPolinomial.getdelta_w(this->TotaldePontos-1);
	apo=(this->malhaPolinomial.getDelta_w_Mais(TotaldePontos-1,DeltinhaTrueRealFalseMedio))*this->ro*this->Cp/this->PassoDeTempo;
	this->CampoDeTemperaturas[TotaldePontos-1]=(CondicaoDeContornoSaidaExplicito(aw, apo)+aw*this->Tinicial[this->TotaldePontos-2])/apo;
	// cout<<endl<<endl<<"aw="<<aw<<"	ae="<<ae<<"	apo="<<apo<<endl<<endl;
	
	
	// cout<<endl<<endl<<"MATRIZ"<<endl;
	// for(int i=0; i<this->TotaldePontos; i++)
	// {
	// 	cout<<endl<<this->CampoDeTemperaturas[i]<<endl;
	// }
}
double GerenteVolumedeControle::CondicaoDeContornoEntradaExplicito(double ae, double apo)
{
	vector<double> CondicoesDeEntrada;
	if(this->TiposPre[0]==1)
	{
		return(this->Pre1[0]);
	}
	if(this->TiposPre[0]==2)
	{
		return(this->Pre1[0]-this->Tinicial[0]*(-apo+ae));
	}
	if(this->TiposPre[0]==3)
	{
		return(this->Pre1[0]*this->Pre1[1]+this->Tinicial[0]*(apo-this->Pre1[1]-ae));
	}
}
double GerenteVolumedeControle::CondicaoDeContornoSaidaExplicito(double aw, double apo)
{
	if(this->TiposPre[1]==1)
	{
		return(this->Pre2[0]);
	}
	if(this->TiposPre[1]==2)
	{
		return(-this->Pre2[0]+this->Tinicial[this->TotaldePontos-1]*(apo-aw));
	}
	if(this->TiposPre[1]==3)
	{
		return(this->Pre2[0]*this->Pre2[1]+this->Tinicial[this->TotaldePontos-1]*(apo-this->Pre2[1]-aw));
	}
}
void GerenteVolumedeControle::TestaConvergenciaTransienteExplicito()
{
	double alpha;
	bool naoconverge=false;
	double teste;
	for(int i=0; i<this->TotaldePontos; i++)
	{
		alpha=(this->propriedadetermicaPolinomial.getk(i)/(ro*Cp));
		teste = alpha*this->PassoDeTempo/(pow(this->malhaPolinomial.getDelta_w_Mais(i,this->DeltinhaTrueRealFalseMedio)+this->malhaPolinomial.getDelta_e_Menos(i,this->DeltinhaTrueRealFalseMedio),2));
		//cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
		//cout<<endl<<endl<<"alpha="<<alpha<<"	Dt="<<this->PassoDeTempo<<"	Dx="<<this->malhaPolinomial.getDelta_w_Mais(i,this->DeltinhaTrueRealFalseMedio)+this->malhaPolinomial.getDelta_e_Menos(i,this->DeltinhaTrueRealFalseMedio)<<"	Dxw+="<<this->malhaPolinomial.getDelta_w_Mais(i,this->DeltinhaTrueRealFalseMedio)<<"	Dxe-="<<this->malhaPolinomial.getDelta_e_Menos(i,this->DeltinhaTrueRealFalseMedio)<<"	valor de teste ="<<teste<<endl<<endl;
		if(teste>0.5)
		{
			naoconverge = true;
		}
	}
	if(naoconverge==true)
	{
		cout<<endl<<endl<<"Atencao! Transiente Explicito pode nao convergir!"<<endl<<endl;
	}
}
void GerenteVolumedeControle::CalculaTpolinomial()
{
	int NumerodeIteracoes = 0;
	vector<double> Tanterior = this->CampoDeTemperaturas;
	bool FlagDeCriterioAtingido = 0;
	while(FlagDeCriterioAtingido==0 && this->iteracoesMax>NumerodeIteracoes)
	{
		vector<vector<double> >A;
		vector<double>b;
		
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

		CriteriodeParada criteriodeparada(this->TipoDeCriterio,this->CriterioParada,this->CampoDeTemperaturas,Tanterior);
		FlagDeCriterioAtingido=criteriodeparada.getFlagDeCriterioAtingido();
		this->ErroDeParada = criteriodeparada.getErro();

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
string GerenteVolumedeControle::TransformaEmString(int Number)
{
	string Result;
	stringstream convert;
	convert << Number;
	Result = convert.str();
	return(Result);
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
		this->kinterface_TodosPontos.resize(TotaldePontos-1);
		kinterface2 = getkInterface(malha1.getdelta_e(0),malha1.getDelta_e_Mais(0,DeltinhaTrueRealFalseMedio),malha1.getDelta_e_Menos(0,DeltinhaTrueRealFalseMedio),propriedadetermica1.getk(1),propriedadetermica1.getk(0),TipoDeKinterface);
		this->kinterface_TodosPontos[0]=kinterface2;
		for(int i=1; i<TotaldePontos-1;i++)
		{
			kinterface2 = getkInterface(malha1.getdelta_e(i),malha1.getDelta_e_Mais(i,DeltinhaTrueRealFalseMedio),malha1.getDelta_e_Menos(i,DeltinhaTrueRealFalseMedio),propriedadetermica1.getk(i+1),propriedadetermica1.getk(i),TipoDeKinterface);
			kinterface1 = getkInterface(malha1.getdelta_w(i),malha1.getDelta_w_Mais(i,DeltinhaTrueRealFalseMedio),malha1.getDelta_w_Menos(i,DeltinhaTrueRealFalseMedio),propriedadetermica1.getk(i),propriedadetermica1.getk(i-1),TipoDeKinterface);
			this->kinterface_TodosPontos[i] = kinterface2;
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
void GerenteVolumedeControle::SalvaDoisVetoresDeintcsv(string NomedoArquivo, vector<int> V1, vector<int> V2)
{
	if(V1.size()==V2.size())
	{
		ofstream myfile;
		myfile.open (NomedoArquivo.c_str());
		for(int i=0; i<V1.size(); i++)
		{
				myfile<<V1[i]<<","<<V2[i]<<"\n";
		}
		myfile.close();
	}
	else
	{
		cout<<endl<<endl<<"PROBLEMA! Vetores a serem salvos nao possuem mesma dimensao!"<<endl<<endl;
	}
}
void GerenteVolumedeControle::SalvaMatrizcsv(string NomedoArquivo,vector<vector<double> >M1)
{
	ofstream myfile;
	myfile.open (NomedoArquivo.c_str());
	for(int i=0; i<M1.size(); i++)
	{
		for(int j=0; j<M1[i].size(); j++)
		{
			myfile<<M1[i][j]<<",";
		}
		myfile<<"\n";
	}
	myfile.close();
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
vector<vector<double> > GerenteVolumedeControle::TransposicionaMatriz(vector<vector<double> >M)
{
	vector<vector<double> >M2;
	M2.resize(M[0].size());
	for(int i=0; i<M.size(); i++)
	{
		M2[i].resize(M.size());
		for(int j=0; j<M[i].size(); j++)
		{
			M2[i][j] = M[j][i];
		}
	}
	return(M2);
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