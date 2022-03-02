#pragma once

#include "documentFunc.h"


void alterPackInformation(vector<Pack>& v, int travelPackNumber, int& lastPackChanged);

void alterClientInformation(vector<Client>& v, int clientNumber, vector<Pack> allPacks);

int askWhichClient(vector<Client>& clients, bool isDisplay);

int askWhichTravelPack(vector<Pack>& travelPacks, bool isDisplay);

void askUserWhatToDo(vector<Client>& allClients, vector<Pack>& allPacks, int& lastPackChanged);