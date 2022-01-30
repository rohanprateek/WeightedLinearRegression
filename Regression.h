#ifndef Regression

#include<iostream>
#include</usr/local/include/eigen3/Eigen/Dense>
#include<fstream>
#include<sstream>
#include<cmath>

using namespace std;
using namespace Eigen;

class Regression
{
    public:
        
        
        
        
        void fitData(vector<vector<float>>& xTrain, vector<vector<float>>& xTest, vector<vector<float>>& yTrain, vector<vector<float>>& yTest)
        {
            TrainX.resize(xTrain.size(), xTrain[0].size());
            
            for(int i = 0; i < xTrain.size(); i++)
            {
                for(int j = 0; j < xTrain[i].size(); j++)
                {
                    TrainX(i, j) = xTrain[i][j];
                }
            }
            
            TrainY.resize(yTrain.size(), 1);
            
            for(int i = 0; i < yTrain.size(); i++)
            {
                    TrainY(i, 0) = yTrain[i][0];
            }
            
            TestX.resize(xTest.size(), xTest[0].size());

            for(int i = 0; i < xTest.size(); i++)
            {
                for(int j = 0; j < xTest[i].size(); j++)
                {
                    TestX(i, j) = xTest[i][j];
                }
            }
            
            TestY.resize(yTest.size(), yTest[0].size());

            for(int i = 0; i < yTest.size(); i++)
            {
                for(int j = 0; j < yTest[i].size(); j++)
                {
                    TrainY(i, j) = yTest[i][j];
                }
            }

            //cout<<TrainX.rows()<<" "<<TrainX.cols()<<"\n"<<TestX.rows()<<" "<<TestX.cols()<<"\n"<<TrainY.rows()<<" "<<TrainY.cols()<<"\n"<<TestY.rows()<<" "<<TestY.cols()<<"\n";
        }

        
        
        
        
        
        void generateLinearWeights()
        {
            X_train.resize(TrainX.rows(), TrainX.cols() + 1);
            X_train << VectorXf::Constant(TrainX.rows(), 1, 1.0), TrainX;
            
            MatrixXf Xt = X_train.transpose();
            MatrixXf temp = Xt * X_train;
            weights = temp.inverse() * Xt * TrainY;
            //cout<<weights.size();
        }

        
        
        
        
        
        void getError(string path, string type="linear")
        {
            
            if(path.length() == 0) 
            {
                path = "TrainingResults_" + type + ".csv";
            }

            else
            {
                path = path + "/TrainingResults_" + type + ".csv";
            }

            //cout<<path<<"\n";
            if(type == "linear")
            {
                TrainResult = X_train * weights;
            }

            else if(type == "weighted")
            {
                TrainResult = X_train * weights_weighted;
            }

            else
            {
                cout<<"Wrong 'Type' was passed... \n aborted\n";
                return;
            }

            fstream fout;            
            fout.open(path, ios :: out);

            vector<double> rmse;

            for(int i = 0; i < TrainResult.rows(); i++)
            {
                double temp = pow(TrainY(i, 0) - TrainResult(i, 0), 2);
                fout<<temp<<"\n";
                rmse.emplace_back(temp);
            }

            fout.close();

            double error = 0.0;

            for(int i = 0; i < rmse.size(); i++)
            {
                error += rmse[i];
            }
            
            error /= rmse.size();
            error = sqrt(error);
            //error = pow(error / rmse.size(), 1/2);
            
            cout<<"The training error was found to be : "<<error<<"\n";
        }

        
        
        
        void predict(string path, string type="linear")
        {
            fstream fout;

            if(path.length() == 0) 
            {
                path = "TestingResults_" + type + ".csv";
            }

            else
            {
                path = path + "/TestingResults_" + type + ".csv";
            }
            //cout<<path<<"\n";

            fout.open(path, ios :: out);

            X_test.resize(TestX.rows(), TestX.cols() + 1);
            X_test << VectorXf::Constant(TestX.rows(), 1, 1.0), TestX;

            if(type == "linear")
            {
                TestResult = X_test * weights;
            }

            else if(type == "weighted")
            {
                TestResult = X_test * weights_weighted;
            }

            else
            {
                cout<<"Wrong 'Type' was passed... \n aborted\n";
                return;
            }

            vector<double> rmse;

            for(int i = 0; i < TestResult.rows(); i++)
            {
                double temp = pow(TestY(i, 0) - TestResult(i, 0), 2);
                fout<<temp<<"\n";
                rmse.emplace_back(temp);
            }

            fout.close();

            double error = 0.0;

            for(int i = 0; i < rmse.size(); i++)
            {
                error += rmse[i];
            }
            
            error /= rmse.size();
            error = sqrt(error);
            //error = pow(error / rmse.size(), 1/2);
            
            cout<<"The testing error was found to be : "<<error<<"\n";
        }

        
        
        void generateWeightedWeights()
        {
            residues = TrainY - (X_train * weights);
            
            corr = residues.array().pow(2).matrix().asDiagonal();
            corr = corr.inverse();
	        
            MatrixXf Xt = X_train.transpose();
            MatrixXf temp = Xt * corr * X_train;
	        MatrixXf temp2 = Xt * corr * TrainY;
	        weights_weighted = temp.inverse() * temp2;
        }




    private:
        MatrixXf TrainX, TestX;
        VectorXf TrainY, TestY, residues;
        MatrixXf weights, X_train, X_test, weights_weighted, corr;
        MatrixXf TrainResult, TestResult;
};


#endif