#include<iostream>
#include "data.h"
#include "Regression.h"

using namespace std;

int main()
{
	Dataset d;
	Regression r;
	string file = "fish.csv";
	vector<vector<float>> xTrain, xTest, yTrain, yTest;
	vector<vector<vector<float>>> data;
	
	data = d.read(file, false, "fishSplitData");
	
	xTrain = data[0];
	yTrain = data[1];
	xTest = data[2];
	yTest = data[3];
	
	r.fitData(xTrain, xTest, yTrain, yTest);


	cout<<"Linear Regression...\n";
	r.generateLinearWeights();
	r.getError("fishSplitData", "linear");
	r.predict("fishSplitData", "linear");

	cout<<"Weighted Linear Regression...\n";
	r.generateWeightedWeights();
	r.getError("fishSplitData", "weighted");
	r.predict("fishSplitData", "weighted");
	//cout<<xTrain.size()<<" "<<yTrain.size()<<" "<<xTest.size()<<" "<<yTest.size()<<"\n";
	
	return 0;
}

