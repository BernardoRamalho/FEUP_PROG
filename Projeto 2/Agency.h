#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "auxFuncs.h"
#include "documentFunc.h"


using namespace std;

class Agency{
 private:
	string name; // name of the  agency
	int VATnumber; // VAT number of the agency
	Address address; // address of the agency
	string URL; // URL of the agency Web site
	vector<Client> clients; // vector to store the existing clients
	vector<Pack> packs; // vector to store the existing packets
	string clientsFilename;
	string packsFilename;
  
	bool clientsInfoHasChanged; // flag that is set to "true" if at least one client has been changed/added/deleted
	bool packetsInfoHasChanged; // flag that is set to "true" if at least one packet has been changed/added/deleted
	unsigned int maxClientsId; // maximum value among all clients identifiers
	unsigned int maxPacketsId; // maximum value among all packets identifiers

 public:
	 Agency();
	 Agency(string filename, int & lastPackChanged);

  // methods GET
	string getName() const;
	unsigned getVATnumber() const;
	Address getAddress() const;
	string getURL() const;
	vector<Client> getClients() const;
	vector<Pack> getPacks() const;
	string getClientsFilename() const;
	string getPacksFilename() const;

  
  // methods SET
	void setName(string newName);
	void setVATnumber(unsigned newVATnumber);
	void setAddress(Address newAddress);
	void setURL(string newURL);
	void setClients(vector<Client> newClients);
	void setPacks(vector<Pack> newPacks);

  // other methods */
  
	void print();
  
};
