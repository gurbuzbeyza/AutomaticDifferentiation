#include <iostream>
#include <string>
#include <vector>
#include <tuple>
//http://www.cplusplus.com/reference/tuple/tuple/

using namespace std;

/*float arr[4];
arr[0] = 6.28;
arr[1] = 2.50;
arr[2] = 9.73;
arr[3] = 4.364;
std::vector<float*> vec = std::vector<float*>();
vec.push_back(arr);
float* ptr = vec.front();
for (int i = 0; i < 3; i++)
    printf("%g\n", ptr[i]);*/
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
                void DisplayDerValuesDummy()
                {
                        for( unsigned int i = 0; i < ders.size(); i++ )
                        {
                                cout << "Element[" << i << "] = " << std::get<0>(ders[i]).getName() << " of der is: " << std::get<1>(ders[i]) << endl;
                        }
                        cout << endl;
                }

                /*Valder::Valder(void){
                        cout<<"valder object created"<<endl;
                }*/ //??

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
                // Overload + operator to add two Box objects.
                Valder operator+(Valder b) {
                    Valder vd;
                    vd.val = this->val + b.val;
                    vd.AddDer(b,b.getVal());
                    //vd.AddDer(this,this->getVal());   //need to uncomment this line but gives error
                    vd.setName("deleteNameField");
                    return vd;
               }

        private:
                std::vector<tuple<Valder,float>> ders;
                string name;
                float val;

};



int main() {
    Valder vd;
    Valder vd2;
    Valder vdres;
    vd.setName("vd");
    vd2.setName("vd2");
    vd.setVal(1);
    vd2.setVal(2);
    vd.AddDer(vd2,3);
    vd.DisplayDerValuesDummy();
    vdres = vd+vd2;
    vdres.DisplayDerValuesDummy();
    return 0;
}
