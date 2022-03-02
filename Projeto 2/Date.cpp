#include "Date.h"
#include <iostream>
#include <iomanip>

Date::Date(){
}

Date::Date(int newDay, int newMonth, int newYear){

	day = newDay;
	month = newMonth;
	year = newYear;
	
}

/*********************************
 * GET Methods
 ********************************/
int Date::getDay() const{

	return day;

}

  
int Date::getMonth() const{

	return month;

}
    
int Date::getYear() const{

	return year;

}

/*********************************
 * SET Methods
 ********************************/

void Date::setDay(int newDay) {
  
	day = newDay;

}
void Date::setMonth(int newMonth) {
  
	month = newMonth;

}

void Date::setYear(int newYear) {

	year = newYear;

}


/*********************************
 * Show Date
 ********************************/  

// disply a Date in a nice format
void Date::print(){

	cout << year << "/";
	cout << setw(2) << setfill('0') << month << "/" << setw(2) << setfill('0') << day << endl;

}
