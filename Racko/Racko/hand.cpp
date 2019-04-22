#include "pch.h"
#include "hand.hpp"
#include<string>
#include<iomanip>
#include<sstream>

#include<iostream>

Hand::Hand()
{
	lowestCard = nullptr;
}

Hand::~Hand()
{
	/*Card* currentCard = lowestCard;
	std::cout << "Desturtor" << std::endl;
	while (currentCard != nullptr) {
		lowestCard = lowestCard->GetNext();
		delete currentCard;
		currentCard = lowestCard;
	}

	lowestCard = nullptr;*/
}

void Hand::AddToHand(Card * card)
{
	if (this->lowestCard == nullptr) {
		this->lowestCard = card;
	}
	else {
		card->SetNext(this->lowestCard);
		this->lowestCard->SetPrev(card);
		this->lowestCard = card;
	}
}

Card * Hand::SwapOutCard(Card * card, int position)
{
	if (position == 1) {
		Card* discardedCard = this->lowestCard;
		card->SetNext(this->lowestCard->GetNext());
		this->lowestCard->GetNext()->SetPrev(card);
		this->lowestCard = card;
		return discardedCard;
	}
	int currentPosition = 1;
	Card* currentCard = this->lowestCard;
	while (currentPosition != position) {
		currentPosition++;
		currentCard = currentCard->GetNext();
	}
	card->SetNext(currentCard->GetNext());
	if (!(card->GetNext() == nullptr)) {
		currentCard->GetNext()->SetPrev(card);
	}
	currentCard->GetPrev()->SetNext(card);
	card->SetPrev(currentCard->GetPrev());
	return currentCard;
}

bool Hand::HasRacko()
{
	bool inOrder = true;
	Card* currentCard = this->lowestCard;
	while (currentCard->GetNext() != nullptr) {
		if (!(currentCard->GetValue() < currentCard->GetNext()->GetValue())) {
			inOrder = false;
			return false;
		}
		currentCard = currentCard->GetNext();
	}
	return true;
}

std::string Hand::ShowHand()
{
	std::stringstream ss;
	Card* currentCard = this->lowestCard;
	for (int i = 1; i <= 10; ++i) {
		ss << i << ":" << std::setw(currentCard->GetValue() + std::to_string(currentCard->GetValue()).length()) << currentCard->GetValue() << std::endl;
		currentCard = currentCard->GetNext();
	}
	return ss.str();
}

Card * Hand::GetLowestCard()
{
	return this->lowestCard; 
}
