#include <stdio.h>      
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <vector>
#include <math.h>
#include "../../AutoDiff/autodiff.h"

using namespace std;

int main() {
    //initialize weights
    
    float w1 [4][2];//2,4
    float w2 [1][4];//4,1
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                w1[i][j]=1;//initialize all weights with 1
            }
        }
        for (int i = 0; i < 1; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                w2[i][j]=1;//initialize all weights with 1
            }
        }
    int iterNum = 10000;
    float inputs[4][2] = {{0, 1},{0, 0},{1, 1},{1, 0}};//4, 2
    float outputs[4][1] = {{1},{0},{1},{1}};
    Var inp1[4][4];
    Var inp2[4][1];
    Var o1[4][4];
    Var o2[4][1];
    float l2error[4][1];
    float l2delta[4][1];

    float l1error[4][4];
    float l1delta[4][4];

    float w1adj [4][2] ;
    float w2adj [1][4] ;

    for (int n = 0; n < 4; ++n)
    {
        for (int i = 0; i < 4; ++i)
        {
            float x = 0;
            inp1[n][i].makeInput();
            for (int j = 0; j < 2; ++j)
            {
                x += inputs[n][j]*w1[i][j];
            }
            inp1[n][i] = x;
            o1[n][i] = tanh(inp1[n][i]);
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            o1[i][j].result();
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            o1[i][j].findDiff();
        }
    }
    for (int n = 0; n < 4; ++n)
    {
        for (int i = 0; i < 1; ++i)
        {
            float x = 0;
            inp2[n][i].makeInput();
            for (int j = 0; j < 4; ++j)
            {
                x += o1[n][j].getVal()*w2[i][j];
            }
            inp2[n][i] = x;
            o2[n][i] = tanh(inp2[n][i]);
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 1; ++j)
        {
            o2[i][j].result();
        }
    }
    while(iterNum>0){
        iterNum--;

        map<Var*, float> o1diffs[4][4];
        map<Var*, float> o2diffs[4][1];
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                o1diffs[i][j] = o1[i][j].findDiff();
            }
        }
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 1; ++j)
            {
                o2diffs[i][j] = o2[i][j].findDiff();
            }
        }
        for (int n = 0; n < 4; ++n)
        {
            for (int i = 0; i < 1; ++i)
            {
                l2error[n][i] = outputs[n][i]-o2[n][i].getVal();
            }
        }
        // cout<<"1"<<endl;
        for (int n = 0; n < 4; ++n)
        {
            for (int i = 0; i < 1; ++i)
            {
                l2delta[n][i] = l2error[n][i]*o2diffs[n][i].at(&inp2[n][i]);
            }
        }
        // cout<<"2"<<endl;
        for (int n = 0; n < 4; ++n)
        {
            for (int i = 0; i < 1; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    l1error[n][j] = l2delta[n][i]*w2[i][j];
                }
            }
        }
        for (int n = 0; n < 4; ++n)
        {
            for (int i = 0; i < 4; ++i)
            {

                l1delta[n][i] = l1error[n][i]*o1diffs[n][i].at(&inp1[n][i]);
            }
        }
        // cout<<"3"<<endl;
        for (int j = 0; j < 2; ++j)
        {
            for (int i = 0; i < 4; ++i)
            {
                float tmp = 0;
                for (int n = 0; n < 4; ++n)
                {
                    tmp += inputs[n][j]*l1delta[n][i];
                }
                w1adj[i][j]=tmp/4;
            }
        }

        for (int j = 0; j < 4; ++j)
        {
            for (int i = 0; i < 1; ++i)
            {
                float tmp = 0;
                for (int n = 0; n < 4; ++n)
                {
                    tmp += o1[n][j].getVal()*l2delta[n][i];
                }
                w2adj[i][j]=tmp/4;
            }
        }

        for (int n = 0; n < 4; ++n)
        {
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 2; ++j)
                {
                    w1[i][j] += w1adj[i][j];
                }
            }
        }

        for (int n = 0; n < 4; ++n)
        {
            for (int i = 0; i < 1; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    w2[i][j] += w2adj[i][j];
                }
            }
        }
        for (int n = 0; n < 4; ++n)
        {
            for (int i = 0; i < 4; ++i)
            {
                float x = 0;
                for (int j = 0; j < 2; ++j)
                {
                    x += inputs[n][j]*w1[i][j];
                }
                inp1[n][i] = x;
            }
        }
        for (int n = 0; n < 4; ++n)
        {
            for (int i = 0; i < 1; ++i)
            {
                float x = 0;
                for (int j = 0; j < 4; ++j)
                {
                    x += o1[n][j].getVal()*w2[i][j];
                }
                inp2[n][i] = x;
            }
        }
    }
    float inp[2] = {1,0};
    float o1in[4];
    float o2in[1];
    for (int i = 0; i < 4; ++i)
    {
        o1in[i] = 0;
        for (int j = 0; j < 2; ++j)
        {
            o1in[i]+=inp[j]*w1[i][j];
        }
        o1in[i] = tanh(o1in[i]);
    }
    for (int i = 0; i < 1; ++i)
    {
        o2in[i] = 0;
        for (int j = 0; j < 4; ++j)
        {
            o2in[i]+=o1in[j]*w2[i][j];
        }
        o2in[i] = tanh(o2in[i]);
    }
    cout<<"wut: "<<o2in[0]<<endl;

}