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
#include <string>
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
	TImage *Image4;
	TMenuItem *N9;

	void __fastcall N4Click(TObject *Sender);
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
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall N7Click(TObject *Sender);

private:	// User declarations



	bool image3MouseEnter = false;
	bool pause = true;


	void LogoutAccount();

	void PlayOrStop();
	void ProcessModalFormResultForForm3(TModalResult result);
	void RegisterOrOpenStatistics (bool N10Enabled,  TForm* Form3, TForm* Form4);
	void WriteStatistics();


public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	float seconds = 0;
	bool firstMoveIsMade;
	bool gameOpen = false;
	bool gameOver;
	int n=0;
    int counter=0;
	String user;

	Stock* stock;
	Waste* waste;
	std::vector<Foundation*> foundationStacks;
	std::vector<Tableau*> tableauStacks;

	std::vector<Stock*> stockGameSnapshots;
	std::vector<Waste*> wasteGameSnapshots;
	std::vector<std::vector<Foundation*>> foundationStacksGameSnapshots;
	std::vector<std::vector<Tableau*>> tableauStacksGameSnapshots;

	void ChangeCardsStacksByRightClick();
	void CountGame(String username);
	void PrepareFormForGame();
	void AddStacksAndCards();
	void DeleteStacksAndCards();
	void ManageTimer(bool anotherFormIsOpen = false);
	void CreateGameSnapshot();
	void GetGameSnapshot();
	void ClearGameSnapshots();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
