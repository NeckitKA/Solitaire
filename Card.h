//---------------------------------------------------------------------------

#ifndef CardH
#define CardH
//---------------------------------------------------------------------------
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------
class Stack;

class Card{
	private:
		Stack* parentStack;
		TForm * parentForm;
		TImage *card;
		int value;
		int X, Y;
        int top;
		int startX, startY;
		int newParentStackNum;
		int cardNumInStack=-1;
		bool cardOpen;
		bool cardDragging = false;
		bool cardInStackArea = false;

		int GetX() const;
		int GetY() const;
		int GetStartX() const;
		int GetStartY() const;
		int GetCardNumInStack() const;
		int GetNewParentStackNum() const;
		bool GetCardDragging() const;
		bool GetCardInStackArea() const;
		TForm* GetParentForm() const;

		void SetStartX(int x);
		void SetStartY(int y);
		void SetTop(int y);
		void SetValue(int v);
		void SetCardNumInStack(int cardNum);
		void SetParentForm(TForm* form);
		void SetCardInStackArea(bool InStackArea);
		void SetNewParentStackNum(int stackNum);


	public:

		Card(int v, bool cardOpen, Stack* parentStack, TForm* parentForm);

        Stack* GetParentStack() const;

		int GetValue() const;
		int GetTop() const;
		bool GetCardOpen() const;

        void SetX(int x);
		void SetY(int y);
		void SetCardOpen(bool open);
        void SetParentStack(Stack* stack);
		void SetCardPicture(int v, bool cardOpen);
		void SetCardDragging(bool Dragging);
		void BringToFront();

		void __fastcall OnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
		void __fastcall OnMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
		void __fastcall OnMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

		~Card();
};

//---------------------------------------------------------------------------
#endif
