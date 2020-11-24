#include <iostream>
using namespace std;

struct Auto {
  string placa;
  string marca;
  string modelo;
  int anio;
};

int hashFunction(string p) {
  int index = 0;
  for(int i = 0; i < p.size(); i++) {
    index += p[i];
  }
  index %= 97;
  return index;
}

void insert(Auto hT[], Auto &a) {

}

void deleteA(Auto hT[], string key) {

}

Auto search(Auto hT[], string key) {
  int index = hashFunction(key);

}


void print(Auto hT[]) {

}

int main() {
  Auto hashTable[97] = {NULL};
  int option;
  cin >> option;
  while(option != 0) {
    if(option == 1) { //insertar
      string placa, marca, modelo;
      int anio;
      cin >> placa;
      cin >> marca;
      cin >> modelo;
      cin >> anio;


    } else if(option == 2) { //eliminar

    } else if(option == 3) { //imprimir tabla

    } else if(option == 4) { //buscar

    }
    cin >> option;
  }
  return 0;
}
