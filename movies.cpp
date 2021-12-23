// movies.cpp
// Implements class movies
// Joshua Thomas: 3937661. Michelle Ly: 3774189

#include "movies.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
using namespace std;
using std::cout;

// constructor sets up empty tree
movies::movies() : root(0) { }

// recursive helper for destructor
void movies::clear(Node* n) {
  if(n!=NULL)
  {
      clear(n->left); // call for left clear
      clear(n->right); // call for right clear
      if(n->left!=NULL) // check if it is not null
          n->left=NULL; // make it null
      if(n->right!=NULL)
          n->right=NULL;
      n = nullptr; // set main n to null
      delete n; // delete it
  }
}

// destructor deletes all nodes
movies::~movies() {
    clear(root); // start clearing
    root = NULL; // ensure root is null
    delete root; // kill it
}

// insert value in tree; return false if duplicate
bool movies::insert(string name, double rating) {
    // handle special case of empty tree first
    if (!root) {
	     root = new Node(name, rating, 0);
	     return true;
    }
    // otherwise use recursive helper
    return insert(name, rating, 1, root);
}

// recursive helper for insert (assumes n is never 0)
bool movies::insert(string name, double rating, int depth, Node *n) {
  if (name.compare(n->name) == 0){
    return false;
  }
  if (name.compare(n->name) < 0) { // if name is alphabeticaly before n->name
    if (n->left) {
      return insert(name, rating, depth + 1, n->left);
    }
    else {
      n->left = new Node(name, rating, depth);
      n->left->parent = n;
      return true;
    }
  }
  else { // if it is after
	  if (n->right)
      return insert(name, rating, depth + 1, n->right);
	  else {
      n->right = new Node(name, rating, depth);
      n->right->parent = n;
      return true;
    }
  }
}

// print tree data pre-order
void movies::printPreOrder() const {
    printPreOrder(this->root);
    cout << endl;
}

// recursive helper for printPreOrder()
void movies::printPreOrder(Node *n) const {
  if (n) {
    cout << n->name << ", " << n->rating << ", " << n->depth << endl;
    printPreOrder(n->left);
    printPreOrder(n->right);
  }
}

// getter function for movie name (within node)
string movies::getName(Node* n) const {
  return n->name;
}

// getter function for rating (within node)
double movies::getRating(Node* n){
  return n->rating;
}

// getter function for depth (within node)
int movies::getDepth(Node* n){
  return n->depth;
}

// helper function for getPrefix puts all movies in vector
void movies::getPrefixhelper(string prefix, Node* pos, vector<Node*>& vec_name) const{
  if (pos == nullptr) {
    return;
  }
  if (pos->name.substr(0,prefix.size()).compare(prefix) < 0) {
    getPrefixhelper(prefix, pos->right, vec_name);
  }
  else if (pos->name.substr(0,prefix.size()).compare(prefix) > 0) {
    getPrefixhelper(prefix, pos->left, vec_name);
  }
  else{
    vec_name.push_back(pos);
    getPrefixhelper(prefix, pos->left, vec_name); getPrefixhelper(prefix, pos->right, vec_name);
  }
}

// getter function to retrieve all movies with prefix
vector<Node*> movies::getPrefix(string prefix, Node* n) const{
  vector<Node*> prefixMovies;
  getPrefixhelper(prefix, n, prefixMovies);
  return prefixMovies;
}

// prints final statement in main if argv[1] is true
void movies::printGetBest(string prefix) const{
  vector<Node*> movielist = getPrefix(prefix, root);
  if(movielist.empty()) { // shouldn't print anything, return to end definition
    return;
  }
  Node* max = movielist[0];
  for(int i=1; i < movielist.size(); i++){ // for loop picks movie with best (max) rating
   if(movielist[i]->rating > max->rating) {
     max = movielist[i];
   }
  }
  cout<< "Best movie is " << max->name << " with rating " << max->rating << endl;
}

// public getter for getting a node given a string (movie name)
Node* movies::getNodeFor(string inputName){
  return getNodeFor(inputName, root);
}

// private part of getNodeFor for access to private node variable
Node* movies::getNodeFor(string inputName, Node* n) const{
  while(n != NULL){ // recursive function works as long as n != NULL
      if(n->name == inputName){ // return node is string == movie name
          return n;
      }
      else if(inputName < n->name){ // if string goes before the node's name in alphabet go left
          n = n->left;
      }
      else{
          n = n->right; // otherwise go right
      }
  }
  return NULL; // if node not found
}

// prints out max, min, and average time it takes to run getNodeFor for every node
void movies::bstTime(vector<float> timeVect, int numNodes, int wSearches){
  int length = wSearches;
  float max(0), min(timeVect[0]), sum(0), average(0);
  
  for(int i = 0; i < length; i++){ // for loop for max
    if(max < timeVect[i]){
      max = timeVect[i];
    }
  }

  for(int j = 1; j < length; j++){ // for loop for min
    if(min > timeVect[j]){
      min = timeVect[j];
    }
  }

  for(int k = 0; k < length; k++){ // for loop for sum
    sum += timeVect[k];
  }

  average = sum / wSearches;
  //printed statements
  cout << "The maximum time for one iteration to search all keys in the BST is " 
       << max * 1000000 / CLOCKS_PER_SEC << " microseconds" << endl;
  cout << "The minimum time for one iteration to search all keys in the BST is "
       << min * 1000000 / CLOCKS_PER_SEC << " microseconds" << endl;
  cout << "The average time for all " << wSearches 
       << " iterations to search all keys in the BST is " << average * 1000000 / CLOCKS_PER_SEC
       << " microseconds" << endl;
}

// adds N and N_visited to a CSV file
void movies::addToCSVFile(int n, int n_visited){
  ofstream myfile;
  myfile.open("temporary_output_file_name.csv", fstream::app);
    if(!myfile.is_open()){ // error thrown
    cerr << "Error: Failure to Open." << endl;
    myfile.close();
    return;
  }
  myfile << n << "," << n_visited << endl; // format that data is put in
  myfile.close();
}