#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <math.h>
#include <map>
#include "operation.h"


using namespace std;


class Node {

    //we should really revise the structure.
    vector<tuple<Node*,float>> derivatives;
    string name;
    float val;
    Operation operation;
    tuple<Node*,Node*> parents;
    void findVals(Node* a, map<Node*, int>& nodeVals);
    vector<tuple<Node*,float>> findDers(Node* a, map<Node*, int>& nodeVals);
public:
    static vector<Node*> nodes;
    Node(Operation operation=Operation::noop, tuple<Node*,Node*>* parents=new tuple<Node*,Node*>);
    ~Node();
    // vector<tuple<Node,float>> GetCopyOfVector();
    void AddDer(Node* derOf,float der);
    // void DisplayDerValues();
    void setName(string s);
    string getName(void);
    void setVal(float v);
    float getVal(void);
    void setOperation(Operation operation);
    Operation getOperation(void);
    void setParents(tuple<Node*,Node*> parents);
    tuple<Node*,Node*> getParents(void);
    Node& operator+(const Node& b);
    Node& operator-(const Node& b);
    Node& operator*(const Node& b);
    Node& operator/(const Node& b);
    bool operator==(const Node& b);
    Node* getNode();
    float findDiff(map<Node*, int>& nodeVals, Node* n);
    string toString();

};


#endif