#include <iostream>
#include <string>
using namespace std;

//Estructuras de datos
struct Auto {
  string placa;
  string marca;
  string modelo;
  int anio;

  void imprimeAuto(){
    cout<<placa<<" "<<marca<<" "<<modelo<<" "<<anio<<endl;
  }
};

struct Casilla{
  char status = 'v';
  Auto* dato;
};

bool isInArray(string p, Casilla hashTable[]){
  for(int i = 0; i < 97; i++){
    if(hashTable[i].dato != NULL) {
      if(hashTable[i].dato -> placa == p) {
        return true;
      }
    }
  }
  return false;
}

int hashFunction(string p) {
  int index = 0;
  for(int i = 0; i < p.size(); i++) {
    index += p[i];
  }
  index %= 97;
  return index;
}

void ins(Auto *new_auto, Casilla hashTable[]) {
  string plac = new_auto -> placa;
  int hash = hashFunction(plac);
  if(hashTable[hash].status == 'v' || hashTable[hash].status == 'b') {
    hashTable[hash].dato = new_auto;
    hashTable[hash].status = 'o';
  } else {
    bool insertado = false;
    bool vacio;
    int index = hash + 1;
    while(insertado != true && index != hash) {
      if(hashTable[index].status == 'v' || hashTable[index].status == 'b') {
        hashTable[index].dato = new_auto;
        hashTable[hash].status = 'o';
        insertado = true;
      }
      if(index + 1 > 96) index = 0;
      else index++;
    }

    if(!insertado) {
      cout << "tabla llena, imposible insertar" << endl;
    }
  }
}

void del(string placaElim, Casilla hashTable[]) {
  int hash = hashFunction(placaElim);
  if(hashTable[hash].dato->placa==placaElim) {
    hashTable[hash].dato = NULL;
    hashTable[hash].status = 'b';
  } else {
    int index=hash;
    char casAct;
    do{
      index++;
      if(index>96) index=0;
      casAct=hashTable[index].status;
      if(casAct!='v' && casAct!='b'){
        if(hashTable[index].dato->placa==placaElim){
          hashTable[hash].dato = NULL;
          hashTable[hash].status = 'b';
        }
      }
    } while(casAct!='v' && index!=hash);
  }
}

Auto* search(string key, Casilla hashTable[]) {
  int hash = hashFunction(key);
  if(hashTable[hash].dato->placa==key){
    return hashTable[hash].dato;
  }else{
    int index=hash;
    char casAct;
    do{
      index++;
      if(index>96) index=0;
      casAct=hashTable[index].status;
      if(casAct!='v' && casAct!='b'){
        if(hashTable[index].dato->placa==key){
          return hashTable[index].dato;
        }
      }
    } while(casAct!='v' && index!=hash);
  }
  return NULL;
}

void print(Casilla hashTable[]){
  for(int i=0;i<97;i++){
    cout<<i<<" ";
    if(hashTable[i].dato!=NULL){
      hashTable[i].dato->imprimeAuto();
    }else{
      cout<<endl;
    }
  }
}


int main() {
  Casilla hashTable[97] = {};
  int option;
  cin >> option;
  while(option != 0) {
    if(option == 1) {
      string placa, marca, modelo, temp, limpia;
      int anio;
      cin>>placa;
      cin.ignore();
      getline(cin, marca);
      getline(cin, modelo);
      getline(cin, temp);
      anio = stoi(temp);

      Auto* new_auto = new Auto;
      new_auto -> placa = placa;
      new_auto -> marca = marca;
      new_auto -> modelo = modelo;
      new_auto -> anio = anio;

      bool result = isInArray(placa, hashTable);
      if(result){
        cout << "imposible insertar, placa duplicada" << endl;
      } else {
        ins(new_auto, hashTable);
      }

    } else if(option == 2) { //eliminar
      string placaElim;
      cin>>placaElim;
      del(placaElim, hashTable);
    } else if(option == 3) { //imprimir tabla
      print(hashTable);
    } else if(option == 4) { //buscar
      string placaBusq;
      cin>>placaBusq;
      Auto* result=search(placaBusq, hashTable);
      if(result==NULL){
        cout<<"dato no encontrado"<<endl;
      }else{
        result->imprimeAuto();
      }
    }
    cin >> option;
  }

  return 0;
}
