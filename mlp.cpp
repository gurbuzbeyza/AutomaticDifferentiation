
#include <stdio.h>      
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Connection
{
    public:
    double ** weights;

    Connection(int numInput,int numNeuron)
    {
        weights = new double*[numNeuron];
        for (int i = 0; i < numNeuron; ++i)
        {
            weights[i] = new double[numInput];
            for (int j = 0; j < numInput; ++j)
            {
                /* generate a number between 1 and 10: */
                weights[i][j] = rand() % 10 + 1;
            }
        }
    }
};

class Network
{
    public:
    int ** weights;
    vector<Connection> connections;
    int numConnections;
    double* totalErrors;
    Network(vector<Connection> connections)
    {
        this->connections = connections;
        numConnections = sizeof(connections)/sizeof(connections[0]);
    }
    double* activate(double* x){
        int dim1 = sizeof(x)/sizeof(x[0]) ;
        double* act =0;
        act = new double[dim1];
        for (int i = 0; i < dim1; ++i)
        {
            act[i] = tanh(x[i]);
        }
        return act;
    }
    double** activate(double** x){
        int dim1 = sizeof(x)/sizeof(x[0]) ;
        int dim2 = sizeof(x[0])/sizeof(x[0][0]);
        double** act =0;
        act = new double*[dim1];
        for (int i = 0; i < dim1; ++i)
        {
            act[i] = new double[dim2];
            for (int j = 0; j < dim2; ++j)
            {
                act[i][j] = tanh(x[i][j]);
            }
        }
        return act;
    }
    double* activateDer(double* x){
        int dim1 = sizeof(x)/sizeof(x[0]);
        double* actDer =0;
        actDer = new double[dim1];
        for (int i = 0; i < dim1; ++i)
        {
            actDer[i] = 1-tanh(x[i])*tanh(x[i]);        //update with autodiff!!!!
        }
        return actDer;
    }
    double** activateDer(double** x){
        int dim1 = sizeof(x)/sizeof(x[0]);
        int dim2 = sizeof(x[0])/sizeof(x[0][0]);
        double** actDer =0;
        actDer = new double*[dim1];
        for (int i = 0; i < dim1; ++i)
        {
            actDer[i] = new double[dim2];
            for (int j = 0; j < dim2; ++j)
            {
                actDer[i][j] = 1-tanh(x[i][j])*tanh(x[i][j]);        //update with autodiff!!!!
            }
        }
        return actDer;
    }

    double* getOutput(double* lyInp){
        int dim1 = sizeof(lyInp)/sizeof(lyInp[0]);        
        for (int i = 0; i < numConnections; ++i)
        {
            lyInp = activate(vectMatrDot(lyInp,transpose(connections[i].weights)));
        }
        return lyInp;
    }
    double LSE(double* y, double* y_expected){
        int n  = sizeof(y)/sizeof(y[0]);
        double error = 0;
        for (int i = 0; i < n; ++i)
        {
            error+=pow((y[i]-y_expected[i]),2)/2;
        }
        error/=n;
        return error;
    }

    double* vectMatrDot(double* vect, double** matr){
        int dim1 = sizeof(matr[0])/sizeof(matr[0][0]);//2   vect[1 0]
        int dim2 = sizeof(matr)/sizeof(matr[0]);//7
        double dot[dim1];
        for (int i = 0; i < dim1; ++i)
         {
             double doti = 0;
             for (int j = 0; j < dim2; ++j)
             {
                 doti+=matr[j][i]*vect[i];
             }
             dot[i] = doti;
         }
         return dot;
    }
    double* transpose(double* matr){
        int dim1 = sizeof(matr)/sizeof(matr[0]);
        int dim2 = 1;
        double** tr =0;
        tr = new double*[dim2];
        for (int i = 0; i < dim1; ++i)
        {
            tr[i] = new double[dim1];
            for (int j = 0; j < dim2; ++j)
            {
                tr[j][i] = matr[i][j];
            }
        }
        return tr;
    }
    double** transpose(double** matr){
        int dim1 = sizeof(matr)/sizeof(matr[0]);
        int dim2 = sizeof(matr[0])/sizeof(matr[0][0]);
        double** tr =0;
        tr = new double*[dim2];
        
        for (int i = 0; i < dim1; ++i)
        {
            tr[i] = new double[dim1];
            for (int j = 0; j < dim2; ++j)
            {
                tr[j][i] = matr[i][j];
            }
        }
        return tr;
    }


    void train(double* lyInp, double* expectedOutputs,double eta,int iterNum){
        int numOutputs = sizeof(expectedOutputs)/sizeof(expectedOutputs[0]);
        double* inputs = lyInp;
        while(iterNum>0){
            iterNum--;
            double* curOutputs[numOutputs];
            for (int i = 0; i < numConnections; ++i)
            {
                lyInp = activate(vectMatrDot(lyInp,transpose(connections[i].weights)));
                curOutputs[i] = lyInp;
            }
            vector<double> errors[numConnections];
            vector<double> deltas[numConnections];
            
            fill(errors+numConnections-1,errors+numConnections,vector<double>(numOutputs));
            fill(deltas+numConnections-1,deltas+numConnections,vector<double>(numOutputs));
            double* derCurout = activateDer(curOutputs[numConnections-1]);
            for (int i = 0; i < numOutputs; ++i)
            {
                errors[numConnections-1][i] =expectedOutputs[i]-curOutputs[numConnections-1][i];
                deltas[numConnections-1][i] =errors[numConnections-1][i]*derCurout[i];       //error may occur due to this line
            }
            //calculate the error starting from the last layer
            for (int i = numConnections-2; i >-1; --i)
            {
                double* dercurouti = activateDer(curOutputs[i]);
                errors[i] = vectMatrDot(deltas[i+1],connections[i+1].weights);
                for (int j = 0; j< sizeof(errors)/sizeof(errors[i]); ++j)
                {
                    deltas[i][j]=errors[i][j]* dercurouti[j];
                }
            }
            double adjustments [numConnections];
            adjustments[0] = vectMatrDot(transpose(inputs),deltas[0]);
            for (int i = 1; i < numConnections; ++i)
            {
                adjustments[i] = vectMatrDot(transpose(curOutputs[i-1]),deltas[i]);
            }
            for (int i = 0; i < numConnections; ++i)
            {
                int dim1 = sizeof(connections[i].weights)/sizeof(connections[i].weights[0]);
                int dim2 = sizeof(connections[i].weights[0])/sizeof(connections[i].weights[0][0]);
                //l.weights+=eta*adjustments[i].T
                double* trAdjs = transpose(adjustments);
                for (int j = 0; j < dim1; ++j)
                {
                    for (int k = 0; k < dim2; ++k)
                    {
                        connections[i].weights[j][k]+= eta*trAdjs[i][j][k];
                    }       
                }
            }
        }
    }

};


int main() {
    Connection c(3,5);

    return 0;
}