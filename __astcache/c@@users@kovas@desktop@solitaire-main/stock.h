//---------------------------------------------------------------------------

#ifndef StockH
#define StockH
//---------------------------------------------------------------------------
#include <vector>
#include "Stack.h"
//---------------------------------------------------------------------------
class Stock: public Stack {
	public:
		Stock(int n, int x, int y, TForm* parentForm);

		Stock(const Stock& other);

		void AddCard(Card* card);
		void RemoveCard();

        void __fastcall OnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
};
//---------------------------------------------------------------------------
#endif
