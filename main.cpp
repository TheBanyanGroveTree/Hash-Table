/**
   Description: Implement Student List using a hash table.
   Author: Aahana Sapra
   Date: 1/28/2026
 */

#include <iostream>
#include <cstring>

using namespace std;

// define function prototypes

int main() {
  // define const var for commands
  const char ADD[] = "ADD";
  const char PRINT[] = "PRINT";
  const char DELETE[] = "DELETE";
  const char QUIT[] = "QUIT";

  // declare char arr for user input
  const int INPUT_LENGTH = 81;
  char userCommand[INPUT_LENGTH];

  // continue prompting user for input until QUIT command
  bool keepModifying = true;
  while (keepModifying) {
    // read in user input
    cout << "Enter a command (ADD, PRINT, DELETE, QUIT): ";
    cin.getline(userCommand, INPUT_LENGTH);

    // convert input to uppercase for comparison
    for (int i = 0; i < strlen(userCommand); i++) {
      userCommand[i] = toupper(userCommand[i]);
    }
    
    // validate input
    if ((strcmp(userCommand, ADD) != 0) &&
	(strcmp(userCommand, PRINT) != 0) &&
	(strcmp(userCommand, DELETE) != 0) &&
	(strcmp(userCommand, QUIT) != 0)) {
      cout << "Please input ADD, PRINT, DELETE, or QUIT." << endl;
    } else {
      // call appropriate method or exit program
      if (strcmp(userCommand, ADD) == 0) {
	
      } else if (strcmp(userCommand, PRINT) == 0) {
	
      } else if (strcmp(userCommand, DELETE) == 0) {
	
      } else if (strcmp(userCommand, QUIT) == 0){
	keepModifying = false;
      }
    }
  }
  
  return 0;
}
