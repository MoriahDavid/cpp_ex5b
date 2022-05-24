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

    // Copy constructor
    Person::Person(const Person& other){
        this->name = other.name;
        this->person_subs = vector<Person>(); // new vector
        
        for(size_t i = 0; i < other.person_subs.size(); i++){ // copy all sub persons
            this->person_subs.emplace_back(Person(other.person_subs[i]));
        }
    }
    Person& Person::operator=(const Person& other){
        if(this==&other){
            return *this;
        }
        this->name = other.name;
        this->person_subs = vector<Person>();
        
        for(size_t i = 0; i < other.person_subs.size(); i++){
            this->person_subs.emplace_back(Person(other.person_subs[i]));
        }
        return *this;
    }
    Person::~Person(){
    }

    // Add son - p to this person
    void Person::add_sub(const Person& sub){
        this->person_subs.push_back(sub);
    }

    // Operator <<: put name in the stream
    ostream& operator<<(ostream& os, const Person& p){
        os << p.name;
        return os;
    }
}            