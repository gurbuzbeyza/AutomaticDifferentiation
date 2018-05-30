#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <math.h>
#include "../../AutoDiff/autodiff.h"
#include <chrono>

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream dataset("../txt_files/regexds.txt");
	ifstream label("../txt_files/regexlb.txt");
	vector<vector<float>> X; 
	vector<float> Y; 
	float a, b, c;
	while (dataset >> a >> b >> c)
	{
        vector<float> v;
		v.push_back(a);
        v.push_back(b);
        v.push_back(c);
        X.push_back(v);
	}

	while (label >> a)
	{
		Y.push_back(a);
	}

    auto start = std::chrono::high_resolution_clock::now();
     
    Var b0;
    Var b1;
    Var b2;
    Var weights[3] = {b0, b1, b2};
    for (int i = 0; i < 3; ++i)
    {
        weights[i].makeInput();
        weights[i] = 0;
    }
    Var err;
    err = 0;
    Var temp;
    temp = 0;
    for (int j = 0; j < 50; ++j)
    {
        Var* p = new Var();
        for (int i = 0; i < 3; ++i)
        {
            *p += weights[i]*X[j][i];
        }
        temp += pow((*p - Y[j]),2)/50;
    }
    err = sqrt(temp);
    err.result();
    float alpha = 0.01;
    int k = 0;
    for(int i = 0; i < 100000; i++){
        k++;
        map<Var*, float> diffs = err.findDiff();
        for (int i = 0; i < 3; ++i)
        {
            float val = weights[i].getVal();
            weights[i] = weights[i].getVal() - (float)(alpha * diffs.at(&weights[i]));
        }
    }
    ofstream myfile;
    myfile.open("../txt_files/regexweights.txt");
    for (int i = 0; i < 3; ++i)
    {
        myfile<<weights[i].getVal()<<" ";
        cout<<weights[i].getVal()<<" ";
    }
    cout<<err.getVal()<<endl;
    auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    return 0;

}