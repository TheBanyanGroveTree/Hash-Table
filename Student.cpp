#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

Student::Student() {
  firstName = "";
  lastName = "";
  id = 0;
  gpa = 0.0;
}

Student::Student(string firstName, string lastName, int id, double gpa) {
  this->firstName = firstName;
  this->lastName = lastName;
  this->id = id;
  this->gpa = gpa;
}

string Student::getFirstName() {
  return firstName;
}

string Student::getLastName() {
  return lastName;
}

int Student::getID() {
  return id;
}

double Student::getGPA() {
  return gpa;
}

Student::~Student() {

}
