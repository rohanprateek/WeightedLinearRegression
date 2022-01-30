#ifndef dataset

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<valarray>

using namespace std;

class Dataset
{
	public:
		vector<vector<vector<float>>> read(string s, bool write=false, string pathToWrite="")
		{
			fstream fin;
			fin.open(s, ios::in);
			
			vector<vector<float>> rows;
		    vector<float> single;
			
			string row, num;
			
			while(!fin.eof())
			{
				single.clear();
				getline(fin, row);
				stringstream ss(row);
				
				while(getline(ss, num, ','))
				{
					single.emplace_back((float)atof(num.c_str()));
				}
				
				rows.emplace_back(single);
			}
                        
			int size = rows.size(), attr = rows[0].size();
			int train = size * 0.8;
			//cout<<size<<" "<<attr<<" "<<train<<"\n";
			vector<vector<float>> xTrain, yTrain, xTest, yTest;
			
			for(int i = 0; i < train; i++)
			{	
				single.resize(attr - 1);
				copy(rows[i].begin(), rows[i].begin() + attr - 1, single.begin());
				xTrain.emplace_back(single);
				single.clear();
				single.emplace_back(rows[i][attr - 1]);
				yTrain.emplace_back(single);
			}
			
			
			for(int i = train; i < size - 1; i++)
			{	
				single.resize(attr - 1);
				copy(rows[i].begin(), rows[i].begin() + attr - 1, single.begin());
				xTest.emplace_back(single);
				single.clear();
				single.emplace_back(rows[i][attr - 1]);
				yTest.emplace_back(single);
			}
			
			if(write)
			{
				writeToDisk(pathToWrite, {xTrain, yTrain, xTest, yTest});
			}

			return {xTrain, yTrain, xTest, yTest}; //return {rows};
		}

		
		void writeToDisk(string path, vector<vector<vector<float>>> splits)
		{
			fstream fout;
			string paths[4];

			if(path.length() != 0)
			{
			       	paths[0] = path + "/xTrain.csv";
			       	paths[1] = path + "/yTrain.csv";
			       	paths[2] = path + "/xTest.csv";
			       	paths[3] = path + "/yTest.csv";
			}

			else
			{
				paths[0] = "xTrain.csv";
			    paths[1] = "yTrain.csv";
			    paths[2] = "xTest.csv";
			    paths[3] = "yTest.csv";
			}
			
			for(int i = 0; i < 4; i++)
			{
				fout.open(paths[i], ios::out);
				vector<vector<float>> cur = splits[i];
			
				for(int j = 0; j < cur.size(); j++)
				{
					int k;
					for(k = 0; k < cur[j].size() - 1; k++)
					      fout<<cur[j][k]<<", ";	
					fout<<cur[j][k]<<"\n";
				}
				
				fout.close();
			}
		}

};

#endif
