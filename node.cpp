#include "node.h"

vector<Node*> Node::nodes;

Node::Node(Operation operation, tuple<Node*,Node*>* parents){
    this->operation = operation;
    this->parents = *parents;
}

Node::~Node(){}

vector<tuple<Node,float>> Node::GetCopyOfVector(){
        return ders;
}

void Node::AddDer(Node derOf,float der){
    tuple<Node,float> tpl_der (derOf,der);
    ders.push_back(tpl_der);
}

void Node::DisplayDerValues(){
    cout<<"displaying ders:"<<endl;
        for( unsigned int i = 0; i < ders.size(); i++ )
        {
            cout<<"derivative to "<<get<0>(ders[i]).getName()<< " is: " << get<1>(ders[i]) << endl;
        }
        cout << endl;
}

void Node::setName(string s){
        name = s;
}

string Node::getName(void){
        return name;
}

void Node::setVal(float v){
        val = v;
}

float Node::getVal(void){
        return val;
}

void Node::setOperation(Operation operation){
    this->operation = operation;
}

Operation Node::getOperation(void){
    return this->operation;
}

void Node::setParents(tuple<Node*,Node*> parents){
    this->parents = parents;
}

tuple<Node*,Node*> Node::getParents(void){
    return this->parents;
}

// Overload + operator to add two Node objects.
Node& Node::operator+(const Node& b) {
    cout<<"+"<<endl;
    Node *newB = (Node*)&b;
    tuple<Node*,Node*> parents (this, newB);
    Node* v = new Node(Operation::add, &parents);
    nodes.push_back(v);
    return *(nodes.back());

}
//subtraction
Node& Node::operator-(const Node& b){
    Node *newB = (Node*)&b;
    tuple<Node*,Node*> parents (this, newB);
    Node* v = new Node(Operation::sub, &parents);
    nodes.push_back(v);
    return *(nodes.back());
}

// Overload * operator to multiply two Node objects.
Node& Node::operator*(const Node& b) {
    Node *newB = (Node*)&b;
    tuple<Node*,Node*> parents (this, newB);
    Node* v = new Node(Operation::mult, &parents);
    cout<<"*"<<endl;
    nodes.push_back(v);
    return *(nodes.back());
}
//division
Node& Node::operator/(const Node& b){
    Node *newB = (Node*)&b;
    tuple<Node*,Node*> parents (this, newB);
    Node* v = new Node(Operation::div, &parents);
    nodes.push_back(v);
    return *(nodes.back());
}

string Node::toString(){
    cout<<this<<" ";
    
    cout<<get<0>(parents)<<" ";
    cout<<get<1>(parents)<<" ";

    return to_string(static_cast<underlying_type<Operation>::type>(this->operation));
}
