/**
   Description: Implement Student List using a hash table.
   Author: Aahana Sapra
   Date: 1/28/2026
 */

#include <iostream>
#include <string>

using namespace std;

// define function prototypes

int main() {
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
