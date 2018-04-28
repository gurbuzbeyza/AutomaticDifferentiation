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
vector<tuple<Var*,float>> Var::getDerivatives(void){
    return this->derivatives;
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
    for (set<Var*>::iterator i = this->inputs.begin(); i != this->inputs.end(); ++i){
        Var* a = *i;
        // cout<<a->toString()<<endl;
        a->setVisited(true);
        this->sortedNodes.push_back(a);
    }
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


// map<Var*, float> Var::recDers(Var* v, map<Var*, float>& derivs){
//     findDers (v);
//     cout<<"loop"<<endl;
//     map<Var*, float> dersLoc;
//     for (set<Var*>::iterator i = v->dependentInputs.begin(); i != v->dependentInputs.end(); ++i){
//         Var* a = *i;
//         // derivs[a] = 1;
//         dersLoc[a] = 0;
//         if (NULL != get<0>(v->getParents()) && get<0>(v->getParents())->dependentInputs.find(a) != get<0>(v->getParents())->dependentInputs.end())
//         {
//             dersLoc[a] += get<1>(v->getDerivatives()[0]);
//         }
//         // cout<<derivs[a]<<endl;
//     }
//     for (set<Var*>::iterator i = v->dependentInputs.begin(); i != v->dependentInputs.end(); ++i){
//         Var* a = *i;
//         // derivs[a] = 1;
//         if (NULL != get<1>(v->getParents()) && get<1>(v->getParents())->dependentInputs.find(a) != get<1>(v->getParents())->dependentInputs.end())
//         {
//             dersLoc[a] += get<1>(v->getDerivatives()[1]);
//         }
//         // cout<<derivs[a]<<endl;
//     }
//     map<Var*, float> x = recDers (get<0>(v->getParents()), derivs);
//     recDers (get<1>(v->getParents()), derivs);
//     for (set<Var*>::iterator i = v->dependentInputs.begin(); i != v->dependentInputs.end(); ++i){
//         Var* a = *i;
//         derivs[a] = dersLoc[a]*x[a];
//     }
// }

 /*void Var::calcDers(map<Var*, float>& derivs){
    map<Var*, float> dersLoc;
    for (set<Var*>::iterator i = this->dependentInputs.begin(); i != this->dependentInputs.end(); ++i){
        Var* a = *i;
        dersLoc[a] = 1;
    }
     for (vector<Var*>::reverse_iterator i = this->sortedNodes.rbegin(); i != this->sortedNodes.rend(); ++i){
         Var* a = *i;
         cout<<a->isInput()<<" isinpt"<<endl;
         findDers (a);
         if (NULL != get<0>(a->getParents())) {
             for (set<Var*>::iterator j = get<0>(a->getParents())->dependentInputs.begin(); j != get<0>(a->getParents())->dependentInputs.end(); ++j){
                // dersLoc[*j] = 1;
                 dersLoc[*j] *= get<1>(a->getDerivatives()[0]);
                 cout<<*j<<" ="<<get<1>(a->getDerivatives()[0])<<endl;
             }
         }
         if (NULL != get<1>(a->getParents())) {
            for (set<Var*>::iterator j = get<1>(a->getParents())->dependentInputs.begin(); j != get<1>(a->getParents())->dependentInputs.end(); ++j){
                // dersLoc[j] = 1;
                 dersLoc[*j] *= get<1>(a->getDerivatives()[1]);
                 cout<<*j<<" *="<<get<1>(a->getDerivatives()[1])<<endl;
             }
         }
         if (a->isInput()){
            cout<<a<<" "<<dersLoc[a]<<" add to input cur total: "<< derivs[a]<<endl;
            derivs[a]+=dersLoc[a];
         }
     }
 }*/

void Var::calcDers(map<Var*,float>& derivs){//base
    derivs = this->calcDers(this);
}

map<Var*, float> Var::calcDers(Var* v){//base
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


/*map<Var*, float> Var::calcDers(map<Var*,float>& derivs, map<Var*,float>& locDers,Var* v){//base
    v.findDiff();
    if(get<0>(v->getParents())==NULL && v->isInput()){
        //derivs[v] += locDers[v];
        return locDers;
    }
    map<Var*,float> newDers;
    if(get<0>(v->getParents())!=NULL){
        newDers = calcDers(derivs,locDers,v->get<0>(getParents()));
           
    }
    if(get<1>(v->getParents())!=NULL){
        newDers += calcDers(derivs,locDers,v->get<1>(getParents()));
    }
    for (set<Var*>::iterator i = v->getDependentInputs().begin(); i != v->getDependentInputs().end(); ++i){
            Var* a = *i;
            locDers[a] *= newDers[a];
    }
}*/

/*map<Var*, float> Var::calcDers(Var* v, map<Var*, float>& derivs,map<Var*, float> locDers){
    findDers (v);
    if (get<0>(v->getParents()) == NULL &&  get<1>(v->getParents()) == NULL )
    {
        for (set<Var*>::iterator i = v->getDependentInputs().begin(); i != v->getDependentInputs().end(); ++i){
            Var* a = *i;
            locDers[a] *= get<1>(a->getDerivatives()[0]);
            derivs[a] += locDers[a];
        }
        return locDers;
    }
    if (get<1>(v->getParents()) == NULL)//one parent only
    {
        for (set<Var*>::iterator i = v->getDependentInputs().begin(); i != v->getDependentInputs().end(); ++i){
            Var* a = *i;
            locDers[a] *= get<1>(a->getDerivatives()[0]);
            locDers[a]*=calcDers(a,derivs,locDers)[a];
        }
    }
    else//2 parents
    {
        map<Var*, float> locDer1;
        map<Var*, float> locDer2;
        map<Var*, float> locDerSum;
        for (set<Var*>::iterator i = v->getDependentInputs().begin(); i != v->getDependentInputs().end(); ++i){
            Var* a = *i;
            locDerSum[a] =1;
        }
        for (set<Var*>::iterator i = get<0>(v->getParents())->getDependentInputs().begin(); i != get<0>(v->getParents())->getDependentInputs().end(); ++i){
            Var* a = *i;
            locDer1[a] = get<1>(a->getDerivatives()[0]);
            locDer1[a]*=calcDers(a,derivs,locDer2)[a];
            locDerSum[a]=locDer1[a];
        }
        for (set<Var*>::iterator i = get<1>(v->getParents())->getDependentInputs().begin(); i != get<1>(v->getParents())->getDependentInputs().end(); ++i){
            Var* a = *i;
            locDer2[a] *= get<1>(a->getDerivatives()[0]);
            locDer2[a]*=calcDers(a,derivs,locDer2)[a];
            locDerSum[a]+=locDer2[a];
        }
        for (set<Var*>::iterator i = v->getDependentInputs().begin(); i != v->getDependentInputs().end(); ++i){
            Var* a = *i;
            locDers[a]*=locDerSum[a];
        }
    }
}*/



map<Var*, float> Var::findDiff(){
    // for (vector<Var*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
    //     Var* a = *i;
    //     // cout<<a->toString()<<endl;
    //     if (NULL == get<0>(a->getParents()) && NULL == get<1>(a->getParents())&& !(a->isScalar())){
    //         lenInputs++;
    //     }
    // }
    //int lenInputs = this->inputs.size();
    calcVals();
    //int lenVars = nodes.size();
    // double** Jacobian = new double*[lenVars];
    // for (int i = 0; i < lenVars; ++i){
    //     Jacobian[i] = new double[lenVars];
    //     for (int j = 0; j < lenVars; ++j)
    //     {
    //         Jacobian[i][j] = 0;
    //     }
    // }
    // for (int i = 0; i < lenVars; ++i){
    //     Jacobian[i][i] = -1;
    // }
    map<Var*, float> derivs;
    //map<Var*, float> locDers;
    /*for (set<Var*>::iterator i = this->inputs.begin(); i != this->inputs.end(); ++i){
        Var* a = *i;
        derivs[a] = 0;
        //locDers[a] = 0;
    }
    for (set<Var*>::iterator i = this->dependentInputs.begin(); i != this->dependentInputs.end(); ++i){
        Var* a = *i;
        derivs[a] = 0;//?1?
        //locDers[a] = 1;
    }*/
    calcDers(derivs);
    // for (vector<Var*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
    //     Var* a = *i;
    //     vector<tuple<Var*,float>> ders = a->derivatives;
    //     for (vector<tuple<Var*,float>>::iterator k = ders.begin(); k != ders.end(); ++k){
    //         ptrdiff_t pos = distance(nodes.begin(), find(nodes.begin(), nodes.end(), get<0>(*k)));
    //         Jacobian[pos][j] = get<1>(*k);
    //         // cout<<pos<<" "<<j<<" "<<get<1>(*k)<<endl;
    //     }
    //     j++;
    // }
    // for (int i = 0; i < lenVars; ++i){
    //     Jacobian[i][i] = -1;
    // }

    // double* y = new double[lenVars];
    // memset(y, 0, lenVars*sizeof(double));
    // ptrdiff_t pos = distance(nodes.begin(), find(nodes.begin(), nodes.end(), this));
    // y[pos] = -1;

    // double* x = r8rmat_fs_new (lenVars, Jacobian, y);
    // double* out = new double[lenInputs];

    // for (int i = 0; i < lenInputs; ++i)
    // {
    //     out[i] = x[i];
    // }
    return derivs;
}

string Var::toString(){
    //cout<<this<<" ";
    // cout<<this->getVal()<<" ";
    // cout<<get<0>(parents)<<" ";
    // cout<<get<1>(parents)<<" ";

    return to_string(this->getVal());
}
