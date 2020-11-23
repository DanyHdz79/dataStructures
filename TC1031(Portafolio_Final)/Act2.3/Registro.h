//Clase sobre los registros de entrada
#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED

#include <iostream>
#include "Date.h"
#include "DirIp.h"
using namespace std;
class Registro{

private:
  Date date;
  DirIp ip;
  string message;

public:
  //Constructor
  Registro(Date &date1, DirIp &ip1, string message1){
    date=date1;
    ip=ip1;
    message= message1;
  }
  Registro(){
    Date date1("",1,1,1,1);
    date = date1;
    DirIp dir1(1,1,1,1,1);
    ip = dir1;
    message="";
  }
  //Sets y gets de atributos
  Date getDate(){
    return date;
  }

  DirIp getIp(){
    return ip;
  }
  
  string getMessage(){
    return message;
  }
  //Método para imprimir
  void printRegistro(){
    date.printDate();
    ip.printIp();
    cout<<" "<<message<<endl;
  }


};
#endif
