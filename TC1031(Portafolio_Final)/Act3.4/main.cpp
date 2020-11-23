//TC1031.2
//Act 3.4 - Actividad Integral de BST (Evidencia Competencia)
//Daniela Hernández y Hernández   A01730397
//David Eduardo Santiago Sánchez  A01733753
//Franco Minutti Simoni           A01733927
//Descripción: Ordena una serie de registros de acuerdo a diferentes filtros,
//los ordena en un árbol de búsqueda binario (BST) y muestra en consola los
//5 registros de con las IP's más grandes.
//24/10/2020

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Registro.h"
using namespace std;


//Estructura de datos-----------------------------------------------------------------
struct Node {
    Registro data;
    Node* left; // Pointer to next node in DLL
    Node* right; // Pointer to previous node in DLL
};

//Crea el nodo con el nuevo registro
//Orden O(1)
Node* creaNodo(Registro &registro1) {
  //Crear nuevo nodo
  Node* new_leaf = new Node();
  new_leaf -> data = registro1;
  new_leaf -> left = NULL;
  new_leaf -> right = NULL;
  return new_leaf;
}

//Filtro de fechas: Si dato 1 es menor que dato2, regresa -1, si es igual regresa 0, si es mayor regresa 1
//Orden O(1)
int comparaFechas(Registro &dato1, Registro &dato2) {
  Date fecha1 = dato1.getDate();
  Date fecha2 = dato2.getDate();
  int m1, m2, d1, d2, h1, h2, min1, min2, s1, s2;
  m1 = fecha1.monthToNumber();
  d1 = fecha1.getDay();
  h1 = fecha1.getHour();
  min1 = fecha1.getMinute();
  s1 = fecha1.getSecond();
  m2 = fecha2.monthToNumber();
  d2 = fecha2.getDay();
  h2 = fecha2.getHour();
  min2 = fecha2.getMinute();
  s2 = fecha2.getSecond();
  if(m1<m2){ //Mes
    return -1;
  }else if(m1>m2){
    return 1;
  }else{
    if(d1<d2){ //Día
      return -1;
    }else if(d1>d2){
      return 1;
    }else{
      if(h1<h2){ //Hora
        return -1;
      }else if(h1>h2){
        return 1;
      }else{
        if(min1<min2){ //Minuto
          return -1;
        }else if(min1>min2){
          return 1;
        }else{
          if(s1<s2){ //Segundo
            return -1;
          }else if(s1>s2){
            return 1;
          }else{
            return 0;
          }
        }
      }
    }
  }
}

//Fitrlo de Ips: Si dato 1 es menor que dato2, regresa -1, si es igual regresa 0, si es mayor regresa 1
//Orden O(1)
int comparaIp(Registro &dato1, Registro &dato2) {
  DirIp ip1 = dato1.getIp();
  DirIp ip2 = dato2.getIp();
  int numOne1, numOne2, numTwo1, numTwo2, numThree1, numThree2, numFour1, numFour2, port1, port2;
  numOne1 = ip1.getNumOne();
  numTwo1 = ip1.getNumTwo();
  numThree1 = ip1.getNumThree();
  numFour1 = ip1.getNumFour();
  port1 = ip1.getPort();
  numOne2 = ip2.getNumOne();
  numTwo2 = ip2.getNumTwo();
  numThree2 = ip2.getNumThree();
  numFour2 = ip2.getNumFour();
  port2 = ip2.getPort();


  if(numOne1<numOne2){ //Primer numero
    return -1;
  }else if(numOne1>numOne2){
    return 1;
  }else{
    if(numTwo1<numTwo2){ //Segundo numero
      return -1;
    }else if(numTwo1>numTwo2){
      return 1;
    }else{
      if(numThree1<numThree2){ //Tercer numero
        return -1;
      }else if(numThree1>numThree2){
        return 1;
      }else{
        if(numFour1<numFour2){ //Cuarto numero
          return -1;
        }else if(numFour1>numFour2){
          return 1;
        }else{
          if(port1<port2){ //Puerto
           return -1;
         }else if(port1>port2){
           return 1;
         }else{
           return 0;
          }
        }
      }
    }
  }
}

//Filtro de mensajes: Si dato 1 es menor que dato2, regresa -1, si es igual regresa 0, si es mayor regresa 1
//Orden O(1)
int comparaMensajes(Registro &dato1, Registro &dato2) {
  string mensaje1 = dato1.getMessage();
  string mensaje2 = dato2.getMessage();

  if(mensaje1 > mensaje2){
    return -1;
  } else if(mensaje1 < mensaje2) {
    return 1;
  } else {
    return 0;
  }
}

//Compara registros con los tres filtros
//Orden O(1)
int comparaRegistros(Node *reg1, Node *reg2){
  if(reg1 == NULL) {
    return 1;
  } else {
    Registro dato1 = reg1 -> data;
    Registro dato2 = reg2 -> data;
    int resultIp = comparaIp(dato1, dato2);
    if(resultIp == 0) {
      int resultFecha = comparaFechas(dato1, dato2);
      if(resultFecha != 0){
        return resultFecha;
      } else {
        int resultMessage = comparaMensajes(dato1, dato2);
        return resultMessage;
      }
    }
    return resultIp;
  }
}

//Descompone la string de ips en sus elementos
//Orden O(n)
vector<int> procesaIP(string ipIn){
  vector<int> ipNum;
  string delimiter1 = ".";
  string delimiter2 = ":";
  int pos = 0;
  string token;

  vector<string> vector_ips;

  while ((pos = ipIn.find(delimiter1)) != string::npos) {
    token = ipIn.substr(0, pos);
    ipIn.erase(0, pos + delimiter1.length());
    vector_ips.push_back(token);
  }

  pos = 0;

  while ((pos = ipIn.find(delimiter2)) != string::npos) {
    token = ipIn.substr(0, pos);
    ipIn.erase(0, pos + delimiter2.length());
    vector_ips.push_back(token);
  }

  vector_ips.push_back(ipIn);

  for(int i = 0; i < vector_ips.size(); i++){
    int terminoIp = stoi(vector_ips[i]);
    ipNum.push_back(terminoIp);
  }
  return ipNum;
}

//Imprime los n registros con las IP's más grandes
//Orden O(n)
void printTree(Node* node, int n) {
    static int count = 0;
    if (node == NULL) return;
    if (count <= n) {
        printTree(node -> right, n);
        count++;
        if(count <= n) {
          Registro new_registro = node -> data;
          new_registro.printRegistro();
        }
        printTree(node -> left, n);
    }
}

//Inserta los nodos en su lugar correspondiente
//Orden O(n)
void insertaArbol(Node* &root, Node* registro){
  Node* temp = root;
  Node* prev;
  bool direction;
  if(root == NULL) {
    root = registro;
  } else {
    while(temp != NULL) {
      prev = temp;
      int result = comparaRegistros(registro,temp);
      if(result == -1) {
        temp = temp -> left;
        direction = 0;
      } else if(result == 1) {
        temp = temp -> right;
        direction = 1;
      } else return;
    }
    if(direction == 0) {
      prev -> left = registro;
    } else if(direction == 1) {
      prev -> right = registro;
    }
  }
}

//Checar si el archivo está vacío
//Orden O(1)
bool isEmpty(ifstream& pFile){
    return pFile.peek() == ifstream::traits_type::eof();
}

int main() {
  int index = 0, d, h, m, s, d1Input, m1Input, d2Input, m2Input;
  vector<string> vector_dates;
  vector<int> ipAct;
  string month_in, day_in, hour_in, ip_in, message_in;
  Node* root = NULL;
  ifstream input("bitacora.txt");
  if(input.is_open()) {
    if (isEmpty(input)) {
      input.close();
    } else {
      while(!input.eof()) {
        getline(input,month_in,' ');//obtiene mes
        getline(input,day_in,' ');//obtiene dia
        getline(input,hour_in,' ');//obtiene la hora sin separar
        getline(input,ip_in,' ');//obtiene ip
        getline(input,message_in);//obtiene el mensaje
        string delimiter = ":";
        int pos = 0;
        string token;

        while ((pos = hour_in.find(delimiter)) != string::npos) {
          token = hour_in.substr(0, pos);
          hour_in.erase(0, pos + delimiter.length());
          vector_dates.push_back(token);//mete hora y minuto al vector
        }

        vector_dates.push_back(hour_in);//mete segundos al vector
        h = stoi(vector_dates[index]);//convierte hora a int
        index++;
        m = stoi(vector_dates[index]);//convierte minuto a int
        index++;
        s = stoi(vector_dates[index]);//convierte segundo a int
        index++;
        d = stoi(day_in);//convierte dia a int
        Date new_date(month_in, d, h, m, s);//Crea un objeto clase fecha
        ipAct = procesaIP(ip_in);
        DirIp new_ip(ipAct[0], ipAct[1], ipAct[2], ipAct[3], ipAct[4]); //Crea un objeto clase DirIp
        Registro new_data(new_date, new_ip, message_in); //Crea un objeto clase Registro

        Node* new_leaf=creaNodo(new_data);
        insertaArbol(root,new_leaf);
      }
    }
    input.close();
  }
  printTree(root, 5);
  return 0;
}
