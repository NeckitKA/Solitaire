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
		int startX, startY;
		int newParentStackNum;
		bool cardOpen;
		bool cardDragging = false;
		bool cardInStackArea = false;

		int GetX() const;
        int GetY() const;
		int GetStartX() const;
		int GetStartY() const;
		int GetNewParentStackNum() const;
		bool GetCardDragging() const;
		bool GetCardInStackArea() const;
		TForm* GetParentForm() const;

        void SetX(int x);
		void SetY(int y);
		void SetStartX(int x);
		void SetStartY(int y);
		void SetValue(int v);
		void SetParentForm(TForm* form);
		void SetCardInStackArea(bool InStackArea);
		void SetCardDragging(bool Dragging);
		void SetNewParentStackNum(int stackNum);
		void Show();
		void Hide();

	public:

		Card(int v, bool cardOpen, Stack* parentStack, TForm* parentForm);

        Stack* GetParentStack() const;
		int GetValue() const;
		bool GetCardOpen() const;

		void SetCardOpen(bool open);
        void SetParentStack(Stack* stack);
		void SetCardPicture(int v, bool cardOpen);
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
