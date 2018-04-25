#include "var.h"
#include <cstring>
vector<Var*> Var::nodes;
vector<Var*> Var::sortedNodes;
set<Var*> Var::inputs;

Var::Var(Operation operation, tuple<Var*,Var*>* parents){
    this->operation = operation;
    this->parents = *parents;
    Var* n = this->getVar();
    if(NULL==n) {
        this->nodes.push_back(this);
    }
    if(get<0>(this->parents) != NULL && get<0>(this->parents)!= NULL){
        this->dependentInputs.insert(get<0>(this->parents)->dependentInputs.begin(),get<0>(this->parents)->dependentInputs.end());
        this->dependentInputs.insert(get<1>(this->parents)->dependentInputs.begin(),get<1>(this->parents)->dependentInputs.end());
    }else if(get<0>(this->parents)!= NULL){
        this->dependentInputs.insert(get<0>(this->parents)->dependentInputs.begin(),get<0>(this->parents)->dependentInputs.end());
    } 
}

Var::~Var(){}

void Var::AddDer(Var* derOf,float der){
    tuple<Var*,float> tpl_der (derOf,der);
    derivatives.push_back(tpl_der);
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

void Var::topologicalSortUtil(Var* v)
{
    // Mark the current node as visited.
    v->setVisited(true);
 
    // Recur for all the vertices adjacent to this vertex
    if (NULL != get<0>(v->getParents()) && !get<0>(v->getParents())->isVisited())
        topologicalSortUtil(get<0>(v->getParents()));
    if (NULL != get<1>(v->getParents()) && !get<1>(v->getParents())->isVisited())
        topologicalSortUtil(get<0>(v->getParents()));
 
    // Push current vertex to stack which stores result
    this->sortedNodes.push_back(v);
}

void Var::result() {
 
    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (vector<Var*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
        Var* a = *i;
        // cout<<a->toString()<<endl;
        if (!a->isVisited()){
            topologicalSortUtil(a);
        }
    }
      
    // Print contents of stack
    
}

Var& Var::makeBinaryVarOperation(const Var& b, Operation op){
    Var *newB = (Var*)&b;
    tuple<Var*,Var*> parents (this, newB);
    Var* v = new Var(op, &parents);
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
        if ((NULL != get<0>(bs->parents))||(NULL != get<1>(bs->parents)))
        {
            this->nodes.push_back(bs);
        }
        get<0>(newB->parents) = bs;
    }
    else if (this == get<1>(newB->parents)) {
        Var* bs = new Var((get<1>(newB->parents))->getOperation(), &((get<1>(newB->parents))->parents));
        bs->setVal((get<1>(newB->parents))->getVal());
        if ((NULL != get<0>(bs->parents))||(NULL != get<1>(bs->parents)))
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
    else if((NULL == get<0>(this->parents))&&(NULL == get<1>(this->parents))){
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
            if (-1 != left) {
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
    for (vector<Var*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
        Var* a = *i;
        if (NULL != get<0>(a->getParents()) && NULL != get<1>(a->getParents()))
        {
            a->setVal(findVals(a, get<0>(a->getParents())->getVal(), get<1>(a->getParents())->getVal()));
        }
        else if (NULL != get<0>(a->getParents()) && NULL == get<1>(a->getParents())) {
           a->setVal(findVals(a, get<0>(a->getParents())->getVal(), -1)); 
        }
    }
}

float Var::recVars(Var* v){
    if (v == NULL)
    {
        // cout<<"sdfs"<<endl;
        return -1;
    }
    if (NULL == get<0>(v->getParents()) && NULL == get<1>(v->getParents()))
    {
        return v->getVal();
    }
    if (NULL == get<1>(v->getParents()))
    {
        float val = findVals(v, recVars(get<0>(v->getParents())), -1);
        v->setVal(val);
        return val;
    }
    float val = findVals(v, recVars(get<0>(v->getParents())), recVars(get<1>(v->getParents())));
    v->setVal(val);
    return val;
}

void Var::findDers(Var* a){
    //TODO scalar operations may be added later
    switch(a->getOperation()){
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
        case Operation::divd :
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
}

void Var::recDers(Var* v){

    findDers (v);
    if (NULL != get<0>(v->getParents()))
    {
        recDers(get<0>(v->getParents()));
    }
    if (NULL != get<1>(v->getParents()))
    {
        recDers(get<1>(v->getParents()));
    }
}


double* Var::findDiff(){
    int lenInputs = 0;
    for (vector<Var*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
        Var* a = *i;
        // cout<<a->toString()<<endl;
        if (NULL == get<0>(a->getParents()) && NULL == get<1>(a->getParents())&& !(a->isScalar())){
            lenInputs++;
        }
    }
    calcVals();
    int lenVars = nodes.size();
    double** Jacobian = new double*[lenVars];
    for (int i = 0; i < lenVars; ++i){
        Jacobian[i] = new double[lenVars];
        for (int j = 0; j < lenVars; ++j)
        {
            Jacobian[i][j] = 0;
        }
    }
    for (int i = 0; i < lenVars; ++i){
        Jacobian[i][i] = -1;
    }
    int j = 0;
    recDers(this);
    for (vector<Var*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
        Var* a = *i;
        vector<tuple<Var*,float>> ders = a->derivatives;
        for (vector<tuple<Var*,float>>::iterator k = ders.begin(); k != ders.end(); ++k){
            ptrdiff_t pos = distance(nodes.begin(), find(nodes.begin(), nodes.end(), get<0>(*k)));
            Jacobian[pos][j] = get<1>(*k);
            // cout<<pos<<" "<<j<<" "<<get<1>(*k)<<endl;
        }
        j++;
    }
    for (int i = 0; i < lenVars; ++i){
        Jacobian[i][i] = -1;
    }

    double* y = new double[lenVars];
    memset(y, 0, lenVars*sizeof(double));
    ptrdiff_t pos = distance(nodes.begin(), find(nodes.begin(), nodes.end(), this));
    y[pos] = -1;

    double* x = r8rmat_fs_new (lenVars, Jacobian, y);
    double* out = new double[lenInputs];

    for (int i = 0; i < lenInputs; ++i)
    {
        out[i] = x[i];
    }
    return out;
}

string Var::toString(){
    //cout<<this<<" ";
    // cout<<this->getVal()<<" ";
    // cout<<get<0>(parents)<<" ";
    // cout<<get<1>(parents)<<" ";

    return to_string(this->getVal());
}
