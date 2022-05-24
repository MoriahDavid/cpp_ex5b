#include "doctest.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

#include "OrgChart.hpp"
using namespace ariel;

TEST_CASE("good inputs"){

    OrgChart organization;

    // Check build works well
    CHECK_NOTHROW(organization.add_root("1"));
    CHECK_NOTHROW(organization.add_sub("1", "1.1"));
    CHECK_NOTHROW(organization.add_sub("1", "1.2"));
    CHECK_NOTHROW(organization.add_sub("1.1", "1.1.1"));
    CHECK_NOTHROW(organization.add_sub("1.2", "1.2.1"));
    CHECK_NOTHROW(organization.add_sub("1.1.1", "1.1.1.1"));
    CHECK_NOTHROW(organization.add_sub("1.2.1", "1.2.1.1"));

    // Level order
    vector<string> correct_results1{"1", "1.1", "1.2", "1.1.1", "1.2.1", "1.1.1.1", "1.2.1.1"};

    vector<string> test_results1;

    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
        test_results1.push_back(*it);
    }    
    CHECK(correct_results1 == test_results1);  


    // Reverse order
    vector<string> correct_results2{"1.1.1.1", "1.2.1.1", "1.1.1", "1.2.1", "1.1", "1.2", "1"};

    vector<string> test_results2;

    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it){
        test_results2.push_back(*it);
    }    
    CHECK(correct_results2 == test_results2); 


    // Preorder (root, left, right)
    vector<string> correct_results3{"1", "1.1", "1.1.1", "1.1.1.1", "1.2", "1.2.1", "1.2.1.1"};

    vector<string> test_results3;

    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it){
        test_results3.push_back(*it);
    }    
    CHECK(correct_results3 == test_results3);


    // Check add root function (with levelorder)
    organization.add_root("new_root");

    vector<string> correct_results4{"new_root", "1.1", "1.2", "1.1.1", "1.2.1", "1.1.1.1", "1.2.1.1"};
    vector<string> test_results4;

    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
        test_results4.push_back(*it);
    }
    CHECK(correct_results4 == test_results4);

    OrgChart organization2;
    // Check build works well a->b->c->d
    CHECK_NOTHROW(organization2.add_root("1"));
    CHECK_NOTHROW(organization2.add_sub("1", "1.1"));
    CHECK_NOTHROW(organization2.add_sub("1.1", "1.2"));
    CHECK_NOTHROW(organization2.add_sub("1.2", "1.3"));
    CHECK_NOTHROW(organization2.add_sub("1.2", "1.4"));

    // Level order
    vector<string> correct_results5{"1", "1.1", "1.2", "1.3", "1.4"};

    vector<string> test_results5;

    for (auto it = organization2.begin_level_order(); it != organization2.end_level_order(); ++it){
        test_results5.push_back(*it);
    }    
    CHECK(correct_results5 == test_results5); 

    // Preorder
    vector<string> correct_results6{"1", "1.1", "1.2", "1.3", "1.4"};

    vector<string> test_results6;

    for (auto it = organization2.begin_preorder(); it != organization2.end_preorder(); ++it){
        test_results6.push_back(*it);
    }    
    CHECK(correct_results6 == test_results6); 
}



TEST_CASE("bad inputs"){

    OrgChart organization;

    // Check create iterator on empty OrgChart
    CHECK_THROWS(organization.begin());
    CHECK_THROWS(organization.begin_level_order());
    CHECK_THROWS(organization.begin_reverse_order());
    CHECK_THROWS(organization.begin_preorder());

    CHECK_THROWS(organization.end());
    CHECK_THROWS(organization.end_level_order());
    CHECK_THROWS(organization.reverse_order());
    CHECK_THROWS(organization.end_preorder());

    CHECK_THROWS(organization.add_root("")); // add empty root
    organization.add_root("1"); 
    CHECK_THROWS(organization.add_sub("1", "")); // add empty child
    CHECK_THROWS(organization.add_sub("1.2", "1.2.1")); // Father 1.2 dont exist
    CHECK_THROWS(organization.add_sub("4", "1.3")); // Father dont exist in the OrgChart

}    