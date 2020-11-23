//TC1031.2
//Act 1.3 - Act 1.3 - Actividad Integral de Conceptos Básicos y Algoritmos Fundamentales (Evidencia Competencia)
//Daniela Hernández y Hernández   A01730397
//David Eduardo Santiago Sánchez  A01733753
//Franco Minutti Simoni           A01733927
//Programa que ordena un archio txt de entrada por fechas, las guarda en otro archivo txt y que busca registros
//dentro de un rango de fechas dado
//13/09/2020

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Ip.h"
using namespace std;


//Comparar fechas y verificar si el primer dato es menor o igual al primero
int comparaFechas(Ip &dato1, Ip &dato2){
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
  if(m1 < m2) {
    return 1;
  } else if(d1<d2 && m1<=m2) {
    return 1;
  } else if(h1<h2 && d1<=d2 && m1<=m2) {
    return 1;
  } else if(min1<min2 && h1<=h2 && d1<=d2 && m1<=m2) {
    return 1;
  } else if(s1<=s2 && min1<=min2 && h1<=h2 && d1<=d2 && m1<=m2) {
    return 1;
  } else {
    return 0;
  }
}

//Método complementario para la función ordenMerge
void merge(vector<Ip> &v1, long start, long middle, long end) {
  long i, j, k;
  long n1 = middle - start + 1;
  long n2 = end - middle;
  vector<Ip> L, R;

  for (i = 0; i < n1; i++) L.push_back(v1[start + i]);
  for (j = 0; j < n2; j++) R.push_back(v1[middle + 1 + j]);

  i = 0;
  j = 0;
  k = start;

  while (i < n1 && j < n2) {
    if (comparaFechas(L[i],R[j]) == 1) {
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
void ordenaMerge(vector<Ip> &v1, long start, long end) {
  if (start < end) {
    long middle = start + (end - start) / 2;
    ordenaMerge(v1, start, middle);
    ordenaMerge(v1, middle + 1, end);
    merge(v1, start, middle, end);
  }
}

//Busca datos en un rango de fechas y los guarda en un vector
vector<Ip> busqSecuencial(vector<Ip> &v, int dDayInf, int dMonthInf, int dDaySup, int dMonthSup) {
  vector<Ip> list;
  int sMonth, sDay;
  for(long i = 0; i < v.size(); i++) {
    sMonth = v[i].getDate().monthToNumber();
    sDay = v[i].getDate().getDay();
    if(dMonthInf==dMonthSup){
      if(sMonth==dMonthInf && sDay>=dDayInf && sDay<=dDaySup){
        list.push_back(v[i]);
      }
    }else if((sMonth == dMonthInf && sDay >= dDayInf) || (sMonth == dMonthSup && sDay <= dDaySup) || (sMonth > dMonthInf && sMonth < dMonthSup)) {
      list.push_back(v[i]);
    }
  }
  return list;
}


int main() {
  int index = 0, d, h, m, s, d1Input, m1Input, d2Input, m2Input;
  vector<Ip> vector_data, vector_list; //almacena los objetos ya hechos
  vector<string> vector_dates; //almacena las fechas
  string month_in, day_in, hour_in, port_in, message_in;
  ifstream input("bitacora.txt");
  if(input.is_open()){

    while(!input.eof()){
      getline(input,month_in,' ');//obtiene mes
      getline(input,day_in,' ');//obtiene dia
      getline(input,hour_in,' ');//obtiene la hora sin separar
      getline(input,port_in,' ');//obtiene puerto
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
      Ip new_data(new_date, port_in, message_in);//crea un objeto clase ip
      vector_data.push_back(new_data);//mete el objeto clase ip al vector de datos
    } //final while
    input.close();
  }

  ordenaMerge(vector_data, 0, vector_data.size()-1);

  ofstream sortedData("sortedData.txt"); //archivo para exportar los datos ordenados

  for(int i = vector_data.size() - 1; i >= 0; i--) {
    sortedData << vector_data[i].getDate().getMonth() << " ";
    sortedData << to_string(vector_data[i].getDate().getDay()) << " ";
    sortedData << to_string(vector_data[i].getDate().getHour()) << ":";
    sortedData << to_string(vector_data[i].getDate().getMinute()) << ":";
    sortedData << to_string(vector_data[i].getDate().getSecond()) << " ";
    sortedData << vector_data[i].getPort() << " ";
    sortedData << vector_data[i].getMessage() << endl;
  }

  cin >> d1Input;
  cin >> m1Input;
  cin >> d2Input;
  cin >> m2Input;
  if(m1Input<m2Input) { //De m1 a m2
    vector_list = busqSecuencial(vector_data, d1Input, m1Input, d2Input, m2Input);
  } else if(m1Input>m2Input) { //De m2 a m1
    vector_list = busqSecuencial(vector_data, d2Input, m2Input, d1Input, m1Input);
  } else if(d1Input<d2Input) { //Mismo mes, de d1 a d2
    vector_list = busqSecuencial(vector_data, d1Input, m1Input, d2Input, m2Input);
  } else { //Mismo mes, de d2 a d1
    vector_list = busqSecuencial(vector_data, d2Input, m2Input, d1Input, m1Input);
  }


  for(int i = 0; i < vector_list.size(); i++){
    vector_list[i].printIp();
  }

  return 0;
}
