#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Estructuras de datos
struct Auto {
  string placa;
  string marca;
  string modelo;
  int anio;
};

struct Casilla{
  char status='v';
  Auto* dato;
};

bool isInArray(string p, Casilla hashTable[]){
  for(int i=0;i<97;i++){
    if(hashTable[i].dato!=NULL){
      if(hashTable[i].dato->placa==p){
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

void ins(Auto *new_auto, Casilla hashTable[]){
  string plac = new_auto->placa;
  int hash=hashFunction(plac);
  if(hashTable[hash].status=='v'){
    hashTable[hash].dato=new_auto;
  }else{
    bool insertado=false;
    bool vacio;
    int index=hash+1;
    while(insertado!=true && index!=hash){
      if(hashTable[index].status=='v'){
        hashTable[index].dato=new_auto;
        insertado=true;
      }
      if(index+1>96){
        index=0;
      }else{
        index++;
      }
    }
    if(insertado=false){
      cout<<"tabla llena, imposible insertar"<<endl;
    }
  }
}

void del(Auto new_auto, Casilla *hashTable[]){

}

Auto search(string key, Casilla hashTable[]){

}

void print(Casilla hashTable[]){

}


int main() {
  Casilla hashTable[97]={};
  int option;
  while(option!=0){
    cin>>option;
    if(option==1){
      string placa, marca, modelo, temp;
      int anio;
      getline(cin,placa);
      getline(cin,marca);
      getline(cin,modelo);
      getline(cin,temp);
      anio=stoi(temp);
      Auto* new_auto = new Auto;
      new_auto -> placa = placa;
      new_auto -> marca = marca;
      new_auto -> modelo = modelo;
      new_auto -> anio = anio;

      bool result=isInArray(placa,hashTable);
      if(result==true){
        cout<<"imposible insertar, placa duplicada"<<endl;
      }else{
        ins(new_auto, hashTable);
      }
    }
  }

  return 0;
}

