//Clase sobre los registros de entrada
#ifndef IP_H_INCLUDED
#define IP_H_INCLUDED

#include <iostream>
#include "Date.h"
using namespace std;
class Ip{

private:
  Date date;
  string port;
  string message;

public:
  //Constructor
  Ip(Date &date1, string port1, string message1){
    date=date1;
    port=port1;
    message= message1;
  }
  //Sets y gets de atributos
  void setDate(Date date){
    date=date;
  }
  Date getDate(){
    return date;
  }
  void setPort(string port1){
    port=port1;
  }
  string getPort(){
    return port;
  }
  void setMessage(string message1){
    message= message1;
  }
  string getMessage(){
    return message;
  }
  //Método para imprimir
  void printIp(){
    date.printDate();
    cout<<port<<" "<<message<<endl;
  }


};
#endif
