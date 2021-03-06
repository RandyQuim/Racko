// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "player.hpp"
#include "game.hpp"
#include <iostream>
#include<vector>

using namespace std;

int main()
{
	std::vector<Player> players; 
	int numOfPlayers = 0;
	string name = "";
	int isComputer = 0;
	cout << "Get ready to play Racko" << endl;
	cout << "How many players (including computer, max 4): ";
	cin >> numOfPlayers;

	for (int i = 0; i < numOfPlayers; ++i) {
		cout << "Enter player number " << i + 1 << "'s name: ";
		cin >> name;
		Player player;
		player.SetName(name);
		cout << "Is this a computer?  Enter 1 for yes, 0 for no: ";
		cin >> isComputer;
		if (isComputer == 1) {
			player.SetIsComputer(true);
		}
		else {
			player.SetIsComputer(false);
		}
		players.push_back(player);
	}

	Game game(players);
	do {
		game.DoNextTurn();
	} while (!game.IsGameOver());  
}

