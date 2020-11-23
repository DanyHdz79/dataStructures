//TC1031.2
//Act 3.1 - Operaciones avanzadas en un BST
//Daniela Hernández y Hernández   A01730397
//David Eduardo Santiago Sánchez  A01733753
//Descripción: Implementación de árboles heap en forma de arreglos.
//23/10/2020

#include <iostream>
#include <vector>
#include "Priority_queue.h"
using namespace std;

int main (){
  Priority_queue heap;
  int resp;
  int new_dato;
  int result;
  bool resultEmpty;

  do {
    cin >> resp;
    if(resp == 1) {
      bool found=0;
      cin >> new_dato;
      vector<int> temp=heap.getData();
      for(int i=0;i<temp.size();i++){
        if(temp[i]==new_dato){
          found=1;
          break;
        }
      }
      if(found==0){
        heap.push(new_dato);
      }
    } else if(resp == 2) {
      heap.pop();
    } else if(resp == 3) {
      heap.print();
      cout << endl;
    } else if(resp == 4) {
      result = heap.top();
      cout << result << endl;
    } else if(resp == 5) {
      resultEmpty = heap.empty();
      cout << (resultEmpty ? "true" : "false") << endl;
    } else if(resp == 6) {
      result = heap.size();
      cout << result << endl;
    }
  } while(resp != 0);
}
