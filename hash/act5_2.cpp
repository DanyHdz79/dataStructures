#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//32749
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
    int numRegisters;
};

struct Summary{
    string dominio;
    int accesos;
    int numIps;
    vector<string> ips;
    Summary *next;

    void imprimeSummary(){
      cout<<dominio<<endl;
      cout<<accesos<<endl;
      cout<<numIps<<endl;
      for(int i=0;i<ips.size();i++){
        cout<<ips[i]<<endl;
      }
    }
};

int hashFunction(string p) {
  int index = 0;
  for(int i = 0; i < p.size(); i++) {
    if(p[i]!='0' && p[i]!='.'){
      index *= p[i];
    }
  }
  index %= 32749;
  return index;
}

vector<int> IpToInt(string ipIn){
  string delimiter1 = ".";
  int pos = 0;
  string token;
  int num;

  vector<int> vector_ints;

  while ((pos = ipIn.find(delimiter1)) != string::npos) {
    token = ipIn.substr(0, pos);
    ipIn.erase(0, pos + delimiter1.length());
    num=stoi(token);
    vector_ints.push_back(num);
  }
  return vector_ints;
}

int comparaIp(string ipA, string ipB){
  vector<int> numsA=IpToInt(ipA);
  vector<int> numsB=IpToInt(ipB);
  if(numsA[0]<numsB[0]){ //Primer numero
    return -1;
  }else if(numsA[0]>numsB[0]){
    return 1;
  }else{
    if(numsA[1]<numsB[1]){ //Segundo numero
      return -1;
    }else if(numsA[1]>numsB[1]){
      return 1;
    }else{
      if(numsA[2]<numsB[2]){ //Tercer numero
        return -1;
      }else if(numsA[2]>numsB[2]){
        return 1;
      }else{
        if(numsA[3]<numsB[3]){ //Cuarto numero
          return -1;
        }else if(numsA[3]>numsB[3]){
          return 1;
        }else{
           return 0;
        }
      }
    }
  }
}

void merge(vector<string> &v1, int start, int middle, int end) {
  int i, j, k;
  int n1 = middle - start + 1;
  int n2 = end - middle;
  vector<string> L, R;

  for (i = 0; i < n1; i++) L.push_back(v1[start + i]);
  for (j = 0; j < n2; j++) R.push_back(v1[middle + 1 + j]);

  i = 0;
  j = 0;
  k = start;

  while (i < n1 && j < n2) {
    if (comparaIp(L[i],R[j]) == -1 || comparaIp(L[i],R[j]) == 0) {
      v1[k] = L[i];
      i++;
    } else {
      v1[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    v1[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    v1[k] = R[j];
    j++;
    k++;
  }
}

//Ordena los dators del vector dado
void ordenaMerge(vector<string> &v1, int start, int end) {
  if (start < end) {
    int middle = start + (end - start) / 2;
    ordenaMerge(v1, start, middle);
    ordenaMerge(v1, middle + 1, end);
    merge(v1, start, middle, end);
  }
}

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
  new_red -> numRegisters = 1;
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
void aumentaNumRedHosts(Red* &r) {
  r -> numHosts ++;
}

//Complejidad O(1)
void aumentaNumRedRegisters(Red* &r) {
  r -> numRegisters ++;
}

//Complejidad O(1)
void aumentaNumHost(Host* &h) {
  h -> numRegisters ++;
}

//---------------------MANEJO DE TABLA-----------------------------------------
void graphToHash(Red* head, Summary* hashTable[]){
  while(head != NULL) {
    Summary* new_summary = new Summary();
    new_summary -> dominio = head->red;
    new_summary -> accesos = head->numRegisters;
    new_summary -> numIps = head->numHosts;
    new_summary -> next = NULL;
    vector<string> ipsList;
    Host* hostAct = head -> hostHead;
    while(hostAct != NULL) {
        string new_ip= head -> red + "." +  hostAct -> host;
        ipsList.push_back(new_ip);
        hostAct = hostAct -> nextHost;
      }
      ordenaMerge(ipsList, 0, ipsList.size()-1);
      new_summary -> ips = ipsList;
      int index=hashFunction(new_summary -> dominio);
      if(hashTable[index] == NULL) {
        hashTable[index] = new_summary;
      } else {
        Summary* aux = hashTable[index];
        while(aux -> next != NULL) {
          aux = aux -> next;
        }
        aux -> next = new_summary;
      }
      head = head -> nextRed;
    }
}

Summary* search(Summary* hT[], string key) {
  int index = hashFunction(key);
  Summary* tmp = hT[index];
  while(tmp -> dominio != key) {
     tmp = tmp -> next;
     if(tmp == NULL) return NULL;
  }
  return tmp;
}


int main() {
  int count = 0;
  string month_in, day_in, hour_in, ip_in, message_in;
  Red* head = NULL;
  Summary* hashTable[32749] = {NULL};
  ifstream input("test5.txt");
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
            aumentaNumRedHosts(new_red);
            aumentaNumRedRegisters(new_red);
          } else {
            insertaRegistro(ipAct[2], fecha, hour_in, message_in, new_red -> hostHead -> headRegistro); //El host existe, insertar datos
            aumentaNumHost(new_host);
            aumentaNumRedRegisters(new_red);
          }
        }
      }
    input.close();
  }
  graphToHash(head, hashTable);

  //Búsqueda de datos
  int n;
  string searchDomain;
  cin>>n;
  for(int i=0;i<n;i++){
    cin>>data;
    Summary* result= search(hashTable, data);
    if(result!=NULL){
      result->imprimeSummary();
    }
  }
}
