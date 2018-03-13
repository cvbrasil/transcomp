#include <vector>
#include <iostream>

using namespace std;

class Malha
{
	public:
		Malha(vector<int>NumerodePontos,vector<double>LarguraporMaterial,int NumerodeMalhas,int TipodeMalha);

		double getdelta_w(int position);

		double getdelta_e(int position);

		double getDelta_e_Mais(int position,bool DeltinhaTrueRealFalseMedio);

		double getDelta_e_Menos(int position,bool DeltinhaTrueRealFalseMedio);

		double getDelta_w_Mais(int position,bool DeltinhaTrueRealFalseMedio);

		double getDelta_w_Menos(int position,bool DeltinhaTrueRealFalseMedio);

		double getLarguraTotal();

		int getTipodeMalha();

		vector<double> getDistanciadaOrigem();

		double getDistanciadaOrigemPosicional(int Position);
	private:
		void setVariaveisdeMalha(vector<int>NumerodePontos,vector<double>LarguraporMaterial,int NumerodeMalhas,int TipodeMalha);

		vector<double> DefineDeltaBase(vector<int>NumerodePontos,vector<double>LarguraporMaterial,int NumerodeMalhas,int TipodeMalha);
		vector<double> DefineDeltaBaseInicial(int TipodeMalha,vector<double> DeltaBase,int NumerodeMalhas);

		vector<double>DistanciadaOrigem;
		vector<double>DistanciadaOrigemMaterial;

		double LarguraTotal;

		int TipodeMalha;
};