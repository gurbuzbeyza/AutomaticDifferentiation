#include <iostream>
#include <math.h>
#include <numeric>
#include "../../AutoDiff/autodiff.h"
#include <chrono>


using namespace std;

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    float inputs[4][3] = {  
        {0.52, 1.12,  0.77},
        {0.88, -1.08, 0.15},
        {0.52, 0.06, -1.30},
        {0.74, -2.49, 1.39}   /*  initializers for row indexed by 2 */
    };

    bool targets[4] = {1, 1, 0, 1};

    Var sum;
    sum = 0;
    Var a;
    Var b;
    Var c;
    Var weights[3] = {a, b, c};
    for (int i = 0; i < 3; ++i)
    {
        weights[i].makeInput();
        weights[i] = 0;
    }
    for (int i = 0; i < 4; ++i)
    {
        Var* pred = new Var();
        *pred = 0;
        Var *temp = new Var();
        *temp = 0;
        for (int j = 0; j < 3; j++)
        {
            *temp += inputs[i][j]*weights[j];

        }
        *pred = 1/(1+exp(-1*(*temp)));

        sum -= log(*pred*targets[i] + (1 - *pred) * (1 - targets[i]));
    }

    sum.result();
    float alpha = 0.01;
    int k = 0;
    for(int i = 0; i < 100000; i++){
        k++;
        map<Var*, float> diffs = sum.findDiff();
        // cout<<sum.getVal()<<endl;;
        for (int i = 0; i < 3; ++i)
        {
            float val = weights[i].getVal();
            weights[i] = weights[i].getVal() - (float)(alpha * diffs.at(&weights[i]));
        }
    }
    // cout<<k<<endl;
    for (int i = 0; i < 3; ++i)
    {
        cout<<weights[i].getVal()<<" ";
    }
    cout<<sum.getVal()<<endl;
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}
