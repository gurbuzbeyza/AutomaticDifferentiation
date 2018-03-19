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
    Node::nodes.push_back(v);
    return *(Node::nodes.back());
}

Node& sqrt(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::sqrt, &parents);
    Node::nodes.push_back(v);
    return *(Node::nodes.back());
}



Node& sin(const Node& var) {
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::sin, &parents);
    Node::nodes.push_back(v);
    cout<<"sin"<<endl;
    // Node *newnode = new Node()
    return *(Node::nodes.back());
}

Node& cos(const Node& var) {
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::cos, &parents);
    cout << "Cos result added" << endl;
    Node::nodes.push_back(v);
    return *(Node::nodes.back());
}

Node& tan(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::tan, &parents);
    Node::nodes.push_back(v);
    return *(Node::nodes.back());
}

Node& asin(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::asin, &parents);
    Node::nodes.push_back(v);
    return *(Node::nodes.back());
}
Node& acos(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::acos, &parents);
    Node::nodes.push_back(v);
    return *(Node::nodes.back());
}

Node& atan(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::atan, &parents);
    Node::nodes.push_back(v);
    return *(Node::nodes.back());
}

Node& exp(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::exp, &parents);
    Node::nodes.push_back(v);
    return *(Node::nodes.back());
}

Node& log(const Node& var){
    Node *newVar = (Node*)&var;
    Node *newP = NULL;
    tuple<Node*,Node*> parents (newVar, newP);
    Node* v = new Node(Operation::log, &parents);
    Node::nodes.push_back(v);
    return *(Node::nodes.back());
}


int main() {
    cout<<asin(1)<<endl;
    /// just try some stuff
    Node a;
    Node b;
    // Node result;
    a.setName("a");
    b.setName("b");
    a.setVal(1.5708);
    b.setVal(16);
    Node res;
    cout<<&a<<endl;
    cout<<&b<<endl;
    res=(b+sin(b))*a;
    res.DisplayDerValues();
    cout<<res.getVal()<<endl;
    
    for (vector<Node*>::iterator i = res.nodes.begin(); i != res.nodes.end(); ++i){
        Node* a = *i;
        cout << a->toString() << endl;
    } 
    return 0;
}



//https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm -> add many on the list, like unary (-)

//http://warp.povusers.org/FunctionParser/  -> warping in c++
