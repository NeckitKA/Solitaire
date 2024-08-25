//---------------------------------------------------------------------------

#pragma hdrstop

#include "Foundation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

Foundation::Foundation(int n, int x, int y, TForm* parentForm)
	: Stack(n, x, y, parentForm) {

}
//---------------------------------------------------------------------------

void Foundation::AddCard(Card* card) {
	cards.push_back(card);
	
}
//---------------------------------------------------------------------------

void Foundation::RemoveCard() {
	cards.pop_back();
}
//---------------------------------------------------------------------------
