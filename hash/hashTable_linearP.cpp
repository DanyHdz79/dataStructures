//TC1031.2
//Act 5.1 - Implementación de un prototipo de tabla hash simple
//Daniela Hernández y Hernández   A01730397
//David Eduardo Santiago Sánchez  A01733753
//Descripción: Crea una tabla hash y almacena información sobre autos.
//Se puede insertar un dato, eliminarlo, buscarlo o imprimir la tabla completa.
//El método para manejar las colisiones de hash es 'linear probing'.
//25/11/2020

#include <iostream>
#include <stdio.h>
using namespace std;

//Estructuras de datos
struct Auto {
  string placa;
  string marca;
  string modelo;
  int anio;

  void imprimeAuto() {
    cout << placa << " " << marca << " " << modelo << " " << anio << endl;
  }
};

struct Casilla{
  char status = 'v';
  Auto* dato = NULL;
};

//Complejidad O(n)
int hashFunction(string p) {
  int index = 0;
  for(int i = 0; i < p.size(); i++) {
    index += p[i];
  }
  index %= 97;
  return index;
}

//Complejidad O(1) [Amortizado] || worst case: O(n)
void ins(Auto *new_auto, Casilla hashTable[]) {
  string plac = new_auto -> placa;
  int hash = hashFunction(plac);
  if(hashTable[hash].status == 'v' || hashTable[hash].status == 'b') {
    hashTable[hash].dato = new_auto;
    hashTable[hash].status = 'o';
  } else {
    bool insertado = false;
    int index = hash + 1;
    while(insertado != true && index != hash) {
      if(hashTable[index].status == 'v' || hashTable[index].status == 'b') {
        hashTable[index].dato = new_auto;
        hashTable[index].status = 'o';
        insertado = true;
      }
      if(index + 1 > 96) index = 0;
      else index++;
    }

    if(!insertado) {
      cout << "tabla llena, imposible insertar" << endl << endl;
    }
  }
}

//Complejidad O(1) [Amortizado] || worst case: O(n)
void del(string placaElim, Casilla hashTable[]) {
  int hash = hashFunction(placaElim);
  if(hashTable[hash].dato == NULL && hashTable[hash].status == 'v') return;
  if(hashTable[hash].status != 'b' && hashTable[hash].dato -> placa == placaElim) {
    hashTable[hash].dato = NULL;
    hashTable[hash].status = 'b';
  } else {
    int index = hash;
    char casAct;
    do {
      index++;
      if(index > 96) index = 0;
      casAct = hashTable[index].status;
      if(casAct != 'v' && casAct != 'b'){
        if(hashTable[index].dato -> placa == placaElim) {
          hashTable[index].dato = NULL;
          hashTable[index].status = 'b';
        }
      }
    } while(casAct != 'v' && index != hash);
  }
}

//Complejidad O(1) [Amortizado] || worst case: O(n)
Auto* search(string key, Casilla hashTable[]) {
  int hash = hashFunction(key);
  if(hashTable[hash].dato == NULL && hashTable[hash].status == 'v') return NULL;
  if(hashTable[hash].status != 'b' && hashTable[hash].dato -> placa == key) {
    return hashTable[hash].dato;
  } else {
    int index = hash;
    char casAct;
    do {
      index++;
      if(index > 96) index = 0;
      casAct = hashTable[index].status;
      if(casAct != 'v' && casAct != 'b') {
        if(hashTable[index].dato -> placa == key) {
          return hashTable[index].dato;
        }
      }
    } while(casAct != 'v' && index != hash);
  }
  return NULL;
}

//Complejidad O(1)
void print(Casilla hashTable[]) {
  for(int i = 0; i < 97; i++) {
    cout << i << " ";
    if(hashTable[i].dato != NULL) {
      hashTable[i].dato -> imprimeAuto();
    } else {
      cout << endl;
    }
  }
}

int main() {
  Casilla hashTable[97] = {};
  int option;
  cin >> option;
  cin.ignore();
  while(option != 0) {
    if(option == 1) { //insertar
      string placa, marca, modelo, temp;
      int anio;
      getline(cin, placa);
      getline(cin, marca);
      getline(cin, modelo);
      getline(cin, temp);
      anio = atoi(temp.c_str());

      Auto* new_auto = new Auto;
      new_auto -> placa = placa;
      new_auto -> marca = marca;
      new_auto -> modelo = modelo;
      new_auto -> anio = anio;
      Auto* result = search(placa, hashTable);
      if(result != NULL) {
        cout << "imposible insertar, placa duplicada" << endl << endl;
      } else {
        ins(new_auto, hashTable);
      }

    } else if(option == 2) { //eliminar
      string placaElim;
      getline(cin, placaElim);
      del(placaElim, hashTable);

    } else if(option == 3) { //imprimir tabla
      print(hashTable);
      cout << endl;
    } else if(option == 4) { //buscar
      string placaBusq;
      getline(cin, placaBusq);
      Auto* result = search(placaBusq, hashTable);
      if(result == NULL) {
        cout << "dato no encontrado" << endl;
      } else {
        result -> imprimeAuto();
      }
      cout << endl;
    }
    cin >> option;
    cin.ignore();
  }
  return 0;
}
