#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <math.h>
#include "valdi.h"
#include <time.h>

using namespace std;
int main(int argc, char const *argv[])
{
    clock_t t1 = clock();
    float x[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    float y[] = {2.0, 4.0, 6.0, 8.0, 10.0, 12.0};
     
    Var b0;
    b0 = 0;
    Var b1;
    b1 = 0;
    b0.makeInput();
    b1.makeInput();
    Var err;
    err = 0;
    float alpha = 0.001;
    for (int j = 0; j < 6; ++j)
    {
        Var* p = new Var();
        Var a = *p;
        *p = b0 + b1 * x[j];
        err += pow((*p - y[j]),2)/2;
    }
    
    err.result();
    int i = 0;
    float val0 = 500000;
    float val1 = 500000;

    while(true){
        map<Var*, float> diffs = err.findDiff();
        val0 = b0.getVal() - (float)(alpha * diffs.at(&b0));
        val1 = b1.getVal() - (float)(alpha * diffs.at(&b1));
        if (abs(b0.getVal() - val0) < 0.0000001 && abs(b1.getVal() - val1) < 0.0000001)
            break;
        b0 = val0;
        b1 = val1;
        i+=1;
    }
    cout<<"afterdiff: \n"<<b0.getVal()<<" "<<b1.getVal()<<" "<<err.getVal()<<endl;
    cout<<i<<endl;
    clock_t t2 = clock();
    cout<<(float)t2-(float)t1<<endl;

    return 0;

}