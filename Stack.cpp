//---------------------------------------------------------------------------

#pragma hdrstop

#include "Stack.h"

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

Stack::Stack(int n, int x, int y, TForm* parentForm){

	 stack = new TImage(parentForm);

	 stack->Width = 102;
	 stack->Height = 146;

	 stack->Name = "Stack_" + IntToStr(n);

	 stack->Center=true;
	 stack->Transparent=true;
	 stack->Picture->LoadFromFile("resources/images/stack102x146.png");

	 SetX(x);
	 SetY(y);
	 SetStackNumber(n);
	 SetTopCardXPosition();
	 SetTopCardYPosition();
	 SetParentForm(parentForm);
	 SendToBack();
	 GetTImage()->OnMouseDown = OnMouseDown;


}
//---------------------------------------------------------------------------

int Stack::GetStackNumber() const {
	return stackNumber;
}
//---------------------------------------------------------------------------

int  Stack::GetTopCardXPosition() const {
	return topCardXPosition;
}
//---------------------------------------------------------------------------


int  Stack::GetTopCardYPosition() const {
	return topCardYPosition;
}
//---------------------------------------------------------------------------

TImage* Stack::GetTImage() const {
	return stack;
}
//---------------------------------------------------------------------------

void Stack::SetParentForm(TForm* form) {
	stack->Parent = form;
	parentForm = form;
}
//---------------------------------------------------------------------------

TForm* Stack::GetParentForm() const {
	return parentForm;
}
//---------------------------------------------------------------------------

void Stack::SetStackNumber(int n) {
	stackNumber = n;
}
//---------------------------------------------------------------------------

void  Stack::SetX(int x) {
	if (stack) {
		X = x;
		stack->Left = X;
	}

}
//---------------------------------------------------------------------------

void  Stack::SetY(int y) {
	if (stack) {
		Y = y;
		stack->Top = Y;
	}

}
//---------------------------------------------------------------------------

void  Stack::SetTopCardXPosition() {
	topCardXPosition = X + 1;
}
//---------------------------------------------------------------------------

void  Stack::SetTopCardYPosition() {
	topCardYPosition = Y + 1;
}
//---------------------------------------------------------------------------



void Stack::SendToBack() {
	if (stack) {
		stack->SendToBack();
	}
}
//--------------------------------------------------------------------------

void __fastcall Stack::OnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y) {
	TForm1* form = dynamic_cast<TForm1*>(GetParentForm());

	if (Button == mbRight) {
		bool n—MFW = false; //no—ardsMoveFromWaste
		bool n—MFT0 = false; //no—ardsMoveFromTableau0
		bool n—MFT1 = false;
		bool n—MFT2 = false;
		bool n—MFT3 = false;
		bool n—MFT4 = false;
		bool n—MFT5 = false;
		bool n—MFT6 = false;
		while (!n—MFW && !n—MFT0 && !n—MFT1 && !n—MFT2 && !n—MFT3 && !n—MFT4 && !n—MFT5 && !n—MFT6) {


			Waste* waste = dynamic_cast<Waste*>(form->waste);

			if (!waste->cards.empty()) {
				while (!waste->cards.empty() && !n—MFW) {
					if ((!form->foundationStacks[0]->cards.empty() && (waste->cards.back()->GetValue()-4)==form->foundationStacks[0]->cards.back()->GetValue()) || ((waste->cards.back()->GetValue())<5 && form->foundationStacks[0]->cards.size()==0)) {
						waste->cards.back()->SetParentStack(form->foundationStacks[0]);
						form->foundationStacks[0]->AddCard(waste->cards.back());
						waste->cards.back()->BringToFront();
						waste->RemoveCard(waste->cards.size()-1);
					}

					else if ((!form->foundationStacks[1]->cards.empty() && (waste->cards.back()->GetValue()-4)==form->foundationStacks[1]->cards.back()->GetValue()) || ((waste->cards.back()->GetValue())<5 && form->foundationStacks[1]->cards.size()==0)) {
						waste->cards.back()->SetParentStack(form->foundationStacks[1]);
						form->foundationStacks[1]->AddCard(waste->cards.back());
						waste->cards.back()->BringToFront();
						waste->RemoveCard(waste->cards.size()-1);
					}

					else if ((!form->foundationStacks[2]->cards.empty() && (waste->cards.back()->GetValue()-4)==form->foundationStacks[2]->cards.back()->GetValue()) || ((waste->cards.back()->GetValue())<5 && form->foundationStacks[2]->cards.size()==0)) {
						waste->cards.back()->SetParentStack(form->foundationStacks[2]);
						form->foundationStacks[2]->AddCard(waste->cards.back());
						waste->cards.back()->BringToFront();
						waste->RemoveCard(waste->cards.size()-1);
					}

					else if ((!form->foundationStacks[3]->cards.empty() && (waste->cards.back()->GetValue()-4)==form->foundationStacks[3]->cards.back()->GetValue()) || ((waste->cards.back()->GetValue())<5 && form->foundationStacks[3]->cards.size()==0)) {
						waste->cards.back()->SetParentStack(form->foundationStacks[3]);
						form->foundationStacks[3]->AddCard(waste->cards.back());
						waste->cards.back()->BringToFront();
						waste->RemoveCard(waste->cards.size()-1);
					}
					else {
						n—MFW = true;
					}
				}
			}
			else {
				n—MFW = true;
            }

			Tableau* tableau0 = dynamic_cast<Tableau*>(form->tableauStacks[0]);
			Tableau* tableau1 = dynamic_cast<Tableau*>(form->tableauStacks[1]);
			Tableau* tableau2 = dynamic_cast<Tableau*>(form->tableauStacks[2]);
			Tableau* tableau3 = dynamic_cast<Tableau*>(form->tableauStacks[3]);
			Tableau* tableau4 = dynamic_cast<Tableau*>(form->tableauStacks[4]);
			Tableau* tableau5 = dynamic_cast<Tableau*>(form->tableauStacks[5]);
			Tableau* tableau6 = dynamic_cast<Tableau*>(form->tableauStacks[6]);

			if (!tableau0->cards.empty()) {
				while (!tableau0->cards.empty() && !n—MFT0) {
					if ((!form->foundationStacks[0]->cards.empty() && (tableau0->cards.back()->GetValue()-4)==form->foundationStacks[0]->cards.back()->GetValue()) || ((tableau0->cards.back()->GetValue())<5 && form->foundationStacks[0]->cards.size()==0)) {
						tableau0->cards.back()->SetParentStack(form->foundationStacks[0]);
						form->foundationStacks[0]->AddCard(tableau0->cards.back());
						tableau0->cards.back()->BringToFront();
						tableau0->cards.back()->SetCardOpen(true);
						tableau0->cards.back()->SetCardPicture(tableau0->cards.back()->GetValue(),tableau0->cards.back()->GetCardOpen());
						tableau0->RemoveCard();
					}

					else if ((!form->foundationStacks[1]->cards.empty() && (tableau0->cards.back()->GetValue()-4)==form->foundationStacks[1]->cards.back()->GetValue()) || ((tableau0->cards.back()->GetValue())<5 && form->foundationStacks[1]->cards.size()==0)) {
						tableau0->cards.back()->SetParentStack(form->foundationStacks[1]);
						form->foundationStacks[1]->AddCard(tableau0->cards.back());
						tableau0->cards.back()->BringToFront();
						tableau0->cards.back()->SetCardOpen(true);
						tableau0->cards.back()->SetCardPicture(tableau0->cards.back()->GetValue(),tableau0->cards.back()->GetCardOpen());
						tableau0->RemoveCard();
					}

					else if ((!form->foundationStacks[2]->cards.empty() && (tableau0->cards.back()->GetValue()-4)==form->foundationStacks[2]->cards.back()->GetValue()) || ((tableau0->cards.back()->GetValue())<5 && form->foundationStacks[2]->cards.size()==0)) {
						tableau0->cards.back()->SetParentStack(form->foundationStacks[2]);
						form->foundationStacks[2]->AddCard(tableau0->cards.back());
						tableau0->cards.back()->BringToFront();
						tableau0->cards.back()->SetCardOpen(true);
						tableau0->cards.back()->SetCardPicture(tableau0->cards.back()->GetValue(),tableau0->cards.back()->GetCardOpen());
						tableau0->RemoveCard();
					}

					else if ((!form->foundationStacks[3]->cards.empty() && (tableau0->cards.back()->GetValue()-4)==form->foundationStacks[3]->cards.back()->GetValue()) || ((tableau0->cards.back()->GetValue())<5 && form->foundationStacks[3]->cards.size()==0)) {
						tableau0->cards.back()->SetParentStack(form->foundationStacks[3]);
						form->foundationStacks[3]->AddCard(tableau0->cards.back());
						tableau0->cards.back()->BringToFront();
						tableau0->cards.back()->SetCardOpen(true);
						tableau0->cards.back()->SetCardPicture(tableau0->cards.back()->GetValue(),tableau0->cards.back()->GetCardOpen());
						tableau0->RemoveCard();
					}
					else {
						n—MFT0 = true;
					}
				}
			}
			else {
				n—MFT0 = true;
			}

			if (!tableau1->cards.empty()) {
				while (!tableau1->cards.empty() && !n—MFT1) {
					if ((!form->foundationStacks[0]->cards.empty() && (tableau1->cards.back()->GetValue()-4)==form->foundationStacks[0]->cards.back()->GetValue()) || ((tableau1->cards.back()->GetValue())<5 && form->foundationStacks[0]->cards.size()==0)) {
						tableau1->cards.back()->SetParentStack(form->foundationStacks[0]);
						form->foundationStacks[0]->AddCard(tableau1->cards.back());
						tableau1->cards.back()->BringToFront();
						tableau1->cards.back()->SetCardOpen(true);
						tableau1->cards.back()->SetCardPicture(tableau1->cards.back()->GetValue(),tableau1->cards.back()->GetCardOpen());
						tableau1->RemoveCard();
					}

					else if ((!form->foundationStacks[1]->cards.empty() && (tableau1->cards.back()->GetValue()-4)==form->foundationStacks[1]->cards.back()->GetValue()) || ((tableau1->cards.back()->GetValue())<5 && form->foundationStacks[1]->cards.size()==0)) {
						tableau1->cards.back()->SetParentStack(form->foundationStacks[1]);
						form->foundationStacks[1]->AddCard(tableau1->cards.back());
						tableau1->cards.back()->BringToFront();
						tableau1->cards.back()->SetCardOpen(true);
						tableau1->cards.back()->SetCardPicture(tableau1->cards.back()->GetValue(),tableau1->cards.back()->GetCardOpen());
						tableau1->RemoveCard();
					}

					else if ((!form->foundationStacks[2]->cards.empty() && (tableau1->cards.back()->GetValue()-4)==form->foundationStacks[2]->cards.back()->GetValue()) || ((tableau1->cards.back()->GetValue())<5 && form->foundationStacks[2]->cards.size()==0)) {
						tableau1->cards.back()->SetParentStack(form->foundationStacks[2]);
						form->foundationStacks[2]->AddCard(tableau1->cards.back());
						tableau1->cards.back()->BringToFront();
						tableau1->cards.back()->SetCardOpen(true);
						tableau1->cards.back()->SetCardPicture(tableau1->cards.back()->GetValue(),tableau1->cards.back()->GetCardOpen());
						tableau1->RemoveCard();
					}

					else if ((!form->foundationStacks[3]->cards.empty() && (tableau1->cards.back()->GetValue()-4)==form->foundationStacks[3]->cards.back()->GetValue()) || ((tableau1->cards.back()->GetValue())<5 && form->foundationStacks[3]->cards.size()==0)) {
						tableau1->cards.back()->SetParentStack(form->foundationStacks[3]);
						form->foundationStacks[3]->AddCard(tableau1->cards.back());
						tableau1->cards.back()->BringToFront();
						tableau1->cards.back()->SetCardOpen(true);
						tableau1->cards.back()->SetCardPicture(tableau1->cards.back()->GetValue(),tableau1->cards.back()->GetCardOpen());
						tableau1->RemoveCard();
					}
					else {
						n—MFT1 = true;
					}
				}
			}
            else {
				n—MFT1 = true;
			}

			if (!tableau2->cards.empty()) {
				while (!tableau2->cards.empty() && !n—MFT2) {
					if ((!form->foundationStacks[0]->cards.empty() && (tableau2->cards.back()->GetValue()-4)==form->foundationStacks[0]->cards.back()->GetValue()) || ((tableau2->cards.back()->GetValue())<5 && form->foundationStacks[0]->cards.size()==0)) {
						tableau2->cards.back()->SetParentStack(form->foundationStacks[0]);
						form->foundationStacks[0]->AddCard(tableau2->cards.back());
						tableau2->cards.back()->BringToFront();
						tableau2->cards.back()->SetCardOpen(true);
						tableau2->cards.back()->SetCardPicture(tableau2->cards.back()->GetValue(),tableau2->cards.back()->GetCardOpen());
						tableau2->RemoveCard();
					}

					else if ((!form->foundationStacks[1]->cards.empty() && (tableau2->cards.back()->GetValue()-4)==form->foundationStacks[1]->cards.back()->GetValue()) || ((tableau2->cards.back()->GetValue())<5 && form->foundationStacks[1]->cards.size()==0)) {
						tableau2->cards.back()->SetParentStack(form->foundationStacks[1]);
						form->foundationStacks[1]->AddCard(tableau2->cards.back());
						tableau2->cards.back()->BringToFront();
						tableau2->cards.back()->SetCardOpen(true);
						tableau2->cards.back()->SetCardPicture(tableau2->cards.back()->GetValue(),tableau2->cards.back()->GetCardOpen());
						tableau2->RemoveCard();
					}

					else if ((!form->foundationStacks[2]->cards.empty() && (tableau2->cards.back()->GetValue()-4)==form->foundationStacks[2]->cards.back()->GetValue()) || ((tableau2->cards.back()->GetValue())<5 && form->foundationStacks[2]->cards.size()==0)) {
						tableau2->cards.back()->SetParentStack(form->foundationStacks[2]);
						form->foundationStacks[2]->AddCard(tableau2->cards.back());
						tableau2->cards.back()->BringToFront();
						tableau2->cards.back()->SetCardOpen(true);
						tableau2->cards.back()->SetCardPicture(tableau2->cards.back()->GetValue(),tableau2->cards.back()->GetCardOpen());
						tableau2->RemoveCard();
					}

					else if ((!form->foundationStacks[3]->cards.empty() && (tableau2->cards.back()->GetValue()-4)==form->foundationStacks[3]->cards.back()->GetValue()) || ((tableau2->cards.back()->GetValue())<5 && form->foundationStacks[3]->cards.size()==0)) {
						tableau2->cards.back()->SetParentStack(form->foundationStacks[3]);
						form->foundationStacks[3]->AddCard(tableau2->cards.back());
						tableau2->cards.back()->BringToFront();
						tableau2->cards.back()->SetCardOpen(true);
						tableau2->cards.back()->SetCardPicture(tableau2->cards.back()->GetValue(),tableau2->cards.back()->GetCardOpen());
						tableau2->RemoveCard();
					}
					else {
						n—MFT2 = true;
					}
				}
			}
            else {
				n—MFT2 = true;
			}

			if (!tableau3->cards.empty()) {
				while (!tableau3->cards.empty() && !n—MFT3) {
					if ((!form->foundationStacks[0]->cards.empty() && (tableau3->cards.back()->GetValue()-4)==form->foundationStacks[0]->cards.back()->GetValue()) || ((tableau3->cards.back()->GetValue())<5 && form->foundationStacks[0]->cards.size()==0)) {
						tableau3->cards.back()->SetParentStack(form->foundationStacks[0]);
						form->foundationStacks[0]->AddCard(tableau3->cards.back());
						tableau3->cards.back()->BringToFront();
						tableau3->cards.back()->SetCardOpen(true);
						tableau3->cards.back()->SetCardPicture(tableau3->cards.back()->GetValue(),tableau3->cards.back()->GetCardOpen());
						tableau3->RemoveCard();
					}

					else if ((!form->foundationStacks[1]->cards.empty() && (tableau3->cards.back()->GetValue()-4)==form->foundationStacks[1]->cards.back()->GetValue()) || ((tableau3->cards.back()->GetValue())<5 && form->foundationStacks[1]->cards.size()==0)) {
						tableau3->cards.back()->SetParentStack(form->foundationStacks[1]);
						form->foundationStacks[1]->AddCard(tableau3->cards.back());
						tableau3->cards.back()->BringToFront();
						tableau3->cards.back()->SetCardOpen(true);
						tableau3->cards.back()->SetCardPicture(tableau3->cards.back()->GetValue(),tableau3->cards.back()->GetCardOpen());
						tableau3->RemoveCard();
					}

					else if ((!form->foundationStacks[2]->cards.empty() && (tableau3->cards.back()->GetValue()-4)==form->foundationStacks[2]->cards.back()->GetValue()) || ((tableau3->cards.back()->GetValue())<5 && form->foundationStacks[2]->cards.size()==0)) {
						tableau3->cards.back()->SetParentStack(form->foundationStacks[2]);
						form->foundationStacks[2]->AddCard(tableau3->cards.back());
						tableau3->cards.back()->BringToFront();
						tableau3->cards.back()->SetCardOpen(true);
						tableau3->cards.back()->SetCardPicture(tableau3->cards.back()->GetValue(),tableau3->cards.back()->GetCardOpen());
						tableau3->RemoveCard();
					}

					else if ((!form->foundationStacks[3]->cards.empty() && (tableau3->cards.back()->GetValue()-4)==form->foundationStacks[3]->cards.back()->GetValue()) || ((tableau3->cards.back()->GetValue())<5 && form->foundationStacks[3]->cards.size()==0)) {
						tableau3->cards.back()->SetParentStack(form->foundationStacks[3]);
						form->foundationStacks[3]->AddCard(tableau3->cards.back());
						tableau3->cards.back()->BringToFront();
						tableau3->cards.back()->SetCardOpen(true);
						tableau3->cards.back()->SetCardPicture(tableau3->cards.back()->GetValue(),tableau3->cards.back()->GetCardOpen());
						tableau3->RemoveCard();
					}
					else {
						n—MFT3 = true;
					}
				}
			}
            else {
				n—MFT3 = true;
			}

			if (!tableau4->cards.empty()) {
				while (!tableau4->cards.empty() && !n—MFT4) {
					if ((!form->foundationStacks[0]->cards.empty() && (tableau4->cards.back()->GetValue()-4)==form->foundationStacks[0]->cards.back()->GetValue()) || ((tableau4->cards.back()->GetValue())<5 && form->foundationStacks[0]->cards.size()==0)) {
						tableau4->cards.back()->SetParentStack(form->foundationStacks[0]);
						form->foundationStacks[0]->AddCard(tableau4->cards.back());
						tableau4->cards.back()->BringToFront();
						tableau4->cards.back()->SetCardOpen(true);
						tableau4->cards.back()->SetCardPicture(tableau4->cards.back()->GetValue(),tableau4->cards.back()->GetCardOpen());
						tableau4->RemoveCard();
					}

					else if ((!form->foundationStacks[1]->cards.empty() && (tableau4->cards.back()->GetValue()-4)==form->foundationStacks[1]->cards.back()->GetValue()) || ((tableau4->cards.back()->GetValue())<5 && form->foundationStacks[1]->cards.size()==0)) {
						tableau4->cards.back()->SetParentStack(form->foundationStacks[1]);
						form->foundationStacks[1]->AddCard(tableau4->cards.back());
						tableau4->cards.back()->BringToFront();
						tableau4->cards.back()->SetCardOpen(true);
						tableau4->cards.back()->SetCardPicture(tableau4->cards.back()->GetValue(),tableau4->cards.back()->GetCardOpen());
						tableau4->RemoveCard();
					}

					else if ((!form->foundationStacks[2]->cards.empty() && (tableau4->cards.back()->GetValue()-4)==form->foundationStacks[2]->cards.back()->GetValue()) || ((tableau4->cards.back()->GetValue())<5 && form->foundationStacks[2]->cards.size()==0)) {
						tableau4->cards.back()->SetParentStack(form->foundationStacks[2]);
						form->foundationStacks[2]->AddCard(tableau4->cards.back());
						tableau4->cards.back()->BringToFront();
						tableau4->cards.back()->SetCardOpen(true);
						tableau4->cards.back()->SetCardPicture(tableau4->cards.back()->GetValue(),tableau4->cards.back()->GetCardOpen());
						tableau4->RemoveCard();
					}

					else if ((!form->foundationStacks[3]->cards.empty() && (tableau4->cards.back()->GetValue()-4)==form->foundationStacks[3]->cards.back()->GetValue()) || ((tableau4->cards.back()->GetValue())<5 && form->foundationStacks[3]->cards.size()==0)) {
						tableau4->cards.back()->SetParentStack(form->foundationStacks[3]);
						form->foundationStacks[3]->AddCard(tableau4->cards.back());
						tableau4->cards.back()->BringToFront();
						tableau4->cards.back()->SetCardOpen(true);
						tableau4->cards.back()->SetCardPicture(tableau4->cards.back()->GetValue(),tableau4->cards.back()->GetCardOpen());
						tableau4->RemoveCard();
					}
					else {
						n—MFT4 = true;
					}
				}
			}
            else {
				n—MFT4 = true;
			}
			if (!tableau5->cards.empty()) {
				while (!tableau5->cards.empty() && !n—MFT5) {
					if ((!form->foundationStacks[0]->cards.empty() && (tableau5->cards.back()->GetValue()-4)==form->foundationStacks[0]->cards.back()->GetValue()) || ((tableau5->cards.back()->GetValue())<5 && form->foundationStacks[0]->cards.size()==0)) {
						tableau5->cards.back()->SetParentStack(form->foundationStacks[0]);
						form->foundationStacks[0]->AddCard(tableau5->cards.back());
						tableau5->cards.back()->BringToFront();
						tableau5->cards.back()->SetCardOpen(true);
						tableau5->cards.back()->SetCardPicture(tableau5->cards.back()->GetValue(),tableau5->cards.back()->GetCardOpen());
						tableau5->RemoveCard();
					}

					else if ((!form->foundationStacks[1]->cards.empty() && (tableau5->cards.back()->GetValue()-4)==form->foundationStacks[1]->cards.back()->GetValue()) || ((tableau5->cards.back()->GetValue())<5 && form->foundationStacks[1]->cards.size()==0)) {
						tableau5->cards.back()->SetParentStack(form->foundationStacks[1]);
						form->foundationStacks[1]->AddCard(tableau5->cards.back());
						tableau5->cards.back()->BringToFront();
						tableau5->cards.back()->SetCardOpen(true);
						tableau5->cards.back()->SetCardPicture(tableau5->cards.back()->GetValue(),tableau5->cards.back()->GetCardOpen());
						tableau5->RemoveCard();
					}

					else if ((!form->foundationStacks[2]->cards.empty() && (tableau5->cards.back()->GetValue()-4)==form->foundationStacks[2]->cards.back()->GetValue()) || ((tableau5->cards.back()->GetValue())<5 && form->foundationStacks[2]->cards.size()==0)) {
						tableau5->cards.back()->SetParentStack(form->foundationStacks[2]);
						form->foundationStacks[2]->AddCard(tableau5->cards.back());
						tableau5->cards.back()->BringToFront();
						tableau5->cards.back()->SetCardOpen(true);
						tableau5->cards.back()->SetCardPicture(tableau5->cards.back()->GetValue(),tableau5->cards.back()->GetCardOpen());
						tableau5->RemoveCard();
					}

					else if ((!form->foundationStacks[3]->cards.empty() && (tableau5->cards.back()->GetValue()-4)==form->foundationStacks[3]->cards.back()->GetValue()) || ((tableau5->cards.back()->GetValue())<5 && form->foundationStacks[3]->cards.size()==0)) {
						tableau5->cards.back()->SetParentStack(form->foundationStacks[3]);
						form->foundationStacks[3]->AddCard(tableau5->cards.back());
						tableau5->cards.back()->BringToFront();
						tableau5->cards.back()->SetCardOpen(true);
						tableau5->cards.back()->SetCardPicture(tableau5->cards.back()->GetValue(),tableau5->cards.back()->GetCardOpen());
						tableau5->RemoveCard();
					}
					else {
						n—MFT5 = true;
					}
				}
			}
            else {
				n—MFT5 = true;
			}

			if (!tableau6->cards.empty()) {
				while (!tableau6->cards.empty() && !n—MFT6) {
					if ((!form->foundationStacks[0]->cards.empty() && (tableau6->cards.back()->GetValue()-4)==form->foundationStacks[0]->cards.back()->GetValue()) || ((tableau6->cards.back()->GetValue())<5 && form->foundationStacks[0]->cards.size()==0)) {
						tableau6->cards.back()->SetParentStack(form->foundationStacks[0]);
						form->foundationStacks[0]->AddCard(tableau6->cards.back());
						tableau6->cards.back()->BringToFront();
						tableau6->cards.back()->SetCardOpen(true);
						tableau6->cards.back()->SetCardPicture(tableau6->cards.back()->GetValue(),tableau6->cards.back()->GetCardOpen());
						tableau6->RemoveCard();
					}

					else if ((!form->foundationStacks[1]->cards.empty() && (tableau6->cards.back()->GetValue()-4)==form->foundationStacks[1]->cards.back()->GetValue()) || ((tableau6->cards.back()->GetValue())<5 && form->foundationStacks[1]->cards.size()==0)) {
						tableau6->cards.back()->SetParentStack(form->foundationStacks[1]);
						form->foundationStacks[1]->AddCard(tableau6->cards.back());
						tableau6->cards.back()->BringToFront();
						tableau6->cards.back()->SetCardOpen(true);
						tableau6->cards.back()->SetCardPicture(tableau6->cards.back()->GetValue(),tableau6->cards.back()->GetCardOpen());
						tableau6->RemoveCard();
					}

					else if ((!form->foundationStacks[2]->cards.empty() && (tableau6->cards.back()->GetValue()-4)==form->foundationStacks[2]->cards.back()->GetValue()) || ((tableau6->cards.back()->GetValue())<5 && form->foundationStacks[2]->cards.size()==0)) {
						tableau6->cards.back()->SetParentStack(form->foundationStacks[2]);
						form->foundationStacks[2]->AddCard(tableau6->cards.back());
						tableau6->cards.back()->BringToFront();
						tableau6->cards.back()->SetCardOpen(true);
						tableau6->cards.back()->SetCardPicture(tableau6->cards.back()->GetValue(),tableau6->cards.back()->GetCardOpen());
						tableau6->RemoveCard();
					}

					else if ((!form->foundationStacks[3]->cards.empty() && (tableau6->cards.back()->GetValue()-4)==form->foundationStacks[3]->cards.back()->GetValue()) || ((tableau6->cards.back()->GetValue())<5 && form->foundationStacks[3]->cards.size()==0)) {
						tableau6->cards.back()->SetParentStack(form->foundationStacks[3]);
						form->foundationStacks[3]->AddCard(tableau6->cards.back());
						tableau6->cards.back()->BringToFront();
						tableau6->cards.back()->SetCardOpen(true);
						tableau6->cards.back()->SetCardPicture(tableau6->cards.back()->GetValue(),tableau6->cards.back()->GetCardOpen());
						tableau6->RemoveCard();
					}
					else {
						n—MFT6 = true;
					}
				}
			}
            else {
				n—MFT6 = true;
			}
		}
	}
}
//---------------------------------------------------------------------------

Stack::~Stack() {
	for (int card = 0; card<cards.size(); ++card) {
		delete cards[card];
	}
    cards.clear();
	if (stack) {
		delete stack;
	}
}
//---------------------------------------------------------------------------

