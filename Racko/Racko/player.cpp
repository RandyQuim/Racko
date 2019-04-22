#include "pch.h"
#include "player.hpp"
#include<iostream>

Player::Player()
{
	this->playerName = "";
	this->isComputer = false;
}

Player::Player(std::string name, Hand hand, bool isComputer)
{
	this->playerName = name;
	this->hand = hand;
	this->isComputer = isComputer;
}

void Player::SetName(std::string name)
{
	this->playerName = name;
}

void Player::SetHand(Hand hand)
{
	this->hand = hand;
}

void Player::SetIsComputer(bool isComputer)
{
	this->isComputer = isComputer;
}

std::string Player::TurnPrompt()
{
	return this->playerName + "'s turn";
}

std::string Player::ShowHand()
{
	return this->hand.ShowHand();
}

Card * Player::SwapOutCard(Card * card, int position)
{
	return this->hand.SwapOutCard(card, position);
}

bool Player::HasRacko()
{
	return this->hand.HasRacko();
}

std::string Player::GetName()
{
	return this->playerName;
}

bool Player::IsComputer()
{
	return this->isComputer;
}

std::string Player::MakeChoice(int discardedOption)
{
	if (hand.GetLowestCard()->GetValue() > discardedOption) {
		return "p";
	}
	int CARDS_IN_HAND = 10;
	int currentPos = 1;
	Card* currentCard = hand.GetLowestCard();
	int highestValue = 0; 
	while (currentPos < CARDS_IN_HAND) {
		highestValue = FindHighestValue(currentCard);
		if (FindPos(highestValue) == 10 && discardedOption > highestValue) {
			return "d";
		}
		if (highestValue < discardedOption) {
			return "p";
		}
		int cardDifference = currentCard->GetValue() - discardedOption;
		if (abs(cardDifference) < 4) {
			return "d";
		}
		++currentPos;
		currentCard = currentCard->GetNext();
	}
	return "p";
}

int Player::FindPos(int value)
{
	Card* currentCard = hand.GetLowestCard();
	int pos = 1;
	while (currentCard != nullptr) {
		if (currentCard->GetValue() == value)
			break;
		++pos;
		currentCard = currentCard->GetNext();
	}
	return pos;
}

Card * Player::InsertionSort(Card * currentCard)
{
	// Establish a temporary linked list with values from actual hand to sort
	Hand tmpHand;
	while (currentCard != nullptr) {
		tmpHand.AddToHand(new Card(currentCard->GetValue()));
		currentCard = currentCard->GetNext();
	}

	Card* next;
	Card* sorted = nullptr;
	Card* current = tmpHand.GetLowestCard();
	while (current != nullptr)
	{
		next = current->GetNext();
		SortedInsert(&sorted, current);
		current = next;
	}

	return sorted;
}

int Player::ProbeSortedHand(Card * currentSortedCard, int cardValue)
{
	Card* tmpNode;
	int cardPos = 1;
	while (currentSortedCard != nullptr) {
		if (currentSortedCard->GetValue() > cardValue) {
			if (IsPosInOrder(cardPos) && cardPos != 10) {  
				++cardPos;
				tmpNode = currentSortedCard;
				currentSortedCard = currentSortedCard->GetNext();
				delete tmpNode;
				continue;
			}
			break;
		}
		++cardPos;
		tmpNode = currentSortedCard;
		currentSortedCard = currentSortedCard->GetNext();
		delete tmpNode;
	}
	delete currentSortedCard;
	return cardPos;
}

int Player::ComputerChooseSlot(int cardValue) 
{
	int POSITION_OF_LAST_CARD_IN_HAND = 10;
	if (this->noPosForCardCount == 10) {
		if (this->numOfDumpedCards >= POSITION_OF_LAST_CARD_IN_HAND - 1) {
			this->numOfDumpedCards = 0;
			this->noPosForCardCount = 0;
			std::cout << "**Card Dump complete**" << std::endl;
			return POSITION_OF_LAST_CARD_IN_HAND;
		}
		return ++this->numOfDumpedCards % this->noPosForCardCount;
	}
	Card* currentCard = hand.GetLowestCard();
	int highestValue = FindHighestValue(currentCard);
	currentCard = hand.GetLowestCard();
	if (hand.GetLowestCard()->GetValue() > cardValue) {
		return 1;
	}
	if (FindPos(highestValue) == POSITION_OF_LAST_CARD_IN_HAND && cardValue > highestValue) {
		++this->noPosForCardCount;
		return -1;
	}
	if (highestValue < cardValue) { 
		return POSITION_OF_LAST_CARD_IN_HAND;
	}

	Card* sorted = InsertionSort(currentCard);
	int cardPos = ProbeSortedHand(sorted, cardValue);
	// The above code goes through each card in hand and checks for ordering relating to the drawn card.
	// If drawn card has no position in the hand it results in the code below, which checks the final
	// position for its order and increments noPosForCardCount when the final position is also in order.
	if (cardPos == POSITION_OF_LAST_CARD_IN_HAND && IsPosInOrder(cardPos)) {
		++this->noPosForCardCount;
		return -1;
	}
	this->noPosForCardCount = 0;
	return cardPos;	
}

int Player::FindHighestValue(Card* currentCard)
{
	int counter = 1;
	int maxValue = 0;
	while (currentCard != nullptr) {
		if (currentCard->GetValue() > maxValue) {
			maxValue = currentCard->GetValue();
		}
		++counter;
		currentCard = currentCard->GetNext();
	}
	currentCard = hand.GetLowestCard();
	return maxValue;
}

void Player::SortedInsert(Card** head, Card * newNode)
{
	Card* current;
	if (*head == NULL || (*head)->GetValue() >= newNode->GetValue())
	{
		newNode->SetNext(*head);
		*head = newNode;
	}
	else
	{
		current = *head;
		while (current->GetNext() != nullptr && current->GetNext()->GetValue() < newNode->GetValue())
		{
			current = current->GetNext();
		}
		newNode->SetNext(current->GetNext());
		current->SetNext(newNode);
	}
}

bool Player::IsPosInOrder(int tmpCardPos)
{
	Card* currentCard = hand.GetLowestCard();
	int handPos = 1;
	while (handPos != tmpCardPos && currentCard != nullptr) {
		++handPos;
		currentCard = currentCard->GetNext();
	}
	if (handPos != 10 && currentCard->GetValue() < currentCard->GetNext()->GetValue() && currentCard->GetValue() > currentCard->GetPrev()->GetValue()) {
		return true;                        
	}
	if (handPos == 10 && currentCard->GetValue() > currentCard->GetPrev()->GetValue()) {
		return true;
	}

	return false;
}