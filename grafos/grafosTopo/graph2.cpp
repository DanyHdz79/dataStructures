//TC1031.2
//Act 4.2 - Grafos: Algoritmos complementarios
//Daniela Hernández y Hernández   A01730397
//David Eduardo Santiago Sánchez  A01733753
//Descripción: Crea un DAG, evalúa si es un árbol y realiza el orden topológico
//18/11/2020

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
  int parents;
};

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
void insertaPrincipal(Principal* &head, string principal, vector<string> adjacency, int parents){
  Principal* new_principal = new Principal();
  Principal* last = head;
  new_principal -> data = principal;
  new_principal -> nextPrincipal = NULL;
  new_principal -> adjacencyHead = NULL;
  new_principal -> status = false;
  new_principal -> parents = parents;

  for(int i = 0; i < adjacency.size(); i++){
    insertaAdyacencia(new_principal -> adjacencyHead, adjacency[i]);
  }

  if(head == NULL){
    head = new_principal;
  } else {
    while(last -> nextPrincipal != NULL){
      last = last -> nextPrincipal;
    }
    last -> nextPrincipal = new_principal;
  }
}

//Complejidad O(n)
vector<string> getAdjacency(string prinAct, vector<vector<string>> adjacencyLists, int m){
  //Buscar en la lista de adyacencias, pares de valores en los que el nodo dado sea padre (lado izquierdo), es decir,
  //recopilar los hijos de ese nodo en un vector
  vector<string> adj;
  for(int i = 0; i < m; i++){
      if(adjacencyLists[i][0] == prinAct) adj.push_back(adjacencyLists[i][1]);
    }
    return adj;
}

//Complejidad O(n)
int getParents(string prinAct, vector<vector<string>> adjacencyLists){
  //Buscar en la lista de adyacencias, pares de valores en los que el nodo dado sea hijo (lado derecho)
  int cont = 0;
  for(int i = 0; i < adjacencyLists.size(); i++){
    if(adjacencyLists[i][1] == prinAct) cont++;
  }
  return cont;
}

//Complejidad O(n)
void loadGraph(int n, int m, vector<vector<string>> adjacencyLists, Principal* &head){
  //Construir el grafo
  vector<string> principalList; //guarda encabezados
  string label;
  //Crear vector de principales basado en número de nodos
  for(int i = 0; i < n; i++){
    label = convertNum(i);
    principalList.push_back(label);
  }

  //Obetener las adyacencias de cada nodo, su número de padres e insertar el nodo en la lista
  for(int i = 0; i < n; i++){
    vector<string> adj = getAdjacency(principalList[i], adjacencyLists, m);
    int parents = getParents(principalList[i], adjacencyLists);
    insertaPrincipal(head, principalList[i], adj, parents);
  }
}

//Complejidad O(n)
bool isTree(Principal* pri, int n, int m){
  //Verificar si es árbol, deja de ser árbol si existe más de un nodo sin padres y si algún
  //nodo tiene más de un padre
  int sinPadres = 0;
  for(int i = 0; i < n; i++){
    if(pri -> parents == 0) sinPadres++;
    if(sinPadres > 1) return false;
    else if(pri -> parents > 1) return false;
    pri = pri -> nextPrincipal;
  }
  return true;
}

//Complejidad O(n^2)
vector<string> checkNoParents(Principal* pri, vector<string> queue){
  //Obtener los nodos que no han sido visitados, que no tengan padres y que no estén dentro
  //de la cola dada
  vector<string> sinPadres;
  //Recorrer la lista de principales
  while(pri != NULL){
    int nParents = pri -> parents;
    bool nStatus = pri -> status;
    bool isInQueue = false;
    for(int i = 0; i < queue.size(); i++){
      if(queue[i] == pri -> data) {
        isInQueue = true;
        break;
      }
    }
    if(nParents == 0 && nStatus == false && isInQueue == false) sinPadres.push_back(pri->data);
    pri = pri -> nextPrincipal;
  }
  return sinPadres;
}

//Complejidad O(n)
vector<string> getAdyacencias(Adjacency* adj){
  //Obtener las adyacencias de un nodo principal en forma de vector
  vector<string> ady;
  while(adj != NULL){
    ady.push_back(adj -> data);
    adj = adj -> nextAdjacency;
  }
  return ady;
}

//Complejidad O(n^2)
void checkVisit(Principal* &pri, string node){
  //Modificar el estatus del nodo visitado y disminuir en uno todos los nodos de
  //los cuales era padre
  Principal* start = pri;
  vector<string> ady;
  while(pri != NULL){
    if(pri -> data == node){
      pri -> status = true;
      ady = getAdyacencias(pri -> adjacencyHead);
    }
    pri = pri -> nextPrincipal;
  }
  pri = start; //Reiniciar pri
  while(pri != NULL){
    for(int i = 0; i < ady.size(); i++){
      if(pri -> data == ady[i]){
        pri -> parents--;
      }
    }
    pri = pri -> nextPrincipal;
  }
}

//Complejidad O(n)
void topologicalSort(Principal* pri, int n, int m){
  Principal* start = pri;
  if(start != NULL){
    vector<string> queue;
    vector<string> temp = checkNoParents(pri, queue); //Vector con los nodos sin padres
    queue.insert(queue.end(), temp.begin(), temp.end()); //Insertar al final de la cola el vector temp
    while(queue.size()){ //Mientras la cola no esté vacía
      pri = start; //Reiniciar pri
      cout << queue[0] <<" ";
      checkVisit(pri, queue[0]);
      queue.erase(queue.begin());
      pri = start; //Reiniciar pri
      temp = checkNoParents(pri, queue);
      queue.insert(queue.end(), temp.begin(), temp.end());
    }
    cout << endl;
  }
}


int main() {
  vector<vector<string>> adjacencyLists; //Guarda adyacencias
  Principal* headPrincipal = NULL;
  int nodes, adj;
  string label;
  cin >> nodes;
  cin >> adj;

  //Crear matriz de adyacencias
  for(int i = 0; i < adj; i++) {
    vector<string> s;
    for(int j = 0; j < 2; j++){
      cin >> label;
      s.push_back(label);
    }
    adjacencyLists.push_back(s);
  }

  loadGraph(nodes, adj, adjacencyLists, headPrincipal);

  bool tree = isTree(headPrincipal, nodes, adj);
  cout << (tree ? "true" : "false") << endl;
  topologicalSort(headPrincipal, nodes, adj);

  return 0;
}
