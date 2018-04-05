#include <bits/stdc++.h>

using namespace std;

class Animal
{
private:
	string name;
public:
	Animal(string _name){
		name = _name;
	}

	string getName(){
		return name;
	}
};

Animal& localCreate(){
	Animal a("essek");
	return a;
}

Animal& dynamicCreate(){
	Animal* a = new Animal("stochastic panter");
	return *a;
}

int main(int argc, char const *argv[])
{
	// Seg. Fault
	//Animal myFirstAnimal = localCreate();
	//cout << "Name of my animal is " << myFirstAnimal.getName() << endl ;

	// No Error
	Animal mySecondAnimal = dynamicCreate();
	cout << "Name of my animal is " << mySecondAnimal.getName() << endl ;
	
}