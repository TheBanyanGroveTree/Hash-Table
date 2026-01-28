#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

class Node {
 public:
  Node(Student*); // Constructor
  Student* getStudent(); // Get Student ptr
  void setNext(Node*); // Set next ptr to corresponding node ptr
  Node* getNext(); // Get next Node ptr
  ~Node(); // Destructor
 private:
  Student* student;
  Node* next;
};

#endif
