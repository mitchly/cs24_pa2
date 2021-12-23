// This file contains all the unit tests for all the
// public interfaces of the classes that we implemented

#include "movies.h"
#include "tests.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main(){
    runAll();
    return 0;
}

void runAll(){
    test_insert_and_printPreOrder();
    test_constructor();
    test_destructor();
    test_getBest();
    test_getNodeFor_NameRatingDepth();
    test_bstTime();
    test_addToCSVFile();
}

void test_insert_and_printPreOrder(){
    START_TEST("test_insert_and_printPreOrder");
    movies movie1;
    
    movie1.insert("Finals", 2.0);
    movie1.insert("Summer", 8.3);
    movie1.insert("Dead Week", 1.5);
    movie1.insert("Vacation", 9.8);

    cout << "If it prints, both insert and printPreOrder function: "
         << endl;
    cout << endl;

    movie1.printPreOrder();

    END_TEST("test_insert_and_printPreOrder");
}

void test_constructor(){
    START_TEST("test_constructor");
    cout << "Ensure the other testers work properly. "
         << "If they do, that means the (main) constructor functions correctly (nothing would work if it didn't)." << endl;
    END_TEST("test_constructor");
}

void test_destructor(){
    START_TEST("test_destructor");
    cout << "Printing movies should result in nothing." << endl;
    movies movie1;

    movie1.insert("Finals", 2.0);
    movie1.insert("Summer", 8.3);
    movie1.insert("Dead Week", 1.5);
    movie1.insert("Vacation", 9.8);
    cout << "Before destructor: " << endl;
    movie1.printPreOrder();
    movie1.~movies();
    cout << "After destructor: " << endl;
    movie1.printPreOrder();
    END_TEST("test_destructor");
}

void test_getBest(){ // tests getPrefixhelper, getPrefix, getBest
    START_TEST("test_getBest");
    movies movie1;
    
    movie1.insert("Finals", 2.0);
    movie1.insert("Fishy Summer", 8.3);
    movie1.insert("Dead Week", 1.5);
    movie1.insert("Vacation", 9.8);

    movie1.printPreOrder();
    cout << "If 'Fishy Summer' is the movie that prints, it works: " << endl;
    movie1.printGetBest("Fi");

    END_TEST("test_getBest");
}

void test_getNodeFor_NameRatingDepth(){ // checks if the right node has been gotten if the right name, rating, and depth is given
    START_TEST("test_getNodeFor_NameRatingDepth");
    movies movie1;
    
    movie1.insert("Finals", 2.0);
    movie1.insert("Summer", 8.3);
    movie1.insert("Dead Week", 1.5);
    movie1.insert("Vacation", 9.8);

    movie1.printPreOrder();

    cout << "Getting node information for 'Vacation'; should match printed info above: "
         << endl;
    cout << "Name: ";
    cout << movie1.getName(movie1.getNodeFor("Vacation")) << endl;
    cout << "Rating: ";
    cout << movie1.getRating(movie1.getNodeFor("Vacation")) << endl;
    cout << "Depth: ";
    cout << movie1.getDepth(movie1.getNodeFor("Vacation")) << endl;

    END_TEST("test_getNodeFor_NameRatingDepth");
}

void test_bstTime(){
    START_TEST("test_bstTime");
    movies movie1;
    vector<float> test;
    test.push_back(50);
    test.push_back(27.4);
    test.push_back(92.03);
    test.push_back(38.2);

    movie1.bstTime(test, 20, 4);

    END_TEST("test_bstTime");
}

void test_addToCSVFile(){
    START_TEST("test_addToCSVFile");
    movies movie1;
    cout << "A CSV File should be created with 1,5 and 2,7 and 3,10: " << endl;
    movie1.addToCSVFile(1, 5);
    movie1.addToCSVFile(2, 7);
    movie1.addToCSVFile(3, 10);
    END_TEST("test_addToCSVFile");
}