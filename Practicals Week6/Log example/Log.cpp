// To compile use:
// g++ -std=c++0x Log.cpp -o Log

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

constexpr int INITIALCAP = 5;

class Log {
  
public :
  Log();
  Log(Log & other);
  Log(Log && other);
  ~Log();
  void addString(string s);
  void printAll();
  void copy(Log & other);
  Log& operator=(Log & other);
  Log& operator=(Log && other);
  
private :
  string* mes_;
  int number_; // number of stored messages
  int cap_; // capacity of the array
};


Log::Log() : mes{nullptr}, number_{0}, cap_{INITIALCAP} {
  mes_ = new string[cap_];
}


Log::Log(Log & other) {
  copy(other);
}

Log::Log(Log && other) : mes_{other.mes_}, number_{other.number_}, cap_{other.cap_} {
  other.mes_ = nullptr;
  other.number_ = 0;
  other.cap_ = 0;
}

void Log::copy(Log &other) {
  cap_= other.cap_;
  number_=other.number_;
  mes_= new string[cap_];
  for (int i=0; i<number_; i++) {
    mes_[i]= other.mes_[i];
  }
}

Log::~Log() {
  if (mes_) {
    delete [] mes_;
  }
}

Log& Log::operator=(Log& other) {
  if (this != &other) {
    if (mes_)
       delete[] mes_;
    copy(other);
  }
  return *this;
}

Log& Log::operator=(Log&& other) {
  if (this != &other) {
    string* temps{mes_};
    mes_ = other.mes_;
    other.mes_ = temps;

    int tempn{number_};
    number_ = other.number_;
    other.number_ = tempn;

    int tempc{cap_};
    cap_ = other.cap_;
    other.cap_ = tempc;
  }
  return *this;
}

void Log::addString(string s) {
  if (number_==cap_) {
    cap_=cap_*2;
    string* temp = new string[cap_];
    for (int i = 0; i < number_;  i++) {
      temp[i]=mes_[i];
    }
    delete [] mes_;
    mes_=temp;
  }
  mes_[number_] = s;
  number_++;
}


void Log::printAll() {
  for (int i=0; i<number_; i++) {
    cout << mes_[i] << endl;
    //cout << "a" << endl;
  }
  cout << "we have "<< number_ << " messages stored. The array size is "<< cap_<<endl;
}




int main() {

  Log l;
  l.addString("hello");
  l.addString("hello2");
  l.printAll();
  l.addString("hello3");
  l.addString("hello4");
  l.addString("hello5");
  l.addString("hello6");
  l.addString("hello7");
  l.addString("hello8");

  l.printAll();

  Log l2;
  l2=l;

  l2.addString("something to L2");
  l.addString("something to L1");

  l.printAll();
  l2.printAll();
 
  return 0;
}
