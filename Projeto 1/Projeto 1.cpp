// Projeto 1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::STRUCTS:::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/
struct Date {
	int year;
	int month;
	int day;
};

struct Address {
	string streetName;
	int doorNumber;
	string floorNumber;
	string postalCode;
	string district;
};

struct Agency {
	string name;
	int NIF;
	string URL;
	Address address;
	string clientsFile;
	string packsFile;
};

struct Client {
	string name;
	int NIF;
	int numberFamilyMembers;
	Address address;
	vector<string> packsBought;
};

struct TravelPack {
	int ID;
	vector<string> placesVisit;
	Date initDate;
	Date endDate;
	int pricePerPerson;
	int MaxPeople;
	int placesSold;
};

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::AUXILIARY FUNCTIONS::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

/*
Converts Strings into integers
@param s a string, can only have numbers in it
*/
int string_to_int(string s) {
	istringstream instr(s);
	int n;
	instr >> n;
	return n;
}

/*
Converts an Integer into a String
*/
string int_to_string(int n) {
	ostringstream outstr;
	outstr << n;
	return outstr.str();
}

/*
Removes blank space at both ends of the string
*/
void trimString(string& s) {

	if (s[0] == ' ')
	{
		s.erase(0, s.find_first_not_of(' '));
	}
	if (s[s.length() - 1] == ' ')
	{
		s.erase(s.length() - 1, 1);
	}

	return;
}

/*
Splits a string based on a char and saves it into a string vector
@param s string that will be splitted
@param l char that will be used as a criteria to split the string, default blank space
@return v string vector where the splitted strings are*/
vector<string> splitString(string s, char l = ' ') {
	vector<string> v;
	istringstream instr(s);
	string holder; //holds the string to put in the vector

	while (getline(instr, holder, l)) {
		
		trimString(holder);
		v.push_back(holder);
	} 

	return v;
}

/*
	Computes the number of packs or clients in the file
*/
int getFileSize(string filename) {

	ifstream openFile(filename);
	string holder;
	int n = 0;

	while (getline(openFile, holder)) {
		if (holder == "::::::::::") {
			n++;
		}
	}

	return n + 1;
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::READING FUNCTIONS::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

/*
Reads the name of the file containing the information of an Agency
@return the filename
*/
string readAgencyFileName() {
	string fileName;

	cout << "What's the name of the agency file (fileName.txt)? ";

	cin >> fileName;

	return fileName;
}

/*
Takes the information in a string and converts it into an Address Object
@param s string that contains the information
@return address where the information of the string is stored
*/
Address readAddress(string s) {
	Address address;
	vector<string> addressInformation;

	addressInformation = splitString(s, '/');

	address.streetName = addressInformation[0];

	address.doorNumber = string_to_int(addressInformation[1]);

	address.floorNumber = addressInformation[2];

	address.postalCode = addressInformation[3];

	address.district = addressInformation[4];

	return address;
}

Date readDate(string s) {
	Date date;

	vector<string> holder = splitString(s, '/');

	date.year = string_to_int(holder[0]);
	date.month = string_to_int(holder[1]);
	date.day = string_to_int(holder[2]);

	return date;
}

/*
	Read the information of the list of places and saves it into a vector
*/
vector<string> readPlacesList(string s) {

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

/*
Takes the information of an agency and stores it in an object of type Agency
@param filename, name of the file where the information is stored
@return agencyInformation
*/
Agency readAgencyInformation(string filename) {

	ifstream agencyFile;

	agencyFile.open(filename);

	if (agencyFile.fail())
	{
		//cerr << "Error opening " << filename << "\n";
		cout << "Please give a correct filename: ";
		cin >> filename;
		return readAgencyInformation(filename);
	}

	Agency agencyInformation;

	getline(agencyFile, agencyInformation.name);

	string documentInformation;	//Variable to get information that is not supposed to be a string					

	getline(agencyFile, documentInformation);

	agencyInformation.NIF = string_to_int(documentInformation);

	getline(agencyFile, agencyInformation.URL);

	getline(agencyFile, documentInformation);

	agencyInformation.address = readAddress(documentInformation);

	getline(agencyFile, agencyInformation.clientsFile);

	getline(agencyFile, agencyInformation.packsFile);

	agencyFile.close();

	return agencyInformation;
}

/*
Takes the information of a client and stores it in an object of type Client
@param filename, name of the file where the information is stored
@return Client Information
*/
Client readClientInformation(string filename, ifstream& clientFile) {

	Client client;

	getline(clientFile, client.name);

	string documentInformation;	//Variable to get information that is not supposed to be a string	

	getline(clientFile, documentInformation);

	client.NIF = string_to_int(documentInformation);

	getline(clientFile, documentInformation);

	client.numberFamilyMembers = string_to_int(documentInformation);

	getline(clientFile, documentInformation);

	client.address = readAddress(documentInformation);

	getline(clientFile, documentInformation);

	client.packsBought = splitString(documentInformation, ';');

	return client;
}

/*
Takes the information of a Travel Pack and stores it in an object of type TravelPack
@param filename, name of the file where the information is stored
@return Travel Pack Information
*/
TravelPack readTravelPackInformation(string filename, ifstream& travelPackFile) {

	string documentInformation;	//Variable to get information that is not supposed to be a string	

	getline(travelPackFile, documentInformation);

	TravelPack travelPack;

	travelPack.ID = string_to_int(documentInformation);

	getline(travelPackFile, documentInformation);

	travelPack.placesVisit = readPlacesList(documentInformation);

	getline(travelPackFile, documentInformation);

	travelPack.initDate = readDate(documentInformation);

	getline(travelPackFile, documentInformation);

	travelPack.endDate = readDate(documentInformation);

	getline(travelPackFile, documentInformation);

	travelPack.pricePerPerson = string_to_int(documentInformation);

	getline(travelPackFile, documentInformation);

	travelPack.MaxPeople = string_to_int(documentInformation);

	getline(travelPackFile, documentInformation);

	travelPack.placesSold = string_to_int(documentInformation);

	return travelPack;
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::SAVING FUNCTIONS::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

vector<TravelPack> saveTravelPackInformation(string filename) {
	int numberPacks = getFileSize(filename);
	int getPosition;
	vector<TravelPack> v;
	ifstream travelPackFile(filename);

	travelPackFile.seekg(3);

	for (int i = 0; i < numberPacks; i++) {
		v.push_back(readTravelPackInformation(filename, travelPackFile));
		getPosition = travelPackFile.tellg();
		travelPackFile.seekg(getPosition+12);
	}

	travelPackFile.close();

	return v;
}

vector<Client> saveClientInformation(string filename) {
	int numberClient = getFileSize(filename);
	int getPosition;
	vector<Client> v;
	ifstream clientFile(filename);

	if (clientFile.fail()) {
	cerr << "Error opening " << filename << "\n";
	}

	for (int i = 0; i < numberClient; i++) {
		v.push_back(readClientInformation(filename, clientFile));
		getPosition = clientFile.tellg();
		clientFile.seekg(getPosition + 12);
	}

	clientFile.close();

	return v;
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::DELETING FUNCTIONS:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

void deleteClient(vector<Client>& v, int clientNumber) {

	cout << "Do you wish to delete the information of the client named " << v[clientNumber].name << "?\n";
	cout << "Enter 1 if Yes or 0 if No: ";
	
	int response;

	cin >> response;

	if (response == 1) {
		v.erase(v.begin()+clientNumber);
	}
	else {
		//adicionar a função de perguntar o que o user quer fazer
	}
	
	return;
}

void deleteTravelPack(vector<TravelPack>& v, int travelPackNumber) {

	cout << "Do you wish to delete the information of the travel pack  " << v[travelPackNumber].ID << "?\n";
	cout << "Enter 1 if Yes or 0 if No: ";

	int response;

	cin >> response;

	if (response == 1) {
		v.erase(v.begin() + travelPackNumber);
	}
	else {
		//adicionar a função de perguntar o que o user quer fazer
	}

	return;
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::DISPLAYING FUNCTIONS::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

void displayDate(Date date) {
	cout << date.year << "/";
	cout << setw(2) << setfill('0') << date.month << "/" << setw(2) << setfill('0') << date.day << endl;
}

void displayAddress(Address address) {
	cout << address.streetName << " / " << address.doorNumber << " / " << address.floorNumber << " / " << address.postalCode << " / " << address.district << endl;
}

void displayPacksBought(vector<string> v) {

	for (int i = 0; i < v.size(); i++) {
		if (i < v.size() - 1) {
			cout << v[i] << " ; ";
		}
		else {
			cout << v[i] << endl;
		}
	}
}

void displayTravelPacksDestinations(vector<string> v) {
	
	if (v.size() == 1) {
		cout << v[0] << endl;
	}
	else {
		cout << v[0] << " - ";

		for (int i = 1; i < v.size(); i++) {
			if (i < v.size() - 1) {
				cout << v[i] << ", ";
			}
			else {
				cout << v[i] << endl;
			}
		}
	}
}

void displayAgencyInformation(Agency agency){

	cout << agency.name << endl << agency.NIF << endl << agency.URL << endl << agency.address.streetName << " / " << agency.address.doorNumber << " / " << agency.address.floorNumber << " / " << agency.address.postalCode << " / " << agency.address.district << endl << agency.clientsFile << endl << agency.packsFile << endl;
}

void displayClientInformation(vector<Client> clients, int clientNumber = 0) {

	if (clientNumber == 0) {	// If 0 then the user chose to see the information of all the clients
		for (int i = 0; i < clients.size(); i++) {
			cout << clients[i].name << endl << clients[i].NIF << endl;
			displayAddress(clients[i].address);
			displayPacksBought(clients[i].packsBought);
			if (i != clients.size() - 1) {
				cout << "::::::::::" << endl;
			}
		}
	}
	else {
		cout << clients[clientNumber-1].name << endl << clients[clientNumber-1].NIF << endl;  //Since the vector starts at indice 0 then you have to -1 the clientNumber
		displayAddress(clients[clientNumber-1].address);
		displayPacksBought(clients[clientNumber-1].packsBought);
	}
}

void displayTravelPackInformation(vector<TravelPack> travelPacks, int travelPackNumber = 0) {

	if (travelPackNumber == 0) {
		for (int i = 0; i < travelPacks.size(); i++) {
			cout << travelPacks[i].ID << endl;
			displayTravelPacksDestinations(travelPacks[i].placesVisit);
			displayDate(travelPacks[i].initDate);
			displayDate(travelPacks[i].endDate);
			cout << travelPacks[i].pricePerPerson << endl << travelPacks[i].MaxPeople << endl << travelPacks[i].placesSold << endl;
			if (i != travelPacks.size() - 1) {
				cout << "::::::::::" << endl;
			}
		}
	}
	else {
		cout << travelPacks[travelPackNumber].ID << endl;
		displayTravelPacksDestinations(travelPacks[travelPackNumber].placesVisit);
		displayDate(travelPacks[travelPackNumber].initDate);
		displayDate(travelPacks[travelPackNumber].endDate);
		cout << travelPacks[travelPackNumber].pricePerPerson << endl << travelPacks[travelPackNumber].MaxPeople << endl << travelPacks[travelPackNumber].placesSold << endl;

	}
	return;
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::ALTERING FUNCTIONS:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

void alterAddress(Address& address) {
	cout << "Which address atribbute do you which to alter?\n";
	cout << "1- Street Name    " <<  "2- Door Number    " << "3- Floor Number\n";
	cout << "4- Postal Code    " << "5- District\n";
	cout << "Enter the number here: ";

	int answer;

	cin >> answer;
	cin.ignore(200, '\n');

	//Alters the Street Name
	if (answer == 1) {
		cout << "The current Street Name saved is " << address.streetName << ".\n";
		cout << "What do you wish to change it for? ";
		getline(cin,address.streetName);
	}
	//Alters the Door Number
	else if (answer == 2) {
		cout << "The current Door Number saved is " << address.doorNumber << ".\n";
		cout << "What do you wish to change it for? ";
		cin >> address.doorNumber;
	}
	//Alters the Floor Nubmer
	else if (answer == 3) {
		cout << "The current number of Floor Number saved is " << address.floorNumber << ".\n";
		cout << "What do you wish to change it for? ";
		cin >> address.floorNumber;
	}
	//Alters the Postal Code
	else if (answer == 4) {
		cout << "The current Postal Code saved is " << address.postalCode << ".\n";;
		cout << "What do you wish to change it for? ";
		getline(cin, address.postalCode);
	}
	//Alters the District
	else {
		cout << "The current district is " << address.district << ".\n";
		cout << "What do you wish to change it for? ";
		getline(cin, address.district);
	}
}

void alterClientInformation(vector<Client>& v, int clientNumber) {
	cout << "Which atribbute do you which to alter?\n";
	cout << "1- Name    " << "2- NIF    " << "3- Nº Family Members\n";
	cout << "4- Address    " << "5- Packs Bought\n";
	cout << "Enter the number here: ";

	int answer;
	string s;

	cin >> answer;
	cin.ignore(200, '\n');

	//Alters the Street Name
	if (answer == 1) {
		cout << "The current name saved is " << v[clientNumber].name << ".\n";
		cout << "What do you wish to change it for? ";
		getline(cin, v[clientNumber].name);
	}
	//Alters the NIF
	else if (answer == 2) {
		cout << "The current NIF saved is " << v[clientNumber].NIF << ".\n";
		cout << "What do you wish to change it for? ";
		cin >> v[clientNumber].NIF;
	}
	//Alters the Number of Family Members
	else if (answer == 3) {
		cout << "The current number of Family members saved is " << v[clientNumber].numberFamilyMembers << ".\n";
		cout << "What do you wish to change it for? ";
		cin >> v[clientNumber].numberFamilyMembers;
	}
	//Alters the Address
	else if (answer == 4) {
		alterAddress(v[clientNumber].address);
	}
	//Alters the list of packs bought
	else {
		cout << "The current bought packs are ";
		displayPacksBought(v[clientNumber].packsBought);
		cout << "What do you wish to change if for?(Use the same format as before) ";
		getline(cin, s);
		v[clientNumber].packsBought = splitString(s, ';');
	}

	return;
}

void alterTravelPackInformation(vector<TravelPack>& v, int travelPackNumber) {
	cout << "Which atribbute do you which to alter?\n";
	cout << "1- ID    " << "2- Places to Visit    " << "3- Initial Date\n";
	cout << "4- Ending Date    " << "5- Prices per Person    " << "6- Total Spots\n";
	cout << "7- Spots Sold\n";
	cout << "Enter the number here: ";

	int answer;
	string s;

	cin >> answer;

	//Alter the ID of the Pack
	if (answer == 1) {
		cout << "The current ID saved is " << v[travelPackNumber].ID << ".\n";
		cout << "What do you wish to change it for? ";
		cin >> v[travelPackNumber].ID;
	}
	//Alter the List of Places to Visit
	else if (answer == 2) {
		cout << "The current destination saved is ";
		displayTravelPacksDestinations(v[travelPackNumber].placesVisit);
		cout << "What do you wish to change it for?(Use same format as before) ";

		cin.ignore(200, '\n');

		getline(cin,s);

		v[travelPackNumber].placesVisit = readPlacesList(s);
	}
	//Alter the Initial Date
	else if (answer == 3) {
		cout << "The current initial date saved is ";

		displayDate(v[travelPackNumber].initDate);

		cout << "What do you wish to change it for?(YYYY/MM/DD) ";

		cin >> s;

		v[travelPackNumber].initDate = readDate(s);
	}
	//Alter the Ending Date
	else if (answer == 4) {
		cout << "The current ending date saved is ";

		displayDate(v[travelPackNumber].endDate);

		cout << "What do you wish to change it for?(YYYY/MM/DD) ";

		cin >> s;

		v[travelPackNumber].endDate = readDate(s);
	}
	//Alter the Price per Person
	else if (answer == 5) {
		cout << "The current price per person saved is " << v[travelPackNumber].pricePerPerson << ".\n";
		cout << "What do you wish to change it for? ";
		cin >> v[travelPackNumber].pricePerPerson;
	}
	//Alter the Maximum Number of People
	else if (answer == 6) {
		cout << "The current maximum number of people is " << v[travelPackNumber].MaxPeople << ".\n";
		cout << "What do you wish to change it for? ";
		cin >> v[travelPackNumber].MaxPeople;
	}
	//Alter the number of Places Sold
	else {
		cout << "The current of places sold are " << v[travelPackNumber].placesSold << ".\n";
		cout << "What do you wish to change it for?(Use the same format as before) ";
		cin >> v[travelPackNumber].placesSold;
	}
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::CREATING FUNCTIONS:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

void createClient(vector<Client>& v) {

	Client newClient;
	
	string answer;

	cout << "Please insert the information of the new Client:\n";

	//Asking for the name of the new Client
	cout << "Name - ";
	
	cin.ignore(200, '\n');

	getline(cin, answer);

	newClient.name = answer;

	//Asking the NIF of the new Client
	cout << "NIF - ";

	cin >> newClient.NIF;

	if (cin.fail() || int_to_string(newClient.NIF).length() != 9) {
		cerr << "Invalid input for NIF\n";
		cout << "Please introduce a valid integer with 9 characters: ";
		cin >> newClient.NIF;
	}

	//Asking the number of Family Members of the new Client
	cout << "Family Members - ";

	cin >> newClient.numberFamilyMembers;

	//Asking the Address of the new Client
	cout << "Address (Street Name / Door Number / Floor Number ( '-' if you don't have) / Postal Code / District) - ";

	cin.ignore(200, '\n');

	getline(cin, answer);

	newClient.address = readAddress(answer);

	//Asking which Packs the new Client has bought
	cout << "Packs Bougt (format Pack1 ; Pack2 ; Pack3) - ";
	
	getline(cin, answer);

	newClient.packsBought = splitString(answer, ';');

	//Saving all the information into the clients vector
	v.push_back(newClient);

	return;
}

void createTravelPack(vector<TravelPack>& v) {

	TravelPack newTravelPack;

	string answer;

	cout << "Please insert the information of the new Travel Pack:\n";

	//Asking for the New ID
	cout << "ID - ";

	cin >> newTravelPack.ID;

	//Asking for the Places that the new Travel Pack will visit
	cout << "Places to Visit (Main place - Place1, Place2) - ";

	cin.ignore(200, '\n');

	getline(cin, answer);

	newTravelPack.placesVisit = readPlacesList(answer);

	//Asking the beginning date of the travel
	cout << "Beginning Date (YYYY/MM/DD) - ";

//	cin.ignore(200, '\n');

	getline(cin, answer);

	newTravelPack.initDate = readDate(answer);

	//Asking the ending date of the travel
	cout << "Ending Date (YYYY/MM/DD) - ";

	//cin.ignore(200, '\n');

	getline(cin, answer);

	newTravelPack.endDate = readDate(answer);

	//Asking the price per person of the pack
	cout << "Price Per Person - ";

	cin >> newTravelPack.pricePerPerson;

	//Asking the total amount of people that can go on the travel
	cout << "Maximum Number of People - ";

	cin >> newTravelPack.MaxPeople;

	//Asking the number of spots that can still be sold
	cout << "Available Spots - ";

	cin >> newTravelPack.placesSold;

	//Saving the information into the travel Packs vector
	v.push_back(newTravelPack);

}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::USER INPUT FUNCTIONS:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

int askWhichClient(vector<Client>& clients) {
	
	cout << "Which Client do you want?\n";
	cout << "0- Everyone   ";
	for (int i = 0; i < clients.size(); i++) {
		if ((i+1) % 3 != 0 || i == 0) {
			cout << i+1 << " - " << clients[i].name << "   ";
		}
		else {
			cout << i+1 << " - " << clients[i].name << endl;
		}
	}

	int answer;

	cout << "Insert you input: ";

	cin >> answer;

	return answer;
}

int askWhichTravelPack(vector<TravelPack>& travelPacks) {
	cout << endl;
	cout << "Which Client do you want?\n";
	cout << "0- Everyone   ";

	for (int i = 0; i < travelPacks.size(); i++) {
		if ((i + 1) % 3 != 0 || i == 0) {
			cout << i + 1 << " - " << travelPacks[i].ID << "   ";
		}
		else {
			cout << i + 1 << " - " << travelPacks[i].ID << endl;
		}
	}

	int answer;

	cout << "Insert you input: ";

	cin >> answer;

	return answer;
}

void askUserWhatToDo(vector<Client>& clients, vector<TravelPack>& travelPacks) {

	cout << endl;
	cout << "What do you wish to do?\n";
	cout << "1- Alter a Pack    2- Alter a Client    3- Create a Pack\n";
	cout << "4- Create a Client 5- Delete a Pack     6- Delete a Client\n";

	int answer;

	cout << "Insert you input: ";

	cin >> answer;

	int n;

	if (answer == 1) {
		n = askWhichTravelPack(travelPacks);
		alterTravelPackInformation(travelPacks, n);
	}
	else if (answer == 2) {
		n = askWhichClient(clients);
		alterClientInformation(clients, n);
	}
	else if (answer == 3) {
		createTravelPack(travelPacks);
	}
	else if (answer == 4) {
		createClient(clients);
	}
	else if (answer == 5) {
		n = askWhichTravelPack(travelPacks);
		alterTravelPackInformation(travelPacks, n);
	}
	else {
		n = askWhichClient(clients);
		alterClientInformation(clients, n);
	}
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::MAIN FUNCTION::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/
int main() {

	string agencyFileName = readAgencyFileName();
	Agency agency = readAgencyInformation(agencyFileName);
	vector<Client> clients = saveClientInformation(agency.clientsFile);
	vector<TravelPack> travelPacks = saveTravelPackInformation(agency.packsFile);

	/*displayAgencyInformation(agency);
	cout << endl;
	displayClientInformation(clients);
	cout << endl;
	displayTravelPackInformation(travelPacks);
	*/

	/*createTravelPack(travelPacks);
	displayTravelPackInformation(travelPacks);
	*/
	askUserWhatToDo(clients, travelPacks);
	displayClientInformation(clients);
	system("PAUSE");
	return 0;
}