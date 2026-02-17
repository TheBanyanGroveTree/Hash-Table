/**
   Description: Implement Student List using a hash table with the addition
   of a random student generator.
   Author: Aahana Sapra
   Date: 2/15/2026
 */


#include <iostream>
#include <string>
#include <limits>
#include <ios>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Node.h"


using namespace std;


// Define hashTable struct
struct hashTable {
  int size; // number of elements it can hold
  int count; // current number of elements
  Node** arr; // array of Node ptr
};


// Define function prototypes
void initializeHashTable(hashTable*, int);
int hashFunction(hashTable*, int); // pass strings by ref for read-only
void addStudent(hashTable*&);
void insert(hashTable*&, int, Student*);
void rehash(hashTable*&);
int countNodes(Node* head);
void randomGenerator(hashTable*&, vector<string>&, vector<string>&);
vector<string> readFile(vector<string>&, const string&);
void printHashTable(hashTable*);
void printLinkedList(Node* head);
void deleteStudentHashTable(hashTable*&);
Node* deleteStudentLinkedList(Node*, int);
void quitHashTable(hashTable*, bool&);
void quitLinkedList(Node*);


int main() {
  // Initialize hash table
  hashTable* table = new hashTable();
  int tableSize = 100;
  initializeHashTable(table, tableSize);

  // Read in names from .txt files
  vector<string> firstNames;
  firstNames = readFile(firstNames, "firstNames.txt");
  vector<string> lastNames;
  lastNames = readFile(lastNames, "lastNames.txt");

  /*
  for (int i = 0; i < firstNames.size(); i++) {
    cout << firstNames[i] << endl;
  }
  */

  srand(time(0)); // Seed random number generator
  
  // Define const var for commands
  const string ADD = "ADD";
  const string RANDOM = "RANDOM";
  const string PRINT = "PRINT";
  const string DELETE = "DELETE";
  const string QUIT = "QUIT";

  // Declare str for user input
  string userCommand = "";

  // Continue prompting user for input until QUIT command
  bool keepModifying = true;
  while (keepModifying) {
    // read in user input
    cout << "Enter a command (ADD, RANDOM, PRINT, DELETE, QUIT): ";
    getline(cin, userCommand);

    // convert input to uppercase for comparison
    for (int i = 0; i < userCommand.size(); i++) {
      userCommand[i] = toupper(userCommand[i]);
    }
    
    // validate input
    if ((userCommand.compare(ADD) != 0) &&
	(userCommand.compare(RANDOM) != 0) &&
	(userCommand.compare(PRINT) != 0) &&
	(userCommand.compare(DELETE) != 0) &&
	(userCommand.compare(QUIT) != 0)) {
      cout << "Please input ADD, RANDOM, PRINT, DELETE, or QUIT." << endl;
    } else {
      // call appropriate method or exit program
      if (userCommand.compare(ADD) == 0) {
	addStudent(table);
      } else if (userCommand.compare(RANDOM) == 0) {
	randomGenerator(table, firstNames, lastNames);
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


// Create new hash table and initialize struct vals
void initializeHashTable(hashTable* table, int tableSize) {
  table->size = tableSize;
  table->count = 0;
  // dynamically allocate memory and initialize to NULL 
  table->arr = new Node*[table->size]();
}


// Implement hashing function (mod) and return bucket index for table
int hashFunction(hashTable* table, int id) {
  /*
  int sum = 0;
  for (int i = 0; i < key.length(); i++) {
    sum += static_cast<int>(key[i]);
  }
  */

  return (id % table->size);
}


// Create new student entry
void addStudent(hashTable*& table) {
  // initialize input vars
  string firstName = "";
  string lastName = "";
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

  // create new Node and insert into hash table where key is id
  insert(table, newStudent->getID(), newStudent);
}


// Insert new entry into hash table
void insert(hashTable*& table, int key, Student* newStudent) {
  // determine bucket index for given key
  int bucketIndex = hashFunction(table, key);

  // create new Node
  Node* newNode = new Node(newStudent);

  // NO collision: empty bucket index
  if (table->arr[bucketIndex] == NULL) {
    table->arr[bucketIndex] = newNode;
  }
  // COLLISION: full bucket index
  else {
    // check for rehash
    if (countNodes(table->arr[bucketIndex]) == 3) {
      rehash(table);
    }
    
    // new Node becomes new head that points to old head (NO traversal)
    newNode->setNext(table->arr[bucketIndex]);
    table->arr[bucketIndex] = newNode;
  }
}


// Rehash table if more than 3 collisions
void rehash(hashTable*& table) {
  // save old information
  int oldSize = table->size;
  Node** oldArr = table-> arr;

  // double size and reinitialize hash table
  int newSize = oldSize * 2;
  initializeHashTable(table, newSize);
  
  // re-insert old nodes iteratively (more common)
  for (int i = 0; i < oldSize; i++) {
    Node* head = oldArr[i];
    while (head != NULL) {
      Node* nextNode = head->getNext(); // save next node
      head->setNext(NULL);
      insert(table, head->getStudent()->getID(), head->getStudent());
      head = nextNode;
    }
  }

  delete[] oldArr; // delete array ptr
}


// Cound nodes in linked list
int countNodes(Node* head) {
  int count = 0;
  while (head != NULL) {
    count++;
    head = head->getNext();
  }

  return count;
}

// Randomly generate students
void randomGenerator(hashTable*& table, vector<string>& firstNames,
		     vector<string>& lastNames) {
  // prompt user for number of students to generate
  int numStudents = 0;
  cout << "Enter the number of students to generate: ";
  cin >> numStudents;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  // generate designated number of students
  int randomFNI = 0;
  string firstName = "";
  int randomLNI = 0;
  string lastName = "";
  int currID = 400000;
  double randomGPA = 0.0;
  for (int i = 0; i < numStudents; i++) {
    // generate random values
    randomFNI = rand() % firstNames.size();
    firstName = firstNames[randomFNI];
    randomLNI = rand() % lastNames.size();
    lastName = lastNames[randomLNI];
    randomGPA = ((double)rand() / RAND_MAX) * 4.0;

    // create new Student
    Student* newStudent = new Student(firstName, lastName, currID, randomGPA);

    // create new Node and insert into hash table
    insert(table, newStudent->getID(), newStudent);

    // increment ID
    currID++;
  }
  
}


// Read .txt file and save info into vector
vector<string> readFile(vector<string>& vec, const string& fileName) {
  // read from given file
  ifstream file(fileName);

  // read file line by line
  string name = "";
  while (getline(file, name)) {
    vec.push_back(name);
  }

  file.close();

  return vec;
}


// Print entries stored in hash table
void printHashTable(hashTable* table) {
  for (int i = 0; i < table->size; i++) {
    printLinkedList(table->arr[i]);
  }
}


// Print entries stored in linked list recursively
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


// Delete student with corresponding ID from hash table
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


// Delete student with corresponding ID from linked list recursively
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


// Delete hash table and change updating status
void quitHashTable(hashTable* table, bool& keepModifying) {
  for (int i = 0; i < table->size; i++) {
    quitLinkedList(table->arr[i]);
  }

  keepModifying = false;
}


// Delete linked list recursively
void quitLinkedList(Node* head) {
  // base case: empty list
  if (head == NULL) {
    return;
  }

  // recursive call
  quitLinkedList(head->getNext());
  delete head; // delete current node
}
