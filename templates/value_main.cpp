#include <iostream>
#include "Value.h"
using namespace std;

int main() {
  Value<int> myValue_i(34);
  cout << myValue_i.getValue() << endl;

  Value<string> myValue_s("Hola");
  cout << myValue_s.getValue() << endl;

  return 0;
}
