#include <iostream>
#include <string.h>

#include "OrgChart.hpp"

using namespace std;
using namespace ariel;

int main(){

OrgChart org;
org.add_root("a")
.add_sub("a", "b").add_sub("a", "c")
.add_sub("b", "d").add_sub("b", "e").add_sub("c", "f").add_sub("c", "g");

cout << org;

bool is_running = true;

    while(is_running){
        
        cout << endl;
        try{

            cout << "choose order: ";
            string order;
            try{
                cin >> order;
            }
            catch (exception & ex) {
                cout << "invalid input: " << ex.what() << endl;
                continue;
            }

            if(order == "level"){
                for (auto it = org.begin_level_order(); it != org.end_level_order(); ++it){
                    cout << (*it) << " " ;
                }    
            }

            else if(order == "reverse"){
                for (auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it){
                    cout << (*it) << " " ;
                }    
            }
            
            else if(order == "preorder"){
                for (auto it=org.begin_preorder(); it!=org.end_preorder(); ++it){
                    cout << (*it) << " " ;
                } 
            }

            else{
                cout << "invalid input, please choose: level | reverse | preorder" << endl;
            }
        }

        catch (exception & ex) {
            cout << "invalid input: " << ex.what() << endl;
            continue;
        }
        cout << endl << "Do you want to continue? (y/n) ";
        char ans;
        cin >> ans; // Get user answer
        if(ans == 'n'){
            is_running = false;
        }
    }
}

