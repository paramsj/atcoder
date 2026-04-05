#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <unistd.h>
#include <sys/types.h>

using namespace std;
using namespace __gnu_pbds;

class Person {
public:
    int age;
    Person(int a) : age(a) {}
    Person() : age(10) {}

    virtual void fly() {
        cout<<"from the person";
    }

    virtual ~Person {};
};

class Student : public Person {
public:
    string name;
    Student(string name,int age) : Person(age) {
        this->name = name;
    } 

    f
    void fly override () {
        cout<<"From student";
    }
};

class Teacher : public Person {
public:
    string subject;
    string name;
    Teacher(string subject,string name,int age) : Person(age),subject(subject),name(name) {}

    void fly override () {
        cout<<"From Teacher";
    }
};

