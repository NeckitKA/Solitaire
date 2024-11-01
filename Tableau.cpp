//---------------------------------------------------------------------------

#pragma hdrstop

#include "Tableau.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

Tableau::Tableau(int n, int x, int y, TForm* parentForm)
	: Stack(n, x, y, parentForm) {
}
//---------------------------------------------------------------------------


void  Tableau::SetTopCardYPosition(bool newStack) {
	int cardOpenCounter=0;
	if (newStack) {

		if (cards.back()->GetCardOpen()) {
			topCardYPosition = topCardYPosition + 7;
		}
		else {
			topCardYPosition = topCardYPosition + 7 + 23;
        }
	}
	else {
		for (int cardNum = cards.size() - 1; cardNum >= 0; --cardNum) {
			if (!cards[cardNum]->GetCardOpen()) {
				break;
			}
			cardOpenCounter++;
		}
		topCardYPosition = cards.size()*7 + Y + 1 + 23*cardOpenCounter;
	}
}

//---------------------------------------------------------------------------

void  Tableau::SetTopCardYPosAtStart() {
	topCardYPosition = cards.size()*7 + Y + 1;
}
//---------------------------------------------------------------------------

void Tableau::AddCard(Card* card) {
	cards.push_back(card);
	SetTopCardYPosition();
}
//---------------------------------------------------------------------------

void Tableau::AddCardsAtStart(Card* card){
	cards.push_back(card);
	SetTopCardYPosAtStart();
}
//---------------------------------------------------------------------------

void Tableau::RemoveCard() {
	cards.pop_back();
    SetTopCardYPosition();
}
//---------------------------------------------------------------------------
