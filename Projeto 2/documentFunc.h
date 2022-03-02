#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

#include "Agency.h"


using namespace std; 

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::READING FUNCTIONS::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

Address readAddress(string s);

Date readDate(string s);

vector<string> readPlacesList(string s);

Client readClientInformation(ifstream& clientFile, vector<Pack> allPacks);

Pack readTravelPackInformation(ifstream& travelPackFile);


/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::CREATING FUNCTIONS:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

void createClient(vector<Client>& v, vector<Pack> allPacks);

void createTravelPack(vector<Pack>& v);

void createDoc(string filename);

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::GET FUNCTIONS:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/


//Return a vector with all the Packs that exist in a eile
vector<Pack> getAllPacks(string filename, int & lastPackChanged);

//Returns a Vector with all the Clients that exist in a file
vector<Client> getAllClients(string filename, vector<Pack> allPacks);

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::DELETING FUNCTIONS:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

void deleteClient(vector<Client>& allPacks, int clientNumber);

void deletePack(vector<Pack>&  allPacks, int travelPackNumber);

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::WRITING FUNCTIONS:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

void writeDate(Date date, ofstream& writeStream);

void writeAddress(Address address, ofstream&  writeStream);

void writePacksBought(vector<string> v, ofstream& writeStream);

void writeTravelPacksDestinations(vector<string> v, ofstream& writeStream);

void writeClientInformation(vector<Client> clients, ofstream& writeStream);

void writeTravelPackInformation(vector<Pack> packs, ofstream& writeStream, int lastPackChanged);

void saveIntoFile( vector<Pack> travelPacks, string packFilename, vector<Client> clients, string clientFilename, int lastPackChanged);