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

void  Tableau::SetTopCardYPos() {
	topCardYPosition = cards.size()*10 + Y + 1;
}
//---------------------------------------------------------------------------

void Tableau::AddCard(Card* card) {
    SetTopCardYPos();
	cards.push_back(card);

}
//---------------------------------------------------------------------------

void Tableau::AddCardsAtStart(Card* card){
	cards.push_back(card);
	SetTopCardYPos();
}
//---------------------------------------------------------------------------

void Tableau::RemoveCard() {
	cards.pop_back();
}
//---------------------------------------------------------------------------
