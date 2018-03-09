#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <math.h>
//http://www.cplusplus.com/reference/tuple/tuple/
//implemented only operations between valders. TODO expand for valder, float operations -> tum floatlari valdere cast edeceksek gerek de yok mu acaba???
// TODO add graph field to valder ? -> keys of AddDer graph yerine gecer mi??? niye lazim ki graph:D
//TODO remove name field?
//TODO implement = overloading to pass by reference and to assign floats to valders at initialization.
using namespace std;

class Valder {

        public:
                Valder()
                {}
                ~Valder()
                {}
                void AddDer(Valder derOf,float der)
                {
                tuple<Valder,float> tpl_der (derOf,der);
                    ders.push_back(tpl_der);
                }
                std::vector<tuple<Valder,float>> GetCopyOfVector()
                {
                        return ders;
                }
                void DisplayDerValues()
                {
                    cout<<"displaying ders:"<<endl;
                        for( unsigned int i = 0; i < ders.size(); i++ )
                        {
                            cout<<"derivative to "<<std::get<0>(ders[i]).getName()<< " is: " << std::get<1>(ders[i]) << endl;
                        }
                        cout << endl;
                }

                void setName(string s){
                        name = s;
                }

                string getName(void){
                        return name;
                }

                void setVal(float v){
                        val = v;
                }

                float getVal(void){
                        return val;
                }
                // Overload + operator to add two Valder objects.
                Valder operator+(Valder b) {
                    Valder vd;
                    vd.setVal(this->val + b.getVal());
                    vd.AddDer(b,1);
                    vd.AddDer(*this,1);
                    vd.setName("deleteNameField");
                    return vd;
               }
               //subtraction
               Valder operator-(Valder b){
                    Valder vd;
                    vd.setVal(this->val-b.getVal());
                    vd.AddDer(b,-1);
                    vd.AddDer(*this,1);
                    vd.setName("subtractionresult");
                    return vd;
                }

               // Overload * operator to multiply two Valder objects.
                Valder operator*(Valder b) {
                    Valder vd;
                    vd.setVal(this->val * b.getVal());
                    vd.AddDer(b,this->val);
                    vd.AddDer(*this,b.getVal());
                    vd.setName("deleteNameField");
                    return vd;
               }
                //division
                Valder operator/(Valder b){
                    Valder v;
                    v.setVal(this->val / b.getVal());
                    v.AddDer(b,(-this->val)/b.getVal()*b.getVal());
                    v.AddDer(*this,1/b.getVal());
                    v.setName("div result");
                    return v;
                }         

        private:
                std::vector<tuple<Valder,float>> ders;
                string name;
                float val;

};

Valder pow(Valder var,Valder p){
    Valder v;
    v.setName("powresult");
    v.setVal(pow(var.getVal(),p.getVal()));
    v.AddDer(var,p.getVal()*(pow(var.getVal(),p.getVal()-1)));
    v.AddDer(p,pow(var.getVal(),p.getVal())*log(var.getVal()));
    return v;   
}

Valder sqrt(Valder var){
    Valder v;
    v.setName("sqrtresult");
    v.setVal(sqrt(var.getVal()));
    v.AddDer(var,1/(2*sqrt(var.getVal())));
    return v;
}



Valder sin(Valder var) {
    Valder v;
    v.setName("sinResult");
    v.setVal(var.getVal());
    v.AddDer(var,cos(var.getVal()));
    cout << "Sin result added" << endl;
    return v;
}

Valder cos(Valder var) {
    Valder v;
    v.setName("cosResult");
    v.setVal(var.getVal());
    v.AddDer(var,(-1)*sin(var.getVal()));
    cout << "Cos result added" << endl;
    return v;
}

Valder tan(Valder var){
    Valder v;
    v.setName("tanresult");
    v.setVal(tan(var.getVal()));
    v.AddDer(var,1/(pow(cos(var.getVal()),2)));
    return v;
}

Valder asin(Valder var){    
    Valder v;
    v.setName("asinresult");
    v.setVal(asin(var.getVal()));
    v.AddDer(var,1/sqrt(1-pow(var.getVal(),2)));
    return v;
}
Valder acos(Valder var){    
    Valder v;
    v.setName("acosresult");
    v.setVal(acos(var.getVal()));
    v.AddDer(var,(-1)/sqrt(1-pow(var.getVal(),2)));
    return v;
}

Valder atan(Valder var){    
    Valder v;
    v.setName("atanresult");
    v.setVal(atan(var.getVal()));
    v.AddDer(var,1/pow(var.getVal(),2)+1);
    return v;
}

Valder exp(Valder var){
    Valder v;
    v.setName("expresult");
    v.setVal(exp(var.getVal()));
    v.AddDer(var,exp(var.getVal()));
}

Valder log(Valder var){
    Valder v;
    v.setName("logresult");
    v.setVal(log(var.getVal()));
    v.AddDer(var,1/var.getVal());
    return v;
}

/*//template

Valder Z(Valder var){    
    Valder v;
    v.setName("Zresult");
    v.setVal(Z(var.getVal()));
    v.AddDer(var,ZZZZ);
    return v;
}*/


int main() {
    
    /// just try some stuff
    Valder a;
    Valder b;
    Valder result;
    a.setName("a");
    b.setName("b");
    a.setVal(2.7);
    a.AddDer(b,3);
    b.setVal(2);
    cout<<"a: "<<endl;
    a.DisplayDerValues();
    result.setVal(23);
    result =a;
    a=log(result)/b;
    cout<<"a again: "<<a.getVal()<<endl;
    a.DisplayDerValues();

    return 0;
}



//https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm -> add many on the list, like unary (-)

//http://warp.povusers.org/FunctionParser/  -> warping in c++
