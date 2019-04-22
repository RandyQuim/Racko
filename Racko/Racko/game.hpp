#pragma once
#ifndef GAME_HPP
#define GAME_HPP
#include<vector>
#include "player.hpp"
#include "deck.hpp"
#include "card.hpp"

class Game {
public:
	Game(std::vector<Player> players);
	void DoNextTurn();
	bool IsGameOver();
	Player* GetPlayer(int playerNumber);
	int ShowTopOfDiscardPile();
	Card* DrawFromDeck();
	void Discard(Card* card);

private:
	std::vector<Player> players;
	int numberOfPlayers;
	int currentPlayerTurn;
	int currentRound;
	Deck deck;
	Deck discard;
	void OutputPlayerInfo(bool isComputer);
	void PlayerChoices(bool isComputer);
 };

#endif