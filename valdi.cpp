#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <math.h>
//http://www.cplusplus.com/reference/tuple/tuple/

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
                    vd.val = this->val + b.val;
                    vd.AddDer(b,1);
                    vd.AddDer(*this,1);
                    vd.setName("deleteNameField");
                    return vd;
               }

               // Overload * operator to multiply two Valder objects.
                Valder operator*(Valder b) {
                    Valder vd;
                    vd.val = this->val * b.val;
                    vd.AddDer(b,this->val);
                    vd.AddDer(*this,b.getVal());
                    vd.setName("deleteNameField");
                    return vd;
               }

        private:
                std::vector<tuple<Valder,float>> ders;
                string name;
                float val;

};

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


int main() {
    Valder a;
    Valder b;
    Valder result;
    a.setName("a");
    b.setName("b");
    a.setVal(1);
    b.setVal(2);
    cout<<"a: "<<endl;
    a.DisplayDerValues();
    result =sin(a);
    cout<<"result: "<<endl;
    result.DisplayDerValues();

    return 0;
}



//https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm -> add many on the list, like unary (-)

//http://warp.povusers.org/FunctionParser/  -> warping in c++
