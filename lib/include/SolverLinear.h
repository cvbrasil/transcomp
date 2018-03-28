#include <vector>
#include <iostream>

using namespace std;

class SolverLinear
{
	public:
		SolverLinear(vector<vector<double> >A,vector<double>b,int n);
		vector<double> getCampodeTemperaturas();
		vector<double> getCampodeTemperaturasTDMA();
	private:
		vector<double>CampodeTemperaturas;
		vector<vector<double> >Avec;
		vector<double>bvec;
		int nint;
};