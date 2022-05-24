#include <iostream>
#include <vector>

using namespace std;

namespace ariel{

    class Person{
        private:

        public:
            string name;

            vector<Person> person_subs;

            Person(const string& name);
            Person();

            // Add son - p to this person
            void add_sub(const Person& sub);

            friend ostream& operator<<(ostream& os, const Person& p);
    };
}
