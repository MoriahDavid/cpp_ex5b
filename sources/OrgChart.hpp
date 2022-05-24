#include <iostream>
#include <vector>
#include <queue>
#include <stack> 
#include "Person.hpp"

using namespace std;

namespace ariel{

    class OrgChart{

        private:
            Person root;
            bool org_is_empty;
            Person* find_person(Person* root, const string& name);

        public:
            class iterator_level_order{
                private:
                    queue<Person*> q;
                    Person* p;
                    void next();
                public:
                    iterator_level_order(Person* root);
                    bool operator==(const iterator_level_order &it) const;
                    bool operator!=(const iterator_level_order &it) const;
                    iterator_level_order& operator++(); //++iterator
                    iterator_level_order operator++(int); //iterator++
                    string& operator*() const;
                    string* operator->() const;
            };

            class iterator_reverse_order{
                private:
                    vector<Person*> vec;
                    int index;
                    void next();
                    void create_vec_reverse_ord(Person* root);

                public:
                    iterator_reverse_order(Person* root);
                    bool operator==(const iterator_reverse_order &it) const;
                    bool operator!=(const iterator_reverse_order &it) const;
                    iterator_reverse_order& operator++(); //++iterator
                    iterator_reverse_order operator++(int); //iterator++
                    string& operator*() const;
                    string* operator->() const;

            };

            class iterator_preorder{
                private:
                    stack<Person*> stk;
                    Person* p;
                    void next();
                public:
                    iterator_preorder(Person* root);
                    bool operator==(const iterator_preorder &it) const;
                    bool operator!=(const iterator_preorder &it) const;
                    iterator_preorder& operator++(); //++iterator
                    iterator_preorder operator++(int); //iterator++
                    string& operator*() const;
                    string* operator->() const;

            };

            iterator_level_order begin(); //call begin level order
            iterator_level_order end() const; //call begin level order

            iterator_level_order begin_level_order();
            iterator_level_order end_level_order() const;
            
            iterator_reverse_order begin_reverse_order();
            iterator_reverse_order reverse_order() const;

            iterator_preorder begin_preorder();
            iterator_preorder end_preorder() const;

            OrgChart& add_root(const string& s);
            OrgChart& add_sub(const string& p, const string& subp);

            OrgChart();
            OrgChart(const OrgChart& other);
            ~OrgChart();
            
            OrgChart& operator=(const OrgChart& other);
            OrgChart& operator=(OrgChart&& other) = default;
            OrgChart(OrgChart&) = default;
            OrgChart(OrgChart&&) = default;

            friend ostream& operator<<(ostream& os, const OrgChart& org); //friend in order to relate to the class
    };


}   