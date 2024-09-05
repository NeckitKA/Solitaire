//---------------------------------------------------------------------------

#ifndef FoundationH
#define FoundationH
//---------------------------------------------------------------------------
#include "Stack.h"
//---------------------------------------------------------------------------

class Foundation : public Stack {
	public:
		Foundation(int n, int x, int y, TForm* parentForm);
		void AddCard(Card* card);
		void RemoveCard();
};
//---------------------------------------------------------------------------
#endif
