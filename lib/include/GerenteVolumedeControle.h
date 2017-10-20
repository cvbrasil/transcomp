#include <vector>
#include <iostream>
#include <string>

using namespace std;

class GerenteVolumedeControle
{
	public:
		GerenteVolumedeControle(vector<int>Nptoscadamat,int Nmalhas,vector<double>LarguraMat,int TipoMalha,vector<double>k,vector<double>Pre1,vector<double>Pre2,vector<int>TiposPre);
		vector<double> getCampoDeTemperaturas();
		void SalvaCampoDeTemperaturascsv(string NomedoArquivo);
	private:
		double getkInterface(double delta, double delta_Mais, double delta_Menos, double kmais, double kmenos);
		int ContaTotaldePontos(vector<int> Nptoscadamat, int Nmalhas);
		vector<double> CriaVetordeNulos(int NumerodePontos);
		vector<vector<double> > CriaMatrizQuadradadeNulos(int NumerodePontos);

		vector<double> CampoDeTemperaturas;
};