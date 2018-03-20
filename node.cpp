#include "node.h"

vector<Node*> Node::nodes;

Node::Node(Operation operation, tuple<Node*,Node*>* parents){
    this->operation = operation;
    this->parents = *parents;
    Node* n = this->getNode();
    if(NULL==n) {
        this->nodes.push_back(this); 
    }
}

Node::~Node(){}

// vector<tuple<Node,float>> Node::GetCopyOfVector(){
//         return ders;
// }

void Node::AddDer(Node* derOf,float der){
    tuple<Node*,float> tpl_der (derOf,der);
    derivatives.push_back(tpl_der);
}

// void Node::DisplayDerValues(){
//     cout<<"displaying ders:"<<endl;
//         for( unsigned int i = 0; i < ders.size(); i++ )
//         {
//             cout<<"derivative to "<<get<0>(ders[i]).getName()<< " is: " << get<1>(ders[i]) << endl;
//         }
//         cout << endl;
// }

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
    Node *newB = (Node*)&b;
    tuple<Node*,Node*> parents (this, newB);
    Node* v = new Node(Operation::add, &parents);
    return *v->getNode();

}
//subtraction
Node& Node::operator-(const Node& b){
    Node *newB = (Node*)&b;
    tuple<Node*,Node*> parents (this, newB);
    Node* v = new Node(Operation::sub, &parents);
    return *v->getNode();
}

// Overload * operator to multiply two Node objects.
Node& Node::operator*(const Node& b) {
    Node *newB = (Node*)&b;
    tuple<Node*,Node*> parents (this, newB);
    Node* v = new Node(Operation::mult, &parents);
    return *v->getNode();
}
//division
Node& Node::operator/(const Node& b){
    Node *newB = (Node*)&b;
    tuple<Node*,Node*> parents (this, newB);
    Node* v = new Node(Operation::div, &parents);
    return *v->getNode();
}

bool Node::operator==(const Node& b){
    Node *newB = (Node*)&b;
    // cout<<"left "<<this<<endl;
    // cout<<"right "<<newB<<endl;
    // cout<<"left parent left "<<get<0>(this->parents)<<" right parent left "<<get<0>(newB->parents)<<endl;
    // cout<<"left parent right "<<get<1>(this->parents)<<" right parent right "<<get<1>(newB->parents)<<endl;
    // cout<<"left op "<<to_string(static_cast<underlying_type<Operation>::type>(this->operation))<<endl;
    // cout<<"right op "<<to_string(static_cast<underlying_type<Operation>::type>(newB->operation))<<endl;
    if (get<0>(this->parents) != get<0>(newB->parents)){
        return false;
    }
    else if(get<1>(this->parents) != get<1>(newB->parents)){
        return false;
    }
    else if(this->operation != newB->operation){
        return false;
    }
    else if((NULL == get<0>(this->parents))&&(NULL == get<1>(this->parents))){
        return false;
    }
    return true;
}


Node* Node::getNode(){
    for (vector<Node*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
        Node* a = *i;
        if (*a == *this){
            return a;
        }
    } 
    return NULL;
}

void Node::findVals(Node* a, map<Node*, int>& nodeVals){
    switch(a->getOperation()) {
        case Operation::noop :
            a->setVal(nodeVals[a]);
            break;
        case Operation::add :
            a->setVal(get<0>(a->getParents())->getVal() + get<1>(a->getParents())->getVal());
            break;
        case Operation::sub :
            a->setVal(get<0>(a->getParents())->getVal() - get<1>(a->getParents())->getVal());
            break;
        case Operation::mult :
            a->setVal(get<0>(a->getParents())->getVal() * get<1>(a->getParents())->getVal());
            break;
        case Operation::div :
            a->setVal(get<0>(a->getParents())->getVal() / get<1>(a->getParents())->getVal());
            break;
        case Operation::sin :
            a->setVal(sin(get<0>(a->getParents())->getVal()));
            break;
        case Operation::cos :
            a->setVal(cos(get<0>(a->getParents())->getVal()));
            break;
        case Operation::tan :
            a->setVal(tan(get<0>(a->getParents())->getVal()));
            break;
        case Operation::asin :
            a->setVal(asin(get<0>(a->getParents())->getVal()));
            break;
        case Operation::acos :
            a->setVal(acos(get<0>(a->getParents())->getVal()));
            break;
        case Operation::atan :
            a->setVal(atan(get<0>(a->getParents())->getVal()));
            break;
        case Operation::exp :
            a->setVal(exp(get<0>(a->getParents())->getVal()));
            break;
        case Operation::log :
            a->setVal(log(get<0>(a->getParents())->getVal()));
            break;
        case Operation::pow :
            a->setVal(pow(get<0>(a->getParents())->getVal(), get<1>(a->getParents())->getVal()));
            break;
        case Operation::sqrt :
            a->setVal(sqrt(get<0>(a->getParents())->getVal()));
            break;
    }
}

vector<tuple<Node*,float>> Node::findDers(Node* a, map<Node*, int>& nodeVals){
    // switch(a->getOperation()) {
    //     case Operation::noop :
    //         a->setVal(nodeVals[a]);
    //         break;
    //     case Operation::add :
    //         a->setVal(get<0>(a->getParents())->getVal() + get<1>(a->getParents())->getVal());
    //         break;
    //     case Operation::sub :
    //         a->setVal(get<0>(a->getParents())->getVal() - get<1>(a->getParents())->getVal());
    //         break;
    //     case Operation::mult :
    //         a->setVal(get<0>(a->getParents())->getVal() * get<1>(a->getParents())->getVal());
    //         break;
    //     case Operation::div :
    //         a->setVal(get<0>(a->getParents())->getVal() / get<1>(a->getParents())->getVal());
    //         break;
    //     case Operation::sin :
    //         a->setVal(sin(get<0>(a->getParents())->getVal()));
    //         break;
    //     case Operation::cos :
    //         a->setVal(cos(get<0>(a->getParents())->getVal()));
    //         break;
    //     case Operation::tan :
    //         a->setVal(tan(get<0>(a->getParents())->getVal()));
    //         break;
    //     case Operation::asin :
    //         a->setVal(asin(get<0>(a->getParents())->getVal()));
    //         break;
    //     case Operation::acos :
    //         a->setVal(acos(get<0>(a->getParents())->getVal()));
    //         break;
    //     case Operation::atan :
    //         a->setVal(atan(get<0>(a->getParents())->getVal()));
    //         break;
    //     case Operation::exp :
    //         a->setVal(exp(get<0>(a->getParents())->getVal()));
    //         break;
    //     case Operation::log :
    //         a->setVal(log(get<0>(a->getParents())->getVal()));
    //         break;
    //     case Operation::pow :
    //         a->setVal(pow(get<0>(a->getParents())->getVal(), get<1>(a->getParents())->getVal()));
    //         break;
    //     case Operation::sqrt :
    //         a->setVal(sqrt(get<0>(a->getParents())->getVal()));
    //         break;
    // }
}

float Node::findDiff(map<Node*, int>& nodeVals, Node* n){
    for (vector<Node*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
        Node* a = *i;
        findVals(a, nodeVals);
    }
    int lenNodes = 0;
    lenNodes = nodes.size();
    float Jacobian[lenNodes][lenNodes];
    memset(Jacobian, 0, lenNodes*lenNodes*sizeof(float));
    for (int i = 0; i < lenNodes; ++i){
        Jacobian[i][i] = -1;
    }
    int j = 0;
    for (vector<Node*>::iterator i = this->nodes.end(); i != this->nodes.begin(); --i){
        Node* a = *i;
        vector<tuple<Node*,float>> ders = findDers(a, nodeVals);
        for (vector<tuple<Node*,float>>::iterator i = ders.begin(); i != ders.end(); ++i){
            ptrdiff_t pos = distance(nodes.begin(), find(nodes.begin(), nodes.end(), get<0>(*i)));
            Jacobian[j][pos] = get<1>(*i);
        }
        j++;
    }
    return this->nodes.back()->getVal();
}

string Node::toString(){
    cout<<this<<" ";
    
    cout<<get<0>(parents)<<" ";
    cout<<get<1>(parents)<<" ";

    return to_string(static_cast<underlying_type<Operation>::type>(this->operation));
}

