//---------------------------------------------------------------------------

#ifndef TableauH
#define TableauH
//---------------------------------------------------------------------------
#include "Stack.h"
//---------------------------------------------------------------------------
class Tableau: public Stack {
	public:
		Tableau(int n, int x, int y, TForm* parentForm);
		void AddCard(Card* card);
		void AddCardsAtStart(Card* card);
		void RemoveCard();
        void SetTopCardYPosition(bool newStack = false);
		void SetTopCardYPosAtStart();
};
//---------------------------------------------------------------------------
#endif
