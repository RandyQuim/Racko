#pragma once
#include "hand.hpp"

class Player {
public:
	Player();
	Player(std::string name, Hand hand, bool isComputer = false);
	void SetName(std::string name);
	void SetHand(Hand hand);
	void SetIsComputer(bool isComputer);
	std::string TurnPrompt();
	std::string ShowHand();
	Card* SwapOutCard(Card* card, int position);
	bool HasRacko();
	std::string GetName();
	bool IsComputer();
	std::string MakeChoice(int discardedOption);
	int ComputerChooseSlot(int cardValue);

private:
	std::string playerName;
	Hand hand;
	bool isComputer;
	int noPosForCardCount;
	int numOfDumpedCards;
	int FindHighestValue(Card* currentCard);
	void SortedInsert(Card** sorted, Card* current);
	bool IsPosInOrder(int cardPos);
	int FindPos(int value);
	Card* InsertionSort(Card* currentCard);
	int ProbeSortedHand(Card* sorted, int cardValue);
 };