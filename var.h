#ifndef VAR_H
#define VAR_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <tuple>
#include <math.h>
#include <map>
#include "operation.h"
#include "solve.hpp"
#include <set>


using namespace std;

class Var {

    //we should really revise the structure.
    vector<tuple<Var*,float>> derivatives;
    string name;
    bool is_input = false;
    float val;
    float * valList;
    set<Var*> inputList;
    bool is_scalar=false;
    Operation operation;
    tuple<Var*,Var*> parents;

    float recVars(Var* v);
    float findVals(Var* a, float left, float right);
    void recDers(Var* v);
    void findDers(Var* a);
    // float solveLinEq(float& Jacobian[lenVars][lenVars], Var& n);
public:
    static vector<Var*> nodes;
    static set<Var*> inputs;
    Var(Operation operation=Operation::noop, tuple<Var*,Var*>* parents=new tuple<Var*,Var*>);
    ~Var();
    // vector<tuple<Var,float>> GetCopyOfVector();
    void AddDer(Var* derOf,float der);
    // void DisplayDerValues();
    void setName(string s);

    string getName(void);
    bool isScalar(void);
    bool isInput(void);
    void makeInput(void);
    void setScalar(bool b);
    void setVal(float v);
    void setVal(float *v);
    float getVal(void);
    void setInputList(set<Var*> p1, set<Var*> p2);
    set<Var*> getInputList(void);
    void setOperation(Operation operation);
    Operation getOperation(void);
    void setParents(tuple<Var*,Var*> parents);
    tuple<Var*,Var*> getParents(void);
    Var& makeBinaryVarOperation(const Var& b, Operation op);
    Var& makeBinaryVarOperation(float i, Operation op);
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
    Var& operator+=(const Var& b);
    Var& operator-=(const Var& b);
    Var& operator*=(const Var& b);
    Var& operator/=(const Var& b);
    Var* getVar();
    double* findDiff();
    string toString();

};


#endif
