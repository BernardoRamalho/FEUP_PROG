#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Date.h"

using namespace std;

class Pack{

private:
	int id; // packet unique identifier
	vector<string> sites; // touristic sites to visit
	Date beginDate;  // begin date
	Date endDate;  // end date
	double pricePerPerson; // price per person
	int maxPeople; // number of persons still available in the packet (updated whenever the packet is sold to a new client)
	int placesSold; //number of places already sold (updated whenever the pack is sold)
  
public:

	Pack();

	Pack(int newID, vector<string> newSites, Date newBeginDate, Date newEndDate, double newPricePerPerson, int newMaxPeople, int placesSold);

	// GET methods
	int getId() const;
	vector<string> getSites() const;
	Date getBeginDate() const;
	Date getEndDate() const;
	double getPricePerPerson() const;
	int getMaxPeople() const;
	int getPlacesSold() const;

	// SET methods
	void setId(int newId);  // to set negatve if "deprecated"
	void setSites(vector<string> newSites);
	void setBeginDate(Date newBeginDate);
	void setEndDate(Date newEndDate);
	void setPricePerPerson(double newPricePerPerson);
	void setMaxPeople(int newMaxPeople);
	void setPlacesSold(int newPlacesSold);

	// other methods
	void displayTravelPacksDestinations(); //Displays the Destinations of the Pack
	void print();
};
