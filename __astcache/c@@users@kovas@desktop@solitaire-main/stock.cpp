//---------------------------------------------------------------------------

#pragma hdrstop

#include "Stock.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

Stock::Stock(int n, int x, int y, TForm* parentForm)
	: Stack(n, x, y, parentForm) {
	GetTImage()->OnMouseDown = OnMouseDown;
}
//---------------------------------------------------------------------------

Stock::Stock(const Stock& other)
	: Stack(other)
{
    GetTImage()->OnMouseDown = OnMouseDown;
}
//---------------------------------------------------------------------------

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
	TForm1* form = dynamic_cast<TForm1*>(GetParentForm());

	if (Button == mbLeft && cards.size()==0) {

		int numOfCards  = form->waste->cards.size();
		for (int cardNum = numOfCards - 1; cardNum >= 0; --cardNum) {
			form->waste->cards[cardNum]->SetParentStack(form->stock);
			form->waste->cards[cardNum]->SetCardOpen(false);
			form->waste->cards[cardNum]->
				SetCardPicture(form->waste->cards[cardNum]->GetValue(),
					form->waste->cards[cardNum]->GetCardOpen());
			form->waste->cards[cardNum]->BringToFront();
			AddCard(form->waste->cards[cardNum]);
			form->waste->RemoveCard(cardNum);
		}
	}

	else if (Button == mbRight) {
        form->ChangeCardsStacksByRightClick();
	}
}
//---------------------------------------------------------------------------
