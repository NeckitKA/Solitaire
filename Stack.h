//---------------------------------------------------------------------------

#ifndef StackH
#define StackH
//---------------------------------------------------------------------------
#include <Vcl.Graphics.hpp>
#include "Card.h"
#include <vector>
//---------------------------------------------------------------------------
class Stack{
	private:

		TImage* stack;
		int stackNumber;

		void SetX(int x);
		void SetY(int y);
		void SetStackNumber(int n);
		void SetTopCardXPosition();
		void SetParentForm(TForm* form);

		void SendToBack();

	public:

		Stack (int n, int x, int y, TForm* parentForm);

		Stack(const Stack& other);

		TForm* parentForm;
		std::vector<Card*> cards;
		int X, Y, topCardXPosition, topCardYPosition;

        int GetStackNumber() const;
		int GetTopCardXPosition() const;
		int GetTopCardYPosition() const;
		int GetCurrentNumberOfCards() const;
		TImage* GetTImage() const;
		TForm* GetParentForm() const;

		virtual void SetTopCardYPosition(bool newStack = false);
        virtual void AddCard(Card* card);

        void Show();
		virtual void __fastcall OnMouseDown(TObject *Sender,
			TMouseButton Button, TShiftState Shift, int X, int Y);

		virtual ~Stack();
};
//---------------------------------------------------------------------------
#endif
