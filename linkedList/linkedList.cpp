#include <iostream>
using namespace std;

struct Node {
  int data;
  struct Node *next;
};

void insertBeg(struct Node **h, int newData) {
  struct Node *tmp = new Node;
  tmp -> data = newData;
  tmp -> next = (*h);
  (*h) = tmp;
}


void modValor(int *pti) {
  (*pti)++;
}


void printList(struct Node * ch) {
  while(ch != NULL) {
    cout << ch -> data << "   ";
    ch = ch -> next;
  }
}

int main() {
  struct Node *head = NULL;
  insertBeg(&head, 5);
  printList(head);

  int a = 5;
  modValor(&a);
  cout << a << endl;

  return 0;
}
