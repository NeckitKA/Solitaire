//---------------------------------------------------------------------------

#pragma hdrstop

#include "Waste.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

Waste::Waste(int n, int x, int y, TForm* parentForm)
	: Stack(n, x, y, parentForm) {

}
//---------------------------------------------------------------------------

void Waste::AddCard(Card* card) {
	cards.push_back(card);
}
//---------------------------------------------------------------------------

void Waste::RemoveCard(int cardNumber) {
	cards.erase(cards.begin()+cardNumber);
}
//---------------------------------------------------------------------------
