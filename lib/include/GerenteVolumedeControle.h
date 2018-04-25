#include <vector>
#include <iostream>
#include <string>

#include <Malha.h>
#include <CondicoesdeContorno.h>
#include <PropriedadeTermica.h>


using namespace std;

class GerenteVolumedeControle
{
	public:
		GerenteVolumedeControle(vector<int>Nptoscadamat,int Nmalhas,vector<double>LarguraMat,int TipoMalha,vector<double>k,int TipoDeKinterface,vector<double>Pre1,vector<double>Pre2,vector<int>TiposPre,bool DeltinhaTrueRealFalseMedio,int caso,int TipoDeCriterio);
		vector<double> getCampoDeTemperaturas();
		vector<double> getDistanciaDaOrigem();
		void SalvaCampoDeTemperaturascsv(string NomedoArquivo);
		void SalvaDoisVetorescsv(string NomedoArquivo, vector<double> V1, vector<double> V2);
		void SalvaDoisVetoresDeintcsv(string NomedoArquivo, vector<int> V1, vector<int> V2);
		void SalvaMatrizcsv(string NomedoArquivo,vector<vector<double> >M1);
		void MostraTiposdeConfiguracao();
		void SetVariaveisPolinomiais(vector<vector<double> >kpolinomial, vector<double>Tinicial, int iteracoesMax, double CriterioParada);
		void SetVariaveisTransiente(double ro, double Cp, vector<double>Tinicial, int iteracoesMax, double CriteriodeParada, double PassoDeTempo, double f);
		void setCoeficientesCosTpreTransiente(double DeslocaY, double Amplitude, double Frequencia, double DeslocaX, int QualExtremo);
		void setVariaveisCilindricas(double RaioInterno);
		int getNumerodeIteracoes();
		vector<double> getkEmTodosPontos();
		vector<double> getkinterface_TodosPontos();
		vector<double> getFluxoTermico();
		string TransformaEmString(int Number);
		double getErroIterativo();
		vector<vector<double> > getTemperaturasTransiente();
	private:
		vector<vector<double> > MontaMatrizA(Malha,PropriedadeTermica, CondicoesdeContorno, int TotaldePontos,bool DeltinhaTrueRealFalseMedio,int TipoDeKinterface);
		vector<double> MontaVetorb(CondicoesdeContorno,int TotaldePontos);
		vector<double> Montaksobredeltaexterno(Malha, PropriedadeTermica, double LarguraTotal, int TotaldePontos);
		vector<double> Montaksobredeltamarginalinterno(Malha, PropriedadeTermica, double LarguraTotal, int TotaldePontos, bool DeltinhaTrueRealFalseMedio, int TipoDeKinterface);
		double getkInterface(double delta, double delta_Mais, double delta_Menos, double kmais, double kmenos,int TipoDeKinterface);
		int ContaTotaldePontos(vector<int> Nptoscadamat, int Nmalhas);
		vector<double> CriaVetordeNulos(int NumerodePontos);
		vector<vector<double> > CriaMatrizQuadradadeNulos(int NumerodePontos);
		double ContaLarguraTotal(vector<double>LarguraMat);
		void ImprimeMatriz(vector<vector<double> >A,vector<double>b, int TotaldePontos);
		void CalculaTpolinomial();
		void CalculaTtransienteExplicito();
		void CalculaUmPassoNoTempoExplicito();
		void TestaConvergenciaTransienteExplicito();
		void CalculaTtransienteImplicito();
		void AjustaTpreSeVariavel(double tAcumulado);
		vector<vector<double> > SomaCoeficientesTransienteNaMatriz(vector<vector<double> >A);
		vector<double> SomaCoeficientesTransienteNoVetor(vector<double>b);
		void SalvaTodok(PropriedadeTermica,int TotaldePontos);
		double CondicaoDeContornoEntradaExplicito(double ae, double apo);
		double CondicaoDeContornoSaidaExplicito(double aw, double apo);

		Malha malhaPolinomial;
		PropriedadeTermica propriedadetermicaPolinomial;
		vector<double> CampoDeTemperaturas;
		vector<vector<double> > CampoDeTemperaturasTransiente;
		vector<double> DistanciaDaOrigem;
		vector<double> k_TodosPontos;
		vector<double> kinterface_TodosPontos;
		vector<double> Tinicial;
		double LarguraTotal;
		int TotaldePontos;
		bool DeltinhaTrueRealFalseMedio;
		int TipoDeKinterface;
		int iteracoesMax;
		double CriterioParada;
		vector<double> Pre1;
		vector<double> Pre2;
		vector<int> TiposPre;
		int TipoMalha;
		int NumerodeIteracoes = 0;
		int TipoDeCriterio;
		double ErroDeParada;
		double ro; double Cp; double PassoDeTempo;
		double DeslocaY1; double Amplitude1; double Frequencia1; double DeslocaX1; bool FlagCoefCosSetado1;
		double DeslocaY2; double Amplitude2; double Frequencia2; double DeslocaX2; bool FlagCoefCosSetado2;
		double RaioInterno=1; bool IndicaCoordenadaCilindrica = 0;
};