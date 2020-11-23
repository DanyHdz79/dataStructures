// TC1031.2
// Act 2.2 - Operaciones con listas ligadas
// Daniela Hernández y Hernández   A01730397
// 7/10/2020

#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *next;
};

//Complejidad O(n)
Node* reverse(Node* &h) {
  if (h == NULL || h -> next == NULL) return h;
  Node *end = reverse(h -> next);
  Node *tmp = h -> next;
  tmp -> next = h;
  h -> next = NULL;
  return end;
}

//Complejidad O(n)
bool equals(Node* &h, Node* &h2) {
  if(h == NULL && h2 == NULL) return true;
  if(h == NULL || h2 == NULL) return false;
  Node *aux1 = h;
  Node *aux2 = h2;
  while(aux1 != NULL) {
    if(aux1 -> data != aux2 -> data) return false;
    aux1 = aux1 -> next;
    aux2 = aux2 -> next;
    if((aux1 == NULL && aux2 != NULL) || (aux2 == NULL && aux1 != NULL))
      return false;
  }
  return true;
}

//Complejidad O(n)
void concat(Node* &h, Node* &h2) {
  if(h == NULL) {
    h = h2;
    return;
  }

  Node *aux1 = h;
  while(aux1 -> next != NULL) {
    aux1 = aux1 -> next;
  }
  aux1 -> next = h2;
}

//Complejidad O(n)
void inserta_al_final(Node* &h, int newData) {
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

//Complejidad O(n)
void imprime(Node * nd) {
  while(nd != NULL) {
    cout << nd -> data << endl;
    nd = nd -> next;
  }
}


int main() {
  Node *head1 = NULL;
  Node *head2 = NULL;
  int m, n, data;
  bool equal;

  cin >> m;
  for(int i = 0; i < m; i++) {
    cin >> data;
    inserta_al_final(head1, data);
  }

  cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> data;
    inserta_al_final(head2, data);
  }

  equal = equals(head1, head2);
  head1 = reverse(head1);
  head2 = reverse(head2);
  imprime(head1);
  imprime(head2);
  concat(head2, head1);
  imprime(head2);
  cout << (equal ? "true" : "false") << endl;
  return 0;
}
