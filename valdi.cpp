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


// void printDiffs(Var & v){

//     double* fs = v.findDiff();
//     cout<<"derivatives: "<<endl;
//     for (int i = 0; i < 2; ++i)
//     {
//             cout<<i<<": "<<fs[i]<<endl;
//     }
// }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////MAIN////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////






// Var& someCalculations(Var& a, Var& b){
//     // res = 0;
//     a = 5;
//     for (int i = 0; i < 2; ++i)
//     {
//         a *= b + 2;
//         // cout<<res.toString()<<endl;
//     }
//     return a;
// }

// int main() {
//     /// just try some stuff

//     //define nodes
//     Var a;
//     Var b;
//     a = 3;
//     b = 2;
//     Var res;
//     //res = {1,2};
//     //
//     res = a + b;
//     res.result();
//     b = 7;
//     // cout<<res.getVal()<<endl;
//     printDiffs(res);
//     return 0;
// }


int main(int argc, char const *argv[])
{
    Var a0,a1,a2,res;
    // a0.makeInput();
    //y = x;
    a0.makeInput();
    a1.makeInput();
    a2.makeInput();

    // a2.makeInput();

    res = 2*a1+a0*a2+a1-a2*a1;// + a1;
    a0 = 1;
    a1 = 25;
    a2=10;
    // a2 = 3;
    //cout<<<<endl;
    cout<<"# total inputs: "<<a1.inputs.size()<<endl;
    // cout<<"# depInps to a0: "<<a0.getDependentInputs().size()<<endl;
    cout<<"# depInps to a1: "<<a1.getDependentInputs().size()<<endl;
    // cout<<"# depInps to a2: "<<a2.getDependentInputs().size()<<endl;
    cout<<"# depInps to res: "<<res.getDependentInputs().size()<<endl;
    res.result();
    map<Var*, float> diffs = res.findDiff();
    map<float, float> newMap;
    cout<<diffs.at(&a0)<<endl;
    cout<<diffs.at(&a1)<<endl;
    cout<<diffs.at(&a2)<<endl;
    // cout<<diffs.at(&a2)<<endl;
    // cout<<res.findDiff().find(a1)<<endl;
    // cout<<res.findDiff().find(a2)<<endl;

    // for (vector<Var*>::iterator i = x.nodes.begin(); i != x.nodes.end(); ++i){
    //     Var* a = *i;
    //     cout<<a->getVal()<<" "<<a->getDependentInputs().size()<<endl;
    // }
    /*clock_t t1 = clock();
    float x[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    float y[] = {2.0, 5.0, 5.0, 8.0, 11.0};
     
    Var b0;
    b0 = 12;
    Var b1;
    b1 = 4;
    Var err;
    err = 0;
    float alpha = 0.01;
    for (int j = 0; j < 5; ++j)
    {
        err += pow((b0 + b1 * x[j] - y[j]),2)/2;
    }
    err.result();
    int i = 0;
    float val0 = 500000;
    float val1 = 500000;

    while (true){
        double* diffs = err.findDiff();
        val0 = b0.getVal() - (float)(alpha * diffs[0]);
        val1 = b1.getVal() - (float)(alpha * diffs[1]);
        if (abs(b0.getVal() - val0) < 0.0001 && abs(b1.getVal() - val1) < 0.0001)
            break;
        b0 = val0;
        b1 = val1;
        i+=1;
    }
    cout<<"afterdiff: \n"<<b0.getVal()<<" "<<b1.getVal()<<" "<<err.getVal()<<endl;
    cout<<i<<endl;
    clock_t t2 = clock();
    cout<<(float)t2-(float)t1<<endl;
    */

    return 0;

}