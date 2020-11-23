//Clase sobre las ip
#ifndef DIRIP_H_INCLUDED
#define DIRIP_H_INCLUDED

#include <iostream>

using namespace std;

class DirIp{
  private:
        int numOne;
        int numTwo;
        int numThree;
        int numFour;
        int port;
  public:
    //Constructor
    DirIp(){
      numOne=0;
      numTwo=0;
      numThree=0;
      numFour=0;
      port=0;
    }

    DirIp(int numOne, int numTwo, int numThree, int numFour, int port){
      this -> numOne = numOne;
      this -> numTwo = numTwo;
      this -> numThree = numThree;
      this -> numFour = numFour;
      this -> port = port;
    }
    //Sets y gets de atributos
    void setNumOne(){
    this -> numOne = numOne;
    }
    int getNumOne(){
      return numOne;
    }
    void setNumTwo(){
      this -> numTwo = numTwo;
    }
    int getNumTwo(){
      return numTwo;
    }
    void setNumThree(){
      this -> numThree = numThree;
    }
    int getNumThree(){
      return numThree;
    }
    void setNumFour(){
      this -> numFour = numFour;
    }
    int getNumFour(){
      return numFour;
    }
    void setPort(int port){
      this->port=port;
    }
    int getPort(){
      return port;
    }
    //Método para imprimir
    void printIp(){
      cout<<numOne<<"."<<numTwo<<"."<<numThree<<"."<<numFour<<":"<<port;
    }
};
#endif
