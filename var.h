#ifndef VAR_H
#define VAR_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <tuple>
#include <math.h>
#include <map>
#include "operation.h"
#include "solve.hpp"


using namespace std;


class Var {

    //we should really revise the structure.
    vector<tuple<Var*,float>> derivatives;
    string name;
    float val;
    float * valList;
    bool is_scalar=false;
    Operation operation;
    tuple<Var*,Var*> parents;
    void findVals(Var* a);
    vector<tuple<Var*,float>> findDers(Var* a);
    // float solveLinEq(float& Jacobian[lenVars][lenVars], Var& n);
public:
    static vector<Var*> nodes;
    Var(Operation operation=Operation::noop, tuple<Var*,Var*>* parents=new tuple<Var*,Var*>);
    ~Var();
    // vector<tuple<Var,float>> GetCopyOfVector();
    void AddDer(Var* derOf,float der);
    // void DisplayDerValues();
    void setName(string s);

    string getName(void);
    bool isScalar(void);
    void setScalar(bool b);
    void setVal(float v);
    void setVal(float *v);
    float getVal(void);
    void setOperation(Operation operation);
    Operation getOperation(void);
    void setParents(tuple<Var*,Var*> parents);
    tuple<Var*,Var*> getParents(void);
    Var& operator+(const Var& b);
    Var& operator+(float b);
    Var& operator+(int b);
    Var& operator-(const Var& b);
    Var& operator-(float b);
    Var& operator-(int b);
    Var& operator*(const Var& b);
    Var& operator*(float b);
    Var& operator*(int b);
    Var& operator/(const Var& b);
    Var& operator/(float b);
    Var& operator/(int b);
    Var& operator=(const Var& b);
    Var& operator=(int b);
    Var& operator=(float b);
    bool operator==(const Var& b);
    Var* getVar();
    double* findDiff();
    string toString();

};


#endif