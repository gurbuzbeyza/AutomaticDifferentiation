#ifndef NODE_H
#define NODE_H

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


class Node {

    //we should really revise the structure.
    vector<tuple<Node*,float>> derivatives;
    string name;
    float val;
    float * valList;
    bool is_scalar=false;
    Operation operation;
    tuple<Node*,Node*> parents;
    void findVals(Node* a);
    vector<tuple<Node*,float>> findDers(Node* a);
    // float solveLinEq(float& Jacobian[lenNodes][lenNodes], Node& n);
public:
    static vector<Node*> nodes;
    Node(Operation operation=Operation::noop, tuple<Node*,Node*>* parents=new tuple<Node*,Node*>);
    ~Node();
    // vector<tuple<Node,float>> GetCopyOfVector();
    void AddDer(Node* derOf,float der);
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
    void setParents(tuple<Node*,Node*> parents);
    tuple<Node*,Node*> getParents(void);
    Node& operator+(const Node& b);
    Node& operator+(float b);
    Node& operator+(int b);
    Node& operator-(const Node& b);
    Node& operator-(float b);
    Node& operator-(int b);
    Node& operator*(const Node& b);
    Node& operator*(float b);
    Node& operator*(int b);
    Node& operator/(const Node& b);
    Node& operator/(float b);
    Node& operator/(int b);
    Node& operator=(const Node& b);
    Node& operator=(int b);
    Node& operator=(float b);
    bool operator==(const Node& b);
    Node* getNode();
    double* findDiff();
    string toString();

};


#endif
