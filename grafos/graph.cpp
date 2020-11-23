//TC1031.2
//Act 4.1 - Grafo: sus representaciones y sus recorridos
//Daniela Hernández y Hernández   A01730397
//David Eduardo Santiago Sánchez  A01733753
//Descripción: Conversión de una matriz de adyacencias a lista de
//adyacencias. Recorridos BFS y DFS en grafos a partir de la lista o matriz.
//15/11/2020

#include <iostream>
#include <vector>
using namespace std;

//Estructura de los nodos adyacentes para la lista
struct Adjacency{
  string data;
  Adjacency* nextAdjacency;
};

//Estructura de los nodos 'vértice' del grafo
struct Principal{
  string data;
  bool status;
  Principal* nextPrincipal;
  Adjacency* adjacencyHead;
};

//Complejidad O(n)
void insertaAdyacencia(Adjacency* &head, string adyacencia){
  Adjacency* new_adjacency = new Adjacency();
  Adjacency* last = head;
  new_adjacency -> data = adyacencia;
  new_adjacency -> nextAdjacency = NULL;

  if(head == NULL){
    head = new_adjacency;
  } else {
    while(last -> nextAdjacency != NULL){
      last = last -> nextAdjacency;
    }
    last -> nextAdjacency = new_adjacency;
  }
}

//Complejidad O(n)
void insertaPrincipal(Principal* &head, string principal, vector<int> adyacencias, vector<string> principales){
  Principal* new_principal = new Principal();
  Principal* last = head;
  new_principal -> data = principal;
  new_principal -> nextPrincipal = NULL;
  new_principal -> adjacencyHead = NULL;
  new_principal -> status = false;
  for(int i = 0; i < adyacencias.size(); i++){
    if(adyacencias[i] == 1) {
      insertaAdyacencia(new_principal -> adjacencyHead, principales[i]);
    }
  }
  if(head == NULL){
    head = new_principal;
  }else{
    while(last -> nextPrincipal != NULL){
      last = last -> nextPrincipal;
    }
    last -> nextPrincipal = new_principal;
  }
}

//Complejidad O(n^2)
void imprimeMatriz(vector<vector<int>> matriz){
  for(int i = 0; i < matriz.size(); i++){
    for(int j = 0; j < matriz[i].size(); j++){
      cout << matriz[i][j] << " ";
    }
    cout << endl;
  }
}

//Complejidad O(n)
void imprimeAdyacencias(Adjacency* adj){
  while(adj != NULL){
    cout << " - " << adj -> data;
    adj = adj -> nextAdjacency;
  }
}

//Complejidad O(n)
void imprimeLista(Principal* pri){
  while(pri != NULL){
    cout << pri -> data;
    imprimeAdyacencias(pri -> adjacencyHead);
    cout << endl;
    pri = pri -> nextPrincipal;
  }
}

//Complejidad O(1)
string convertNum(int n) {
  //Recibe un índice para regresar la letra correspondiente
  vector<string> letras = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
  if(n > 25) {
    //si el índice es mayor al número de letras en el abecedario
    //se regresa un par de letras. Ej: "AA"
    return letras[n/26-1] + letras[n-26];
  } else {
    return letras[n];
  }
}

//Complejidad O(n^2)
void DFS(vector<vector<int>> matriz, int nodoIn){
  //Deapth First Traversal
  if(matriz.size()) {
    cout << convertNum(nodoIn) << " ";
    vector<int> stack;
    int actual = 0;

    //marca como visitados los nodos de la columna inicial
    for(int i = 0; i < matriz.size(); i++) matriz[i][0] = 0;

    //inserta las adyacencias del nodo inicial al stack
    for(int i = matriz.size()-1; i >= 0; i--) {
      if(matriz[actual][i] == 1) stack.push_back(i);
    }

    bool signal;
    int reference, num;

    while(stack.size()) {
      //mientras haya elementos en la pila...
      signal = false;
      //establece nodo actual como el de hasta arriba en la pila
      actual = stack[stack.size()-1];
      reference = 0;
      while(!signal && reference < matriz.size()) {
        if(matriz[reference][actual] == 1) {
          //activa la bandera si se encuentra una adyacencia para salir del ciclo
          signal = true;
        }
        reference++;
      }

      num = stack[stack.size()-1]; //obtiene el elemento de hasta arriba en la pila
      stack.erase(stack.end()-1); // hace pop del stack

      if(signal) {
        cout << convertNum(num) << " "; //imprime la letra del nodo correspondiente
        for(int i = 0; i < matriz.size(); i++) {
          //marca los nodos como visitados
          matriz[i][actual] = 0;
        }
        for(int i = matriz.size()-1; i >= 0; i--) {
          //vuelve a insertar las adyacencias del noto actual a la pila
          if(matriz[num][i] == 1) stack.push_back(i);
        }
      }
    }
  }
}

//Complejidad O(n)
bool checkVisit(vector<string> v, string data) {
  //revisa si el nodo ya fue visitado
  for(int i = 0; i < v.size(); i++) {
    if(v[i] == data) return true;
  }
  return false;
}

//Complejidad O(n^2)
void BFS(Principal* pri, int nodoIn){
  //Breadth First Traversal
  Principal* start = pri;

  if(start != NULL) {
    vector<string> queue;
    queue.push_back(convertNum(nodoIn));
    vector<string> visited;

    while(queue.size()) {
      //mientras haya elementos en la cola...
      if(!(start -> status)) {
        //si el nodo actual no ha sido visitado
        cout << queue[0] << " "; //imprime el primer elemento de la cola
        start -> status = true; //marca ese nodo como visitado
        visited.push_back(start -> data); // y lo inserta a la cola
        if(start -> adjacencyHead != NULL) {
          //si el nodo tiene adyacencias
          Adjacency* neighbour = start -> adjacencyHead;
          while(neighbour != NULL) {
            //agrega todas las que no hayan sido visitadas a la cola
            bool vis = checkVisit(visited, neighbour -> data);
            if(!vis) queue.push_back(neighbour -> data);
            neighbour = neighbour -> nextAdjacency;
          }
        }
      }

      queue.erase(queue.begin()); //hace pop de la cola
      start = pri; //regresa el puntero al inicio de la lista
      while(start -> data != queue[0]) {
        //encuentra el nodo que sigue en la cola
        start = start -> nextPrincipal;
      }
    }
  }
}


int main() {
  vector<string> principalList; //guarda encabezados
  vector<vector<int>> adjacencyLists; //guarda adyacencias

  int lines, adj;
  string label;
  int cont = 0;
  cin >> lines;

  for(int i = 0; i < lines; i++) {
    label = convertNum(cont); //convierte los ints en nodos con letras
    principalList.push_back(label);
    cont++;
    vector<int> s;
    for(int j = 0; j < lines; j++) {
      cin >> adj;
      s.push_back(adj);
    }
    adjacencyLists.push_back(s); //crea la matriz de adyacencias
  }

  imprimeMatriz(adjacencyLists);
  cout << endl;

  //Crea lista de adyacencias
  Principal* headPrincipal = NULL;
  for(int i = 0; i < principalList.size(); i++) {
    insertaPrincipal(headPrincipal, principalList[i], adjacencyLists[i], principalList);
  }

  imprimeLista(headPrincipal);
  cout << endl;
  BFS(headPrincipal, 0);
  cout << endl << endl;
  DFS(adjacencyLists, 0);
  cout << endl;

  return 0;
}
