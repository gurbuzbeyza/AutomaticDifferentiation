#include "valdi.h"

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

Var& sinh(const Var& var)
{   return makeUnaryOperation(var,Operation::sinh);  }

Var& cosh(const Var& var)
{   return makeUnaryOperation(var,Operation::cosh);  }

Var& tanh(const Var& var)
{   return makeUnaryOperation(var,Operation::tanh);  }

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
