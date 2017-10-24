#include <vector>
#include <iostream>
#include <string>

using namespace std;

class GerenteVolumedeControle
{
	public:
		GerenteVolumedeControle(vector<int>Nptoscadamat,int Nmalhas,vector<double>LarguraMat,int TipoMalha,vector<double>k,int TipoDeKinterface,vector<double>Pre1,vector<double>Pre2,vector<int>TiposPre,bool DeltinhaTrueRealFalseMedio);
		vector<double> getCampoDeTemperaturas();
		vector<double> getDistanciaDaOrigem();
		void SalvaCampoDeTemperaturascsv(string NomedoArquivo);
		void MostraTiposdeConfiguracao();
	private:
		double getkInterface(double delta, double delta_Mais, double delta_Menos, double kmais, double kmenos,int TipoDeKinterface);
		int ContaTotaldePontos(vector<int> Nptoscadamat, int Nmalhas);
		vector<double> CriaVetordeNulos(int NumerodePontos);
		vector<vector<double> > CriaMatrizQuadradadeNulos(int NumerodePontos);

		vector<double> CampoDeTemperaturas;
		vector<double> DistanciaDaOrigem;
};