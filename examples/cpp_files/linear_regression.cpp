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
	ifstream dataset("../txt_files/lineards.txt");
	ifstream label("../txt_files/linearlb.txt");
	vector<float> X; 
	vector<float> Y; 
	float a;
	while (dataset >> a)
	{
		X.push_back(a);
	}

	while (label >> a)
	{
		Y.push_back(a);
	}

    auto start = std::chrono::high_resolution_clock::now();
     
    Var b0;
    b0 = 0;
    Var b1;
    b1 = 0;
    b0.makeInput();
    b1.makeInput();
    Var err;
    err = 0;
    Var temp;
    temp = 0;
    float alpha = 0.01;
    for (int j = 0; j < 50; ++j)
    {
        temp += pow((b0 + b1 * X[j] - Y[j]),2)/50;
    }
    err = sqrt(temp);
    err.result();
    float val0 = 500000;
    float val1 = 500000;
    int k = 0;
    for(int i = 0; i < 100000; i++){
        map<Var*, float> diffs = err.findDiff();
        val0 = b0.getVal() - (float)(alpha * diffs.at(&b0));
        val1 = b1.getVal() - (float)(alpha * diffs.at(&b1));
        if (abs(b0.getVal() - val0) < 0.0000001 && abs(b1.getVal() - val1) < 0.0000001)
            break;
        b0 = val0;
        b1 = val1;
        k++;
    }
    ofstream myfile;
    myfile.open("../txt_files/linearweights.txt");
    myfile<<b1.getVal()<<" "<<b0.getVal();
    cout<<"number of iterations: " << k<<endl;
    cout<<"afterdiff: \n"<<b1.getVal()<<" "<<b0.getVal()<<" "<<err.getVal()<<endl;
    auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    return 0;

}