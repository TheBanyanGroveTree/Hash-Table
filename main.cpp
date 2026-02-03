/**
   Description: Implement Student List using a hash table.
   Author: Aahana Sapra
   Date: 2/3/2026
 */

#include <iostream>
#include <string>
#include <limits>
#include <ios>
#include "Node.h"

using namespace std;

// define hashTable struct
struct hashTable {
  int count; // number of elements
  int size; // number of elements it can hold
  Node** arr; // array of Node ptr
};

// define function prototypes
void initializeHashTable(hashTable*, const int&);
int hashFunction(hashTable*, const string&); // pass by ref for read-only
void addStudent();
void insert();
void printStudentInfo();
void deleteStudent();
void quit();

int main() {
  // declare hash table
  hashTable* table = new hashTable();
  const int TABLE_SIZE = 100;
  
  // define const var for commands
  const string ADD = "ADD";
  const string PRINT = "PRINT";
  const string DELETE = "DELETE";
  const string QUIT = "QUIT";

  // declare str for user input
  string userCommand = "";

  // continue prompting user for input until QUIT command
  bool keepModifying = true;
  while (keepModifying) {
    // read in user input
    cout << "Enter a command (ADD, PRINT, DELETE, QUIT): ";
    getline(cin, userCommand);

    // convert input to uppercase for comparison
    for (int i = 0; i < userCommand.size(); i++) {
      userCommand[i] = toupper(userCommand[i]);
    }
    
    // validate input
    if ((userCommand.compare(ADD) != 0) &&
	(userCommand.compare(PRINT) != 0) &&
	(userCommand.compare(DELETE) != 0) &&
	(userCommand.compare(QUIT) != 0)) {
      cout << "Please input ADD, PRINT, DELETE, or QUIT." << endl;
    } else {
      // call appropriate method or exit program
      if (userCommand.compare(ADD) == 0) {
	
      } else if (userCommand.compare(PRINT) == 0) {
	
      } else if (userCommand.compare(DELETE) == 0) {
	
      } else if (userCommand.compare(QUIT) == 0){
	keepModifying = false;
      }
    }
  }
  
  return 0;
}

// create new hash table
void initializeHashTable(hashTable* table, const int& TABLE_SIZE) {
  table->count = 0;
  table->size = TABLE_SIZE;
  // dynamically allocate memory and initialize to NULL 
  table->arr = new Node*[table->size]();
}

// implement hashing function (mod) and return bucket index for table
int hashFunction(hashTable* table, const string& key) {
  int sum, bucketIndex = 0;
  for (int i = 0; i < key.length(); i++) {
    sum += static_cast<int>(key[i]);
  }

  return sum % table->size;
}

// create new student entry
void addStudent() {
  string firstName, lastName = "";
  int id = 0;
  float gpa = 0.0;

  // read in user input
  cout << "Enter the student's first name: ";
  getline(cin, firstName);

  cout << "Enter the student's last name: ";
  getline(cin, lastName);

  cout << "Enter the student's ID: ";
  cin >> id;
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

  cout << "Enter the student's GPA: ";
  cin >> gpa;
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

  // create new Student
  Student* newStudent = new Student(firstName, lastName, id, gpa);

  // create new Node and insert into hash table
  Node* newNode = new Node(newStudent);
}

// insert new entry into hash table
void insert() {

}

// print entries stored in hash table
void printStudentInfo() {

}

// delete student with corresponding ID from linked list
void deleteStudent() {

}

// delete hash table and change updating status
void quit() {

}
