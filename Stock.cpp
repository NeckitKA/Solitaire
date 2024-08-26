//---------------------------------------------------------------------------

#pragma hdrstop

#include "Stock.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

Stock::Stock(int n, int x, int y, TForm* parentForm)
	: Stack(n, x, y, parentForm) {
	SetParentForm(parentForm);
	GetTImage()->OnMouseDown = OnMouseDown;
}
//---------------------------------------------------------------------------

void Stock::SetParentForm(TForm* form) {
	parentForm = form;
}
//---------------------------------------------------------------------------

TForm* Stock::GetParentForm() const {
	return parentForm;
}

void Stock::AddCard(Card* card) {
	cards.push_back(card);
}
//---------------------------------------------------------------------------

void Stock::RemoveCard() {
	cards.pop_back();
}
//---------------------------------------------------------------------------

void __fastcall Stock::OnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y) {
	if (GetTImage() && Button == mbLeft && cards.size()==0) {
		TForm1* mainForm = dynamic_cast<TForm1*>(GetParentForm());
		int numOfCards  = mainForm->waste->cards.size();
		for (int cardNumber = numOfCards - 1; cardNumber >= 0; --cardNumber) {
			mainForm->waste->cards[cardNumber]->SetCardOpen(false);
			mainForm->waste->cards[cardNumber]->
				SetCardPicture(mainForm->waste->cards[cardNumber]->GetValue(),
					mainForm->waste->cards[cardNumber]->GetCardOpen());
			mainForm->waste->cards[cardNumber]->SetParentStack(mainForm->stock);
			mainForm->waste->cards[cardNumber]->BringToFront();
			AddCard(mainForm->waste->cards[cardNumber]);
			mainForm->waste->RemoveCard(cardNumber);
		}
	}
}
//---------------------------------------------------------------------------
