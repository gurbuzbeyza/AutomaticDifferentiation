#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <math.h>
#include "node.h"

//http://www.cplusplus.com/reference/tuple/tuple/
//implemented only operations between Nodes. TODO expand for Node, float operations -> tum floatlari Nodee cast edeceksek gerek de yok mu acaba???
// TODO add graph field to Node ? -> keys of AddDer graph yerine gecer mi??? niye lazim ki graph:D
//TODO remove name field?
//TODO implement = overloading to pass by reference and to assign floats to Nodes at initialization.
using namespace std;


Node& pow(const Node& var,const Node&  p){
    Node *newVar = (Node*)&var;
    Node *newP = (Node*)&p;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::pow, &parents);
    return *v->getNode();
}

Node& sqrt(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::sqrt, &parents);
    return *v->getNode();
}

Node& sin(const Node& var) {
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::sin, &parents);
    // Node *newnode = new Node()
    return *v->getNode();
}

Node& cos(const Node& var) {
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::cos, &parents);
    return *v->getNode();
}

Node& tan(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::tan, &parents);
    return *v->getNode();
}

Node& asin(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::asin, &parents);
    return *v->getNode();
}

Node& acos(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::acos, &parents);
    return *v->getNode();
}

Node& atan(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::atan, &parents);
    return *v->getNode();
}

Node& exp(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::exp, &parents);
    return *v->getNode();
}

Node& log(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::log, &parents);
    return *v->getNode();
}


int main() {
    /// just try some stuff
    Node a;
    Node b;
    cout<<get<1>(a.getParents())<<endl;
    // Node result;
    a.setName("a");
    b.setName("b");
    a.setVal(1.5708);
    b.setVal(16);
    Node res;
    cout<<&a<<endl;
    cout<<&b<<endl;
    res=(a+sin(b));
    map<Node*, int> nodeVals;
    nodeVals[&a] = 3;
    nodeVals[&b] = 5;
    cout<<res.findDiff(nodeVals, &a)<<endl;
    // res.DisplayDerValues();
    cout<<res.getVal()<<endl;
    
    for (vector<Node*>::iterator i = res.nodes.begin(); i != res.nodes.end(); ++i){
        Node* a = *i;
        cout << a->toString() << endl;
    } 
    return 0;
}



//https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm -> add many on the list, like unary (-)

//http://warp.povusers.org/FunctionParser/  -> warping in c++
