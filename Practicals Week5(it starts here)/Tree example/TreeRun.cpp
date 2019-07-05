#include <iostream>
#include "Tree.hpp"

using namespace std;


int main(){
  Tree t;
  int x=100;
  while(x!=0){
    x=100;
    while(x<0||x>6) {
      cout<<"Please input "<<endl;
      cout<<" 1 - water tree" << endl;
      cout<<" 2 - cut tree" << endl;
      cout<<" 3 - draw tree" << endl;
      cout<<" 4 - get height of the tree" << endl;
      cout<<" 5 - information of the tree" << endl;
      cout << endl;
      cout<<" 0 - end" << endl;
      cin >>x;
    }
    
    switch (x){
    case 1 : t.grow();
      break;
    case 2 : t.cut();
      break;
    case 3 : t.display();
      break;
    case 4 : cout << t.getHeight() <<endl;
      break;
    case 5 : cout << t.toString() << endl;
      
    }
  }
    return 1;

}

