#include <vector>
#include <iostream>

using namespace std;

class PropriedadeTermica
{
	public:
		PropriedadeTermica(vector<double>kcadaMat,vector<int>NumerodePontosCadaMat);

		double getk(int P);
	private:
		void setk(vector<double>kcadaMat, vector<int>NumerodePontosCadaMat);

		vector<double>k;
};