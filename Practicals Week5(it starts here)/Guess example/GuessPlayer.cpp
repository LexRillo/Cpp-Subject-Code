#include <iostream>
#include <string>   
#include <cmath>   
#include <cstdlib>

#include "GuessPlayer.hpp"

using namespace std;  

GuessPlayer::GuessPlayer() {
  count=0;
  target=rand() % 100;
}

int  GuessPlayer::guess(int g) {
  count++;
  if (target<g){ 
      return -1;
  }
  if (target>g){
      return 1;
  }
  return 0;
}

int GuessPlayer::numberOfGuesses() {
  return count;
}

int GuessPlayer::getTarget(){
  return target;
}
