//---------------------------------------------------------------------------

#pragma hdrstop

#include "Stack.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

Stack::Stack(int n, int x, int y, TForm* parentForm){

	 stack = new TImage(parentForm);

	 stack->Width = 102;
	 stack->Height = 146;

	 stack->Name = "Stack_" + IntToStr(n);
	 stack->Parent = parentForm;
	 stack->Center=true;
	 stack->Transparent=true;
	 stack->Picture->LoadFromFile("resources/images/stack102x146.png");

	 SetX(x);
	 SetY(y);
	 SetStackNumber(n);
	 SetTopCardXPosition();
	 SetTopCardYPosition();
	 SendToBack();


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

