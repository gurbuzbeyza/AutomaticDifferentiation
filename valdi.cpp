#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <math.h>
#include "var.h"
#include <time.h>

using namespace std;

Var& pow(const Var& var, const Var& p){
    Var *newVar = (Var*)&var;
    Var *newP = (Var*)&p;
    tuple<Var*,Var*> parents (newVar, newP);
    Var* v = new Var(Operation::pow, &parents);
    return *v;
}

Var& pow(const Var& var, float p){
    Var *newVar = (Var*)&var;
    tuple<Var*,Var*> noParents (NULL, NULL);
    Var* bs = new Var(Operation::noop, &noParents);
    bs-> setVal(p);
    bs-> setScalar(true);
    tuple<Var*,Var*> parents (newVar, bs);
    Var* v = new Var(Operation::pow,&parents);
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
{    return makeBinaryScalarOperator(-1.0,n,Operation::sub);   }

Var& operator+(const Var& n)
{    return makeBinaryScalarOperator(1.0,n,Operation::add);    }



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////MAIN////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////




int main(int argc, char const *argv[])
{
    clock_t t1 = clock();
    float x[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    float y[] = {2.0, 5.0, 5.0, 8.0, 11.0};
     
    Var b0;
    b0 = 1;
    Var b1;
    b1 = 2;
    b0.makeInput();
    b1.makeInput();
    Var err;
    err = 0;
    float alpha = 0.001;
    for (int j = 0; j < 5; ++j)
     {
         err += pow((b0 + b1 * x[j] - y[j]),2)/2;
     }
    err = pow((b0 + b1 * x[1] - y[1]),2)/2 + pow((b0 + b1 * x[0] - y[0]),2)/2;
    
    err.result();
    int i = 0;
    float val0 = 500000;
    float val1 = 500000;

    while(true){
        map<Var*, float> diffs = err.findDiff();
        val0 = b0.getVal() - (float)(alpha * diffs.at(&b0));
        val1 = b1.getVal() - (float)(alpha * diffs.at(&b1));
        if (abs(b0.getVal() - val0) < 0.000001 && abs(b1.getVal() - val1) < 0.000001)
            break;
        b0 = val0;
        b1 = val1;
    }
    cout<<"afterdiff: \n"<<b0.getVal()<<" "<<b1.getVal()<<" "<<err.getVal()<<endl;
    cout<<i<<endl;
    clock_t t2 = clock();
    cout<<(float)t2-(float)t1<<endl;

    return 0;

}