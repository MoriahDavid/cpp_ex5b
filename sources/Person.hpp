#include <iostream>
#include <vector>

using namespace std;

namespace ariel{

    class Person{
        private:

        public:
            string name;

            vector<Person> person_subs;

            Person();
            Person(const string& name);
            Person(const Person& other);
            ~Person();

            Person& operator=(const Person& other);
            Person& operator=(Person&& other) = default;
            Person(Person&) = default;
            Person(Person&&) = default;


            // Add son - p to this person
            void add_sub(const Person& sub);

            friend ostream& operator<<(ostream& os, const Person& p);
    };
}
