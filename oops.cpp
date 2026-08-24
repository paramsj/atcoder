#include <iostream>
#include <string>
using namespace std;

class Person {

protected:
    string name;
    int age;

public:

    Person(string name, int age)
        : name(name), age(age) {}

    // setter
    void setName(string newName) {
        name = newName;
    }

    // getter
    string getName() const {
        return name;
    }

    void introduce() const {
        cout << "My name is "
             << name
             << " and I am "
             << age
             << " years old\n";
    }
};


class Student : public Person {
private :
	int rollNo;

public :
	
	Student(string name,int age, int rollNo) : Person(name,age),rollNo(rollNo) {}

	void study() const {
		cout<<name<<" is studying!"<<endl;
	}
};
int main() {

	Student s1("Sumit", 21, 101);

    s1.introduce();

    s1.study();


    return 0;
}