#include "pch.h"
#include "deck.hpp"
#include <stdlib.h> 
#include<time.h> 

#include<iostream>

Deck::Deck()
{
	this->top = nullptr;
	this->numberOfCardsInDeck = 0; 
}

Deck::~Deck()
{
	/*Card* currentCard = top;
	Card* next;
	while (currentCard != nullptr) {
		next = currentCard->GetNext();
		delete currentCard;
		currentCard = next;
	}
	top = nullptr; */
}

void Deck::MakeFullDeck()
{
	while (numberOfCardsInDeck < NUMBER_OF_CARDS_IN_RACKO_DECK) {
		Push(numberOfCardsInDeck + 1);
	}
}

void Deck::Push(int value)  
{
	if (numberOfCardsInDeck + 1 > NUMBER_OF_CARDS_IN_RACKO_DECK) {
		std::cout << "There are no more cards to add to the deck!" << std::endl;
	}
	else {
		Card* newCard = new Card(value);
		if (this->top == nullptr) {
			this->top = newCard;
			++numberOfCardsInDeck;
		}
		else {
			newCard->SetNext(this->top);
			this->top = newCard;
			++numberOfCardsInDeck;
		}
	}
}

void Deck::Discard(Card * card)
{
	if (numberOfCardsInDeck > NUMBER_OF_CARDS_IN_RACKO_DECK) {
		std::cout << "There are no more cards to add to the dicard pile!" << std::endl;
	}
	else {
		if (this->top == nullptr) {
			this->top = card;
			++numberOfCardsInDeck;
		}
		else {
			card->SetNext(this->top);
			this->top = card;
			++numberOfCardsInDeck;
		}
	}
}

Card * Deck::Draw()
{
	if (numberOfCardsInDeck == 0) {
		return nullptr;
	}
	Card* nodeToDelete = this->top;
	Card* drawCard = new Card(this->top->GetValue());
	this->top = this->top->GetNext();
	delete nodeToDelete;
	--numberOfCardsInDeck;
	return drawCard;
}

int Deck::Peek()
{
	if (this->top == nullptr) {
		return -1;
	}
	return this->top->GetValue();
}

void Deck::Shuffle()
{
	int countTwice = -59;
	srand(time(0));
	int randomInt = 0;
	while (countTwice <= numberOfCardsInDeck) {    
		randomInt = rand() % (numberOfCardsInDeck - 1) + 1;
		if (!(IsInDeck(randomInt)) || (numberOfCardsInDeck == NUMBER_OF_CARDS_IN_RACKO_DECK)) {
			Card* card = Draw();
			InsertAt(card, randomInt);
			++countTwice;
		}
	}
}

void Deck::InsertAt(Card * card, int index)
{
	if (CheckBounds(index)) {
		if (index == 1) {
			Push(card->GetValue());
			delete card;
			return;
		}
		
		int currentPosition = 1;
		Card* currentCard = this->top;
		if (index == numberOfCardsInDeck) {
			while (currentCard->GetNext() != NULL) {
				currentCard = currentCard->GetNext();
			}
			currentCard->SetNext(card);
			++numberOfCardsInDeck;
			return;
		}
	
		while (currentPosition != index - 1) {
			currentPosition++;
			currentCard = currentCard->GetNext();
		}
	
		card->SetNext(currentCard->GetNext());  
		currentCard->SetNext(card);
		++numberOfCardsInDeck;
	}
}

bool Deck::CheckBounds(int index)
{
	if (index < 1 || index > numberOfCardsInDeck) {
		std::cout << "That index does not exist!" << std::endl;
		return false;
	}
	if (numberOfCardsInDeck == NUMBER_OF_CARDS_IN_RACKO_DECK || numberOfCardsInDeck == 40) {
		std::cout << "There are already the max cards in the deck!" << std::endl;
		return false;
	}
	return true;
}

bool Deck::IsInDeck(int randInt)
{
	int currentPosition = 0;
	Card* currentCard = this->top;
	while (currentCard != nullptr) {
		if (currentCard->GetValue() == randInt) {
			return true;
		}
		currentCard = currentCard->GetNext();
		++currentPosition;   
	}
	return false;  
}