#include <iostream>
#include <string>

#include "GuessPlayer.hpp"

using namespace std; 



int main() {


  GuessPlayer gp;
  
  int choice=0;
  
  while (choice!=4) {
    cout << "please select 1-4";
    cin >> choice;
    if (choice==1) {
      cout << "You have used "<< gp.numberOfGuesses() << " number of guesses"
	   << endl;
    }
    if (choice ==2) {
      cout << "The target was " << gp.getTarget() << endl;
    }
    
    if (choice ==3) {
      int g;
      cout << "What is your choice"<< endl;
      cin >> g;
      cout << gp.guess(g) << endl;
    }
  }


  
  return 0;
}
