#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include "Pack.h"
#include "Client.h"

using namespace std;
/*
Converts Strings into integers
@param s a string, can only have numbers in it
*/
int string_to_int(string s);

/*
Converts an Integer into a String
*/
string int_to_string(int n);

/*
Removes blank space at both ends of the string
*/
void trimString(string& s);

/*
Splits a string based on a char and saves it into a string vector
@param s string that will be splitted
@param l char that will be used as a criteria to split the string, default blank space
@return v string vector where the splitted strings are*/
vector<string> splitString(string s, char l = ' ');

/*
Computes the number of packs or clients in the file
*/
int getFileSize(string filename);

void removeNewLine(string filename);

//Checks if a file is empty
bool is_fileEmpty(ifstream& pFile);

//Gets a Pack by the ID
Pack getPack(int packID, vector<Pack> packsList);

//Gets a Client by the VATnumber
Client getClient(int VATnumber, vector<Client> clientList);

//Gets a vector of Packs with a list of IDs;
vector<Pack> getPackList(vector<string> idList, vector<Pack> allPacks);

//Gets a vector of Clients with a list of VATnumber
vector<Client> getClientList(vector<int> VATnumberList, vector<Client> allClients);

//Gets the value of all the packs sold
int getPacksSold(vector<Client> allClients);

int getPackIDwithSite(string site, vector<Pack> allPacks);

//Gest a list of the n most sold places
void getMostSoldPlaces(vector<Pack> allPacks, int n, bool isDisplay, map<string, int> & sites);

void suggestPlace(vector<Client> allClients, map<string, int> sites, vector<Pack> allPacks);