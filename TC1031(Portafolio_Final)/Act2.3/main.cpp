//TC1031.2
//Act 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia)
//Daniela Hernández y Hernández   A01730397
//David Eduardo Santiago Sánchez  A01733753
//Franco Minutti Simoni           A01733927
//Descripción: Ordena una serie de registros de acuerdo a diferentes filtros, exporta
//una lista doblemente ligada con los elementos ordenados a un archivo de texto
//de forma ascendente y muestra en consola los registros de forma descendente buscados
//por el usuario por su IP.
//12/10/2020

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Registro.h"
using namespace std;


//Estructura de datos-----------------------------------------------------------------
struct Node {
    Registro data;
    Node* next; // Pointer to next node in DLL
    Node* prev; // Pointer to previous node in DLL
};

//Filtro de fechas: Si dato 1 es menor que dato2, regresa -1, si es igual regresa 0, si es mayor regresa 1
//Orden O(1)
int comparaFechas(Registro &dato1, Registro &dato2){
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
int comparaIp(Registro &dato1, Registro &dato2){
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
int comparaMensajes(Registro &dato1, Registro &dato2){
  string mensaje1 = dato1.getMessage();
  string mensaje2 = dato2.getMessage();

  if(mensaje1 < mensaje2){
    return -1;
  } else if(mensaje1 > mensaje2) {
    return 1;
  } else {
    return 0;
  }
}

//Compara registros con los tres filtros
//Orden O(1)
int comparaRegistros(Node *reg1, Node *reg2){
  if(reg1==NULL){
    return 1;
  }else{
    Registro dato1=reg1->data;
    Registro dato2=reg2->data;
    int resultIp = comparaIp(dato1, dato2);
    if(resultIp == 0){
      int resultFecha = comparaFechas(dato1, dato2);
      if(resultFecha != 0){
        return resultFecha;
      }else{
        int resultMessage = comparaMensajes(dato1, dato2);
        return resultMessage;
      }
    }
    return resultIp;
  }
}

//Descopone la string de ips en sus elementos
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

  pos=0;

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

//ImprimeLista de inicio a fin
//Orden O(n)
void ImprimeLista(Node* head) {
   Node* previo;
   while (head != NULL) {
      Registro regAct=head->data;
      regAct.printRegistro();
      previo = head;
      head = head->next;
   }
}

//Inseta los nodos en su lugar correspondiente
//Orden O(n)
Node* InsertaOrden(Node* &head, Registro &registro1) {
  //Crea un nuevo nodo con el registro pasado
  Node* new_node = new Node();
  new_node -> data = registro1;
  new_node -> next = NULL;
  new_node -> prev = NULL;
  Node *aux1 = head; //Nodo actual
  Node *aux2; //Nodo anterior
  int resultComp = -2;
  Node* tail=head;
  //Lista vacía
  if(head == NULL){
    head = new_node;
    return head;
  }else{
    do{ //Recorrer hasta que el nodo actual sea null o si el nodo actual es mayor al registro
        resultComp = comparaRegistros(aux1, new_node);
        if(resultComp != 1){ //Si es mayor, quedarse en ese nodo
          aux2 = aux1;
          aux1 = aux1 -> next;
        }
    }while (aux1 != NULL && resultComp != 1);
    //Insertar nodo antes de la cabeza
    if(head == aux1){
      new_node -> next = aux1;
      aux1 -> prev = new_node;
      head = new_node;
    }else if(aux1 == NULL) { //Insertar al final
      new_node -> prev = aux2;
      aux2 -> next = new_node;
    } else { //Insertar entre dos nodos
      new_node -> next = aux1;
      new_node -> prev = aux2;
      aux1 -> prev = new_node;
      aux2 -> next = new_node;
    }
    while(tail->next!=NULL){
      tail=tail->next;
    }
    return tail;
  }
}

//Muestra los registros de forma descendente según las entradas de búsqueda
//Orden O(n)
void busqueda(string min, string max, Node* &tail){
  Node* tailTemp=tail;
  vector<int> ipTrans;
  Date fechaMin("Jan",1,0,0,0);
  Date fechaMax("Dec",31,23,59,59);
  min=min+":-10";
  max=max+":10000000";
  ipTrans = procesaIP(min);
  DirIp minIp(ipTrans[0], ipTrans[1], ipTrans[2], ipTrans[3], ipTrans[4]); //Crea un objeto clase DirIp con la fecha mínima
  Registro regMin(fechaMin,minIp,"A");
  ipTrans= procesaIP(max);
  DirIp maxIp(ipTrans[0], ipTrans[1], ipTrans[2], ipTrans[3], ipTrans[4]); //Crea un objeto clase DirIp con la fecha máxima
  Registro regMax(fechaMax,maxIp,"Z");

  Node* pointMin = new Node();
  pointMin -> data = regMin;
  pointMin -> next = NULL;
  pointMin -> prev = NULL;

  Node* pointMax = new Node();
  pointMax -> data = regMax;
  pointMax -> next = NULL;
  pointMax -> prev = NULL;

  int comparaRango;
  int comparaMin;
  int comparaMax;
  while(tailTemp->prev!=NULL){
    comparaMin=comparaRegistros(tailTemp,pointMin);
    comparaMax=comparaRegistros(tailTemp,pointMax);
    if(comparaMin!=-1 && comparaMax!=1){
      Registro temp=tailTemp->data;
      temp.printRegistro();
    }
    tailTemp=tailTemp->prev;
  }
}

//Mandar los registros a un txt
//Orden O(n)
void sortedToFile(Node* &head){
  Node* headTemp = head;
  ofstream SortedData("SortedData.txt"); //archivo para exportar los datos ordenados
  while (headTemp != NULL) {
      Registro regAct=headTemp->data;
      SortedData << regAct.getDate().getMonth() << " ";
      SortedData << regAct.getDate().getDayFile() << " ";
      SortedData << regAct.getDate().getHourFile() << ":";
      SortedData << regAct.getDate().getMinuteFile() << ":";
      SortedData << regAct.getDate().getSecondFile() << " ";
      SortedData << regAct.getIp().getNumOne() << ".";
      SortedData << regAct.getIp().getNumTwo() << ".";
      SortedData << regAct.getIp().getNumThree() << ".";
      SortedData << regAct.getIp().getNumFour() << ":";
      SortedData << regAct.getIp().getPort() << " ";
      SortedData << regAct.getMessage() << endl;
      headTemp=headTemp->next;
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
  Node* head = NULL;
  Node* tailLista=NULL;
  ifstream input("bitacora.txt");
  if(input.is_open()){
    if (isEmpty(input)) {
      ofstream SortedData("SortedData.txt");
      SortedData <<"";
      input.close();
    }else{
      while(!input.eof()){
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
          tailLista = InsertaOrden(head, new_data);
        }
        input.close();
        // Recibir IPs de búsqueda
        string ipMin;
        string ipMax;
        cin >> ipMin;
        cin >> ipMax;
        busqueda(ipMin,ipMax,tailLista);
        sortedToFile(head);
      }
  } //final while


  return 0;
}
