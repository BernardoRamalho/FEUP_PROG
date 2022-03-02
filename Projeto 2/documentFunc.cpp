#include "documentFunc.h"

//FALTA COMENTAR

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::READING FUNCTIONS::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

Address readAddress(string s){

	Address address;

	vector<string> addressInformation;

	addressInformation = splitString(s, '/');

	//Set Street Name
	address.setStreet(addressInformation[0]);

	//Set DoorNumber
	address.setDoorNumber(string_to_int(addressInformation[1]));

	//Set the Floor
	address.setFloor(addressInformation[2]);

	//Set the Postal Code
	address.setPostalCode(addressInformation[3]);

	//Set the Location
	address.setLocation(addressInformation[4]);

	return address;

}

Date readDate(string s){

	Date date;

	vector<string> holder = splitString(s, '/');

	date.setYear(string_to_int(holder[0]));
	date.setMonth(string_to_int(holder[1]));
	date.setDay(string_to_int(holder[2]));

	return date;
}

vector<string> readPlacesList(string s){
	vector<string> placesVisit, holder;

	if (s.find('-') != -1) {

		holder = splitString(s, '-');

		placesVisit.push_back(holder[0]);

		holder = splitString(holder[1], ',');

		for (int i = 0; i < holder.size(); i++) {
			placesVisit.push_back(holder[i]);
		}

	}
	else {
		placesVisit.push_back(s);
	}

	return placesVisit;
}

Client readClientInformation(ifstream& clientFile, vector<Pack> allPacks){

	Client client;

	string documentInformation;	//Variable to get information that is not supposed to be a string

	//Set Name
	getline(clientFile, documentInformation);
	
	client.setName(documentInformation);

	//Set VATnumber
	getline(clientFile, documentInformation);
	
	client.setVATnumber(string_to_int(documentInformation));

	//Set Family Size
	getline(clientFile, documentInformation);
	
	client.setFamilySize(string_to_int(documentInformation));

	//Set Address
	getline(clientFile, documentInformation);
	
	client.setAddress(readAddress(documentInformation));

	//Set List of Packs Bought

	getline(clientFile, documentInformation);

	vector<string> packsBought;

	if (documentInformation.find(';') != -1) {
		 packsBought = splitString(documentInformation, ';');
	}
	else {
		vector<string> packsBought;
		packsBought.push_back(documentInformation);
	}

	vector<Pack> packList;

	for (int i = 0; i < packsBought.size(); i++) {
		packList.push_back(getPack(string_to_int(packsBought[i]), allPacks));
	}

	client.setPackList(packList);

	//Set Total Purchased by the Client
	getline(clientFile, documentInformation);

	client.setTotalPurchased(string_to_int(documentInformation));

	return client;
}

Pack readTravelPackInformation(ifstream& travelPackFile){

	Pack pack;

	string documentInformation;	//Variable to get information that is not supposed to be a string	

	//Set ID
	getline(travelPackFile, documentInformation);
	
	pack.setId(string_to_int(documentInformation));

	//Set the List of Places Of the Pack
	getline(travelPackFile, documentInformation);

	pack.setSites(readPlacesList(documentInformation));

	//Set the Beginning Date
	getline(travelPackFile, documentInformation);

	pack.setBeginDate(readDate(documentInformation));

	//Set the Ending Date
	getline(travelPackFile, documentInformation);

	pack.setEndDate(readDate(documentInformation));

	//Set the Price Per Person
	getline(travelPackFile, documentInformation);

	pack.setPricePerPerson(string_to_int(documentInformation));

	//Set the Maximum of People that can buy the Travel Pack
	getline(travelPackFile, documentInformation);

	pack.setMaxPeople(string_to_int(documentInformation));

	//Set the Number of Places Already Sold
	getline(travelPackFile, documentInformation);

	pack.setPlacesSold(string_to_int(documentInformation));

	return pack;
}


/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::CREATING FUNCTIONS:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

void createClient(vector<Client>& v, vector<Pack> allPacks) {

	Client newClient;

	string string_answer;
	int int_answer;

	cout << "Please insert the information of the new Client:\n";

	//Asking for the name of the new Client
	cout << "Name - ";

	cin.ignore(200, '\n');

	getline(cin, string_answer);

	newClient.setName(string_answer);

	//Asking the VATnumber of the new Client
	cout << "VATnumber - ";

	cin >> int_answer;

	newClient.setVATnumber(int_answer);

	if (cin.fail() || int_to_string(newClient.getVATnumber()).length() != 9) {
		cerr << "Invalid input for NIF\n";
		cout << "Please introduce a valid integer with 9 characters: ";
		cin >> int_answer;
		newClient.setVATnumber(int_answer);
	}

	//Asking the number of Family Members of the new Client
	cout << "Family Members - ";

	cin >> int_answer;

	newClient.setFamilySize(int_answer);

	//Asking the Address of the new Client
	cout << "Address (Street Name / Door Number / Floor Number ( '-' if you don't have) / Postal Code / District) - ";

	cin.ignore(200, '\n');

	getline(cin, string_answer);

	newClient.setAddress(readAddress(string_answer));

	//Asking which Packs the new Client has bought
	cout << "Packs Bougt (format: Pack1 ; Pack2 ; Pack3) - ";

	getline(cin, string_answer);

	newClient.setPackList(getPackList(splitString(string_answer, ';'), allPacks));

	//Saving all the information into the clients vector
	v.push_back(newClient);

	return;
}

void createTravelPack(vector<Pack>& v) {

	Pack newPack;

	string string_answer;
	int int_answer;

	cout << "Please insert the information of the new Travel Pack:\n";

	//Asking for the New ID
	cout << "ID - ";

	cin >> int_answer;

	newPack.setId(int_answer);

	//Asking for the Places that the new Travel Pack will visit
	cout << "Places to Visit (Main place - Place1, Place2) - ";

	cin.ignore(200, '\n');

	getline(cin, string_answer);

	newPack.setSites(readPlacesList(string_answer));

	//Asking the beginning date of the travel
	cout << "Beginning Date (YYYY/MM/DD) - ";

	//	cin.ignore(200, '\n');

	getline(cin, string_answer);

	newPack.setBeginDate(readDate(string_answer));

	//Asking the ending date of the travel
	cout << "Ending Date (YYYY/MM/DD) - ";

	//cin.ignore(200, '\n');

	getline(cin, string_answer);

	newPack.setEndDate(readDate(string_answer));

	//Asking the price per person of the pack
	cout << "Price Per Person - ";

	double answer;

	cin >> answer;

	newPack.setPricePerPerson(answer);

	//Asking the total amount of people that can go on the travel
	cout << "Maximum Number of People - ";

	cin >> int_answer;

	newPack.setMaxPeople(int_answer);

	//Asking the number of spots that can still be sold
	cout << "Available Spots - ";

	cin >> int_answer;

	newPack.setPlacesSold(int_answer);

	//Saving the information into the travel Packs vector
	v.push_back(newPack);

}

void createDoc(string filename) {

	ofstream writeStream(filename);

	writeStream.close();

	return;
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::GET FUNCTIONS:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

vector<Pack> getAllPacks(string filename, int & lastPackChanged) {

	int numberPacks = getFileSize(filename);

	int getPosition;
	
	vector<Pack> allPacks;
	
	ifstream travelPackFile(filename);

	if (is_fileEmpty(travelPackFile)) {
		createTravelPack(allPacks);
	}
	else {
		removeNewLine(filename);

		string holder;

		getline(travelPackFile, holder);

		lastPackChanged = string_to_int(holder);

		for (int i = 0; i < numberPacks; i++) {
			allPacks.push_back(readTravelPackInformation(travelPackFile));
			
			getPosition = travelPackFile.tellg();
			
			travelPackFile.seekg(getPosition + 12);
		}
	}


	travelPackFile.close();

	return allPacks;
}

vector<Client> getAllClients(string filename, vector<Pack> allPacks) {

	int numberClient = getFileSize(filename);
	
	int getPosition;
	
	vector<Client> allClients;
	
	ifstream clientFile(filename);

	if (is_fileEmpty(clientFile)) {
		createClient(allClients, allPacks);
	}
	else {

		removeNewLine(filename);

		if (clientFile.fail()) {
			cerr << "Error opening " << filename << "\n";
		}

		for (int i = 0; i < numberClient; i++) {
			allClients.push_back(readClientInformation(clientFile, allPacks));
			
			getPosition = clientFile.tellg();
			
			clientFile.seekg(getPosition + 12);
		}
	}

	clientFile.close();

	return allClients;
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::DELETING FUNCTIONS:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

void deleteClient(vector<Client>& allClients, int clientNumber) {

	cout << "Do you wish to delete the information of the client with VAT number " << allClients[clientNumber - 1].getVATnumber() << "?\n";
	cout << "Enter 1 if Yes or 0 if No: ";

	int response;

	cin >> response;

	if (response == 1) {
		allClients.erase(allClients.begin() + clientNumber - 1);
	}

	return;
}

void deletePack(vector<Pack>& allPacks, int travelPackNumber) {

	cout << "Do you wish to delete the information of the travel pack  " << allPacks[travelPackNumber - 1].getId() << "?\n";
	cout << "Enter 1 if Yes or 0 if No: ";

	int response;

	cin >> response;

	if (response == 1) {
		allPacks.erase(allPacks.begin() + travelPackNumber - 1);
	}

	return;
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::WRITING FUNCTIONS:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

void writeDate(Date date, ofstream& writeStream) {
	writeStream << date.getYear() << "/";
	writeStream << setw(2) << setfill('0') << date.getMonth() << "/" << setw(2) << setfill('0') << date.getDay() << endl;
}

void writeAddress(Address address, ofstream&  writeStream) {
	writeStream << address.getStreet() << " / " << address.getDoorNumber() << " / " << address.getFloor() << " / " << address.getPostalCode() << " / " << address.getLocation() << endl;
}

void writePacksBought(vector<string> v, ofstream& writeStream) {

	for (int i = 0; i < v.size(); i++) {
		if (i < v.size() - 1) {
			writeStream << v[i] << " ; ";
		}
		else {
			writeStream << v[i] << endl;
		}
	}
}

void writeTravelPacksDestinations(vector<string> v, ofstream& writeStream) {

	if (v.size() == 1) {
		writeStream << v[0] << endl;
	}
	else {
		writeStream << v[0] << " - ";

		for (int i = 1; i < v.size(); i++) {
			if (i < v.size() - 1) {
				writeStream << v[i] << ", ";
			}
			else {
				writeStream << v[i] << endl;
			}
		}
	}
}

void writeClientInformation(vector<Client> clients, ofstream& writeStream) {

	for (int i = 0; i < clients.size(); i++) {
		writeStream << clients[i].getName() << endl << clients[i].getVATnumber() << endl << clients[i].getFamilySize() << endl;
		writeAddress(clients[i].getAddress(), writeStream);
		
		for (int j = 0; j < clients[i].getPackList().size(); j++) {
			
			if (j != clients[i].getPackList().size() - 1) {
				writeStream << clients[i].getPackList()[j].getId() << " ; ";
			}
			else {
				writeStream << clients[i].getPackList()[j].getId() << endl ;
			}
			
		}

		writeStream << clients[i].getTotalPurchased() << endl;

		if (i != clients.size() - 1) {
			writeStream << "::::::::::" << endl;
		}

	}

}

void writeTravelPackInformation(vector<Pack> packs, ofstream& writeStream, int lastPackChanged) {

	writeStream << lastPackChanged << endl;

	for (int i = 0; i < packs.size(); i++) {
		writeStream << packs[i].getId() << endl;
		writeTravelPacksDestinations(packs[i].getSites(), writeStream);
		writeDate(packs[i].getBeginDate(), writeStream);
		writeDate(packs[i].getEndDate(), writeStream);
		writeStream << packs[i].getPricePerPerson() << endl << packs[i].getMaxPeople() << endl << packs[i].getPlacesSold() << endl;
		if (i != packs.size() - 1) {
			writeStream << "::::::::::" << endl;
		}
	}

	return;
}

void saveIntoFile( vector<Pack> travelPacks, string packFilename, vector<Client> clients, string clientFilename, int lastPackChanged) {
	ofstream travelPackWriteStream(packFilename, std::ofstream::out | std::ofstream::trunc);

	writeTravelPackInformation(travelPacks, travelPackWriteStream, lastPackChanged);

	ofstream clientWriteStream(clientFilename, std::ofstream::out | std::ofstream::trunc);

	writeClientInformation(clients, clientWriteStream);
}
