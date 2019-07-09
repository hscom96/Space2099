#include<iostream>
#include<string>
using namespace std;

class COUT {
public :
	void operator <<(int i) {
		printf("%d gg\n", i);
	}
	void operator <<(double i) {
		printf("%d gg\n", i);
	}
	void operator <<(const char* i) {
		printf("%s gg\n", i);
	}
};


int main() {
	COUT cout;
	cout << "ddkga";
}