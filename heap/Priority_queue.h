//Clase de heap
#ifndef PRIORITY_QUEUE_H_INCLUDED
#define PRIORITY_QUEUE_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;

class Priority_queue {
  private:
    vector<int> data;

  public:
    Priority_queue() {
      vector<int> data1;
      data = data1;
    };

    //Complejidad O(n)
    void heapify(vector<int> &array, int fatherIndex){
      if(fatherIndex >= 0) {

        //Asigna los índices para la 'raíz' y las 'hojas' del subárbol a ordenar
        int left = array[2*fatherIndex+1];
        int right = array[2*fatherIndex+2];
        int fatherAct = array[fatherIndex];

        //Se hace el intercambio dependiendo si el hijo derecho o izquierdo son mayores
        if(left > fatherAct && left > right) {
          int temp = fatherAct;
          array[fatherIndex] = array[2*fatherIndex+1];
          array[2*fatherIndex+1] = temp;
        } else if(right > fatherAct && right > left) {
          int temp = fatherAct;
          array[fatherIndex] = array[2*fatherIndex+2];
          array[2*fatherIndex+2] = temp;
        }
        //Función recursiva para ordenar todo el arreglo
        heapify(array, fatherIndex-1);
      }
    }

    //Complejidad O(n)
    void heapifyTopBottom(vector<int> &array, int fatherIndex){
      int aux = array.size()/2;
      if((fatherIndex%2==0 && fatherIndex <= aux-1) || (fatherIndex%2!=0 && fatherIndex <= aux)){
        //Asigna los índices para la 'raíz' y las 'hojas' del subárbol a ordenar
        int left = array[2*fatherIndex+1];
        int right = array[2*fatherIndex+2];
        bool flagLeft = 0;
        bool flagRight = 0;
        if(2*fatherIndex+1>array.size()){
          flagLeft = 1;
        }if(2*fatherIndex+2>array.size()){
          flagRight = 1;
        }
        int fatherAct = array[fatherIndex];
        //Se hace el intercambio dependiendo si el hijo derecho o izquierdo son mayores
        if(flagLeft==0 && left > fatherAct && left > right) {
          int temp = fatherAct;
          array[fatherIndex] = left;
          array[2*fatherIndex+1] = temp;
        } else if(flagRight==0 && right > fatherAct && right > left) {
          int temp = fatherAct;
          array[fatherIndex] = right;
          array[2*fatherIndex+2] = temp;
        }
        //Función recursiva para ordenar todo el arreglo
        heapifyTopBottom(array, fatherIndex+1);
      }
    }

    //Complejidad O(1)
    void push(int num) {
      if(data.size() == 0) {
        data.push_back(num);
      } else {
        data.push_back(num);
        int arg;
        //Obtiene el índice para hacer 'heapify'
        if(data.size()%2 == 0) {
          arg = data.size()/2 - 1;
        } else {
          arg = data.size()/2;
        }
        heapify(data, arg);
      }
    }

    //Complejidad O(1)
    void pop() {
      if(data.size() > 0) {
        cout << data[0] << endl;
        data[0] = data[data.size()-1];
        data.pop_back();
        //Obtiene el índice para hacer 'heapify'
        heapifyTopBottom(data,0);
      }
    }

    //Complejidad O(n)
    void print() {
      for(int i = 0; i < data.size(); i++) {
        cout << data[i] << " ";
      }
    }

    //Complejidad O(1)
    int top() {
      if(data.size() == 0) return -1;
      else return data[0];
    }

    //Complejidad O(1)
    bool empty() {
      if(data.size() == 0) return true;
      else return false;
    }

    //Complejidad O(1)
    int size(){
      return data.size();
    }

    //Complejidad O(1)
    vector<int> getData(){
      return data;
    }
};

#endif
