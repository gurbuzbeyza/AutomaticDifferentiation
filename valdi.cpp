#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <math.h>
#include "node.h"

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

Node sigmoid(Node x){
    return exp(x);
}

Node& operator+(int i, const Node& n)
{
    Node *newVar = (Node*)&n;
    tuple<Node*,Node*> noParents (NULL, NULL);
    Node* bs = new Node(Operation::noop, &noParents);
    bs-> setVal((float)i);
    bs-> setScalar(true);
    tuple<Node*,Node*> parents (bs, newVar);
    Node* v = new Node(Operation::add,&parents);
    return *v ->getNode();
}

Node& operator+(float i, const Node& n)
{
    Node *newVar = (Node*)&n;
    tuple<Node*,Node*> noParents (NULL, NULL);
    Node* bs = new Node(Operation::noop, &noParents);
    bs-> setVal((float)i);
    bs-> setScalar(true);
    tuple<Node*,Node*> parents (bs, newVar);
    Node* v = new Node(Operation::add,&parents);
    return *v ->getNode();
}

Node& operator-(int i, const Node& n)
{
    Node *newVar = (Node*)&n;
    tuple<Node*,Node*> noParents (NULL, NULL);
    Node* bs = new Node(Operation::noop, &noParents);
    bs-> setVal((float)i);
    bs-> setScalar(true);
    tuple<Node*,Node*> parents (bs, newVar);
    Node* v = new Node(Operation::sub,&parents);
    return *v ->getNode();
}

Node& operator-(float i, const Node& n)
{
    Node *newVar = (Node*)&n;
    tuple<Node*,Node*> noParents (NULL, NULL);
    Node* bs = new Node(Operation::noop, &noParents);
    bs-> setVal((float)i);
    bs-> setScalar(true);
    tuple<Node*,Node*> parents (bs, newVar);
    Node* v = new Node(Operation::sub,&parents);
    return *v ->getNode();
}

Node& operator*(int i, const Node& n)
{
    Node *newVar = (Node*)&n;
    tuple<Node*,Node*> noParents (NULL, NULL);
    Node* bs = new Node(Operation::noop, &noParents);
    bs-> setVal((float)i);
    bs-> setScalar(true);
    tuple<Node*,Node*> parents (bs, newVar);
    Node* v = new Node(Operation::mult,&parents);
    return *v ->getNode();
}

Node& operator*(float i, const Node& n)
{
    Node *newVar = (Node*)&n;
    tuple<Node*,Node*> noParents (NULL, NULL);
    Node* bs = new Node(Operation::noop, &noParents);
    bs-> setVal((float)i);
    bs-> setScalar(true);
    tuple<Node*,Node*> parents (bs, newVar);
    Node* v = new Node(Operation::mult,&parents);
    return *v ->getNode();
}

Node& operator/(int i, const Node& n)
{
    Node *newVar = (Node*)&n;
    tuple<Node*,Node*> noParents (NULL, NULL);
    Node* bs = new Node(Operation::noop, &noParents);
    bs-> setVal((float)i);
    bs-> setScalar(true);
    tuple<Node*,Node*> parents (bs, newVar);
    Node* v = new Node(Operation::divd,&parents);
    return *v ->getNode();
}

Node& operator/(float i, const Node& n)
{
    Node *newVar = (Node*)&n;
    tuple<Node*,Node*> noParents (NULL, NULL);
    Node* bs = new Node(Operation::noop, &noParents);
    bs-> setVal((float)i);
    bs-> setScalar(true);
    tuple<Node*,Node*> parents (bs, newVar);
    Node* v = new Node(Operation::divd,&parents);
    return *v ->getNode();
}

Node& operator-(const Node& n)
{
    Node *newVar = (Node*)&n;
    tuple<Node*,Node*> noParents (NULL, NULL);
    Node* bs = new Node(Operation::noop, &noParents);
    bs-> setVal(-1);
    bs-> setScalar(true);
    tuple<Node*,Node*> parents (bs, newVar);
    Node* v = new Node(Operation::mult,&parents);
    return *v ->getNode();
}

Node& operator+(const Node& n)
{
    Node *newVar = (Node*)&n;
    tuple<Node*,Node*> noParents (NULL, NULL);
    Node* bs = new Node(Operation::noop, &noParents);
    bs-> setVal(1);
    bs-> setScalar(true);
    tuple<Node*,Node*> parents (bs, newVar);
    Node* v = new Node(Operation::mult,&parents);
    return *v ->getNode();
}



int main() {
    /// just try some stuff
    Node a;
    Node b;
    Node c;
    Node res;
    res=((c)+c);
    //map<Node*, int> nodeVals;
    a = 4;
    b = 25;
    c = 2;
    Node ar [3] = {a,b,c};
    cout<<ar[0].getVal()<<endl;
   // cout<<ar[0]<<endl;


    //////////////// bu kismi nodeValsi universal tutup = overloadinge eklemeliyiz./////////////////
    //nodeVals[&a] = a.getVal();
    //nodeVals[&b] = b.getVal();
    ////////////////////////////////////////////////////////////////////////////////////////////////
    double* fs = res.findDiff();
    for (int i = 0; i < 3; ++i)
    {
        cout<<"fsi: "<<fs[i]<<endl;
    }
    return 0;
}
