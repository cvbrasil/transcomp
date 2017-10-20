#include <vector>
#include <iostream>

using namespace std;

class CondicoesdeContorno
{
	public:
		CondicoesdeContorno(vector<double>Pre1,vector<double>Pre2,vector<int>TiposdePRE,int TipodeMalha,vector<double> ksobredeltaexterno, vector<double> ksobredeltamarginalinterno);
		double getPrimeiroTermodeEntrada();
		double getSegundoTermodeEntrada();
		double getTerceiroTermodeEntrada();

		double getPrimeiroTermodeSaida();
		double getSegundoTermodeSaida();
		double getTerceiroTermodeSaida();
	private:
		void setCondicoesdeContorno(vector<double>Pre1,vector<double>Pre2,vector<int>TiposdePRE,int TipodeMalha,vector<double> ksobredeltaexterno, vector<double> ksobredeltamarginalinterno);
		vector<double> TermodeEntrada;
		vector<double> TermodeSaida;
};