#include "pch.h"
#include "game.hpp"
#include<iostream>
#include<iomanip>

Game::Game(std::vector<Player> players)
{
	this->players = players;
	this->numberOfPlayers = players.size();
	this->currentRound = 0;
	this->currentPlayerTurn = 0;
	deck.MakeFullDeck();
	deck.Shuffle();
	for (int i = 0; i < numberOfPlayers; ++i) {
		Hand hand;
		for (int j = 0; j < 10; ++j) {
			hand.AddToHand(deck.Draw());
		}
		this->players.at(i).SetHand(hand);
	}
	
	Discard(deck.Draw());
}

void Game::DoNextTurn()
{
bool isComputer = players.at(currentPlayerTurn).IsComputer();
	OutputPlayerInfo(isComputer);		
	PlayerChoices(isComputer);
}

bool Game::IsGameOver()
{
	bool win = this->players.at(currentPlayerTurn).HasRacko();
	std::string name = GetPlayer(currentPlayerTurn + 1)->GetName();
	currentPlayerTurn = ++currentPlayerTurn % numberOfPlayers;
	if (currentPlayerTurn == 0) {
		++currentRound;
	}
	if (win) {
		std::cout << "\n*************************************" << std::endl;
		std::cout << "RRRRRRAAAAAAAACKO " << name << " won!!!" << std::endl;
		std::cout << "*************************************" << std::endl;
	}
	return win;
}

Player * Game::GetPlayer(int playerNumber)
{
	return &this->players.at(playerNumber - 1);
}

int Game::ShowTopOfDiscardPile()
{
	return discard.Peek();
}

Card * Game::DrawFromDeck()
{
	Card* card = deck.Draw();
	if (card == nullptr) {
		card = discard.Draw();
		while (card != nullptr) {
			deck.Push(card->GetValue());
			delete card;
			card = discard.Draw();
		}
		deck.Shuffle();
		return deck.Draw();
	}
	return card;
}

void Game::Discard(Card * card)
{
	discard.Discard(card);
}

void Game::OutputPlayerInfo(bool isComputer)
{
	std::string nextLine = "";
	if (isComputer) {
		std::cout << std::setfill('-') << std::setw(80) << std::endl;
		nextLine = "\n";
	}
	else {
		std::cout << std::setfill('#') << std::setw(80) << std::endl; 
		std::cout << "\nRound: " << currentRound << std::endl;
	}
	std::cout << nextLine << players.at(currentPlayerTurn).TurnPrompt() << std::endl;
	std::cout << "HAND:" << std::endl;
	std::cout << players.at(currentPlayerTurn).ShowHand() << std::endl;
	std::cout << "Available card in discard pile: " << ShowTopOfDiscardPile() << std::endl;
}

void Game::PlayerChoices(bool isComputer)
{
	std::string whichDeckDraw = "";
	int slotNumber = 0;
	Card* card;
	if (!isComputer) {
		std::cout << "Enter 'p' to get the card from the discard pile, or 'd' to draw the unknown card from the top of the deck: ";
		std::cin >> whichDeckDraw;
	}
	else {
		whichDeckDraw = players.at(currentPlayerTurn).MakeChoice(ShowTopOfDiscardPile());
		std::cout << whichDeckDraw << std::endl;
	}
	if (whichDeckDraw == "p") {
		card = discard.Draw();
	}
	else {
		card = DrawFromDeck();
	}
	std::cout << "Enter the slot number from the left edge of the display that you want to replace with " << card->GetValue() << ". Less than 1 simply discards the card: ";
	if (!isComputer) {
		std::cin >> slotNumber;
	}
	else {
		slotNumber = players.at(currentPlayerTurn).ComputerChooseSlot(card->GetValue());
		std::cout << slotNumber << std::endl;
	}
	if (slotNumber >= 1) {
		Discard(players.at(currentPlayerTurn).SwapOutCard(card, slotNumber));
	}
	else {
		Discard(card);
	}
}
