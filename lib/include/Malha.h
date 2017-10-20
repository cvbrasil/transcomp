#include <vector>
#include <iostream>

using namespace std;

class Malha
{
	public:
		Malha(vector<int>NumerodePontos,vector<double>LarguraporMaterial,int NumerodeMalhas,int TipodeMalha);

		double getdelta_w(int position);

		double getdelta_e(int position);

		double getDelta_e_Mais(int position);

		double getDelta_e_Menos(int position);

		double getDelta_w_Mais(int position);

		double getDelta_w_Menos(int position);

		double getLarguraTotal();

		int getTipodeMalha();

		vector<double> getDistanciadaOrigem();

		double getDistanciadaOrigemPosicional(int Position);
	private:
		void setVariaveisdeMalha(vector<int>NumerodePontos,vector<double>LarguraporMaterial,int NumerodeMalhas,int TipodeMalha);

		vector<double> DefineDeltaBase(vector<int>NumerodePontos,vector<double>LarguraporMaterial,int NumerodeMalhas,int TipodeMalha);
		double DefineDeltaBaseInicial(int TipodeMalha,double DeltaBaseMaterial1);
		vector<double>DefineDeltasdeTransferencia(double DeltaBaseMat1,double DeltaBaseMatUltimo,int TipodeMalha);

		vector<double>DistanciadaOrigem;

		vector<double>DistanciadaOrigemMaterial;

		double LarguraTotal;

		int TipodeMalha;
};