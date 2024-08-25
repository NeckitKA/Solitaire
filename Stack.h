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
		void SetTopCardYPosition();


		void Show();
		void Hide();
		void SendToBack();

	public:

		Stack (int n, int x, int y, TForm* parentForm);
		int X,Y;
		int topCardXPosition;
		int topCardYPosition;

		std::vector<Card*> cards;

		TImage* GetTImage() const;
		int GetStackNumber() const;
		int GetTopCardXPosition() const;
		int GetTopCardYPosition() const;
		int GetCurrentNumberOfCards() const;


		virtual ~Stack();


};
//---------------------------------------------------------------------------
#endif
