#include <vector>
#include <iostream>

using namespace std;

class SolverLinear
{
	public:
		SolverLinear(vector<vector<double> >A,vector<double>b,int n);
		vector<double> getCampodeTemperaturas();
	private:
		vector<double>CampodeTemperaturas;
};