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

void Card::SetParentStack(Stack* stack) {
	parentStack = stack;
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

void Card::Show() {
	if (card) {
		card->Visible = true;
	}
}
//---------------------------------------------------------------------------

void Card::Hide() {
	if (card) {
		card->Visible = false;
    }
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
		TForm1* mainForm = dynamic_cast<TForm1*>(GetParentForm());
		if (mainForm && mainForm->GetStockStack() == GetParentStack()) {
			SetCardOpen(true);
			SetCardPicture(GetValue(),GetCardOpen());
			SetParentStack(mainForm->waste);
			BringToFront();
			mainForm->waste->AddCard(this);
			mainForm->stock->RemoveCard();
		}
		else {
			if (GetCardOpen()) {
				SetCardPicture(value,cardOpen);
				SetX(card->Left + X - (card->Width-2)/2);
				SetY(card->Top + Y - (card->Height-2)/2);
				SetCardDragging(true);
				BringToFront();
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Card::OnMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y) {
	if (card && Button == mbLeft && GetCardOpen()) {      //SetCardPicture(value,cardOpen); �������� �� ������
		if (GetCardInStackArea()) {
			TForm1* mainForm = dynamic_cast<TForm1*>(GetParentForm());

			if (2<=GetNewParentStackNum() && GetNewParentStackNum()<=5) {

				if (mainForm->foundationStacks[GetNewParentStackNum()-2]->cards.size()==0) {

					if (GetValue()<5) {

						mainForm->foundationStacks[GetNewParentStackNum()-2]->AddCard(this);

						if (2<=GetParentStack()->GetStackNumber() && GetParentStack()->GetStackNumber()<=5){

							Foundation* oldParentStack = dynamic_cast<Foundation*>(GetParentStack());
							oldParentStack->RemoveCard();
						}

						else if (6<=GetParentStack()->GetStackNumber()){

							Tableau* oldParentStack = dynamic_cast<Tableau*>(GetParentStack());
							oldParentStack->RemoveCard();

							if (oldParentStack->cards.size()!=0) {

								oldParentStack->cards.back()->SetCardOpen(true);
								oldParentStack->cards.back()->SetCardPicture(oldParentStack->cards.back()->GetValue(),GetCardOpen());
							}
						}

						else {

							Waste* oldParentStack = dynamic_cast<Waste*>(GetParentStack());

							for (int cardNum = 0; cardNum < oldParentStack->cards.size(); ++cardNum) {

								if (GetValue() == oldParentStack->cards[cardNum]->GetValue()) {
									oldParentStack->RemoveCard(cardNum);
								}
							}
						}

						SetParentStack(mainForm->foundationStacks[GetNewParentStackNum()-2]);
						BringToFront();
						SetCardInStackArea(false);
					}
				}

				else {
					if ((mainForm->foundationStacks[GetNewParentStackNum()-2]->cards.back()->GetValue() + 4) == GetValue()) {
						mainForm->foundationStacks[GetNewParentStackNum()-2]->AddCard(this);
						if (2<=GetParentStack()->GetStackNumber() && GetParentStack()->GetStackNumber()<=5){
							Foundation* oldParentStack = dynamic_cast<Foundation*>(GetParentStack());
							oldParentStack->RemoveCard();
						}
						else if (6<=GetParentStack()->GetStackNumber()){
							Tableau* oldParentStack = dynamic_cast<Tableau*>(GetParentStack());
							oldParentStack->RemoveCard();
                            if (oldParentStack->cards.size()!=0) {

								oldParentStack->cards.back()->SetCardOpen(true);
								oldParentStack->cards.back()->SetCardPicture(oldParentStack->cards.back()->GetValue(),GetCardOpen());
							}
						}
						else {
							Waste* oldParentStack = dynamic_cast<Waste*>(GetParentStack());
							for (int cardNum = 0; cardNum < oldParentStack->cards.size(); ++cardNum) {
								if (GetValue() == oldParentStack->cards[cardNum]->GetValue()) {
									oldParentStack->RemoveCard(cardNum);
								}
							}
						}
						SetParentStack(mainForm->foundationStacks[GetNewParentStackNum()-2]);
						BringToFront();
						SetCardInStackArea(false);
					}
				}
			}

			else  {
				if (mainForm->tableauStacks[GetNewParentStackNum()-6]->cards.size()==0) {

					if (49<=GetValue()) {

						mainForm->tableauStacks[GetNewParentStackNum()-6]->AddCard(this);

						if (2<=GetParentStack()->GetStackNumber() && GetParentStack()->GetStackNumber()<=5){

							Foundation* oldParentStack = dynamic_cast<Foundation*>(GetParentStack());
							oldParentStack->RemoveCard();
						}

						else if (6<=GetParentStack()->GetStackNumber()){

							Tableau* oldParentStack = dynamic_cast<Tableau*>(GetParentStack());
							oldParentStack->RemoveCard();

							if (oldParentStack->cards.size()!=0) {

								oldParentStack->cards.back()->SetCardOpen(true);
								oldParentStack->cards.back()->SetCardPicture(oldParentStack->cards.back()->GetValue(),GetCardOpen());
							}
						}

						else {

							Waste* oldParentStack = dynamic_cast<Waste*>(GetParentStack());

							for (int cardNum = 0; cardNum < oldParentStack->cards.size(); ++cardNum) {

								if (GetValue() == oldParentStack->cards[cardNum]->GetValue()) {
									oldParentStack->RemoveCard(cardNum);
								}
							}
						}

						SetParentStack(mainForm->tableauStacks[GetNewParentStackNum()-6]);
						BringToFront();
						SetCardInStackArea(false);
					}
				}

				else {
					int backCardValue = mainForm->tableauStacks[GetNewParentStackNum()-6]->cards.back()->GetValue();
					if ((backCardValue%4==0 && (backCardValue-GetValue()==6 || backCardValue-GetValue()==7)) ||
						(backCardValue%4==3 && (backCardValue-GetValue()==5 || backCardValue-GetValue()==6)) ||
						(backCardValue%4==2 && (backCardValue-GetValue()==2 || backCardValue-GetValue()==3)) ||
						(backCardValue%4==1 && (backCardValue-GetValue()==1 || backCardValue-GetValue()==2))) {

						mainForm->tableauStacks[GetNewParentStackNum()-6]->AddCard(this);
						if (2<=GetParentStack()->GetStackNumber() && GetParentStack()->GetStackNumber()<=5){
							Foundation* oldParentStack = dynamic_cast<Foundation*>(GetParentStack());
							oldParentStack->RemoveCard();
						}
						else if (6<=GetParentStack()->GetStackNumber()){
							Tableau* oldParentStack = dynamic_cast<Tableau*>(GetParentStack());
							oldParentStack->RemoveCard();
                            if (oldParentStack->cards.size()!=0) {
								oldParentStack->cards.back()->SetCardOpen(true);
								oldParentStack->cards.back()->SetCardPicture(oldParentStack->cards.back()->GetValue(),GetCardOpen());
							}
						}
						else {
							Waste* oldParentStack = dynamic_cast<Waste*>(GetParentStack());
							for (int cardNum = 0; cardNum < oldParentStack->cards.size(); ++cardNum) {
								if (GetValue() == oldParentStack->cards[cardNum]->GetValue()) {
									oldParentStack->RemoveCard(cardNum);
								}
							}
						}
						SetParentStack(mainForm->tableauStacks[GetNewParentStackNum()-6]);
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
		TForm1* mainForm = dynamic_cast<TForm1*>(GetParentForm());
		for (int foundationStackNum = 2; foundationStackNum < 6; ++foundationStackNum) {

			int foundationStackTopCardXPos = mainForm->foundationStacks[foundationStackNum-2]->GetTopCardXPosition();
			int foundationStackTopCardYPos = mainForm->foundationStacks[foundationStackNum-2]->GetTopCardYPosition();

			if (foundationStackTopCardXPos!=GetParentStack()->GetTopCardXPosition() ||
				foundationStackTopCardYPos!=GetParentStack()->GetTopCardYPosition()) {

				if (GetX()>=foundationStackTopCardXPos && GetX()<=(foundationStackTopCardXPos+102) &&
						GetY()>=foundationStackTopCardYPos && GetY()<=(foundationStackTopCardYPos+146)) {

					SetNewParentStackNum(foundationStackNum);
					SetCardInStackArea(true);
					break;
				}
			}
		}
		for (int tableauStackNum = 6; tableauStackNum < 13; ++tableauStackNum) {

			int tableauStackTopCardXPos = mainForm->tableauStacks[tableauStackNum-6]->GetTopCardXPosition();
			int tableauStackTopCardYPos = mainForm->tableauStacks[tableauStackNum-6]->GetTopCardYPosition();

			if (tableauStackTopCardXPos!=GetParentStack()->GetTopCardXPosition() ||
				tableauStackTopCardYPos!=GetParentStack()->GetTopCardYPosition()) {

				if (GetX()>=tableauStackTopCardXPos && GetX()<=(tableauStackTopCardXPos+102) &&
						GetY()>=tableauStackTopCardYPos && GetY()<=(tableauStackTopCardYPos+146)) {

					SetNewParentStackNum(tableauStackNum);
					SetCardInStackArea(true);
                    break;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

Card::~Card() {
	if (card) {
		delete card;
	}
}
//---------------------------------------------------------------------------
