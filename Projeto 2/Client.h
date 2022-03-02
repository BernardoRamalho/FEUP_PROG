#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "defs.h"
#include "Pack.h"
#include "Address.h"

using namespace std;

class Client{
 private:
  string name; // name of the client
  unsigned VATnumber; // VAT number of client
  unsigned short familySize;  // number of family members
  Address address; // client's address
  vector<Pack> packs; // vector to store client's packets bought
  unsigned  totalPurchased; // total value spent by the client

 public:
	 Client();
	Client(string newName, unsigned newVATnumber, unsigned short newFamilySize, Address newAddress);  // for a new client
	Client(string newName, unsigned newVATnumber, unsigned short newFamilySize, Address newAddress, vector<Pack> & newPacks, unsigned newTotalPurchased);  // client read from file

  // GET methods
  
  string getName() const;
  unsigned getVATnumber() const;
  unsigned short getFamilySize() const;
  Address getAddress() const;
  vector<Pack> getPackList() const;
  unsigned getTotalPurchased() const;
  
  // SET methods
  
  void setName(string newName);
  void setVATnumber(unsigned newVATnumber);
  void setFamilySize(unsigned short newFamilySize);
  void setAddress(Address newAddress);
  void setPackList(vector<Pack> newPacks);
  void setTotalPurchased(unsigned newTotalPurchased);
  
  // other methods

  void displayPacksBought();

  void print();

  void buyPack(int packId, vector<Pack> & existingPacks);
};
