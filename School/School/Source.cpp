#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#define MAX 5

using namespace std;

class Animal {
public : 
	virtual void monya() { cout << "���� !" << endl; }
	void whatRU() { cout << "An animal!" << endl; }

};
class Dog : public Animal {
public : 
	virtual void monya() { cout << "�۸���! \n"; }
	void whatRU() { cout << "A Dog!" << endl; }
};

int main() {
	Animal* ap; Animal a2;
	Dog* fido = new Dog(); Dog doggy;
	ap = fido; a2 = doggy;
	fido -> monya(); fido->whatRU();
	ap->monya(); ap->whatRU();
	a2.monya(); a2.whatRU();
}