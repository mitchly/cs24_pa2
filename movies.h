//movies.h
// Joshua Thomas: 3937661. Michelle Ly: 3774189
#include <string>
#include <vector>
#include <iostream>
#ifndef MOVIES_H
#define MOVIES_H

using std::cout;

struct Node {
  std::string name;
  double rating;
  int depth;
  Node *left, *right, * parent;
  // useful constructor:
   Node(std::string name, double rating, int depth) : name(name), rating(rating), depth(depth), left(0), right(0), parent(0) { }
};

class movies {

 public:
    // ctor, dtor, insert and one print method already done in intbst.cpp:
    movies(); // constructor
    ~movies(); // destructor
    bool insert(std::string name, double rating); // insert value; return false if duplicate
    void printPreOrder() const; // prints tree data pre-order to cout

    // Methods
    std::string getName(Node* n) const;
    double getRating(Node* n);
    int getDepth(Node* n);
    void printGetBest(std::string prefix) const;
    Node* getNodeFor(std::string inputName);
    void bstTime(std::vector<float> timeVect, int numNodes, int wSearches);
    void addToCSVFile(int n, int n_visted);

 private:
    // just one instance variable (pointer to root node):
    Node *root;

    // recursive utility functions for use by public methods above
    Node* getNodeFor(std::string inputName, Node* n) const;
    void clear(Node *n); // for destructor
    bool insert(std::string name, double rating, int depth, Node *n); // note overloading names for simplicity
    void printPreOrder(Node *n) const;
    void getPrefixhelper(std::string prefix, Node* pos, std::vector<Node*>& vec_name) const;
    std::vector<Node*> getPrefix(std::string prefix, Node* n) const;
    int insertCount(std::string name, double rating, int counter, Node* n);
};

#endif