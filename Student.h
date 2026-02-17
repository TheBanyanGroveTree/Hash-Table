#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

class Student {
 public:
  Student(); // Default constructor
  Student(string, string, int, double); // Constructor with parameters
  string getFirstName(); // Get first name
  string getLastName(); // Get last name
  int getID(); // Get ID
  double getGPA(); // Get GPA
  ~Student(); // Destructor
 private:
  string firstName;
  string lastName;
  int id;
  float gpa;
};

#endif
