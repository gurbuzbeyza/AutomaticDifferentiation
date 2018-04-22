using namespace std;

#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
int main(int argc, char const *argv[])
{
    clock_t t1 = clock();
    float x[] = {1,2,3,4,5,10,11,12,13,14};
    float y[] = {0,0,0,0,0,1,1,1,1,1};
     
    double b0;
    b0 = 0;
    double b1;
    b1 = 0;
    double err;
    float alpha = 0.01;
    for (int i = 0; i < 1; i ++) {
        int idx = i % 5;
        double p = b0 + b1 * x[idx];
        err = p - y[idx];
        b0 = b0 - alpha * err;
        b1 = b1 - alpha * err * x[idx];
    }
    clock_t t2 = clock();
    cout<<(float)t2-(float)t1<<endl;
    return 0;

}