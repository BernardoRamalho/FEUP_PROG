#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "defs.h"

using namespace std;

class Date{
 private:
  int day;
  int month;
  int year;

 public:
  Date();
  Date(int newDay, int newMonth, int newYear);

  // GET methods
  int getDay() const;
  int getMonth() const;
  int getYear() const;
  
  // SET methods
  
  void setDay(int newDay);
  void setMonth(int newMonth);
  void setYear(int newYear);

  // outhet methods */
  
  void print();

};
