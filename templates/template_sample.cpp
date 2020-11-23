#include <iostream>
#include <string>
using namespace std;

template <typename T>
T Max(T a, T b) {
  return a < b ? b : a;
}

template <typename T1, typename T2>
T2 Suma(T1 a, T2 b) {
  return a + b;
}

int main() {
  int i = 39, j = 20;
  cout << "Max(i, j): " << Max(i, j) << endl;

  string s1 = "Hello", s2 = "World!";
  cout << "Max(s1, s2): " << Max(s1, s2) << endl;

  cout << Suma(2, 3.4) << endl;

  return 0;
}
