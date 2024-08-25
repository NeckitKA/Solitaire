//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include  "Stock.h"
#include  "Waste.h"
#include  "Foundation.h"
#include  "Tableau.h"

//#include "Stack.h"
//#include "Card.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *N11;
	TMenuItem *N12;
	TMenuItem *N13;
	TMenuItem *N14;
	TMenuItem *N15;
	TMenuItem *N16;
	TButton *Button1;
	TButton *Button2;
	TTimer *Timer1;
	TLabel *Label1;
	TImage *Image1;
	TImage *Image2;
	TImage *Image3;

	void __fastcall N9Click(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall N14Click(TObject *Sender);
	void __fastcall N15Click(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall Image2Click(TObject *Sender);
	void __fastcall Image3Click(TObject *Sender);
	void __fastcall Image1MouseEnter(TObject *Sender);
	void __fastcall Image2MouseEnter(TObject *Sender);
	void __fastcall Image3MouseEnter(TObject *Sender);
	void __fastcall Image1MouseLeave(TObject *Sender);
	void __fastcall Image2MouseLeave(TObject *Sender);
	void __fastcall Image3MouseLeave(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall N4Click(TObject *Sender);

private:	// User declarations

	float seconds = 0;
	bool pause = false, gameOpen = false;

	void Play();
	void LogoutAccount();
	void PlayOrStop(bool gameOpen, bool I3);
	void ProcessModalFormResult(TModalResult result);
	void RegisterOrOpenStatistics (bool N10Enabled,  TForm* Form3, TForm* Form4);

	void AddStacksAndCards(){
        stock = new Stock(0,130,51,this);
		waste = new Waste(1,281,51,this);
		for (int stackNum = 0; stackNum < 4; ++stackNum) {   //4?
			foundationStacks.push_back(new Foundation(stackNum+2,583+151*stackNum,51,this));
		}

		for (int stackNum = 0; stackNum < 7; ++stackNum) {     //7?
			tableauStacks.push_back(new Tableau (stackNum+6,130+151*stackNum,248,this));
		}
		std::vector<int> cardValues;
        for (int i = 0; i < 52; ++i) {
			cardValues.push_back(i+1);
		}
        std::random_device rd;
		std::mt19937 g(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
		std::shuffle(cardValues.begin(), cardValues.end(), g);

		int cardCounter = 0;
		for (int stackNum = 0; stackNum < 7; ++stackNum) {
			for (int numOfCards = 0; numOfCards < stackNum+1; numOfCards++) {
				if (numOfCards != stackNum) {
					tableauStacks[stackNum]->AddCardsAtStart(new Card(cardValues[cardCounter++],
						false,tableauStacks[stackNum],this));
				}
				else{
					tableauStacks[stackNum]->AddCardsAtStart(new Card(cardValues[cardCounter++],
						true,tableauStacks[stackNum],this));
				}
			}
		}
        for (int carNum = cardCounter; carNum < cardValues.size(); ++carNum) {
			stock->AddCard(new Card(cardValues[cardCounter++],
				false,stock,this));
		}
	}

	void ChangeCardStack(Card* card, Stack* newStack) {
    if (card && newStack) {

	}
    }

	void DeleteStacksAndCards(){
		delete stock;
		delete waste;
		for (int stackNum = 0; stackNum < 4; ++stackNum) {
			delete foundationStacks[stackNum];
		}
		foundationStacks.clear();

		for (int stackNum = 0; stackNum < 7; ++stackNum) {
			delete tableauStacks[stackNum];
		}
		tableauStacks.clear();
	};

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    Stock* stock;
	Waste* waste;
	std::vector<Foundation*> foundationStacks;
	std::vector<Tableau*> tableauStacks;

    Stack* GetStockStack() const;
    Stack* GetWasteStack() const;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif