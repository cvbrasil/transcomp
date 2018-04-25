#include <vector>
#include <iostream>

using namespace std;

class CriteriodeParada
{
	public:
		CriteriodeParada(int TipodeCriterio,double CriterioDeParada,vector<double>TemperaturasAtuais,vector<double>TemperaturasAnteriores);

		bool getFlagDeCriterioAtingido();
		double getErro();
		bool getFlagDeCriterioAtingidoOscilante(double TemperaturasAtuais,double TemperaturasAnteriores1,double TemperaturasAnteriores2);
	private:
		void maxDiferencaSimples(double CriterioDeParada,vector<double>TemperaturasAtuais, vector<double>TemperaturasAnteriores);
		void maxDiferencaRelativa(double CriterioDeParada,vector<double>TemperaturasAtuais, vector<double>TemperaturasAnteriores);
		void DiferencasQuadradasSobreNVC(double CriterioDeParada,vector<double>TemperaturasAtuais, vector<double>TemperaturasAnteriores);
		void ModulodasDiferencasSobreNVC(double CriterioDeParada,vector<double>TemperaturasAtuais, vector<double>TemperaturasAnteriores);
		void ModulodasDiferencasRelativas(double CriterioDeParada,vector<double>TemperaturasAtuais, vector<double>TemperaturasAnteriores);
		void ResiduosQuadrados();
		bool CriterioAtingidoOscilante(double TemperaturasAtuais,double TemperaturasAnteriores1,double TemperaturasAnteriores2);

		double ProcuraTmax(vector<double> TemperaturasAtuais);
		double ProcuraTmin(vector<double> TemperaturasAtuais);

		bool FlagDeCriterioAtingido=false;
		double ErroDeParada;
};