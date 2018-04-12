#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <math.h>
#include "var.h"
#include <time.h>

using namespace std;

Var& pow(const Var& var,const Var&  p){
    Var *newVar = (Var*)&var;
    Var *newP = (Var*)&p;
    tuple<Var*,Var*> parents (newVar, newP);
    Var* v = new Var(Operation::pow, &parents);
    return *v;
}

Var&makeUnaryOperation(const Var& var, Operation op){
    Var *newVar = (Var*)&var;
    Var *newP = NULL;
    tuple<Var*,Var*> parents (newVar, newP);
    Var* v = new Var(op, &parents);
    return *v;    
}

Var& sqrt(const Var& var)
{    return makeUnaryOperation(var,Operation::sqrt);    }

Var& sin(const Var& var)
{   return makeUnaryOperation(var,Operation::sin);  }

Var& cos(const Var& var)
{   return makeUnaryOperation(var,Operation::cos);  }

Var& tan(const Var& var)
{   return makeUnaryOperation(var,Operation::tan);  }

Var& asin(const Var& var)
{   return makeUnaryOperation(var,Operation::asin);  }

Var& acos(const Var& var)
{   return makeUnaryOperation(var,Operation::acos);  }

Var& atan(const Var& var)
{   return makeUnaryOperation(var,Operation::atan);  }

Var& exp(const Var& var)
{   return makeUnaryOperation(var,Operation::exp);  }

Var& log(const Var& var)
{   return makeUnaryOperation(var,Operation::log);  }


Var& makeBinaryScalarOperator(float i, const Var& n, Operation op){
    Var *newVar = (Var*)&n;
    tuple<Var*,Var*> noParents (NULL, NULL);
    Var* bs = new Var(Operation::noop, &noParents);
    bs-> setVal(i);
    bs-> setScalar(true);
    tuple<Var*,Var*> parents (bs, newVar);
    Var* v = new Var(op,&parents);
    return *v;
}

Var& operator+(float i, const Var& n)
{    return makeBinaryScalarOperator(i,n,Operation::add);    }

Var& operator-(float i, const Var& n)
{    return makeBinaryScalarOperator(i,n,Operation::sub);   }

Var& operator*(float i, const Var& n)
{    return makeBinaryScalarOperator(i,n,Operation::mult);  }

Var& operator/(float i, const Var& n)
{    return makeBinaryScalarOperator(i,n,Operation::divd);   }

Var& operator-(const Var& n)
{    return makeBinaryScalarOperator(-1.0,n,Operation::mult);   }

Var& operator+(const Var& n)
{    return makeBinaryScalarOperator(1.0,n,Operation::mult);    }


void printDiffs(Var & v){

    double* fs = v.findDiff();
    cout<<"derivatives: "<<endl;
    for (int i = 0; i < 2; ++i)
    {
            cout<<i<<": "<<fs[i]<<endl;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////MAIN////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////





int main(int argc, char const *argv[])
{
    clock_t t1 = clock();
    float x[] = {1,2,3,4,5,10,11,12,13,14};
    float y[] = {0,0,0,0,0,1,1,1,1,1};
     
    Var b0;
    b0 = 2;
    Var b1;
    b1 = 2;
    Var err;
    Var p;
    float alpha = 0.01;
    for (int i = 0; i < 20; i ++) {
        int idx = i % 10;
        p = b0 + b1 * x[idx];
        err = (p - y[idx])*(p - y[idx]);
        double* diffs = err.findDiff();
        //cout<<"afterdiff: \n"<<b0.toString()<<"\n"<<b1.toString()<<"\n"<<err.toString()<<endl;
        //cout<<diffs[0]<<" "<<diffs[1]<<endl;
        b0 = b0 - (float)(alpha * diffs[0]);
        b1 = b1 - (float)(alpha * diffs[1]);
    }
    clock_t t2 = clock();
    cout<<(float)t2-(float)t1<<endl;
    return 0;

}

/*Var& someCalculations(Var& a, Var& b){
    // res = 0;
    a = 5;
    for (int i = 0; i < 2; ++i)
    {
        a *= b + 2;
        // cout<<res.toString()<<endl;
    }
    return a;
}

int main() {
    /// just try some stuff

    //define nodes
    Var a;
    Var b;
    Var res;
    //res = {1,2};
    //
    res = someCalculations(a, b);
    b = 7;
    // cout<<res.getVal()<<endl;
    printDiffs(res);
    return 0;
}*/