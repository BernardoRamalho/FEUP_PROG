#include "Pack.h"

Pack::Pack() {}

Pack::Pack(int newID, vector<string> newSites, Date newBeginDate, Date newEndDate, double newPricePerPerson, int newMaxPeople, int newPlacesSold){

	id = newID;
	sites = newSites;
	beginDate = newBeginDate;
	endDate = newEndDate;
	pricePerPerson = newPricePerPerson;
	maxPeople = newMaxPeople;
	placesSold = newPlacesSold;
}

  // metodos GET

int Pack::getId() const{

	return id;
}

vector<string> Pack::getSites() const{

	return sites;
}

Date Pack::getBeginDate() const{

	return beginDate;
}

Date Pack::getEndDate() const{

	return endDate;
}

double Pack::getPricePerPerson() const{

	return pricePerPerson;
}

int Pack::getMaxPeople() const{

	return maxPeople;
}

int Pack::getPlacesSold() const {
	return placesSold;
}

  // metodos SET

void Pack::setId(int newId){

	id = newId;
	return;
}

void Pack::setSites(vector<string> newSites){

	sites = newSites;
	return;
}

void Pack::setBeginDate(Date newBeginDate){

	beginDate = newBeginDate;
	return;
}

void Pack::setEndDate(Date newEndDate){

	endDate = newEndDate;
	return;
}

void Pack::setPricePerPerson(double newPricePerPerson){

	pricePerPerson = newPricePerPerson;
	return;
}

void Pack::setMaxPeople(int newMaxPeople){

	maxPeople = newMaxPeople;
	return;
}

void Pack::setPlacesSold(int newPlacesSold) {
	placesSold = newPlacesSold;
	return;
}


/*********************************
 * Show Packet information
 ********************************/  

// shows a packet content 
void Pack::displayTravelPacksDestinations() {

	if (sites.size() == 1) {
		cout << sites[0] << endl;
	}
	else {
		cout << sites[0] << " - ";

		for (int i = 1; i < sites.size(); i++) {
			if (i < sites.size() - 1) {
				cout << sites[i] << ", ";
			}
			else {
				cout << sites[i] << endl;
			}
		}
	}

	return;
}

void Pack::print(){

	cout << id << endl;
	displayTravelPacksDestinations();
	beginDate.print();
	endDate.print();
	cout << pricePerPerson << endl << maxPeople << endl << placesSold << endl;

	return;

}
