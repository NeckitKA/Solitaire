//---------------------------------------------------------------------------

#ifndef WasteH
#define WasteH
//---------------------------------------------------------------------------
#include "Stack.h"
//---------------------------------------------------------------------------
class Waste : public Stack {
	public:
		Waste(int n, int x, int y, TForm* parentForm);
		void AddCard(Card* card);
		void RemoveCard(int cardNumber);
};
//---------------------------------------------------------------------------
#endif
