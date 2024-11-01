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
	SetParentStack(parentStack, false);
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

Card::Card(const Card& other) {
	TForm1* form = dynamic_cast<TForm1*>(Application->MainForm);
	SetParentForm(form);
    card = new TImage(form);
	card->Width = 100;
	card->Height = 144;
	parentStack = other.GetParentStack();
	SetParentStack(other.GetParentStack(),false,true);

	//card->Left=other.card->Left;
	//card->Top=other.card->Top;

	SetValue(other.GetValue());
	SetCardOpen(other.GetCardOpen());
	SetTop(other.GetTop());
	SetStartX(other.GetStartX());
	SetStartY(other.GetStartY());
	SetCardNumInStack(other.GetCardNumInStack());
	SetNewParentStackNum(other.GetNewParentStackNum());
	SetCardInStackArea(false);
	SetCardDragging(false);

	card->Parent = form;
	card->Name = other.card->Name+"_"+IntToStr(form->n)+"_";

	card->Center=true;
	card->Transparent=true;
	card->OnMouseDown = OnMouseDown;
	card->OnMouseUp = OnMouseUp;
	card->OnMouseMove = OnMouseMove;
	card->Visible = false;

}
//---------------------------------------------------------------------------

int Card::GetX() const{
	return xPos;
}
//---------------------------------------------------------------------------
int Card::GetY() const{
	return yPos;
}
//---------------------------------------------------------------------------
int Card::GetValue() const{
	return value;
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
int Card::GetCardNumInStack() const {
	return cardNumInStack;
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
void Card::SetX(int x) {
	if (card) {
		xPos = x + (card->Width-2)/2;
		card->Left = x;
	}
}
//---------------------------------------------------------------------------
void Card::SetY(int y) {
	if (card) {
		yPos = y + (card->Height-2)/2;
		card->Top = y;
		SetTop(y);
	}
}
//---------------------------------------------------------------------------
void Card::SetValue(int v){
	value = v;
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
			card->Picture->LoadFromFile("resources/images/deck/"+IntToStr(v)+
			  ".png");
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
void Card::SetParentStack(Stack* stack, bool manageTimer, bool newStack) {
	TForm1* form = dynamic_cast<TForm1*>(GetParentForm());
	if (manageTimer) {
		form->n=form->n+1;
		//form->CreateGameSnapshot();
		form->firstMoveIsMade=true;
		if (form->counter==0) {
			form->CountGame(form->user);
			form->counter++;
		}
		form->ManageTimer();
	}
	parentStack = stack;
	if (6<=stack->GetStackNumber()) {
		Tableau* currentStack = dynamic_cast<Tableau*>(parentStack);
		if (newStack) {
			currentStack->SetTopCardYPosition(newStack);
		}
		else {
			currentStack->SetTopCardYPosition();
		}
	}
	if (parentStack->GetStackNumber()>5) {
        SetCardNumInStack(stack->cards.size());
		SetStartX(stack->GetTopCardXPosition());
		SetStartY(stack->GetTopCardYPosition());              //-7*(stack->cards.size()+1)
		SetX(stack->GetTopCardXPosition());
		SetY(stack->GetTopCardYPosition());                     //-7*(stack->cards.size()+1)
	}
	else {
        SetCardNumInStack(stack->cards.size());
		SetStartX(stack->GetTopCardXPosition());
		SetStartY(stack->GetTopCardYPosition());
		SetX(stack->GetTopCardXPosition());
		SetY(stack->GetTopCardYPosition());
    }
}
//---------------------------------------------------------------------------
void Card::SetCardNumInStack(int cardNum){
	cardNumInStack = cardNum;
}
//---------------------------------------------------------------------------
void Card::SetNewParentStackNum(int stackNum) {
	newParentStackNum = stackNum;
}
//---------------------------------------------------------------------------
void Card::SetParentForm(TForm* form) {
	parentForm = form;
}
//---------------------------------------------------------------------------
void Card::Show(){
	SetCardPicture(value, cardOpen);
	card->Visible=true;

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
		 if (form->stock == GetParentStack()) {
			SetParentStack(form->waste);
			SetCardOpen(true);
			SetCardPicture(GetValue(),GetCardOpen());
			BringToFront();
			form->waste->AddCard(this);
			form->stock->RemoveCard();
		}
		else {
			if (GetCardOpen()) {
				BringToFront();
				if (6<=GetParentStack()->GetStackNumber() &&
				 GetValue()!=GetParentStack()->cards.back()->GetValue()) {
					Tableau*tableau=
					  form->tableauStacks[GetParentStack()->GetStackNumber()-6];
					for (int cardNum=GetCardNumInStack();cardNum<tableau->cards.size();++cardNum) {
						if (tableau->cards[cardNum]->GetCardOpen() && tableau->cards[cardNum]->GetValue()!=GetValue()) {
							tableau->cards[cardNum]->SetX(card->Left+(X-(card->Width-2)/2));
							tableau->cards[cardNum]->SetY(card->Top+Y+24*(tableau->cards[cardNum]->GetCardNumInStack()-GetCardNumInStack()));
							tableau->cards[cardNum]->SetCardDragging(true);
							tableau->cards[cardNum]->BringToFront();
						}
					}
				}
				SetX(card->Left+(X-(card->Width-2)/2));
				SetY(card->Top+(Y-(card->Height-2)/2));
				SetCardDragging(true);
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Card::OnMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y) {
	TForm1* form = dynamic_cast<TForm1*>(GetParentForm());
	for (int foundationNum = 2; foundationNum < 6; ++foundationNum) {
		int foundationTopCardX = form->foundationStacks[foundationNum-2]->GetTopCardXPosition();
		int foundationTopCardY = form->foundationStacks[foundationNum-2]->GetTopCardYPosition();
		if ((foundationTopCardX!=GetParentStack()->GetTopCardXPosition() || foundationTopCardY!=GetParentStack()->GetTopCardYPosition()) &&
		  (GetX()>=(foundationTopCardX+2) && GetX()<=(foundationTopCardX+100) && GetY()>=(foundationTopCardY+2) && GetY()<=(foundationTopCardY+144))) {
			if (GetValue()==GetParentStack()->cards.back()->GetValue()) {
                SetNewParentStackNum(foundationNum);
				SetCardInStackArea(true);
				break;
			}
		}
	}
	for (int tableauNum = 6; tableauNum < 13; ++tableauNum) {
		int tableauTopCardX = form->tableauStacks[tableauNum-6]->GetTopCardXPosition();
		int tableauTopCardY1 = form->tableauStacks[tableauNum-6]->GetTopCardYPosition();
		int tableauTopCardY2 = -1000;
		if (form->tableauStacks[tableauNum-6]->cards.size()!=0) {
			tableauTopCardY2 = form->tableauStacks[tableauNum-6]->cards.back()->GetTop();
		}
		if ((GetParentStack()->GetStackNumber()!=form->tableauStacks[tableauNum-6]->GetStackNumber()) &&
		  ((GetX()>=(tableauTopCardX+2) && GetX()<=(tableauTopCardX+100)) &&
		  ((GetY()>=(tableauTopCardY1+1) && GetY()<=(tableauTopCardY1+143)) || (GetY()>=(tableauTopCardY2+1) && GetY()<=(tableauTopCardY2+143))))) {
			SetNewParentStackNum(tableauNum);
			SetCardInStackArea(true);
			break;
		}
	}
	if (card && Button == mbLeft && GetCardOpen()) {
		if (GetCardInStackArea()) {
			if (6<=GetParentStack()->GetStackNumber() && GetValue()!=GetParentStack()->cards.back()->GetValue()) {
				int backCardValue = form->tableauStacks[GetNewParentStackNum()-6]->cards.back()->GetValue();
				int valueDifference = backCardValue-GetValue();
				if ((backCardValue%4==0 && (valueDifference==6 || valueDifference==7)) ||
				  (backCardValue%4==3 && (valueDifference==5 || valueDifference==6)) ||
				  (backCardValue%4==2 && (valueDifference==2 || valueDifference==3)) ||
				  (backCardValue%4==1 && (valueDifference==1 || valueDifference==2)) ||
				  (49<=GetValue() && form->tableauStacks[GetNewParentStackNum()-6]->cards.size()==0)) {
					Tableau* oldStack = dynamic_cast<Tableau*>(GetParentStack());
					Tableau* newTableau = form->tableauStacks[GetNewParentStackNum()-6];
					int cardNumInOldStack = GetCardNumInStack();
					for (int cardNum = GetCardNumInStack(); cardNum < oldStack->cards.size(); ++cardNum) {
						oldStack->cards[cardNum]->SetParentStack(form->tableauStacks[newTableau->GetStackNumber()-6]);
						newTableau->AddCard(oldStack->cards[cardNum]);
					}
					for (int cardNum = oldStack->cards.size()-1; cardNum >= cardNumInOldStack; --cardNum) {
						oldStack->RemoveCard();
					}
					if (oldStack->cards.size()!=0) {
							oldStack->cards.back()->SetCardOpen(true);
							oldStack->cards.back()->SetCardPicture(oldStack->cards.back()->GetValue(),GetCardOpen());
					}
					for (int cardNum = GetCardNumInStack(); cardNum < GetParentStack()->cards.size(); ++cardNum) {
						GetParentStack()->cards[cardNum]->BringToFront();
						GetParentStack()->cards[cardNum]->SetCardInStackArea(false);
						GetParentStack()->cards[cardNum]->SetCardDragging(false);
					}
				}
			}
			else if (2<=GetNewParentStackNum() && GetNewParentStackNum()<=5 && GetValue()==GetParentStack()->cards.back()->GetValue()) {
				if (form->foundationStacks[GetNewParentStackNum()-2]->cards.size()==0) {
					if (GetValue()<5) {
						if (2<=GetParentStack()->GetStackNumber() && GetParentStack()->GetStackNumber()<=5){
							Foundation* oldStack = dynamic_cast<Foundation*>(GetParentStack());
							SetParentStack(form->foundationStacks[GetNewParentStackNum()-2]);
							form->foundationStacks[GetNewParentStackNum()-2]->AddCard(this);
							oldStack->RemoveCard();
						}
						else if (6<=GetParentStack()->GetStackNumber()){
							Tableau* oldStack = dynamic_cast<Tableau*>(GetParentStack());
                            SetParentStack(form->foundationStacks[GetNewParentStackNum()-2]);
							form->foundationStacks[GetNewParentStackNum()-2]->AddCard(this);
							oldStack->RemoveCard();
							if (oldStack->cards.size()!=0) {
								oldStack->cards.back()->SetCardOpen(true);
								oldStack->cards.back()->SetCardPicture(oldStack->cards.back()->GetValue(),GetCardOpen());
							}
						}
						else {
							Waste* oldStack = dynamic_cast<Waste*>(GetParentStack());
                            SetParentStack(form->foundationStacks[GetNewParentStackNum()-2]);
							form->foundationStacks[GetNewParentStackNum()-2]->AddCard(this);
							for (int cardNum = 0; cardNum < oldStack->cards.size(); ++cardNum) {
								if (GetValue() == oldStack->cards[cardNum]->GetValue()) {
									oldStack->RemoveCard(cardNum);
								}
							}
						}
                        BringToFront();
						SetCardInStackArea(false);
					}
				}
				else if (form->foundationStacks[GetNewParentStackNum()-2]->cards.size()!=0) {
					if ((form->foundationStacks[GetNewParentStackNum()-2]->cards.back()->GetValue() + 4) == GetValue()) {
						if (2<=GetParentStack()->GetStackNumber() && GetParentStack()->GetStackNumber()<=5){
							Foundation* oldStack = dynamic_cast<Foundation*>(GetParentStack());
							SetParentStack(form->foundationStacks[GetNewParentStackNum()-2]);
							form->foundationStacks[GetNewParentStackNum()-2]->AddCard(this);
							oldStack->RemoveCard();
						}
						else if (6<=GetParentStack()->GetStackNumber()){
							Tableau* oldStack = dynamic_cast<Tableau*>(GetParentStack());
							SetParentStack(form->foundationStacks[GetNewParentStackNum()-2]);
							form->foundationStacks[GetNewParentStackNum()-2]->AddCard(this);
							oldStack->RemoveCard();
							if (oldStack->cards.size()!=0) {
								oldStack->cards.back()->SetCardOpen(true);
								oldStack->cards.back()->SetCardPicture(oldStack->cards.back()->GetValue(),GetCardOpen());
							}
						}
						else {
							Waste* oldStack = dynamic_cast<Waste*>(GetParentStack());
                            SetParentStack(form->foundationStacks[GetNewParentStackNum()-2]);
							form->foundationStacks[GetNewParentStackNum()-2]->AddCard(this);
							for (int cardNum = 0; cardNum < oldStack->cards.size(); ++cardNum) {
								if (GetValue() == oldStack->cards[cardNum]->GetValue()) {
									oldStack->RemoveCard(cardNum);
								}
							}
						}
                        BringToFront();
						SetCardInStackArea(false);
					}
				}
			}
			else  {
				if (form->tableauStacks[GetNewParentStackNum()-6]->cards.size()==0 && 49<=GetValue()) {
					if (2<=GetParentStack()->GetStackNumber() && GetParentStack()->GetStackNumber()<=5){
						Foundation* oldStack = dynamic_cast<Foundation*>(GetParentStack());
                        SetParentStack(form->tableauStacks[GetNewParentStackNum()-6]);
						form->tableauStacks[GetNewParentStackNum()-6]->AddCard(this);
						oldStack->RemoveCard();
					}
					else if (6<=GetParentStack()->GetStackNumber()){
						Tableau* oldStack = dynamic_cast<Tableau*>(GetParentStack());
                        SetParentStack(form->tableauStacks[GetNewParentStackNum()-6]);
						form->tableauStacks[GetNewParentStackNum()-6]->AddCard(this);
						oldStack->RemoveCard();
						if (oldStack->cards.size()!=0) {
							oldStack->cards.back()->SetCardOpen(true);
							oldStack->cards.back()->SetCardPicture(oldStack->cards.back()->GetValue(),GetCardOpen());
						}
					}
					else {
						Waste* oldStack = dynamic_cast<Waste*>(GetParentStack());
						SetParentStack(form->tableauStacks[GetNewParentStackNum()-6]);
						form->tableauStacks[GetNewParentStackNum()-6]->AddCard(this);
						for (int cardNum = 0; cardNum < oldStack->cards.size(); ++cardNum) {
							if (GetValue() == oldStack->cards[cardNum]->GetValue()) {
								oldStack->RemoveCard(cardNum);
							}
						}
					}
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
						if (2<=GetParentStack()->GetStackNumber() && GetParentStack()->GetStackNumber()<=5){
							Foundation* oldStack = dynamic_cast<Foundation*>(GetParentStack());
							SetParentStack(form->tableauStacks[GetNewParentStackNum()-6]);
							form->tableauStacks[GetNewParentStackNum()-6]->AddCard(this);
							oldStack->RemoveCard();
						}
						else if (6<=GetParentStack()->GetStackNumber()){
							Tableau* oldStack = dynamic_cast<Tableau*>(GetParentStack());
                            SetParentStack(form->tableauStacks[GetNewParentStackNum()-6]);
							form->tableauStacks[GetNewParentStackNum()-6]->AddCard(this);
							oldStack->RemoveCard();
							if (oldStack->cards.size()!=0) {
								oldStack->cards.back()->SetCardOpen(true);
								oldStack->cards.back()->SetCardPicture(oldStack->cards.back()->GetValue(),GetCardOpen());
							}
						}
						else {
							Waste* oldStack = dynamic_cast<Waste*>(GetParentStack());
							SetParentStack(form->tableauStacks[GetNewParentStackNum()-6]);
							form->tableauStacks[GetNewParentStackNum()-6]->AddCard(this);
							for (int cardNum = 0; cardNum < oldStack->cards.size(); ++cardNum) {
								if (GetValue() == oldStack->cards[cardNum]->GetValue()) {
									oldStack->RemoveCard(cardNum);
								}
							}
						}
                        BringToFront();
						SetCardInStackArea(false);
					}
				}
			}
		}
		if (GetValue()!=GetParentStack()->cards.back()->GetValue()) {
			for (int cardNum = GetCardNumInStack(); cardNum < GetParentStack()->cards.size(); ++cardNum) {
				GetParentStack()->cards[cardNum]->SetX(GetParentStack()->cards[cardNum]->GetStartX());
				GetParentStack()->cards[cardNum]->SetY(GetParentStack()->cards[cardNum]->GetStartY());
				GetParentStack()->cards[cardNum]->SetCardDragging(false);
			}
		}
		SetX(GetStartX());
		SetY(GetStartY());
		SetCardDragging(false);
		SetCardInStackArea(false);
	}
	else if (card && Button == mbRight) {
        form->ChangeCardsStacksByRightClick();
    }
}
//---------------------------------------------------------------------------
void __fastcall Card::OnMouseMove(TObject *Sender, TShiftState Shift, int X, int Y) {
	if (GetCardDragging()) {
		SetX(card->Left+(X-(card->Width-2)/2));
		SetY(card->Top+(Y-(card->Height-2)/2));
		TForm1* form = dynamic_cast<TForm1*>(GetParentForm());
		if (6<=GetParentStack()->GetStackNumber() && GetValue()!=GetParentStack()->cards.back()->GetValue()) {
			Tableau* tableau = form->tableauStacks[GetParentStack()->GetStackNumber()-6];
			if (GetValue()!=GetParentStack()->cards.back()->GetValue()) {
				for (int cardNum = GetCardNumInStack(); cardNum < tableau->cards.size(); ++cardNum) {
					if (tableau->cards[cardNum]->GetCardOpen() && tableau->cards[cardNum]->GetValue()!=GetValue()) {
						tableau->cards[cardNum]->SetX(card->Left+(X-(card->Width-2)/2));
						tableau->cards[cardNum]->SetY(card->Top+Y+24*(tableau->cards[cardNum]->GetCardNumInStack()-GetCardNumInStack()));
						tableau->cards[cardNum]->BringToFront();
					}
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
