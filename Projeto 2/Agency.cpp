#include "Agency.h"

Agency::Agency(){}

Agency::Agency(string filename, int & lastPackChanged) {
	ifstream agencyFile;

	agencyFile.open(filename);

	string documentInformation;	//Variable to get information from the document

	getline(agencyFile, documentInformation);

	name = documentInformation;

	getline(agencyFile, documentInformation);
	
	VATnumber = string_to_int(documentInformation);

	getline(agencyFile, documentInformation);

	URL = documentInformation;

	getline(agencyFile, documentInformation);

	address = readAddress(documentInformation);

	getline(agencyFile, clientsFilename);

	getline(agencyFile, packsFilename);

	packs = getAllPacks(packsFilename, lastPackChanged);

	clients = getAllClients(clientsFilename, packs);
	
	agencyFile.close();
}

  // metodos GET
string Agency::getName() const{

	return name;
}

unsigned Agency::getVATnumber() const{

	return VATnumber;
}

Address Agency::getAddress() const{

	return address;
}

string Agency::getURL() const{

	return URL;
}

vector<Client> Agency::getClients() const{

	return clients;
}

vector<Pack> Agency::getPacks() const{

	return packs;
}

string Agency::getClientsFilename() const {
	
	return clientsFilename;
}

string Agency::getPacksFilename() const {

	return packsFilename;
}

  
  // SET Methods

void Agency::setName(string newName){

	name = newName;
}

void Agency::setVATnumber(unsigned newVATnumber){

	VATnumber = newVATnumber;
}

void Agency::setAddress(Address newAddress){

	address = newAddress;
}
void Agency::setURL(string newURL) {

	URL = newURL;

}
void Agency::setClients(vector<Client> newClients){

	clients = newClients;

}
  void Agency::setPacks(vector<Pack> newPacks){

	packs = newPacks;

}

/*********************************
 * Mostrar Loja
 ********************************/  

// mostra o conteudo de uma agencia

void Agency::print() {

	cout << name << endl << VATnumber << endl;
	cout << URL << endl;
	address.print();
	cout << clientsFilename << endl << packsFilename << endl;

}

