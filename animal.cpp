#include <bits/stdc++.h>
using namespace std;

template <typename T>
T maximum(T a, T b) {
	return (a > b) ? a : b;
}

class Animal {
public:
	Animal() {
		cout<<"Im a animal";
	}
	virtual void makeNoise() {
		cout<<"I am horse"<<endl;
	}
	virtual ~Animal() {
		cout<<"i am no longer a horse";
	}
};

class Tikam : public Animal {
public:

	Tikam() {
		cout<<"I m a person";
	}

	void makeNoise() {
		[[likely]]cout<<"I am aryan tikam"<<endl;
	}

	~Tikam() {
		cout<<"i am no longet a tikam";
	}
};


class A {
public:

	A() {
		cout<<"Hello!";
	}
	void greet() {
		cout<<"Hello from A";
	}
	~A() {
		cout<<"Destructore called";
	}
};

class Person{
public:
	string name;
	Person(string name) {
		this->name = name;
	}
	~Person() {
		cout<<"Gone with the wind"<<endl;
	}
};


class String{
public:
	string bin;

	String(string bin) {
		this->bin = bin;
	}

	virtual void getDistinct() = 0;

	int getLength() {
		return this->bin.length();
	}

};

class Child : public String {
public:
	Child(string bin) : String(bin) {

	}

	void getDistinct() override {
		vector<int> freq(26,0);
		int n = this->getLength();
		for(int i=0;i<n;i++) {
			freq[this->bin[i] - 'a']++;
		}
		int res = 0;
		for(int i=0;i<26;i++) {
			if(freq[i]) {
				res++;
			}
		}
		cout<<res<<" ";
	}
};

int main() {
	Animal a;
	a.makeNoise();
    return 0;
}