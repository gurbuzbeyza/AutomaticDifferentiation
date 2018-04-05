#include "var.h"
#include <cstring>
vector<Var*> Var::nodes;

Var::Var(Operation operation, tuple<Var*,Var*>* parents){
    this->operation = operation;
    this->parents = *parents;
    Var* n = this->getVar();
    if(NULL==n) {
        this->nodes.push_back(this);
    }
}

Var::~Var(){}

// vector<tuple<Var,float>> Var::GetCopyOfVector(){
//         return ders;
// }

void Var::AddDer(Var* derOf,float der){
    tuple<Var*,float> tpl_der (derOf,der);
    derivatives.push_back(tpl_der);
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

// Overload + operator to add two Var objects.
Var& Var::operator+(const Var& b) {
    Var *newB = (Var*)&b;
    tuple<Var*,Var*> parents (this, newB);
    Var* v = new Var(Operation::add, &parents);
    return *v->getVar();

}

Var& Var::operator+(int b) {
    tuple<Var*,Var*> noParents (NULL, NULL);
    Var* bs = new Var(Operation::noop, &noParents);
    bs-> setVal((float)b);
    bs-> setScalar(true);
    tuple<Var*,Var*> parents (this, bs);
    Var* v = new Var(Operation::add,&parents);
    return *v ->getVar();

}
Var& Var::operator+(float b) {
    tuple<Var*,Var*> noParents (NULL, NULL);
    Var* bs = new Var(Operation::noop, &noParents);
    bs-> setVal((float)b);
    bs-> setScalar(true);
    tuple<Var*,Var*> parents (this, bs);
    Var* v = new Var(Operation::add,&parents);
    return *v ->getVar();

}

//subtraction
Var& Var::operator-(const Var& b){
    Var *newB = (Var*)&b;
    tuple<Var*,Var*> parents (this, newB);
    Var* v = new Var(Operation::sub, &parents);
    return *v->getVar();
}
Var& Var::operator-(int b) {
    tuple<Var*,Var*> noParents (NULL, NULL);
    Var* bs = new Var(Operation::noop, &noParents);
    bs-> setVal((float)b);
    bs-> setScalar(true);
    tuple<Var*,Var*> parents (this, bs);
    Var* v = new Var(Operation::sub,&parents);
    return *v ->getVar();

}

Var& Var::operator-(float b) {
    tuple<Var*,Var*> noParents (NULL, NULL);
    Var* bs = new Var(Operation::noop, &noParents);
    bs-> setVal((float)b);
    bs-> setScalar(true);
    tuple<Var*,Var*> parents (this, bs);
    Var* v = new Var(Operation::sub,&parents);
    return *v ->getVar();

}

// Overload * operator to multiply two Var objects.
Var& Var::operator*(const Var& b) {
    Var *newB = (Var*)&b;
    tuple<Var*,Var*> parents (this, newB);
    Var* v = new Var(Operation::mult, &parents);
    return *v->getVar();
}
Var& Var::operator*(int b) {
    tuple<Var*,Var*> noParents (NULL, NULL);
    Var* bs = new Var(Operation::noop, &noParents);
    bs-> setVal((float)b);
    bs-> setScalar(true);
    tuple<Var*,Var*> parents (this, bs);
    Var* v = new Var(Operation::mult,&parents);
    return *v ->getVar();

}

Var& Var::operator*(float b) {
    tuple<Var*,Var*> noParents (NULL, NULL);
    Var* bs = new Var(Operation::noop, &noParents);
    bs-> setVal((float)b);
    bs-> setScalar(true);
    tuple<Var*,Var*> parents (this, bs);
    Var* v = new Var(Operation::mult,&parents);
    return *v ->getVar();

}
//division
Var& Var::operator/(const Var& b){
    Var *newB = (Var*)&b;
    tuple<Var*,Var*> parents (this, newB);
    Var* v = new Var(Operation::divd, &parents);
    return *v->getVar();
}
Var& Var::operator/(int b) {
    tuple<Var*,Var*> noParents (NULL, NULL);
    Var* bs = new Var(Operation::noop, &noParents);
    bs-> setVal((float)b);
    bs-> setScalar(true);
    tuple<Var*,Var*> parents (this, bs);
    Var* v = new Var(Operation::divd,&parents);
    return *v ->getVar();
}

Var& Var::operator/(float b) {
    tuple<Var*,Var*> noParents (NULL, NULL);
    Var* bs = new Var(Operation::noop, &noParents);
    bs-> setVal((float)b);
    bs-> setScalar(true);
    tuple<Var*,Var*> parents (this, bs);
    Var* v = new Var(Operation::divd,&parents);
    return *v ->getVar();
}

Var& Var::operator=(const Var& b){
    Var *newB = (Var*)&b;
    this->setVal(newB->getVal());
    tuple<Var*,Var*> parents (newB, NULL);
    this->setParents(parents);
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


Var* Var::getVar(){
    for (vector<Var*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
        Var* a = *i;
        if (*a == *this){
            return a;
        }
    } 
    return NULL;
}

void Var::findVals(Var* a){
    switch(a->getOperation()) {
        case Operation::noop :
            if (NULL != get<0>(a->getParents())) {
                a->setVal(get<0>(a->getParents())->getVal());
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
        case Operation::divd :
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

vector<tuple<Var*,float>> Var::findDers(Var* a){
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
    return a->derivatives;
}


double* Var::findDiff(){
    int lenInputs = 0;
    for (vector<Var*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
        Var* a = *i;
        findVals(a);
        if (NULL == get<0>(a->getParents())&& NULL == get<1>(a->getParents())&& !(a->isScalar())){
            lenInputs++;
        }
    }
    int lenVars = nodes.size();
    double** Jacobian = new double*[lenVars];
    for (int i = 0; i < lenVars; ++i){
        Jacobian[i] = new double[lenVars];
        for (int j = 0; j < lenVars; ++j)
        {
            Jacobian[i][j] = 0;
        }
    }
    // memset(Jacobian, 0, lenVars*lenVars*sizeof(double));
    for (int i = 0; i < lenVars; ++i){
        Jacobian[i][i] = -1;
    }
    int j = 0;
    for (vector<Var*>::iterator i = this->nodes.begin(); i != this->nodes.end(); ++i){
        Var* a = *i;
        vector<tuple<Var*,float>> ders = findDers(a);
        // ders.push_back(tuple<Var*, float> (new Var(), 3 ));
        //cout<<a->toString()<<endl;
        for (vector<tuple<Var*,float>>::iterator k = ders.begin(); k != ders.end(); ++k){
            ptrdiff_t pos = distance(nodes.begin(), find(nodes.begin(), nodes.end(), get<0>(*k)));
            Jacobian[pos][j] = get<1>(*k);
            //cout<<pos<<" "<<j<<" "<<get<1>(*k)<<endl;
        }
        j++;
    }
    //cout<<"sfs"<<endl;
    for (int i = 0; i < lenVars; ++i){
        Jacobian[i][i] = -1;
    }
    /*cout<<"------"<<endl;
    for (int i = 0; i < lenVars; ++i){
        for (int j = 0; j < lenVars; ++j)
        {
            cout<<Jacobian[i][j]<<" ";
        }
        cout<<endl;
    }*/
    double* y = new double[lenVars];
    memset(y, 0, lenVars*sizeof(double));
    y[lenVars-1] = -1;
    //cout<<"------"<<endl;
    double* x = r8rmat_fs_new (lenVars, Jacobian, y);
    /*for (int i = 0; i < lenVars; ++i)
    {
        cout<<x[i]<<" ";
    }
    cout<<endl;
    */
    double* out = new double[lenInputs];
    for (int i = 0; i < lenInputs; ++i)
    {
        out[i] = x[i];
    }
    //ptrdiff_t pos = distance(nodes.begin(), find(nodes.begin(), nodes.end(), n));
    return out;
}

string Var::toString(){
    //cout<<this<<" ";
    
    cout<<get<0>(parents)<<" ";
    cout<<get<1>(parents)<<" ";

    return to_string(static_cast<underlying_type<Operation>::type>(this->operation));
}

