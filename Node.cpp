#include <iostream>
#include <string>
#include "Node.h"
#include "Student.h"

using namespace std;

Node::Node(Student* student) {
  this->student = student;
  next = NULL; 
}

Student* Node::getStudent() {
  return student;
}

void Node::setNext(Node* next) {
  this->next = next;
}

Node* Node::getNext() {
  return next;
}

Node::~Node() {
  delete student;
  next = NULL;
}
