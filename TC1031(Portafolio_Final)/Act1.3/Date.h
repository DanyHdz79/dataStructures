//Clase de fechas
#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>
#include "Ip.h"
#include <string>

using namespace std;

class Date{
  private:
    string month;
    int day, hour, minute, second;

  public:
    //Constructores
    Date(){
      month="";
      day=0;
      hour=0;
      minute=0;
      second=0;
    }

    Date(string m, int d, int h, int min, int s){
     month=m;
     day=d;
     hour=h;
     minute=min;
     second=s;
    }
    //Sets y gets
    string getMonth() const{
      return month;
    }
    int getDay() const{
      return day;
    }
    int getHour() const{
      return hour;
    }
    int getMinute() const{
      return minute;
    }
    int getSecond() const{
      return second;
  }


  void setMonth(int month1){
    month = month1;
  }
  void setDay(int day1){
    day = day1;
  }
  void setHour(int hour1){
    hour = hour1;
  }
  void setMinute(int minute1){
    minute = minute1;
  }
  void setSecond(int second1){
    second = second1;
  }

  //Imprime la fecha en el formato h:min:s
  void printDate(){
    std::string d=std::to_string(day);
    std::string h=std::to_string(hour);
    std::string min=std::to_string(minute);
    std::string s=std::to_string(second);
    if(day<10){
      d="0"+d;
    }
    if(hour<10){
      h="0"+h;
    }
    if(minute<10){
      min="0"+min;
    }
    if(second<10){
      s="0"+s;
    }
    cout<<month<<" "<<d<<" "<<h<<":"<<min<<":"<<s<<" ";
  }

  //Convierte la string de meses a un entero
  int monthToNumber(){
      if(month=="Jan"){
        return 1;
      }else if(month=="Feb"){
        return 2;
      }else if(month=="Mar"){
        return 3;
      }else if(month=="Apr"){
        return 4;
      }else if(month=="May"){
        return 5;
      }else if(month=="Jun"){
        return 6;
      }else if(month=="Jul"){
        return 7;
      }else if(month=="Aug"){
        return 8;
      }else if(month=="Sep"){
        return 9;
      }else if(month=="Oct"){
        return 10;
      }else if(month=="Nov"){
        return 11;
      }else if(month=="Dec"){
        return 12;
      }
      return 0;
  }
};
#endif
