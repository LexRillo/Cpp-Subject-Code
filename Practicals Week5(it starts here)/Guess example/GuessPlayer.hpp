#include <iostream>
#include <string>   

using namespace std;  

class GuessPlayer{

public:
  GuessPlayer();
  int guess(int g);
  int numberOfGuesses();
  int getTarget();
private:
  int target;
  int count;
};
