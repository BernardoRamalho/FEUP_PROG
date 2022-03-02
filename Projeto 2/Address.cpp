#include "Address.h"



Address::Address() {
}

Address::Address(string street, unsigned short doorNumber, string floor, string postalCode, string location) {

	this->street = street;
	this->doorNumber = doorNumber;
	this->floor = floor;
	this->postalCode = postalCode;
	this->location = location;
}

// metodos GET


string Address::getStreet() const {

	return street;
}

unsigned short Address::getDoorNumber() const {

	return doorNumber;
}

string Address::getFloor() const {

	return floor;
}

string Address::getPostalCode() const {

	return postalCode;
}

string Address::getLocation() const {

	return location;
}



// metodos SET

void Address::setStreet(string newStreet) {

	street = newStreet;
}

void Address::setDoorNumber(unsigned short newDoorNumber) {

	doorNumber = newDoorNumber;
}

void Address::setFloor(string newfloor) {

	floor = newfloor;
}

void Address::setPostalCode(string newPostalCode) {

	postalCode = newPostalCode;
}

void Address::setLocation(string  newLocation) {

	location = newLocation;
}


/*********************************
 * Mostrar Address
 ********************************/

 // discplyes an address in a nice format
void Address::print() {

	cout << street << " / " << doorNumber << " / " << floor << " / " << postalCode << " / " << location << endl;

}