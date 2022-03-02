#include "Menus.h"


void alterPackInformation(vector<Pack>& v, int travelPackNumber, int& lastPackChanged) {
	cout << endl;
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
		cout << "The current ID saved is " << v[travelPackNumber - 1].getId() << ".\n";
		cout << "What do you wish to change it for? ";
		cin >> answer;
		v[travelPackNumber - 1].setId(answer);
	}
	//Alter the List of Places to Visit
	else if (answer == 2) {
		cout << "The current destination saved is ";
		v[travelPackNumber - 1].displayTravelPacksDestinations();
		cout << "What do you wish to change it for?(Use same format as before) ";

		cin.ignore(200, '\n');

		getline(cin, s);

		v[travelPackNumber - 1].setSites(readPlacesList(s));
	}
	//Alter the Initial Date
	else if (answer == 3) {
		cout << "The current initial date saved is ";

		v[travelPackNumber - 1].getBeginDate().print();

		cout << "What do you wish to change it for?(YYYY/MM/DD) ";

		cin >> s;

		v[travelPackNumber - 1].setBeginDate(readDate(s));
	}
	//Alter the Ending Date
	else if (answer == 4) {
		cout << "The current ending date saved is ";

		v[travelPackNumber - 1].getEndDate().print();

		cout << "What do you wish to change it for?(YYYY/MM/DD) ";

		cin >> s;

		v[travelPackNumber - 1].setEndDate(readDate(s));
	}
	//Alter the Price per Person
	else if (answer == 5) {
		cout << "The current price per person saved is " << v[travelPackNumber - 1].getPricePerPerson() << ".\n";
		cout << "What do you wish to change it for? ";
		cin >> answer;
		v[travelPackNumber - 1].setPricePerPerson(answer);
	}
	//Alter the Maximum Number of People
	else if (answer == 6) {
		cout << "The current maximum number of people is " << v[travelPackNumber - 1].getMaxPeople() << ".\n";
		cout << "What do you wish to change it for? ";
		cin >> answer;
		v[travelPackNumber - 1].setMaxPeople(answer);
	}
	//Alter the number of Places Sold
	else {
		cout << "The current of places sold are " << v[travelPackNumber - 1].getPlacesSold() << ".\n";
		cout << "What do you wish to change it for?(Use the same format as before) ";
		cin >> answer;
		v[travelPackNumber - 1].setPlacesSold(answer);
	}

	lastPackChanged = v[travelPackNumber - 1].getId();
}

void alterClientInformation(vector<Client>& v, int clientNumber, vector<Pack> allPacks) {
	cout << endl;
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
		cout << "The current name saved is " << v[clientNumber - 1].getName() << ".\n";
		cout << "What do you wish to change it for? ";
		getline(cin, s);
		v[clientNumber - 1].setName(s);
	}
	//Alters the NIF
	else if (answer == 2) {
		cout << "The current VATnumber saved is " << v[clientNumber - 1].getVATnumber() << ".\n";
		cout << "What do you wish to change it for? ";
		cin >> answer;
		v[clientNumber - 1].setVATnumber(answer);
	}
	//Alters the Number of Family Members
	else if (answer == 3) {
		cout << "The current number of Family members saved is " << v[clientNumber - 1].getFamilySize() << ".\n";
		cout << "What do you wish to change it for? ";
		cin >> answer;
		v[clientNumber - 1].setFamilySize(answer);
	}
	//Alters the Address
	else if (answer == 4) {
		cout << "The current address is set to ";
		v[clientNumber - 1].getAddress().print();
		cout << "What do you wish to change it for? ";
		cin >> s;
		v[clientNumber - 1].setAddress(readAddress(s));
	}

	else {
		cout << "The current bought packs are ";
		v[clientNumber - 1].displayPacksBought();
		cout << "What do you wish to change if for? (Use the same format as before) ";
		getline(cin, s);
		v[clientNumber - 1].setPackList(getPackList(splitString(s, ';'), allPacks));
	}

	return;
}

int askWhichClient(vector<Client>& clients, bool isDisplay) {

	cout << "Which Client do you want?\n";

	if (isDisplay) {
		cout << "0- Everyone   ";
	}

	for (int i = 0; i < clients.size(); i++) {
		if ((i + 1) % 3 != 0 || i == 0) {
			cout << i + 1 << " - " << clients[i].getName() << "   ";

			if (i == clients.size() - 1) {
				cout << endl;
			}
		}
		else {
			cout << i + 1 << " - " << clients[i].getName() << endl;
		}
	}

	int answer;

	cout << "Insert you input (-1 to go back): ";

	cin >> answer;

	return answer;
}

int askWhichTravelPack(vector<Pack>& travelPacks, bool isDisplay) {
	cout << endl;
	cout << "Which travel pack do you want?\n";

	if (isDisplay)
	{
		cout << "0- Everyone   ";
	}

	for (int i = 0; i < travelPacks.size(); i++) {
		if ((i + 1) % 3 != 0 || i == 0) {
			cout << i + 1 << " - " << travelPacks[i].getId() << "   ";

			if (i == travelPacks.size() - 1) {
				cout << endl;
			}
		}
		else {
			cout << i + 1 << " - " << travelPacks[i].getId() << endl;
		}
	}

	int answer;

	cout << "Insert you input (-1 to go back): ";

	cin >> answer;

	return answer;
}

void askUserWhatToDo(vector<Client>& allClients, vector<Pack>& allPacks, int& lastPackChanged) {

	cout << endl;
	cout << "What do you wish to do?\n";
	cout << "1- Alter a Pack    2- Alter a Client    3- Create a Pack\n";
	cout << "4- Create a Client 5- Delete a Pack     6- Delete a Client\n";
	cout << "7- Display Pack    8- Display Clients   9- Buy a Travel Pack\n";
	cout << "10- Packs Sold     11- Most Visited     12- Sites Recommendation\n";

	int answer;

	cout << "Insert you input: ";

	cin >> answer;

	int n;

	if (answer == 1) {
		n = askWhichTravelPack(allPacks, false);

		if (n == -1) {
			askUserWhatToDo(allClients, allPacks, lastPackChanged);
			return;
		}

		alterPackInformation(allPacks, n, lastPackChanged);
	}
	else if (answer == 2) {
		n = askWhichClient(allClients, false);

		if (n == -1) {
			askUserWhatToDo(allClients, allPacks, lastPackChanged);
			return;
		}

		alterClientInformation(allClients, n, allPacks);
	}
	else if (answer == 3) {
		createTravelPack(allPacks);
	}
	else if (answer == 4) {
		createClient(allClients, allPacks);
	}
	else if (answer == 5) {
		n = askWhichTravelPack(allPacks, false);

		if (n == -1) {
			askUserWhatToDo(allClients, allPacks, lastPackChanged);
			return;
		}

		deletePack(allPacks, n);
	}
	else if (answer == 6) {
		n = askWhichClient(allClients, false);

		if (n == -1) {
			askUserWhatToDo(allClients, allPacks, lastPackChanged);
			return;
		}

		deleteClient(allClients, n);
	}
	else if (answer == 7) {
		n = askWhichTravelPack(allPacks, true);

		if (n == 0) {
			for (int i = 0; i < allPacks.size(); i++) {
				allPacks[i].print();

				if (i != allPacks.size() - 1) {
					cout << "::::::::::\n";
				}
			}
		}
		else {
			allPacks[n - 1].print();
		}
		
	}
	else if (answer == 8) {
		n = askWhichClient(allClients, true);

		if (n == -1) {
			askUserWhatToDo(allClients, allPacks, lastPackChanged);
			return;
		}

		if (n == 0) {
			for (int i = 0; i < allClients.size(); i++) {
				allClients[i].print();

				if (i != allClients.size() - 1) {
					cout << "::::::::::\n";
				}
			}
		}
		else {
			allClients[n - 1].print();
		}

	}
	else if (answer == 9) {           
		n = askWhichClient(allClients, false);
		int p;
		p = askWhichTravelPack(allPacks, false);

		if (n == -1 || p == -1) {
			askUserWhatToDo(allClients, allPacks, lastPackChanged);
			return;
		}

		allClients[n - 1].buyPack(allPacks[n - 1].getId(), allPacks);
    
	}
	else if (answer == 10) {

		cout << "The agency as sold a total of " << getPacksSold(allClients) << " travel packs to " << allClients.size() << " clients.\n";
		
	}
	else if (answer == 11) {
		cout << "How many places do you want to see? ";
		int answer;
		cin >> answer;

		map<string, int> sites;

		getMostSoldPlaces(allPacks, answer, true, sites);
	}
	else {
		map<string, int> sites;

		getMostSoldPlaces(allPacks, answer, false, sites);

		suggestPlace(allClients, sites, allPacks);

	}

	return;
}





    
