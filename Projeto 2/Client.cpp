#include "Client.h"

Client::Client(){}

Client::Client(string newName, unsigned newVATnumber, unsigned short newFamilySize, Address newAddress){
  
	name = newName;
	VATnumber = newVATnumber;
	familySize = newFamilySize;
	address = newAddress;

}

Client::Client(string newName, unsigned newVATnumber, unsigned short newFamilySize, Address newAddress, vector<Pack> & newPacks, unsigned newTotalPurchased){
  
	name = newName;
	VATnumber = newVATnumber;
	familySize = newFamilySize;
	address = newAddress;
	packs = newPacks;
	totalPurchased = newTotalPurchased;
}

  // GET methods

string Client::getName() const{
  
	return name;
}
  
unsigned Client::getVATnumber() const{
  
	return VATnumber;
}

unsigned short Client::getFamilySize() const{
  
	return familySize;
}

Address Client::getAddress() const{
  
	return address;
}

vector<Pack> Client::getPackList() const{
  
	return packs;
}

unsigned Client::getTotalPurchased() const{
  
	return totalPurchased;
}
  
  // metodos SET
	  
void Client::setName(string newName){
  
	name = newName;
}

void Client::setVATnumber(unsigned newVATnumber){
  
	VATnumber = newVATnumber;
}

void Client::setFamilySize(unsigned short newFamilySize){
  
	familySize = newFamilySize;
}
void Client::setAddress(Address newAddress){
  
	address = newAddress;
}
void Client::setPackList(vector<Pack> newPacks){
  
	packs = newPacks;
}
void Client::setTotalPurchased(unsigned newTotalPurchased){
  
	totalPurchased = newTotalPurchased;
}
  
  // outros metodos

void Client::displayPacksBought() {

	for (int i = 0; i < packs.size(); i++) {
		if (i < packs.size() - 1) {
			cout << packs[i].getId() << " ; ";
		}
		else {
			cout << packs[i].getId() << endl;
		}
	}
}

void Client::print(){

	cout << name << endl << VATnumber << endl;
	address.print();
	displayPacksBought();
	cout << totalPurchased << endl;

}

void Client::buyPack(int packId, vector<Pack> & existingPacks) {

	for (int i = 0; i < existingPacks.size(); i++) {

		if (existingPacks[i].getId() == packId) {

			if (existingPacks[i].getPlacesSold() == existingPacks[i].getMaxPeople()) {
				cout << "We are sorry but this pack is already sold out.\n";

				return;
			}

			packs.push_back(existingPacks[i]);

			cout << "Is the client buying the pack for itself or for the family (input 1 if for itself and 2 otherwise)? ";

			int answer;

			cin >> answer;

			if (answer == 1) {
				existingPacks[i].setPlacesSold(existingPacks[i].getPlacesSold() + 1);
			}
			else {
				existingPacks[i].setPlacesSold(existingPacks[i].getPlacesSold() + familySize);
			}
			
			return;
		}
	}

	cout << "You introduce a invalid pack ID. Please input a valid one: ";
	cin >> packId;

	buyPack(packId, existingPacks);

	return;
}


