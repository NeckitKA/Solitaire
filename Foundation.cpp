//---------------------------------------------------------------------------

#pragma hdrstop

#include "Foundation.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

Foundation::Foundation(int n, int x, int y, TForm* parentForm)
	: Stack(n, x, y, parentForm) {

}
//---------------------------------------------------------------------------

void Foundation::AddCard(Card* card) {
	cards.push_back(card);
    TForm1* form = dynamic_cast<TForm1*>(GetParentForm());
    if (form->foundationStacks[0]->cards.size()==13 &&
	  form->foundationStacks[1]->cards.size()==13 &&
	  form->foundationStacks[2]->cards.size()==13 &&
	  form->foundationStacks[3]->cards.size()==13) {
        form->gameOver=true;
		form->ManageTimer();
	}
}
//---------------------------------------------------------------------------

void Foundation::RemoveCard() {
	cards.pop_back();
}
//---------------------------------------------------------------------------
