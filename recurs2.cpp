#include <iostream>
#include <string>
using namespace std;

//1. compare strings
bool compara(string s1, string s2) {
  if(s1.size() != s2.size()) return false;
  if(s1 == "" && s2 == "") return true;
  else if (s1[0] == s2[0])
    return compara(s1.substr(1, s1.size()-1), s2.substr(1, s2.size()-1));
  return false;
}

//2. cuántas veces hay un char en un string
int veces(char c, string s) {
  if(s == "")
    return 0;
  if(s[0] == c)
    return 1 + veces(c, s.substr(1, s.size()-1));
  else return 0 + veces(c, s.substr(1, s.size()-1));
}


//3. valor mínimo de elementos de un array
int menor(int a, int b) {
  if(a < b) return a;
  else return b;
}

int myarr(int arr[], int idInf, int idSup) {
  if(idInf == idSup)
    return arr[idInf];
  return menor(arr[idInf], myarr(arr, idInf + 1, idSup));
}


//4. suma de serie
int suma(int a, int b) {
  return a + b;
}

int sumaR(int arr[], int inf, int sup) {
  if(inf == sup) return arr[inf];
  else return suma(arr[inf], sumaR(arr, inf +1, sup));
}


//5. invertir orden de array
void reverse(int list[], int inf, int sup) {
  int x = list[sup];
  int y = list[inf];
  if(x == y) list[sup] = x;
  else {
    list[sup] = y;
    list[inf] = x;
    reverse(list, inf+1, sup-1);
  }
}


//6. invertir strings
string backString(string b) {
  if(b.size() == 0) return "";
  return b[b.size()-1] + backString(b.substr(0,b.size()-1));
}

//7. invertir integer


//8. sum of digits of integer
int sumDigit(int num) {
  int mod;
  if(num == 0) return 0;
  else {
    mod = num%10;
    num /= 10;
    return suma(mod, sumDigit(num));
  }
}

//9. conversión decimal a binario


//10. palíndromo y/n
bool palind(string p, int inf, int sup) {
  if(inf == sup) return true;
  else if (p[inf] == p[sup]){
    inf++;
    sup--;
    return palind(p, inf, sup);
  }
  return false;
}


int main() {
  cout << "comparaTrue: " << compara("hola", "hola") << endl;
  cout << "comparaFalse: " << compara("hola", "pato") << endl;

  cout << "veces: " << veces('a', "Manzana") << endl;

  int array[4] = {1,2,3,4};
  cout << "sumaR: " << sumaR(array, 0, 3) << endl;

  int arrR[5] = {1,2,3,4,5};
  reverse(arrR, 0, 4);
  cout << "reverse: ";
  for(int i = 0; i < 5; i++) {
    cout << arrR[i] << " ";
  }
  cout << endl;

  cout << "backString: " << backString("hello") << endl;

  cout << "sumDigit: " << sumDigit(471) << endl;

  cout << "palindT: " << palind("civic", 0, 4) << endl;
  cout << "palindF: " << palind("perro", 0, 4) << endl;

  return 0;
}
