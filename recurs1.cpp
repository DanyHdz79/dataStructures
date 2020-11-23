#include <iostream>
using namespace std;

int factorial(int n) {
  if (n == 0) return 1; //caso base (a.k.a. condición de paro)
  else return n*factorial(n-1); //recursión: se llama a sí misma
}

int fibonacci(int n) {
  if(n <= 2) return 1;
  else return fibonacci(n-1) + fibonacci(n-2);
}

double bacteria(int d) {
  if(d <= 0) return 1;
  else return (3.78*bacteria(d-1))-(2.34*bacteria(d-1));
}

double inversion(double amount, int m) {
  if(m <= 0) return amount;
  else return amount*0.1875+(inversion(amount, m-1));
}

int potencia(int x, int y) {
  if(y <= 0) return 1;
  else return x*potencia(x, y-1);
}

int main() {
  cout << "factorial: " << factorial(3) << endl;
  cout << "fibonacci: " << fibonacci(6) << endl;
  cout << "bacteria: " << bacteria(4) << endl;
  cout << "inversion: " << inversion(100, 5) << endl;
  cout << "potencia: " << potencia(2, 3) << endl;
  return 0;
}
