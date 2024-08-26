//---------------------------------------------------------------------------

#pragma hdrstop

#include "Card.h"
#include "Stack.h"
//#include  "Stock.h"
#include  "Waste.h"
#include  "Foundation.h"
#include  "Tableau.h"
#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

Card::Card(int v, bool cardOpen, Stack* parentStack, TForm* parentForm) {

	SetParentForm(parentForm);
	card = new TImage(GetParentForm());

	SetParentStack(parentStack);
	SetValue(v);
	SetCardOpen(cardOpen);
	SetCardPicture(GetValue(),GetCardOpen());

    card->Parent = GetParentForm();
	card->Name = "Card_" + IntToStr(GetValue());
	card->Width = 100;
	card->Height = 144;
	card->Center=true;
	card->Transparent=true;
	card->OnMouseDown = OnMouseDown;
	card->OnMouseUp = OnMouseUp;
	card->OnMouseMove = OnMouseMove;
}
//---------------------------------------------------------------------------

int Card::GetValue() const{
	return value;
}
//---------------------------------------------------------------------------

int Card::GetX() const{
	return X;
}
//---------------------------------------------------------------------------

int Card::GetY() const{
	return Y;
}
//---------------------------------------------------------------------------

int Card::GetTop() const{
	return top;
}
//---------------------------------------------------------------------------

int Card::GetStartX() const{
	return startX;
}
//---------------------------------------------------------------------------

int Card::GetStartY() const{
	return startY;
}
//---------------------------------------------------------------------------

bool Card::GetCardOpen() const{
	return cardOpen;
}
//---------------------------------------------------------------------------

bool Card::GetCardDragging() const {
	return cardDragging;
}
//---------------------------------------------------------------------------

bool Card::GetCardInStackArea() const {
	return cardInStackArea;
}
//---------------------------------------------------------------------------

Stack* Card::GetParentStack() const {
	return parentStack;
}
//---------------------------------------------------------------------------

int Card::GetNewParentStackNum() const {
	return newParentStackNum;
}
//---------------------------------------------------------------------------

TForm* Card::GetParentForm() const {
	return parentForm;
}
//---------------------------------------------------------------------------

int Card::GetCardNumInStack() const {
	return cardNumInStack;
}

void Card::SetParentStack(Stack* stack) {
	parentStack = stack;
	SetCardNumInStack(stack->cards.size());
	SetStartX(stack->GetTopCardXPosition());
	SetStartY(stack->GetTopCardYPosition());
	SetX(stack->GetTopCardXPosition());
	SetY(stack->GetTopCardYPosition());
}
//---------------------------------------------------------------------------

void Card::SetValue(int v){
	value = v;
}
//---------------------------------------------------------------------------

void Card::SetX(int x) {
	if (card) {
		X = x + (card->Width-2)/2;
		card->Left = x;
	}
}
//---------------------------------------------------------------------------

void Card::SetY(int y) {
	if (card) {
		Y = y + (card->Height-2)/2;
		card->Top = y;
		SetTop(y);
	}
}
//---------------------------------------------------------------------------

void Card::SetStartX(int x) {
	if (card) {
		startX = x;
	}
}
//---------------------------------------------------------------------------

void Card::SetStartY(int y) {
	if (card) {
		startY = y;
	}
}
//---------------------------------------------------------------------------

void Card::SetTop(int y) {
	top = y;
}
//---------------------------------------------------------------------------

void Card::SetCardPicture(int v, bool cardOpen) {
	if (card)
	{
		if (cardOpen) {
			card->Picture->LoadFromFile("resources/images/deck/" + IntToStr(v) +".png");
		}
		else {
			card->Picture->LoadFromFile("resources/images/deck/card_back.png");
		}
	}
}
//---------------------------------------------------------------------------

void Card::SetCardOpen(bool open) {
	cardOpen = open;
}
//---------------------------------------------------------------------------

void Card::SetCardDragging(bool Dragging) {
	cardDragging = Dragging;
}
//---------------------------------------------------------------------------

void Card::SetCardInStackArea(bool InStackArea) {
	cardInStackArea =  InStackArea;
}
//---------------------------------------------------------------------------

void Card::SetParentForm(TForm* form) {
	parentForm = form;
}
//---------------------------------------------------------------------------

void Card::SetNewParentStackNum(int stackNum) {
	newParentStackNum = stackNum;
}
//---------------------------------------------------------------------------

void Card::SetCardNumInStack(int cardNum){
	cardNumInStack = cardNum;
}
//---------------------------------------------------------------------------

void Card::BringToFront(){
	if (card) {
		card->BringToFront();
	}
}
//---------------------------------------------------------------------------

void __fastcall Card::OnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y) {
	if (card && Button == mbLeft) {
		TForm1* form = dynamic_cast<TForm1*>(GetParentForm());
		if (form && form->GetStockStack() == GetParentStack()) {
			SetCardOpen(true);
			SetCardPicture(GetValue(),GetCardOpen());
			SetParentStack(form->waste);
			BringToFront();
			form->waste->AddCard(this);
			form->stock->RemoveCard();
		}

		else {

			if (GetCardOpen()) {
                SetX(card->Left + X - (card->Width-2)/2);
				SetY(card->Top + Y - (card->Height-2)/2);
				SetCardDragging(true);
				BringToFront();

				if (6<=GetParentStack()->GetStackNumber() &&
					GetValue()!=GetParentStack()->cards.back()->GetValue()) {
					Tableau* tableau = form->tableauStacks[GetParentStack()->GetStackNumber()-6];

					if (GetCardNumInStack()!=(tableau->cards.size()-1)) {
						for (int cardNum = GetCardNumInStack()+1; cardNum < tableau->cards.size(); ++cardNum) {
							tableau->cards[cardNum]->SetX(GetX()-(card->Width-2)/2);
							tableau->cards[cardNum]->SetY(GetY()+24*(tableau->cards[cardNum]->GetCardNumInStack()-GetCardNumInStack()));
							tableau->cards[cardNum]->SetCardDragging(true);
							tableau->cards[cardNum]->BringToFront();
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Card::OnMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y) {
    TForm1* form = dynamic_cast<TForm1*>(GetParentForm());
	for (int foundationNum = 2; foundationNum < 6; ++foundationNum) {

		int foundationTopCardXPos = form->foundationStacks[foundationNum-2]->GetTopCardXPosition();
		int foundationTopCardYPos = form->foundationStacks[foundationNum-2]->GetTopCardYPosition();

		if ((foundationTopCardXPos!=GetParentStack()->GetTopCardXPosition() ||      //������
		  foundationTopCardYPos!=GetParentStack()->GetTopCardYPosition()) &&
		  (GetX()>=(foundationTopCardXPos+2) && GetX()<=(foundationTopCardXPos+100) &&
		  GetY()>=(foundationTopCardYPos+2) && GetY()<=(foundationTopCardYPos+144))) {

			SetNewParentStackNum(foundationNum);
			SetCardInStackArea(true);
			break;
		}
	}

	for (int tableauNum = 6; tableauNum < 13; ++tableauNum) {

		int tableauTopCardXPos = form->tableauStacks[tableauNum-6]->GetTopCardXPosition();
		int tableauTopCardYPos1 = form->tableauStacks[tableauNum-6]->GetTopCardYPosition();
		int tableauTopCardYPos2 = form->tableauStacks[tableauNum-6]->cards.back()->GetTop();

		if (GetParentStack()->GetStackNumber()!=form->tableauStacks[tableauNum-6]->GetStackNumber() &&     //������
		  ((GetX()>=(tableauTopCardXPos+2) && GetX()<=(tableauTopCardXPos+100)) &&
		  ((GetY()>=(tableauTopCardYPos1+1) && GetY()<=(tableauTopCardYPos1+143)) ||
		  (GetY()>=(tableauTopCardYPos2+1) && GetY()<=(tableauTopCardYPos2+143))))) {

			SetNewParentStackNum(tableauNum);
			SetCardInStackArea(true);
			break;
		}
	}
	if (card && Button == mbLeft && GetCardOpen()) {

		if (GetCardInStackArea()) {


			if (2<=GetNewParentStackNum() && GetNewParentStackNum()<=5) {

				if (form->foundationStacks[GetNewParentStackNum()-2]->cards.size()==0) {

					if (GetValue()<5) {
						form->foundationStacks[GetNewParentStackNum()-2]->AddCard(this);

						if (2<=GetParentStack()->GetStackNumber() && GetParentStack()->GetStackNumber()<=5){
							Foundation* oldStack = dynamic_cast<Foundation*>(GetParentStack());
							oldStack->RemoveCard();
						}

						else if (6<=GetParentStack()->GetStackNumber()){
							Tableau* oldStack = dynamic_cast<Tableau*>(GetParentStack());
							oldStack->RemoveCard();
							oldStack->SetTopCardYPosition();

							if (oldStack->cards.size()!=0) {
								oldStack->cards.back()->SetCardOpen(true);
								oldStack->cards.back()->SetCardPicture(oldStack->cards.back()->GetValue(),GetCardOpen());
							}
						}

						else {
							Waste* oldStack = dynamic_cast<Waste*>(GetParentStack());
							for (int cardNum = 0; cardNum < oldStack->cards.size(); ++cardNum) {
								if (GetValue() == oldStack->cards[cardNum]->GetValue()) {
									oldStack->RemoveCard(cardNum);
								}
							}
						}

						SetParentStack(form->foundationStacks[GetNewParentStackNum()-2]);
						BringToFront();
						SetCardInStackArea(false);
					}
				}

				else {
					if ((form->foundationStacks[GetNewParentStackNum()-2]->cards.back()->GetValue() + 4) == GetValue()) {
						form->foundationStacks[GetNewParentStackNum()-2]->AddCard(this);

						if (2<=GetParentStack()->GetStackNumber() && GetParentStack()->GetStackNumber()<=5){
							Foundation* oldStack = dynamic_cast<Foundation*>(GetParentStack());
							oldStack->RemoveCard();
						}

						else if (6<=GetParentStack()->GetStackNumber()){
							Tableau* oldStack = dynamic_cast<Tableau*>(GetParentStack());
							oldStack->RemoveCard();
							oldStack->SetTopCardYPosition();
							if (oldStack->cards.size()!=0) {

								oldStack->cards.back()->SetCardOpen(true);
								oldStack->cards.back()->SetCardPicture(oldStack->cards.back()->GetValue(),GetCardOpen());
							}
						}

						else {
							Waste* oldStack = dynamic_cast<Waste*>(GetParentStack());
							for (int cardNum = 0; cardNum < oldStack->cards.size(); ++cardNum) {
								if (GetValue() == oldStack->cards[cardNum]->GetValue()) {
									oldStack->RemoveCard(cardNum);
								}
							}
						}

						SetParentStack(form->foundationStacks[GetNewParentStackNum()-2]);
						BringToFront();
						SetCardInStackArea(false);
					}
				}
			}

			else  {
				if (form->tableauStacks[GetNewParentStackNum()-6]->cards.size()==0 && 49<=GetValue()) {
					form->tableauStacks[GetNewParentStackNum()-6]->AddCard(this);

					if (2<=GetParentStack()->GetStackNumber() && GetParentStack()->GetStackNumber()<=5){
						Foundation* oldStack = dynamic_cast<Foundation*>(GetParentStack());
						oldStack->RemoveCard();
					}

					else if (6<=GetParentStack()->GetStackNumber()){
						Tableau* oldStack = dynamic_cast<Tableau*>(GetParentStack());
						oldStack->RemoveCard();
						oldStack->SetTopCardYPosition();

						if (oldStack->cards.size()!=0) {
							oldStack->cards.back()->SetCardOpen(true);
							oldStack->cards.back()->SetCardPicture(oldStack->cards.back()->GetValue(),GetCardOpen());
						}
					}

					else {
						Waste* oldStack = dynamic_cast<Waste*>(GetParentStack());
						for (int cardNum = 0; cardNum < oldStack->cards.size(); ++cardNum) {
							if (GetValue() == oldStack->cards[cardNum]->GetValue()) {
								oldStack->RemoveCard(cardNum);
							}
						}
					}

					SetParentStack(form->tableauStacks[GetNewParentStackNum()-6]);
					BringToFront();
					SetCardInStackArea(false);
				}

				else {
					int backCardValue = form->tableauStacks[GetNewParentStackNum()-6]->cards.back()->GetValue();
					int valueDifference = backCardValue-GetValue();
					if ((backCardValue%4==0 && (valueDifference==6 || valueDifference==7)) ||
					  (backCardValue%4==3 && (valueDifference==5 || valueDifference==6)) ||
					  (backCardValue%4==2 && (valueDifference==2 || valueDifference==3)) ||
					  (backCardValue%4==1 && (valueDifference==1 || valueDifference==2))) {

						form->tableauStacks[GetNewParentStackNum()-6]->AddCard(this);

						if (2<=GetParentStack()->GetStackNumber() && GetParentStack()->GetStackNumber()<=5){
							Foundation* oldStack = dynamic_cast<Foundation*>(GetParentStack());
							oldStack->RemoveCard();
						}

						else if (6<=GetParentStack()->GetStackNumber()){
							Tableau* oldStack = dynamic_cast<Tableau*>(GetParentStack());
							oldStack->RemoveCard();
							if (oldStack->cards.size()!=0) {
								oldStack->cards.back()->SetCardOpen(true);
								oldStack->cards.back()->SetCardPicture(oldStack->cards.back()->GetValue(),GetCardOpen());
							}
						}

						else {
							Waste* oldStack = dynamic_cast<Waste*>(GetParentStack());
							for (int cardNum = 0; cardNum < oldStack->cards.size(); ++cardNum) {
								if (GetValue() == oldStack->cards[cardNum]->GetValue()) {
									oldStack->RemoveCard(cardNum);
								}
							}
						}
						SetParentStack(form->tableauStacks[GetNewParentStackNum()-6]);
						BringToFront();
						SetCardInStackArea(false);
					}
				}
			}
		}

		SetX(GetStartX());
		SetY(GetStartY());
		SetCardDragging(false);
	}
}
//---------------------------------------------------------------------------

void __fastcall Card::OnMouseMove(TObject *Sender, TShiftState Shift, int X, int Y) {
	if (GetCardDragging()) {
		SetX(card->Left + (X - (card->Width-2)/2));
		SetY(card->Top + (Y - (card->Height-2)/2));
		TForm1* form = dynamic_cast<TForm1*>(GetParentForm());

		if (6<=GetParentStack()->GetStackNumber() && GetValue()!=GetParentStack()->cards.back()->GetValue()) {

			Tableau* tableau = form->tableauStacks[GetParentStack()->GetStackNumber()-6];
			if (GetCardNumInStack()!=(tableau->cards.size()-1)) {
				for (int cardNum = GetCardNumInStack()+1; cardNum < tableau->cards.size(); ++cardNum) {
					tableau->cards[cardNum]->SetX(GetX()-(card->Width-2)/2);
					tableau->cards[cardNum]->SetY(GetY()+24*(tableau->cards[cardNum]->GetCardNumInStack()-GetCardNumInStack()));
					tableau->cards[cardNum]->SetCardDragging(true);
					tableau->cards[cardNum]->BringToFront();
				}
			}
		}
		//�� ��� ���� �� ������ ������������ �����

	}
}
//---------------------------------------------------------------------------

Card::~Card() {
	if (card) {
		delete card;
	}
}
//---------------------------------------------------------------------------
