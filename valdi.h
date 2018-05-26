#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <math.h>
#include "var.h"
#include <time.h>

using namespace std;

Var& pow(const Var& var, const Var& p);
Var& pow(const Var& var, float p);
Var&makeUnaryOperation(const Var& var, Operation op);
Var& sqrt(const Var& var);
Var& sin(const Var& var);
Var& cos(const Var& var);
Var& tan(const Var& var);
Var& asin(const Var& var);
Var& acos(const Var& var);
Var& atan(const Var& var);
Var& exp(const Var& var);
Var& log(const Var& var);
Var& makeBinaryScalarOperator(float i, const Var& n, Operation op);
Var& operator+(float i, const Var& n);
Var& operator-(float i, const Var& n);
Var& operator*(float i, const Var& n);
Var& operator/(float i, const Var& n);
Var& operator-(const Var& n);
Var& operator+(const Var& n);