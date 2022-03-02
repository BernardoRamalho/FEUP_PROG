#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Address {
private:
	string street; // street name
	unsigned short doorNumber; // doro number
	string floor; // floor number ("-" is not applicable)
	string postalCode; // postal code
	string location; // site

public:
	Address();
	Address(string street, unsigned short doorNumber, string floor, string postalCode, string location);

	// metodos GET
	string getStreet() const;
	unsigned short getDoorNumber() const;
	string getFloor() const;
	string getPostalCode() const;
	string getLocation() const;

	// metodos SET
	void setStreet(string newStreet);
	void setDoorNumber(unsigned short newDoorNumber);
	void setFloor(string newFloor);
	void setPostalCode(string newPostalCode);
	void setLocation(string  newLocation);

	// outros */

	void print();

};