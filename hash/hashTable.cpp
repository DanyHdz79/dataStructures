#include <iostream>
using namespace std;

struct Auto {
  string placa;
  string marca;
  string modelo;
  int anio;
  Auto *next;
};

int hashFunction(string p) {
  int index = 0;
  for(int i = 0; i < p.size(); i++) {
    index += p[i];
  }
  index %= 97;
  return index;
}

void insert(Auto* hT[], Auto* &a) {
  int index = hashFunction(a -> placa);
  if(hT[index] == NULL) {
    hT[index] = a;
  } else {
    Auto* aux = hT[index];
    while(aux -> next != NULL) {
      aux = aux -> next;
    }
    aux -> next = a;
  }
}

void deleteA(Auto* hT[], string key) {

}

Auto* search(Auto* hT[], string key) {
  int index = hashFunction(key);
  Auto* tmp = hT[index];
  while(tmp -> placa != key) {
     tmp = tmp -> next;
     if(tmp == NULL) return NULL;
  }
  return tmp;
}

void imprimeAuto(Auto* a) {
  cout << a -> placa << " ";
  cout << a -> marca << " ";
  cout << a -> modelo << " ";
  cout << a -> anio << endl;
}

void print(Auto* hT[]) {

}

int main() {
  Auto* hashTable[97] = {NULL};
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

      Auto* new_auto = new Auto;
      new_auto -> placa = placa;
      new_auto -> marca = marca;
      new_auto -> modelo = modelo;
      new_auto -> anio = anio;
      new_auto -> next = NULL;

      insert(hashTable, new_auto);

    } else if(option == 2) { //eliminar

    } else if(option == 3) { //imprimir tabla

    } else if(option == 4) { //buscar
      string target;
      cin >> target;
      Auto* s = search(hashTable, target);
      if(s != NULL) imprimeAuto(s);
      else cout << "NULL" << endl;
    }
    cin >> option;
  }
  return 0;
}
