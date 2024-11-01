	//---------------------------------------------------------------------------

#ifndef CardH
#define CardH
//---------------------------------------------------------------------------
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------

class Stack;

class Card{
	private:

		TImage *card;
		TForm * parentForm;

		int cardNumInStack=-1;
		int value, xPos, yPos, startX, startY, top, newParentStackNum=-1;
		bool cardOpen = false, cardDragging = false, cardInStackArea = false;

		int GetX() const;
		int GetY() const;
		int GetCardNumInStack() const;
		int GetNewParentStackNum() const;
		bool GetCardDragging() const;
		bool GetCardInStackArea() const;
		TForm* GetParentForm() const;

		void SetTop(int y);
		void SetValue(int v);
		void SetStartX(int x);
		void SetStartY(int y);
		void SetParentForm(TForm* form);
		void SetCardNumInStack(int cardNum);
		void SetNewParentStackNum(int stackNum);
		void SetCardInStackArea(bool InStackArea);

	public:
        Stack* parentStack;
		Card(int v, bool cardOpen, Stack* parentStack, TForm* parentForm);

		Card(const Card& other);

        Card& operator=(const Card& other);

		int GetTop() const;
		int GetValue() const;
		int GetStartX() const;
		int GetStartY() const;
		bool GetCardOpen() const;
		Stack* GetParentStack() const;

		void SetX(int x);
		void SetY(int y);
		void SetCardOpen(bool open);
		void SetParentStack(Stack* stack, bool manageTimer = true, bool newStack = false);
		void SetCardDragging(bool Dragging);
		void SetCardPicture(int v, bool cardOpen);

        void Show();
		void BringToFront();

		void __fastcall OnMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y);
		void __fastcall OnMouseUp(TObject *Sender, TMouseButton Button,
		 TShiftState Shift,int X, int Y);
		void __fastcall OnMouseMove(TObject *Sender, TShiftState Shift,
		 int X, int Y);

		~Card();
};
//---------------------------------------------------------------------------
#endif
