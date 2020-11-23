//TC1031.2
//Act 3.1 - Operaciones avanzadas en un BST
//Daniela Hernández y Hernández   A01730397
//David Eduardo Santiago Sánchez  A01733753
//Descripción: Creación de un árbol binario de búsqueda, con operaciones
//para insertar y eliminar nodos, calcular su altura, ubicar el nivel un
//de un nodo e imprimir sus ancestros.
//17/10/2020

#include <iostream>
#include <vector>
using namespace std;

struct Node {
   int data;
   Node *left;
   Node *right;
};

//Complejidad O(1)
Node* creaNodo(int num){
  //Crear nuevo nodo
  Node* new_leaf = new Node();
  new_leaf -> data = num;
  new_leaf -> left = NULL;
  new_leaf -> right = NULL;
  return new_leaf;
}

//Complejidad O(n)
void insertaArbol(Node* &root, int num){
  Node* temp = root;
  Node* prev;
  Node* new_leaf=creaNodo(num);
  bool direction;
  if(root == NULL){
    root = new_leaf;
  } else {
    while(temp != NULL){
      prev = temp;
      if(num < temp -> data){
        temp = temp -> left;
        direction = 0;
      } else if(num > temp -> data){
        temp = temp -> right;
        direction = 1;
      }
    }
    if(direction==0){
      prev->left=new_leaf;
    }else if(direction==1){
      prev->right=new_leaf;
    }
  }
}

//Complejidad O(n)
void preorder(Node* r) {
  if(r != NULL) {
    cout << r -> data << " ";
    preorder(r -> left);
    preorder(r -> right);
  }
}

//Complejidad O(n)
void inorder(Node* r) {
  if(r != NULL) {
    inorder(r -> left);
    cout << r -> data << " ";
    inorder(r -> right);
  }
}

//Complejidad O(n)
void postorder(Node* r) {
  if(r != NULL) {
    postorder(r -> left);
    postorder(r -> right);
    cout << r -> data << " ";
  }
}

//Complejidad O(n)
void level(Node* r) {
  if(r != NULL){
    vector<Node*> cola;
    cola.push_back(r);

    while(cola.size() != 0){
      Node* temp = cola[0];
      cout << temp -> data <<" ";
      cola.erase(cola.begin());

      if(temp->left != NULL)
        cola.push_back(temp->left);

      if(temp->right !=NULL)
        cola.push_back(temp->right);
    }
  }
}

//Complejidad O(1)
void traversal(Node* r, int type) {
  if(type == 1) preorder(r);
  else if(type == 2) inorder(r);
  else if(type == 3) postorder(r);
  else if(type == 4) level(r);
}

//Complejidad O(n)
int findMinMay(Node* &root){
  Node* temp = root;
  Node* prev = temp;
  temp = temp -> right;
  while(temp != NULL){
    prev = temp;
    temp = temp -> left;
  }
  return prev -> data;
}

//Complejidad O(n)
void eliminaNodo(Node* &root, int num){
  //Buscar nodo
  Node* temp = root;
  Node* prev;
  bool direction;
  while(temp != NULL && temp -> data != num){
    prev = temp;
    if(num < temp -> data){
      temp = temp -> left;
      direction = 0;
    }else if(num > temp -> data){
      temp = temp -> right;
      direction = 1;
    }
  }
  //Borrar todo el árbol
  if(temp == root && temp->left== NULL && temp->right==NULL){
    root=NULL;
    delete temp;
  } else {
  if(temp != NULL) {
    //El nodo a borrar es una hoja
    if(temp -> left == NULL && temp -> right == NULL){
      if(direction == 0){
        prev -> left = NULL;
      }else if(direction == 1){
        prev -> right = NULL;
      }
      delete temp;
    }

    //El nodo a borrar tiene sólo una rama
    else if((temp -> left == NULL && temp -> right != NULL) || (temp -> left != NULL && temp -> right == NULL) ){
      if(direction == 0){//El nodo a borrar es izquierdo
        if(temp -> left != NULL){
          prev -> left = temp -> left; //El nodo a borrar tiene rama izquierda, conectar con previo
        } else if(temp -> right != NULL){
          prev -> left = temp -> right; //El nodo a borrar tiene rama derecha, conectar con previo
        }
        delete temp;
      } else if(direction == 1) { //El nodo a borrar es derecho
        if(temp -> left != NULL){
          prev -> right = temp -> left; //El nodo a borrar tiene rama izquierda, conectar con previo
        }else if(temp -> right != NULL){
          prev -> right = temp -> right; //El nodo a borrar tiene rama derecha, conectar con previo
        }
        delete temp;
      }
    }

    //El nodo a borrar tiene dos ramas
    else if(temp -> left != NULL && temp -> right != NULL){
      int minMay = findMinMay(temp);
      eliminaNodo(root, minMay);
      temp -> data = minMay;
    }
  }
 }
}

//Complejidad O(1)
int height(Node* root) {
  if(root == NULL) return 0;

  int lHeight = height(root -> left);
  int rHeight = height(root -> right);

  if (lHeight > rHeight)  return(1 + lHeight);
  else return(1 + rHeight);
  //Happy coding :D
}

//Complejidad O(n)
void ancestors(Node* root, int num) {
  Node* temp = root;
  bool direction;
  vector<int> ancestorsNum;
  while(temp != NULL && temp -> data != num){
    ancestorsNum.push_back(temp->data);
    if(num < temp -> data){
      temp = temp -> left;
      direction = 0;
    }else if(num > temp -> data){
      temp = temp -> right;
      direction = 1;
    }
  }
  if(temp != NULL) {
    if(temp -> data == num) {
      for(int i = 0; i < ancestorsNum.size(); i++){
        cout << ancestorsNum[i] << " ";
      }
    }
  } 
}

//Complejidad O(n)
int whatlevelamI(Node* root, int num) {
  if (root==NULL) return -1;
  if(root -> data == num) return 0;
  int level = 0;
  Node* temp = root;
  while(temp != NULL && temp -> data != num) {
    level++;
    if(num < temp -> data) {
      temp = temp -> left;
    } else if(num > temp -> data) {
      temp = temp -> right;
    }
  }
  if(temp == NULL) return -1;
  return level;
}

//Complejidad O(n)
void procesaEntradas(vector<int> &array, int numData){
  int new_Data;
  bool repeat;
  int index = 0;
  for(int i = 0; i < numData; i++){
    cin >> new_Data;
    repeat = false;
    while(index != array.size() && repeat != true){
      if(array.size() == 0){
        index = array.size()-1;
      } else {
        if(array[index] == new_Data) {
          repeat = true;
        }
        index++;
      }
    }
    if(array.size() == 0){
      array.push_back(new_Data);
    } else {
      if(repeat == false){
        array.push_back(new_Data);
      }
    }
    repeat = false;
    index = 0;
  }
}

//Complejidad O(n)
void creaArbol(vector<int> data, Node* &root){
    for(int i = 0; i < data.size(); i++){
      insertaArbol(root, data[i]);
    }
  }

//Complejidad O(n)
void destruyeNodos(vector<int> data, Node* &root){
  for(int i = 0; i < data.size(); i++){
    eliminaNodo(root, data[i]);
  }
}

//Complejidad O(n^2)
void muestraAncestros(vector<int> data, vector<int> tree, Node* &root){
  bool found = 0;
  for(int i = 0; i < data.size(); i++) {
    for(int j = 0; j < tree.size(); j++) {
      if(tree[j] == data[i]) {
        found = 1;
        break;
      }
    }

    if(found) {
    ancestors(root, data[i]);
    cout << endl;
    } else cout << endl;
    found = 0;
  }
}

//Complejidad O(n)
void obtenerNivel(vector<int> data, Node* &root){
  for(int i = 0; i < data.size(); i++) {
    cout << whatlevelamI(root, data[i]) << endl;
  }
}


int main() {
  //Declarar variables y vectores
  vector<int> input, elimina, ancestors, requestLevel;
  int numInsert, numElimina, numAncest, numLevel;
  Node* root = NULL;

  //Entradas ignorando datos repetidos
  cin >> numInsert;
  procesaEntradas(input, numInsert);
  creaArbol(input, root);

  //Eliminación de nodos
  cin >> numElimina;
  procesaEntradas(elimina, numElimina);
  destruyeNodos(elimina, root);
  //Recorridos
  traversal(root, 1);
  cout << endl;
  traversal(root, 2);
  cout << endl;
  traversal(root, 3);
  cout<<endl;
  traversal(root, 4);
  cout << endl;

  //Calcula altura del árbol
  cout << height(root) << endl;

  //Imprime los ancestros de los nodos dados
  cin >> numAncest;
  procesaEntradas(ancestors, numAncest);
  muestraAncestros(ancestors, input, root);
  //Imprime el nivel en que se encuentra el nodo dado
  cin >> numLevel;
  procesaEntradas(requestLevel, numLevel);
  obtenerNivel(requestLevel, root);

  return 0;
}
