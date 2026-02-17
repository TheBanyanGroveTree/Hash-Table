/**
   Description: Implement Student List using a hash table.
   Author: Aahana Sapra
   Date: 2/15/2026
 */

#include <iostream>
#include <string>
#include <limits>
#include <ios>
#include <iomanip>
#include "Node.h"

using namespace std;

// define hashTable struct
struct hashTable {
  int size; // number of elements it can hold
  int count; // current number of elements
  Node** arr; // array of Node ptr
};

// define function prototypes
void initializeHashTable(hashTable*, const int&);
int hashFunction(hashTable*, const string&); // pass by ref for read-only
void addStudent(hashTable*&);
void insert(hashTable*&, const string&, Student*);
void printHashTable(hashTable*);
void printLinkedList(Node* head);
void deleteStudentHashTable(hashTable*&);
Node* deleteStudentLinkedList(Node*, int);
void quitHashTable(hashTable*, bool&);
void quitLinkedList(Node*);

int main() {
  // initialize hash table
  hashTable* table = new hashTable();
  const int TABLE_SIZE = 100;
  initializeHashTable(table, TABLE_SIZE);
  
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
	addStudent(table);
      } else if (userCommand.compare(PRINT) == 0) {
	printHashTable(table);
      } else if (userCommand.compare(DELETE) == 0) {
	deleteStudentHashTable(table);
      } else if (userCommand.compare(QUIT) == 0){
	quitHashTable(table, keepModifying);
      }
    }
  }
  
  return 0;
}

// create new hash table
void initializeHashTable(hashTable* table, const int& TABLE_SIZE) {
  table->size = TABLE_SIZE;
  table->count = 0;
  // dynamically allocate memory and initialize to NULL 
  table->arr = new Node*[table->size]();
}

// implement hashing function (mod) and return bucket index for table
int hashFunction(hashTable* table, const string& key) {
  int sum = 0;
  int bucketIndex = 0;
  for (int i = 0; i < key.length(); i++) {
    sum += static_cast<int>(key[i]);
  }

  bucketIndex = sum % table->size;
  return bucketIndex;
}

// create new student entry
void addStudent(hashTable*& table) {
  string firstName, lastName = "";
  int id = 0;
  double gpa = 0.0;

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
  // key = student last name
  insert(table, newStudent->getLastName(), newStudent);
}

// insert new entry into hash table
void insert(hashTable*& table, const string& key, Student* newStudent) {
  // determine bucket index for give key-val pair
  int bucketIndex = hashFunction(table, key);

  // create new Node
  Node* newNode = new Node(newStudent);

  // NO collision: empty bucket index
  if (table->arr[bucketIndex] == NULL) {
    table->arr[bucketIndex] = newNode;
  }
  // COLLISION: full bucket index
  else {
    // new Node becomes new head that points to old head (NO traversal)
    newNode->setNext(table->arr[bucketIndex]);
    table->arr[bucketIndex] = newNode;
  }
  
  // TODO: add check for rehashing
}

// print entries stored in hash table
void printHashTable(hashTable* table) {
  for (int i = 0; i < table->size; i++) {
    printLinkedList(table->arr[i]);
  }
}

// print entries stored in linked list recursively
void printLinkedList(Node* head) {
  // base case: reached end of list
  if (head == NULL) {
    return;
  }

  // recursive call
  cout << head->getStudent()->getFirstName() << ' '
       << head->getStudent()->getLastName() << ", "
       << head->getStudent()->getID() << ", "
       << fixed << setprecision(2) << head->getStudent()->getGPA() << endl;
  printLinkedList(head->getNext());
}

// delete student with corresponding ID from hash table
void deleteStudentHashTable(hashTable*& table) {
  // prompt user for ID to delete
  int userID = 0;
  cout << "Enter the student's ID: ";
  cin >> userID;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  // delete student from linked list
  for (int i = 0; i < table->size; i++) {
    table->arr[i] = deleteStudentLinkedList(table->arr[i], userID);
  }
}

// delete student with corresponding ID from linked list recursively
Node* deleteStudentLinkedList(Node* head, int id) {
  // base case 1: empty list
  if (head == NULL) {
    return NULL;
  }

  // base case 2: reached node to delete
  if (head->getStudent()->getID() == id) {
    Node* next = head->getNext();
    delete head;
    return next;
  }
  
  // recursive call
  head->setNext(deleteStudentLinkedList(head->getNext(), id));
  return head;
}

// delete hash table and change updating status
void quitHashTable(hashTable* table, bool& keepModifying) {
  for (int i = 0; i < table->size; i++) {
    quitLinkedList(table->arr[i]);
  }

  keepModifying = false;
}

// delete linked list recursively
void quitLinkedList(Node* head) {
  // base case: empty list
  if (head == NULL) {
    return;
  }

  // recursive call
  quitLinkedList(head->getNext());
  delete head; // delete current node
}
