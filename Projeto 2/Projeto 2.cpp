// Projeto 2.cpp : Defines the entry point for the console application.
//


#include "Menus.h"

using namespace std;

int main()
{

	cout << "Welcome!\n";
	cout << "Input the agency filename (filename.txt): ";

	
	string filename;
	cin >> filename;

	int lastPackChanged = 0;

	Agency agency(filename, lastPackChanged);

	vector<Client> allClients = agency.getClients();

	vector<Pack> allPacks = agency.getPacks();

	while (true) {
		askUserWhatToDo(allClients, allPacks, lastPackChanged);

		cout << endl;
		cout << "Do you wish to do anything else?(1 if yes, 0 if no) ";

		int s;

		cin >> s;

		if (s == 0) {
			cout << "Have a nice day! Press enter to close the program." << endl;
			system("PAUSE");
			break;
		}
	}

	saveIntoFile(allPacks, agency.getPacksFilename(), allClients, agency.getClientsFilename(), lastPackChanged);

    return 0;
}

