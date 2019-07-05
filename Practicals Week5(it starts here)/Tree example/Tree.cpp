#include "Tree.hpp"


Tree::Tree(){
  height=3;
}

void Tree::grow(){
  if (height>=0)
    height++;
}

void Tree::cut(){
  height=0;
}

int Tree::getHeight(){
  return height;
}

string Tree::spacesStars(int spaces, int stars) {
  string ans;
  for (int i=0;i<spaces; ++i) 
    ans=ans+" ";
  for (int i=0;i<stars; ++i) 
    ans=ans+"*";
  return ans;
}
    

void Tree::display(){
  for (int i=0; i<height;i++)
    cout << spacesStars(2+height-i,2*i+1) <<endl;
  for (int i=0; i<3; i++)
    cout << spacesStars(1+height,3) << endl;
}

string Tree::toString(){
  return "This tree is of height "+height;
}

