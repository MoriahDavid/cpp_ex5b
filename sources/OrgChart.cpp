#include <iostream>
#include <vector>
#include <queue>
#include <stack> 

#include "OrgChart.hpp"


using namespace std;


namespace ariel{


    //****// Level Order Iterator //****//

    // Constructor: add root to iterator
    OrgChart::iterator_level_order::iterator_level_order(Person* root){
        this->p = root;
        this->q = queue<Person*>();

        if(root != nullptr){
            q.push(root);
        }
    }

    // Operator == : checks if the iterators are of the same type
    bool OrgChart::iterator_level_order::operator==(const iterator_level_order& it) const{
        return this->p == it.p;
    }

    // Operator != : checks if the iterators are not of the same type
    bool OrgChart::iterator_level_order::operator!=(const iterator_level_order& it) const{
        return !(this->operator==(it));
    }

    // Go to the next person (after the curr iter possition)
    void OrgChart::iterator_level_order::next(){
        if(!q.empty()){ // the queue not empty
            Person* front = q.front(); // take the front person
            for(size_t i = 0; i < front->person_subs.size(); i++){
                q.push(&front->person_subs[i]); //push all person's child to the queue
            }
            q.pop(); // take the front son
            if(q.empty()){
                p = nullptr;
            }
            else{
                p = q.front(); // save the next child
            }
        }
        else{
            p = nullptr; // there is no more sons to person
        }
    } 

    // Operator ++iterator: go to next person and return iterator
    OrgChart::iterator_level_order& OrgChart::iterator_level_order::operator++(){ //++iterator
        this->next();
        return *this;
    }

    // Operator iterator++: return the current person and go to next
    OrgChart::iterator_level_order OrgChart::iterator_level_order::operator++(int){ //iterator++
        iterator_level_order temp= *this;
        this->next();
		return temp;
    }

    // Operator *: return the name of this current person
    string& OrgChart::iterator_level_order::operator*() const{
        return p->name;
    }

    // Operator ->: return pointer to the name of this current person
    string* OrgChart::iterator_level_order::operator->() const{
        return &p->name;
    }




    //****// Reverse Iterator //****//

    // Constructor: add root to iterator
    OrgChart::iterator_reverse_order::iterator_reverse_order(Person* root){
        this->vec = vector<Person*>();

        if(root == nullptr){
            this->index = -1;
        }
        else{
            this->create_vec_reverse_ord(root);
            this->index = 0;
        }
    }

    // Operator == : checks if the iterators are of the same type
    bool OrgChart::iterator_reverse_order::operator==(const iterator_reverse_order &it) const{
        return this->index == it.index;
    }

    // Operator != : checks if the iterators are not of the same type
    bool OrgChart::iterator_reverse_order::operator!=(const iterator_reverse_order &it) const{
        return !(this->operator==(it));
    }

    // Go to the next person (after the curr iter possition)
    void OrgChart::iterator_reverse_order::next(){
        if(this->index == this->vec.size()-1){ // if got to the end of the persons list
            this->index = -1; // change the index (flag)
        }
        else{
            this->index = this->index + 1;
        }
    }    

    // Operator ++iterator: go to next person and return iterator
    OrgChart::iterator_reverse_order& OrgChart::iterator_reverse_order::operator++(){ //++iterator
        this->next();
        return *this;
    }

    // Operator iterator++: return the current person and go to next
    OrgChart::iterator_reverse_order OrgChart::iterator_reverse_order::operator++(int){ //iterator++
        iterator_reverse_order temp = *this;
        this->next();
		return temp;
    }

    // Operator *: return the name of this current person
    string& OrgChart::iterator_reverse_order::operator*() const{
        return this->vec[(size_t)this->index]->name;
    }

    // Operator ->: return pointer to the name of this current person
    string* OrgChart::iterator_reverse_order::operator->() const{
        return &this->vec[(size_t)this->index]->name;
    }




    //****// Preorder Iterator //****//

    // Constructor: add root to iterator
    OrgChart::iterator_preorder::iterator_preorder(Person* root){
        this->stk = stack<Person*>{};

        this->p = root;
        if(root != nullptr){
            stk.push(root);
        }
    }    

    // Operator == : checks if the iterators are of the same type
    bool OrgChart::iterator_preorder::operator==(const iterator_preorder &it) const{
        return this->p == it.p;
    }

    // Operator != : checks if the iterators are not of the same type
    bool OrgChart::iterator_preorder::operator!=(const iterator_preorder &it) const{
        return !(this->operator==(it));
    }

    // Go to the next person (after the curr iter possition)
    void OrgChart::iterator_preorder::next(){
        if(!this->stk.empty()){ // the queue not empty
            Person* top = this->p;
            this->stk.pop();
            if(!top->person_subs.empty()){
                for(int i = (int)top->person_subs.size()-1; i > -1; i--){
                    this->stk.push(&top->person_subs[(size_t)i]);
                }
            }
            if(this->stk.empty()){
                this->p = nullptr;
            }
            else{
                this->p = this->stk.top();
            }
        }
        else{
            this->p = nullptr;
        }
    }

    // Operator ++iterator: go to next person and return iterator
    OrgChart::iterator_preorder& OrgChart::iterator_preorder::operator++(){ //++iterator
        this->next();
        return *this;
    }

    // Operator iterator++: return the current person and go to next
    OrgChart::iterator_preorder OrgChart::iterator_preorder::operator++(int){ //iterator++
        iterator_preorder temp = *this;
        this->next();
        return temp;
    }

    // Operator *: return the name of this current person
    string& OrgChart::iterator_preorder::operator*() const{
        return p->name;
    }

    // Operator ->: return pointer to the name of this current person
    string* OrgChart::iterator_preorder::operator->() const{
        return &p->name;
    }


    OrgChart::OrgChart(){
        this->org_is_empty = true;
        this->root = Person();
    }

    OrgChart::iterator_level_order OrgChart::begin(){
        if(org_is_empty){
            throw logic_error("cant get iterator because org is empty");
        }
        return iterator_level_order(&root);
    }

    OrgChart::iterator_level_order OrgChart::end() const{
        if(org_is_empty){
            throw logic_error("cant get iterator because org is empty");
        }
        return iterator_level_order(nullptr);
    }

    OrgChart::iterator_level_order OrgChart::begin_level_order(){
        if(org_is_empty){
            throw logic_error("cant get iterator because org is empty");
        }
        return iterator_level_order(&root);
    }

    OrgChart::iterator_level_order OrgChart::end_level_order() const{
        if(org_is_empty){
            throw logic_error("cant get iterator because org is empty");
        }
        return iterator_level_order(nullptr);
    }
    
    OrgChart::iterator_reverse_order OrgChart::begin_reverse_order(){
        if(org_is_empty){
            throw logic_error("cant get iterator because org is empty");
        }
        return iterator_reverse_order(&root);
    }

    OrgChart::iterator_reverse_order OrgChart::reverse_order() const{
        if(org_is_empty){
            throw logic_error("cant get iterator because org is empty");
        }
        return iterator_reverse_order(nullptr);
    }

    OrgChart::iterator_preorder OrgChart::begin_preorder(){
        if(org_is_empty){
            throw logic_error("cant get iterator because org is empty");
        }
        return iterator_preorder(&root);
    }

    OrgChart::iterator_preorder OrgChart::end_preorder() const{
        if(org_is_empty){
            throw logic_error("cant get iterator because org is empty");
        }
        return iterator_preorder(nullptr);
    }

    // Add to OrgChart root by the person name and return the Orgchart
    OrgChart& OrgChart::add_root(const string& s){
        if(s.empty()){
            throw logic_error("name cant be empty");
        }
        this->root.name = s;
        this->org_is_empty = false;
        return *this;
    }

    // Add to person (p) son (subp) by names and return the OrgChart
    OrgChart& OrgChart::add_sub(const string& p, const string& subp){
        if(org_is_empty){
            throw logic_error("cant add sub because org is empty");
        }
        if(p.empty() || subp.empty()){
            throw logic_error("names cant be empty");
        }
        Person* father = find_person(&this->root, p);
        if(father == nullptr){
            throw logic_error("Person(father) dont found");
        }
        father->add_sub(Person(subp));
        return *this;
    }

    // Find person in OrgChart by his name and return the person pointer
    Person* OrgChart::find_person(Person* root, const string& name){

        if(root->name == name){
            return root;
        }
        for(size_t i = 0; i < root->person_subs.size(); i++){
            Person* result = find_person(&root->person_subs[i], name);
            if(result != nullptr){
                return result;
            }
        }   
        return nullptr;
    }

    // Create string of the OrgChart
    void print_org_chart(ostream& os, const string& prefix, const Person* p, bool last_bro){
        if(p != nullptr){
            os << prefix;
            if(last_bro){
                os << "└─";
            }
            else{
                os << "├─" ;
            }
            // print the name of the person
            os << p->name;
            if(!p->person_subs.empty()){ // has childs
                os << "┐";
            }
            os << endl;
            string prefix_add;
            if(last_bro){
                prefix_add = string(p->name.size()+2, ' ');
            }
            else{
                prefix_add = "│" + string(p->name.size()+1, ' ');// + string(' ',p->name.size());
            }
            for(size_t i=0; i<p->person_subs.size(); i++){
                bool l = (i == p->person_subs.size()-1);

                print_org_chart(os, prefix + prefix_add, &p->person_subs[i], l);
            }
        }
    }

    // Print the OrgChart
    ostream& operator<<(ostream& os, const OrgChart& org){
        print_org_chart(os, "", &org.root, true);
        return os;
    }

    // Func for reverse order - create vector for OrgChart with its people.
    void OrgChart::iterator_reverse_order::create_vec_reverse_ord(Person* root){
        queue<Person*> q;
        q.push(root);
        while(!q.empty()){
            Person* front = q.front();
            q.pop();
            this->vec.insert(this->vec.begin(), front);
            if(!front->person_subs.empty()){
                for(int i = (int)front->person_subs.size()-1; i >= 0; i--){ // do reverse to the vector
                    q.push(&front->person_subs[(size_t) i]);
                }
            }
        }
    }

}