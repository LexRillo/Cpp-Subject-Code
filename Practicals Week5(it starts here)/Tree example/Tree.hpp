#include <iostream>
#include <math.h>
using namespace std;

class Tree{
private:
  int height;
  string spacesStars(int spaces, int stars);
  
public:
  Tree();
  void grow();
  void cut();
  int getHeight();
  void display();
  string toString();
};

