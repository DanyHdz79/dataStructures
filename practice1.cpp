#include <iostream>
#include <string>
using namespace std;

const int max1 = 100;

template <typename T>
class Lista {
private:
  int size;
  T data[max1];

public:
  Lista() {
    this -> size = 0;
  }

  void insert(T newElement) {
    if(size < 100) {
      data[size] = newElement;
      size++;
    } else {
      cout << "No hay espacio en el arreglo." << endl;
    }
  }

  void erase() {
    if(size == 0) cout << "No hay elementos." << endl;
    else {
      cout << "Elemento a borrar: " << data[size] << endl;
      size--;
    }
  }

  T getData(int pos) {
    //0 <= pos < size
    if(0 <= pos && pos < size){
      return data[pos];
    } else {
      cout << "Posición inválida." << endl;
    }
  }

  int getSize() {
    return size;
  }

  void print() {
    // [pos] - dato
    for(int i = 0; i < size; i++) {
      cout << "[" << i << "] - " << data[i] << endl;
    }
  }
};

int main() {
  Lista <int> li;
  li.insert(4);
  li.insert(5);
  li.insert(6);
  cout << "li size: " << li.getSize() << endl;
  li.print();
  li.getData(8);
  cout << "Data in pos2: "<< li.getData(2) << endl;
  return 0;
}
