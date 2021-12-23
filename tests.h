#ifndef TESTS_H
#define TESTS_H
#include <iostream>
using namespace std;

void runAll();
void test_constructor();
void test_destructor();
void test_insert_and_printPreOrder();
void test_getBest();
void test_getNodeFor_NameRatingDepth();
void test_bstTime();
void test_addToCSVFile();

void START_TEST(string testname){
  cout<<"Start "<<testname<<endl;
}

void END_TEST(string testname) {
  cout<<"End "<<testname<<endl<<endl;
}


#endif