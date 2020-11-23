//TC1031.2
//Act 4.3 - Actividad Integral de Grafos (Evidencia Competencia)
//Daniela Hernández y Hernández   A01730397
//David Eduardo Santiago Sánchez  A01733753
//Franco Minutti Simoni           A01733927
//Descripción: Recibe un archivo con registros y los separa en red, host y mensaje.
//Estos atributos se colocan en nodos y se construye un grafo. A partir de esta
//estructura, se buscan aqueyan redes y hosts con mayor número de incidentes.
//23/11/2020

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//Estructuras de datos
struct Registro {
    string puerto;
    string mensaje;
    string fecha;
    string hora;
    Registro* nextRegistro;
};

struct Host {
    string host;
    Host* nextHost;
    Registro* headRegistro;
    int numRegisters;
};

struct Red {
    string red;
    Red* nextRed;
    Host* hostHead;
    int numHosts;
};

//Complejidad O(n)
Red* existeRed(string redAct, Red* head) {
  //recorre la lista de redes para comprobar si ya hubo un incidente previo
  //y no agregar redes repetidas
   while (head != NULL) {
     if(head -> red == redAct){
       return head;
     }
      head = head -> nextRed;
  }
  return NULL;
}

//Complejidad O(n)
Host* existeHost(string hostAct, Host* head) {
  //recorre la lista de hosts para comprobar si ya hubo un incidente previo
  //y no agregar hosts repetidas
  while (head != NULL) {
    if(head -> host == hostAct) {
      return head;
    }
    head = head -> nextHost;
  }
  return NULL;
}

//Complejidad O(n)
vector<string> procesaIP(string ipIn) {
  //Procesa el string de la IP y lo separa en componentes
  string delimiter1 = ".";
  string delimiter2 = ":";
  int pos = 0;
  string token;

  vector<string> vector_ips;
  vector<string> vector_final;

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

  vector_final.push_back(vector_ips[0]+"."+vector_ips[1]); //Primeros dos num de Ip (red)
  vector_final.push_back(vector_ips[2]+"."+vector_ips[3]); //Segundos dos num de Ip (host)
  vector_final.push_back(vector_ips[4]); //Último num de Ip (puerto)

  return vector_final;
}

//Complejidad O(n)
void insertaRegistro(string puertoIn, string fechaIn, string horaIn, string mensajeIn, Registro* &head) {
  Registro* new_registro = new Registro();
  Registro* last = head;
  new_registro -> puerto = puertoIn;
  new_registro -> mensaje = mensajeIn;
  new_registro -> fecha = fechaIn;
  new_registro -> hora = horaIn;
  new_registro -> nextRegistro = NULL;

  if(head == NULL) {
    head = new_registro;
  } else {
    while(last -> nextRegistro != NULL){
      last = last -> nextRegistro;
    }
    last -> nextRegistro = new_registro;
  }
}

//Complejidad O(n)
void crearNuevoHost(string hostIn, string puertoIn, string fechaIn, string horaIn, string mensajeIn, Host* &head){
  Host* new_host = new Host();
  Host* last = head;
  new_host -> host = hostIn;
  new_host -> nextHost = NULL;
  new_host -> headRegistro = NULL;
  new_host -> numRegisters = 1;
  insertaRegistro(puertoIn, fechaIn, horaIn, mensajeIn, new_host -> headRegistro);
  if(head == NULL) {
    head = new_host;
  } else {
    while(last -> nextHost != NULL){
      last = last -> nextHost;
    }
    last -> nextHost = new_host;
  }
}

//Complejidad O(n)
void crearNuevaRed(string redIn, string hostIn, string puertoIn, string fechaIn, string horaIn, string mensajeIn, Red* &head) {
  Red* new_red = new Red();
  Red* last = head;
  new_red -> red = redIn;
  new_red -> nextRed = NULL;
  new_red -> hostHead = NULL;
  new_red -> numHosts = 1;
  crearNuevoHost(hostIn, puertoIn, fechaIn, horaIn, mensajeIn, new_red -> hostHead);

  if(head == NULL) {
    head = new_red;
  } else {
    while(last -> nextRed != NULL){
      last = last -> nextRed;
    }
    last -> nextRed = new_red;
  }
}

//Complejidad O(n)
void imprimeRed(Red* r) {
  Red* redAct = r;
  int maxHosts = 0;
  while(redAct != NULL) {
    if(maxHosts < redAct -> numHosts) {
      maxHosts = redAct -> numHosts;
    }
    redAct = redAct -> nextRed;
  }
  redAct = r;
  while(redAct != NULL) {
    if(maxHosts == redAct -> numHosts) {
      cout << redAct -> red << endl;
    }
    redAct = redAct -> nextRed;
  }
}

//Complejidad O(n^2)
void imprimeRedyHost(Red* r) {
  Red* redAct = r;
  int maxRegisters = 0;
  while(redAct != NULL) {
    Host* hostAct = redAct -> hostHead;
    while(hostAct != NULL) {
      if(maxRegisters < hostAct -> numRegisters) {
        maxRegisters = hostAct -> numRegisters;
      }
      hostAct = hostAct -> nextHost;
    }
    redAct = redAct -> nextRed;
  }

  redAct = r;

  while(redAct != NULL) {
    Host* hostAct = redAct -> hostHead;
    while(hostAct != NULL) {
      if(maxRegisters == hostAct -> numRegisters) {
        cout << redAct -> red << "." << hostAct -> host << endl;
      }
      hostAct = hostAct -> nextHost;
    }
    redAct = redAct -> nextRed;
  }
}

//Complejidad O(1)
void aumentaNumRed(Red* &r) {
  r -> numHosts ++;
}

//Complejidad O(1)
void aumentaNumHost(Host* &h) {
  h -> numRegisters ++;
}

int main() {
  int count = 0;
  string month_in, day_in, hour_in, ip_in, message_in;
  Red* head = NULL;
  ifstream input("bitacora2.txt");
  if(input.is_open()) {
      while(!input.eof()) {
        getline(input,month_in,' ');//obtiene mes
        getline(input,day_in,' ');//obtiene dia
        getline(input,hour_in,' ');//obtiene la hora sin separar
        getline(input,ip_in,' ');//obtiene ip
        getline(input,message_in);//obtiene el mensaje
        string fecha = month_in + " " + day_in;
        vector<string> ipAct = procesaIP(ip_in);
        Red* new_red = existeRed(ipAct[0], head);
        if(new_red == NULL) {
          crearNuevaRed(ipAct[0], ipAct[1], ipAct[2], fecha, hour_in, message_in, head); //La red no existe en grafo, crearlo
        } else {
          Host* new_host = existeHost(ipAct[1], new_red -> hostHead);
          if(new_host == NULL) {
            crearNuevoHost(ipAct[1], ipAct[2], fecha, hour_in, message_in, new_red -> hostHead); //El host no existe en grado, crearlo
            aumentaNumRed(new_red);
          } else {
            insertaRegistro(ipAct[2], fecha, hour_in, message_in, new_red -> hostHead -> headRegistro); //El host existe, insertar datos
            aumentaNumHost(new_host);
          }
        }
      }
      input.close();
  }
  imprimeRed(head);
  imprimeRedyHost(head);

  return 0;
}
