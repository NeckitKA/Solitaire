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
        form->ChangeCardsStacksByRightClick();
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

