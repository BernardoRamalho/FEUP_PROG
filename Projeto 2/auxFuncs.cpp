#include "auxFuncs.h"


int string_to_int(string s) {
	istringstream instr(s);
	int n;
	instr >> n;
	return n;
}

string int_to_string(int n) {
	ostringstream outstr;
	outstr << n;
	return outstr.str();
}

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

vector<string> splitString(string s, char l) {
	vector<string> v;
	istringstream instr(s);
	string holder; //holds the string to put in the vector

	if (s.find(l) == -1) {
		cout << s << l << endl;
		cout << "Please introduce a value in the correct format: ";
		cin >> s;
		return splitString(s, l);
	}

	while (getline(instr, holder, l)) {

		trimString(holder);
		v.push_back(holder);
	}

	return v;
}

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

void removeNewLine(string filename) {

	std::ifstream ifs(filename);
	std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	return;
}

bool is_fileEmpty(ifstream& pFile){
	return pFile.peek() == ifstream::traits_type::eof();
}

Pack getPack(int packID, vector<Pack> packsList) {

	for (int i = 0; i < packsList.size(); i++) {

		if (packsList[i].getId() == packID) {
			return packsList[i];
		}
	}

	cout << "You introduce a invalid pack ID. Please input a valid one: ";
	cin >> packID;

	return getPack(packID, packsList);
}

Client getClient(int VATnumber, vector<Client> clientList) {

	for (int i = 0; i < clientList.size(); i++) {

		if (clientList[i].getVATnumber() == VATnumber) {

			return clientList[i];
		}
	}

	cout << "You introduce a invalid VAT number. Please input a valid one: ";
	cin >> VATnumber;

	return getClient(VATnumber, clientList);

}

vector<Pack> getPackList(vector<string> idList, vector<Pack> allPacks) {
	
	vector<Pack> packList;

	for (int i = 0; i < idList.size(); i++) {

		packList.push_back(getPack(string_to_int(idList[0]), allPacks));

	}

	return packList;
}

vector<Client> getClientList(vector<int> VATnumberList, vector<Client> allClients) {

	vector<Client> clientList;

	for (int i = 0; i < VATnumberList.size(); i++) {

		clientList.push_back( getClient(VATnumberList[i], allClients) );

	}

	return clientList;
}

int getPacksSold(vector<Client> allClients) {
	int total = 0;

	for (int i = 0; i < allClients.size(); i++) {
		total += allClients[i].getPackList().size();
	}

	return total;
}

int getPackIDwithSite(string site, vector<Pack> allPacks) {
	
	vector <string> packSites;

	for (int i = 0; i < allPacks.size(); i++) {
		packSites = allPacks[i].getSites();
		if (find(packSites.begin(), packSites.end(), site) != packSites.end()) {
			return allPacks[i].getId();
		}
	}

	cout << "There are no packs that go to " << site << ".\n" << "Introduce a valid site: ";

	cin.ignore(200, '\n');

	getline(cin, site);

	return getPackIDwithSite(site, allPacks);
}

vector<string> getSitesList(Client client) {

	vector<Pack> clientPacks = client.getPackList();
	vector<string> packSites;
	vector<string> sitesList;

	for (int i = 0; i < clientPacks.size(); i++) {

		packSites = clientPacks[i].getSites();

		for (int j = 0; j < packSites.size(); j++) {
			
			sitesList.push_back(packSites[i]);
			
		}
	}

	return sitesList;
}

void getMostSoldPlaces(vector<Pack> allPacks, int n, bool isDisplay, map<string, int> & sites) {

	vector<pair<string, int>> orderedSites;

	orderedSites.reserve(sites.size());

	for (int i = 0; i < allPacks.size(); i++) {

		vector<string> holder = allPacks[i].getSites();

		for (int j = 0; j < holder.size(); j++) {

			if (sites.find(holder[j]) == sites.end()) {
				sites[holder[j]] = allPacks[i].getPlacesSold();
			}
			else {
				sites[holder[j]] += allPacks[i].getPlacesSold();
			}
		}
	}

	for (auto itr = sites.begin(); itr != sites.end(); itr++) {
		orderedSites.push_back(*itr);
	}

	sort(orderedSites.begin(), orderedSites.end(), [](pair<string, int>& a, pair<string, int>& b)
	{
		return a.second > b.second;
	});

	if (isDisplay == true) {
		for (int k = 0; k < n; k++) {

			if (orderedSites[k].second != 1) {
				cout << k + 1 << " -- " << orderedSites[k].first << " with " << orderedSites[k].second << " visits.\n";
			}
			else {
				cout << k + 1 << " -- " << orderedSites[k].first << " with " << orderedSites[k].second << " visit.\n";
			}
			
		}
	}
}

void suggestPlace(vector<Client> allClients, map<string, int> sites, vector<Pack> allPacks) {

	vector<string> clientSites;

	vector<pair<string, int>> orderedSites;

	for (auto itr = sites.begin(); itr != sites.end(); itr++) {
		orderedSites.push_back(*itr);
	}

	for (int i = 0; i < allClients.size(); i++) {

		clientSites = getSitesList(allClients[i]);

			for (int j = 0; j < orderedSites.size(); i++) {
				if (find(clientSites.begin(),clientSites.end(), orderedSites[j].first) == clientSites.end()) {
					cout << "The client named " << allClients[i].getName() << " didn't go to " << orderedSites[j].first << " , which is a part of the pack with ID " << getPackIDwithSite(orderedSites[j].first, allPacks) << ".\n";
					break;
				}
			}
	}
}