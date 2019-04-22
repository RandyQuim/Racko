#include "pch.h"
#include "card.hpp"

Card::~Card()
{
}

Card::Card(int value, Card * prev, Card * next)
{
	this->value = value;
	this->prev = prev;
	this->next = next;
}

void Card::SetNext(Card * next)
{
	this->next = next;
}

void Card::SetPrev(Card * prev)
{
	this->prev = prev;
}

int Card::GetValue()
{
	return this->value;
}

Card * Card::GetNext()
{
	return this->next;
}

Card * Card::GetPrev()
{
	return this->prev;
}
