#include "var.h"
#include <cstring>
vector<Var*> Var::nodes;
set<Var*> Var::inputs;

Var::Var(Operation operation, tuple<Var*,Var*>* parents){
    this->operation = operation;
    this->parents = *parents;
    Var* n = this->getVar();
    if(NULL==n) {
        this->nodes.push_back(this);
    }
    if(get<0>(this->parents) != NULL && get<1>(this->parents)!= NULL){
        setDependentInputs(this->dependentInputs,get<0>(this->parents)->dependentInputs);
        setDependentInputs(this->dependentInputs,get<1>(this->parents)->dependentInputs);
    }else if(get<0>(this->parents)!= NULL){
        setDependentInputs(this->dependentInputs,get<0>(this->parents)->dependentInputs);    } 
}

Var::~Var(){}

void Var::AddDer(Var* derOf,float der){
    tuple<Var*,float> tpl_der (derOf,der);
    derivatives.push_back(tpl_der);
}
void Var::ClearDers(){
    derivatives.clear();
}

bool Var::isInput(void){
    return is_input;
}

void Var::makeInput(void){
    is_input = true;
    dependentInputs.insert(this);
    //make set empty if needed. but it is empty:D
    inputs.insert(this);
}

void Var::setDependentInputs(set<Var*> p1,set<Var*> p2){
    p1.insert(p2.begin(),p2.end());
    dependentInputs = p1;
}

void Var::setDependentInputs(set<Var*> p){
    dependentInputs = p;
}
    
set<Var*> Var::getDependentInputs(){
    return dependentInputs;
}

vector<Var*> Var::getSortedNodes(){
    return sortedNodes;
}

void Var::setName(string s){
        name = s;
}

string Var::getName(void){
        return name;
}

void Var::setVal(float v){
        val = v;
}


bool Var::isScalar(void){
        return is_scalar;
}

void Var::setScalar(bool b){
        is_scalar = b;
}

bool Var::isVisited(void){
        return visited;
}

void Var::setVisited(bool b){
        visited = b;
}

float Var::getVal(void){
        return val;
}

void Var::setOperation(Operation operation){
    this->operation = operation;
}

Operation Var::getOperation(void){
    return this->operation;
}

void Var::setParents(tuple<Var*,Var*> parents){
    this->parents = parents;
}

tuple<Var*,Var*> Var::getParents(void){
    return this->parents;
}
vector<tuple<Var*,float>> Var::getDerivatives(void){
    return this->derivatives;
}

void Var::topologicalSortUtil(Var* v)
{
    // Mark the current node as visited.
    v->setVisited(true);
 
    // Recur for all the vertices adjacent to this vertex
    if (get<0>(v->getParents()) != NULL && !get<0>(v->getParents())->isVisited())
        topologicalSortUtil(get<0>(v->getParents()));
    if (get<1>(v->getParents()) != NULL && !get<1>(v->getParents())->isVisited())
        topologicalSortUtil(get<1>(v->getParents()));
 
    // Push current vertex to stack which stores result
    this->sortedNodes.push_back(v);
}

void Var::result() {
 
    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (set<Var*>::iterator i = this->dependentInputs.begin(); i != this->dependentInputs.end(); ++i){
        Var* a = *i;

        a->setVisited(true);
        this->sortedNodes.push_back(a);
    }
    topologicalSortUtil(this);         
}

Var& Var::makeBinaryVarOperation(const Var& b, Operation op){
    Var *newB = (Var*)&b;
    tuple<Var*,Var*> parents (this, newB);
    Var* v = new Var(op, &parents);
    v->setVal(newB->getVal());
    return *v;    
}

Var& Var::makeBinaryVarOperation(float b, Operation op){
    tuple<Var*,Var*> noParents (NULL, NULL);
    Var* bs = new Var(Operation::noop, &noParents);
    bs-> setVal(b);
    bs-> setScalar(true);
    tuple<Var*,Var*> parents (this, bs);
    Var* v = new Var(op,&parents);
    return *v;
}
// Overload + operator to add two Var objects.
Var& Var::operator+(const Var& b)
{    return makeBinaryVarOperation(b, Operation::add);  }

Var& Var::operator+(int b) 
{    return makeBinaryVarOperation((float)b, Operation::add);  }
Var& Var::operator+(float b) 
{    return makeBinaryVarOperation(b, Operation::add);  }

//subtraction
Var& Var::operator-(const Var& b)
{    return makeBinaryVarOperation(b, Operation::sub);  }

Var& Var::operator-(int b) 
{    return makeBinaryVarOperation((float)b, Operation::sub);  }

Var& Var::operator-(float b) 
{    return makeBinaryVarOperation(b, Operation::sub);  }

// Overload * operator to multiply two Var objects.
Var& Var::operator*(const Var& b) 
{    return makeBinaryVarOperation(b, Operation::mult);  }

Var& Var::operator*(int b)
{    return makeBinaryVarOperation((float)b, Operation::mult);  }

Var& Var::operator*(float b) 
{    return makeBinaryVarOperation(b, Operation::mult);  }

//division
Var& Var::operator/(const Var& b)
{    return makeBinaryVarOperation(b, Operation::divd);  }

Var& Var::operator/(int b) 
{    return makeBinaryVarOperation((float)b, Operation::divd);  }

Var& Var::operator/(float b) 
{    return makeBinaryVarOperation(b, Operation::divd);  }

Var& Var::operator=(const Var& b){
    Var *newB = (Var*)&b;
    if (this == get<0>(newB->parents))
    {
        Var* bs = new Var((get<0>(newB->parents))->getOperation(), &((get<0>(newB->parents))->parents));
        bs->setVal((get<0>(newB->parents))->getVal());
        if ((get<0>(bs->parents) != NULL)||(get<1>(bs->parents) != NULL))
        {
            this->nodes.push_back(bs);
        }
        get<0>(newB->parents) = bs;
    }
    else if (this == get<1>(newB->parents)) {
        Var* bs = new Var((get<1>(newB->parents))->getOperation(), &((get<1>(newB->parents))->parents));
        bs->setVal((get<1>(newB->parents))->getVal());
        if ((get<0>(bs->parents) != NULL)||(get<1>(bs->parents) != NULL))
        {
            this->nodes.push_back(bs);
        }
        get<1>(newB->parents) = bs;
    }
    this->setVal(newB->getVal());
    tuple<Var*,Var*> parents (newB, NULL);
    this->setParents(parents);
    this->setDependentInputs(newB->getDependentInputs());

    return *this;
}


Var& Var::operator=(float b){
    this->setVal(b);
    return *this;
}

Var& Var::operator=(int b){
    this->setVal(b);
    return *this;
}

bool Var::operator==(const Var& b){
    Var *newB = (Var*)&b;
    if (get<0>(this->parents) != get<0>(newB->parents)){
        return false;
    }
    else if(get<1>(this->parents) != get<1>(newB->parents)){
        return false;
    }
    else if(this->operation != newB->operation){
        return false;
    }
    else if((get<0>(this->parents)) == NULL && (get<1>(this->parents)) == NULL){
        return false;
    }
    return true;
}


Var& Var::operator+=(const Var& b){
    Var *newB = (Var*)&b;
    return *this = *this + *newB;
}

Var& Var::operator-=(const Var& b){
    Var *newB = (Var*)&b;
    return *this = *this - *newB;
}

Var& Var::operator*=(const Var& b){
    Var *newB = (Var*)&b;
    return *this = *this * *newB;
}

Var& Var::operator/=(const Var& b){
    Var *newB = (Var*)&b;
    return *this = *this / *newB;
}

Var& Var::operator+=(float b){
    return *this = *this + b;
}

Var& Var::operator-=(float b){
    return *this = *this - b;
}

Var& Var::operator*=(float b){
    return *this = *this * b;
}

Var& Var::operator/=(float b){
    return *this = *this / b;
}

Var* Var::getVar(){
    for (vector<Var*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
        Var* a = *i;
        if (*a == *this){
            return a;
        }
    } 
    return NULL;
}

float Var::findVals(Var* a, float left, float right){
    switch(a->getOperation()) {
        case Operation::noop :
            if (-INFINITY != left) {
                return (left);
            }
            else {
                return a->getVal();
            }
        case Operation::add :
            return (left + right);
        case Operation::sub :
            return (left - right);
        case Operation::mult :
            return (left * right);
        case Operation::divd :
            return (left / right);
        case Operation::sig :
            return (exp(left)/(1+exp(left)));
        case Operation::sin :
            return (sin(left));
        case Operation::cos :
            return (cos(left));
        case Operation::tan :
            return (tan(left));
        case Operation::asin :
            return (asin(left));
        case Operation::acos :
            return (acos(left));
        case Operation::atan :
            return (atan(left));
        case Operation::sinh :
            return (sinh(left));
        case Operation::cosh :
            return (cosh(left));
        case Operation::tanh :
            return (tanh(left));
        case Operation::exp :
            return (exp(left));
        case Operation::log :
            return (log(left));
        case Operation::pow :
            return (pow(left, right));
        case Operation::sqrt :
            return (sqrt(left));
    }
    return 0;
}

void Var::calcVals(){
    for (vector<Var*>::iterator i = this->sortedNodes.begin(); i != this->sortedNodes.end(); ++i){
        Var* a = *i;
        if (get<0>(a->getParents()) != NULL && get<1>(a->getParents()) != NULL)
        {
            a->setVal(findVals(a, get<0>(a->getParents())->getVal(), get<1>(a->getParents())->getVal()));
        }
        else if (get<0>(a->getParents()) != NULL && get<1>(a->getParents()) == NULL) {
           a->setVal(findVals(a, get<0>(a->getParents())->getVal(), -INFINITY)); 
        }
    }
}

void Var::findDers(Var* a){
    switch(a->getOperation()){
        case Operation::noop :
            if (get<0>(a->getParents()) != NULL) {
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
        case Operation::divd :
            if (get<0>(a->getParents())==get<1>(a->getParents())){
                a->AddDer(get<0>(a->getParents()), 0);
            }else{
                a->AddDer(get<0>(a->getParents()), 1/get<1>(a->getParents())->getVal());
                a->AddDer(get<1>(a->getParents()), (-1)*get<0>(a->getParents())->getVal()/(get<1>(a->getParents())->getVal()*get<1>(a->getParents())->getVal()));
            }
            break;
        case Operation::sig :
            a->AddDer(get<0>(a->getParents()), (exp(get<0>(a->getParents())->getVal())/(1+exp(get<0>(a->getParents())->getVal())))*(1-exp(get<0>(a->getParents())->getVal())/(1+exp(get<0>(a->getParents())->getVal()))));
            break;
        case Operation::sin :
            a->AddDer(get<0>(a->getParents()), cos(get<0>(a->getParents())->getVal()));
            break;
        case Operation::cos :
            a->AddDer(get<0>(a->getParents()), -sin(get<0>(a->getParents())->getVal()));
            break;
        case Operation::tan :
            a->AddDer(get<0>(a->getParents()), 1/(cos(get<0>(a->getParents())->getVal())*cos(get<0>(a->getParents())->getVal())));
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
        case Operation::sinh :
            a->AddDer(get<0>(a->getParents()), cosh(get<0>(a->getParents())->getVal()));
            break;
        case Operation::cosh :
            a->AddDer(get<0>(a->getParents()), sinh(get<0>(a->getParents())->getVal()));
            break;
        case Operation::tanh :
            a->AddDer(get<0>(a->getParents()), 1/(cosh(get<0>(a->getParents())->getVal())*cosh(get<0>(a->getParents())->getVal())));
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
}

//used dfs algorithm
map<Var*, float> Var::calcDers(Var* v){
    v->ClearDers();
    findDers(v);
    map<Var*,float> newDers;
    if(get<0>(v->getParents())==NULL && v->isInput()){
        newDers[v] = 1;
        return newDers;
    }
    map<Var*,float> curDers;
    if(get<0>(v->getParents())==NULL){
        return curDers;
    }
    if(get<0>(v->getParents())!=NULL){
        curDers = calcDers(get<0>(v->getParents()));
        map<Var*, float>::iterator it;
        for ( it = curDers.begin(); it != curDers.end(); it++ )
        {
            newDers[it->first] = (it->second)*get<1>(v->getDerivatives()[0]);
        }
    }
    if(get<1>(v->getParents())!=NULL){
        curDers = calcDers(get<1>(v->getParents()));
        map<Var*, float>::iterator it;
        for ( it = curDers.begin(); it != curDers.end(); it++ )
        {
            newDers[it->first] += (it->second)*get<1>(v->getDerivatives()[1]);
        }
    }
    return newDers;
}

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}


map<Var*, float> Var::findDiff(){

    calcVals();
    map<Var*, float> ders = calcDers(this);
    return ders;
}

string Var::toString(){
    cout<<this<<" ";
    cout<<get<0>(parents)<<" ";
    cout<<get<1>(parents)<<" ";
    cout<<as_integer(this->operation)<<" ";
    return to_string(this->getVal());
}
