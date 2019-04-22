#pragma once
#include "card.hpp"

class Deck {
	public:
		Deck();
		~Deck();
		void MakeFullDeck();
		void Push(int value);
		void Discard(Card* card);
		Card* Draw();
		int Peek();
		void Shuffle();
		void InsertAt(Card* card, int index);

	private:
		Card* top;
		const int NUMBER_OF_CARDS_IN_RACKO_DECK = 60;
		int numberOfCardsInDeck;
		bool CheckBounds(int index);
		bool IsInDeck(int randInt);
};