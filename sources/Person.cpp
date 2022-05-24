#include <iostream>
#include <vector>
#include "Person.hpp"

using namespace std;
namespace ariel{

    Person::Person(const string& name){
        this->name = name;
        this->person_subs = vector<Person>();
    }
    Person::Person(){
        this->name = "";
        this->person_subs = vector<Person>();
    }

    // Add son - p to this person
    void Person::add_sub(const Person& sub){
        this->person_subs.push_back(sub);
    }

    ostream& operator<<(ostream& os, const Person& p){
        os << p.name;
        return os;
    }
}            