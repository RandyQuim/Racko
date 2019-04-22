#pragma once
#ifndef CARD_HPP
#define CARD_HPP

class Card {
public:
	~Card();
	Card(int value, Card* prev = nullptr, Card* next = nullptr);
	void SetNext(Card* next);
	void SetPrev(Card* prev);
	int GetValue();
	Card* GetNext();
	Card* GetPrev();
private:
	int value;
	Card* prev;
	Card* next;
};

#endif