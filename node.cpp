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

Node& Node::operator=(const Node& b){
    Node *newB = (Node*)&b;
    this->setVal(newB->getVal());
    tuple<Node*,Node*> parents (newB, NULL);
    this->setParents(parents);
    return *this;
}

bool Node::operator==(const Node& b){
    Node *newB = (Node*)&b;
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
            if (NULL != get<0>(a->getParents())) {
                a->setVal(get<0>(a->getParents())->getVal());
            }
            else {
                a->setVal(nodeVals[a]);
            }
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

vector<tuple<Node*,float>> Node::findDers(Node* a){
    //TODO scalar operations may be added later
    switch(a->getOperation()) {
        case Operation::noop :
            if (NULL != get<0>(a->getParents())) {
                a->AddDer(get<0>(a->getParents()),1);
            }
            else {
                a->AddDer(a,1);
            }
            break;
        case Operation::add :
            if (((get<0>(a->getParents())))==((get<1>(a->getParents())))){
                a->AddDer(get<0>(a->getParents()), 2);
            }else{
                a->AddDer(get<0>(a->getParents()), 1);
                a->AddDer(get<1>(a->getParents()), 1);
            }
            break;
        case Operation::sub :
            if (get<0>(a->getParents())==get<1>(a->getParents())){
                a->AddDer(get<0>(a->getParents()), 0);
            }
            else{
                a->AddDer(get<0>(a->getParents()), 1);
                a->AddDer(get<1>(a->getParents()), -1);
            }
            break;
        case Operation::mult :
            if (get<0>(a->getParents())==get<1>(a->getParents())){
                a->AddDer(get<0>(a->getParents()), 2*get<0>(a->getParents())->getVal());
            }else{
                a->AddDer(get<0>(a->getParents()), get<1>(a->getParents())->getVal());
                a->AddDer(get<1>(a->getParents()), get<0>(a->getParents())->getVal());
            }
            break;
        case Operation::div :
            if (get<0>(a->getParents())==get<1>(a->getParents())){
                a->AddDer(get<0>(a->getParents()), 0);
            }else{
                a->AddDer(get<0>(a->getParents()), 1/get<1>(a->getParents())->getVal());
                a->AddDer(get<1>(a->getParents()), (-1)*get<0>(a->getParents())->getVal()/(get<0>(a->getParents())->getVal()*get<0>(a->getParents())->getVal()));
            }
            break;
        case Operation::sin :
            a->AddDer(get<0>(a->getParents()), cos(get<0>(a->getParents())->getVal()));
            break;
        case Operation::cos :
            a->AddDer(get<0>(a->getParents()), -sin(get<0>(a->getParents())->getVal()));
            break;
        case Operation::tan :
            a->AddDer(get<0>(a->getParents()), 1/(cos(get<0>(a->getParents())->getVal())*get<0>(a->getParents())->getVal()));
            break;
        case Operation::asin :
            a->AddDer(get<0>(a->getParents()), 1/sqrt(1-get<0>(a->getParents())->getVal()*get<0>(a->getParents())->getVal()));
            break;
        case Operation::acos :
            a->AddDer(get<0>(a->getParents()), -1/sqrt(1-get<0>(a->getParents())->getVal()*get<0>(a->getParents())->getVal()));
            break;
        case Operation::atan :
            a->AddDer(get<0>(a->getParents()), 1/(get<0>(a->getParents())->getVal()*get<0>(a->getParents())->getVal()+1));
            break;
        case Operation::exp :
            a->AddDer(get<0>(a->getParents()), exp(get<0>(a->getParents())->getVal()));
            break;
        case Operation::log :
            a->AddDer(get<0>(a->getParents()), 1/get<0>(a->getParents())->getVal());
            break;
        case Operation::pow :
            a->AddDer(get<0>(a->getParents()), get<1>(a->getParents())->getVal()*(pow(get<0>(a->getParents())->getVal(),get<1>(a->getParents())->getVal()-1)));
            a->AddDer(get<1>(a->getParents()), pow(get<0>(a->getParents())->getVal(),get<1>(a->getParents())->getVal())*log(get<1>(a->getParents())->getVal()));
            break;
        case Operation::sqrt :
            a->AddDer(get<0>(a->getParents()), 1/(2*sqrt(get<0>(a->getParents())->getVal())));
            break;
    }
    return a->derivatives;
}

// float Node::solveLinEq(float& Jacobian**, Node& n){
//     lenNodes = Jacobian.size();
//     float& L[lenNodes][lenNodes];
//     float& U[lenNodes][lenNodes];
//     memset(L, 0, lenNodes*lenNodes*sizeof(float));
//     memset(U, 0, lenNodes*lenNodes*sizeof(float));
//     for (int i = 0; i < lenNodes; ++i)
//     {
//         for (int k = i; k < lenNodes; ++i)
//         {
//             int sum = 0;
//             for (int j = 0; i < i; ++i)
//             {
//                 sum += L[i][j]*U[j][k];
//             }
//             U[i][k] = Jacobian[i][k] - sum;
//         }
//         for (int k = i; k < lenNodes; ++i)
//         {
//             if (i==k){
//                 L[i][k] = 1;
//             }
//             else{
//                 int sum = 0;
//                 for (int j = 0; i < i; ++i)
//                 {
//                     sum += L[i][j]*U[j][k];
//                 }
//                 L[i][k] = (Jacobian[i][k] - sum)/U[k][k];
//             }
//         }
//     }
// }

double* Node::findDiff(map<Node*, int>& nodeVals){
    for (vector<Node*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
        Node* a = *i;
        findVals(a, nodeVals);
    }
    int lenNodes = nodes.size();
    int lenInputs = nodeVals.size();
    double** Jacobian = new double*[lenNodes];
    for (int i = 0; i < lenNodes; ++i){
        Jacobian[i] = new double[lenNodes];
        for (int j = 0; j < lenNodes; ++j)
        {
            Jacobian[i][j] = 0;
        }
    }
    // memset(Jacobian, 0, lenNodes*lenNodes*sizeof(double));
    for (int i = 0; i < lenNodes; ++i){
        Jacobian[i][i] = -1;
    }
    int j = 0;
    for (vector<Node*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
        Node* a = *i;
        vector<tuple<Node*,float>> ders = findDers(a);
        // ders.push_back(tuple<Node*, float> (new Node(), 3 ));

        for (vector<tuple<Node*,float>>::iterator k = ders.begin(); k != ders.end(); ++k){
            ptrdiff_t pos = distance(nodes.begin(), find(nodes.begin(), nodes.end(), get<0>(*k)));
            Jacobian[pos][j] = get<1>(*k);
            // cout<<pos<<" "<<j<<" "<<get<1>(*k)<<endl;
        }
        j++;
    }
    for (int i = 0; i < lenNodes; ++i){
        Jacobian[i][i] = -1;
    }
    cout<<"------"<<endl;
    for (int i = 0; i < lenNodes; ++i){
        for (int j = 0; j < lenNodes; ++j)
        {
            cout<<Jacobian[i][j]<<" ";
        }
        cout<<endl;
    }
    double* y = new double[lenNodes];
    memset(y, 0, lenNodes*sizeof(double));
    y[lenNodes-1] = -1;
    cout<<"------"<<endl;
    double* x = r8rmat_fs_new (lenNodes, Jacobian, y);
    for (int i = 0; i < lenNodes; ++i)
    {
        cout<<x[i]<<" ";
    }
    cout<<endl;
    double* out = new double[lenInputs];
    for (int i = 0; i < lenInputs; ++i)
    {
        out[i] = x[i];
    }
    //ptrdiff_t pos = distance(nodes.begin(), find(nodes.begin(), nodes.end(), n));
    return out;
}

string Node::toString(){
    cout<<this<<" ";
    
    cout<<get<0>(parents)<<" ";
    cout<<get<1>(parents)<<" ";

    return to_string(static_cast<underlying_type<Operation>::type>(this->operation));
}

