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
#include <stack>
#include "operation.h"
#include "solve.hpp"
#include <set>


using namespace std;

class Var {

    //we should really revise the structure.
    vector<tuple<Var*,float>> derivatives;
    string name;
    float val;
    float * valList;
    bool is_scalar = false;
    bool is_input = false;
    bool visited = false;
    set<Var*> dependentInputs;
    Operation operation;
    tuple<Var*,Var*> parents;

    float recVars(Var* v);
    void calcVals();
    float findVals(Var* a, float left, float right);
    void calcDers(map<Var*,float>& derivs);
    map<Var*, float> calcDers(Var* v);
    void findDers(Var* a);
    void topologicalSortUtil(Var* v);
public:
    static vector<Var*> nodes;
    static vector<Var*> sortedNodes;
    static set<Var*> inputs;
    Var(Operation operation=Operation::noop, tuple<Var*,Var*>* parents=new tuple<Var*,Var*>);
    ~Var();
    void AddDer(Var* derOf,float der);
    void ClearDers();
    // void DisplayDerValues();
    void setName(string s);
    string getName(void);
    bool isScalar(void);
    bool isInput(void);
    void makeInput(void);
    void setScalar(bool b);
    bool isVisited(void);
    void setVisited(bool b);
    void setVal(float v);
    void setVal(float *v);
    float getVal(void);
    void setDependentInputs(set<Var*> p1, set<Var*> p2);
    void setDependentInputs(set<Var*> p);
    set<Var*> getDependentInputs(void);
    void setOperation(Operation operation);
    Operation getOperation(void);
    void setParents(tuple<Var*,Var*> parents);
    void result();
    tuple<Var*,Var*> getParents(void);
    vector<tuple<Var*,float>> getDerivatives(void);
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
    map<Var*, float> findDiff();
    string toString();

};


#endif