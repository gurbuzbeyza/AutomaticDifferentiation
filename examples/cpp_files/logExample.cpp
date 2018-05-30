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

	vector<float> X; 
    vector<float> Y; 
    vector<float> Ydiff; 
    Var res;
    Var x;
    x.makeInput();
    res = log(x);
    for (int i = 0; i < 50; ++i)
    {
        X.push_back((float)i);
    }
    res.result();
    ofstream myfile;
    myfile.open("../txt_files/logEx.txt");
    for (int i = 0; i < X.size(); ++i)
    {
        x = X[i];
        map<Var*, float> diffs = res.findDiff();
        Ydiff.push_back(diffs[&x]);
        Y.push_back(res.getVal());
    }
    for (int i = 0; i < Y.size(); ++i)
    {
        myfile<<X[i]<<" "<<Y[i]<<" "<<Ydiff[i]<<endl;
    }
    return 0;

}