#include <vector>
#include <iostream>
#include <string>

using namespace std;

class GerenteVolumedeControle
{
	public:
		GerenteVolumedeControle(vector<int>Nptoscadamat,int Nmalhas,vector<double>LarguraMat,int TipoMalha,vector<double>k,int TipoDeKinterface,vector<double>Pre1,vector<double>Pre2,vector<int>TiposPre,bool DeltinhaTrueRealFalseMedio,bool kPolinomial);
		vector<double> getCampoDeTemperaturas();
		vector<double> getDistanciaDaOrigem();
		void SalvaCampoDeTemperaturascsv(string NomedoArquivo);
		void SalvaDoisVetorescsv(string NomedoArquivo, vector<double> V1, vector<double> V2);
		void MostraTiposdeConfiguracao();
	private:
		vector<vector<double> > MontaMatrizA(Malha,PropriedadeTermica, CondicoesdeContorno, int TotaldePontos,bool DeltinhaTrueRealFalseMedio,int TipoDeKinterface);
		vector<double> MontaVetorb(CondicoesdeContorno,int TotaldePontos);
		vector<double> Montaksobredeltaexterno(Malha, PropriedadeTermica, double LarguraTotal, int TotaldePontos);
		double getkInterface(double delta, double delta_Mais, double delta_Menos, double kmais, double kmenos,int TipoDeKinterface);
		int ContaTotaldePontos(vector<int> Nptoscadamat, int Nmalhas);
		vector<double> CriaVetordeNulos(int NumerodePontos);
		vector<vector<double> > CriaMatrizQuadradadeNulos(int NumerodePontos);
		double ContaLarguraTotal(vector<double>LarguraMat);
		void ImprimeMatriz(vector<vector<double> >A,vector<double>b, int TotaldePontos);

		vector<double> CampoDeTemperaturas;
		vector<double> DistanciaDaOrigem;
};