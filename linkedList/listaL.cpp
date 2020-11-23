// TC1031.2
// Act 2.1 - Implementación de un ADT de estructura de datos lineales (Listas Ligadas)
// Daniela Hernández y Hernández   A01730397
// 7/10/2020

#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *next;
};

//Complejidad O(1)
void Inserta_al_inicio(Node* &h, int newData) {
  Node *tmp = new Node;
  tmp -> data = newData;
  tmp -> next = h;
  h = tmp;
}

//Complejidad O(n)
void Inserta_al_final(Node* &h, int newData) {
  Node *tmp = new Node;
  tmp -> data = newData;
  Node *aux1 = h;
  Node *aux2;

  while(aux1 != NULL) {
    aux2 = aux1;
    aux1 = aux1 -> next;
  }

  if(h == aux1) h = tmp;
  else aux2 -> next = tmp;
  tmp -> next = aux1;
}

//Complejidad O(1)
void Elimina_al_inicio(Node* &h) {
  Node* tmp = h;
  if(tmp == NULL) {
    cout << "ERROR" << endl;
  } else {
    h = tmp -> next;
    delete(tmp);
  }
}

//Complejidad O(n)
void Elimina_al_final(Node* &h) {
  if(h == NULL) {
    cout << "ERROR" << endl;
  } else {
    Node *aux_borrar = h;
    Node *aux;

    while(aux_borrar -> next != NULL) {
      aux = aux_borrar;
      aux_borrar = aux_borrar -> next;
    }

    if(aux_borrar == h) {
      delete aux_borrar;
      h = NULL;
    } else {
      aux -> next = aux_borrar -> next;
      delete aux_borrar;
    }
  }
}

//Complejidad O(n)
void Imprime(Node * nd) {
  while(nd != NULL) {
    cout << nd -> data << endl;
    nd = nd -> next;
  }
}

int main() {
  Node *head = NULL;
  int num, dt;
  while(num != 0) {
    cin >> num;
    if(num == 1) {
      cin >> dt;
      Inserta_al_inicio(head, dt);
    } else if(num == 2) {
      cin >> dt;
      Inserta_al_final(head, dt);
    } else if(num == 3) Elimina_al_inicio(head);
    else if(num == 4) Elimina_al_final(head);
    else if(num == 5) Imprime(head);
  }
  return 0;
}
