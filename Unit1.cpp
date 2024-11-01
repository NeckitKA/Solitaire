﻿//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N9Click(TObject *Sender)
{
	ManageTimer(true);
	Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N10Click(TObject *Sender)
{
	ManageTimer(true);
	Form3->ShowModal();
	ProcessModalFormResultForForm3(Form3->ModalResult);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N11Click(TObject *Sender)
{
	LogoutAccount();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N13Click(TObject *Sender)
{
	ManageTimer(true);
	Form4->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N14Click(TObject *Sender)
{
	ManageTimer(true);
	Form5->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N15Click(TObject *Sender)
{
	ManageTimer(true);
	Form6->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1Click(TObject *Sender)
{
	ManageTimer(true);
	Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2Click(TObject *Sender)
{
	ManageTimer(true);
	RegisterOrOpenStatistics(N10->Enabled, Form3, Form4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image3Click(TObject *Sender)
{
	ManageTimer();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image3MouseEnter(TObject *Sender)
{
	if (pause) {
		Image3->Picture->LoadFromFile("resources/images/playstroke60x60.png");

	}
	else {
		Image3->Picture->LoadFromFile("resources/images/pausestroke60x60.png");
	}
	image3MouseEnter = true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image3MouseLeave(TObject *Sender)
{
	if (pause) {
		Image3->Picture->LoadFromFile("resources/images/play60x60.png");
	}
	else {
		Image3->Picture->LoadFromFile("resources/images/pause60x60.png");
	}
	image3MouseEnter = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseEnter(TObject *Sender)
{
	Image1->Picture->LoadFromFile("resources/images/gearstroke60x60.png");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2MouseEnter(TObject *Sender)
{
	Image2->Picture->LoadFromFile("resources/images/greennerdstroke60x60.png");
}
//---------------------------------------------------------------------------

void TForm1::ProcessModalFormResultForForm3(TModalResult result){
		if (result==mrYes) {
			N10->Enabled=false;
			N11->Enabled=true;
			N13->Enabled=true;
		}
}
//---------------------------------------------------------------------------

void TForm1::LogoutAccount(){
	N10->Enabled=true;
	N11->Enabled=false;
	N13->Enabled=false;
}
//---------------------------------------------------------------------------

void TForm1::RegisterOrOpenStatistics (bool N10Enabled,  TForm* Form3, TForm* Form4){
	if (N10Enabled) {
		Form3->ShowModal();
		ProcessModalFormResultForForm3(Form3->ModalResult);
	}
	else {
		Form4->ShowModal();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseLeave(TObject *Sender)
{
	Image1->Picture->LoadFromFile("resources/images/gear60x60.png");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2MouseLeave(TObject *Sender)
{
	Image2->Picture->LoadFromFile("resources/images/greennerd60x60.png");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if (user.IsEmpty()) {
        Form3->ShowModal();
		ProcessModalFormResultForForm3(Form3->ModalResult);
	}
	else {
        PrepareFormForGame();
		AddStacksAndCards();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	seconds+=0.1;
	Label1->Caption=AnsiString().sprintf("%.1f", seconds);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{

	if (gameOpen) {
		DeleteStacksAndCards();
		//ClearGameSnapshots();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
	if (gameOpen) {
		DeleteStacksAndCards();
		//ClearGameSnapshots();
	}

	if (user.IsEmpty()) {
		Form3->ShowModal();
		ProcessModalFormResultForForm3(Form3->ModalResult);
	}
	else {
        PrepareFormForGame();
		AddStacksAndCards();
    }

}
//---------------------------------------------------------------------------

void TForm1::PrepareFormForGame(){

	counter=0;
	N5->Enabled=false;
	N7->Enabled=false;
	Button1->Visible=false;
	Button2->Visible=false;
	Image3->Visible=true;
    Image4->Visible=false;
	Label1->Visible=true;
	Label1->Caption="0";
	Timer1->Enabled=false;
	seconds = 0;
	gameOpen = true;
	gameOver = false;
	firstMoveIsMade = false;
	pause = true;
	if (image3MouseEnter) {
		Image3->Picture->LoadFromFile("resources/images/playstroke60x60.png");
	}
	else {
        Image3->Picture->LoadFromFile("resources/images/play60x60.png");
	}
}
//---------------------------------------------------------------------------

void TForm1::ManageTimer(bool anotherFormIsOpen) {
	if (gameOpen) {
		if (gameOver) {
            pause = true;
			Timer1->Enabled=false;
			Image3->Picture->LoadFromFile("resources/images/play60x60.png");

			Form7->ShowModal();
		}

		else if (anotherFormIsOpen) {
			pause = true;
			Timer1->Enabled=false;
			Image3->Picture->LoadFromFile("resources/images/play60x60.png");
		}

		else if (firstMoveIsMade) {
			pause = false;
			Timer1->Enabled=true;
			Image3->Picture->LoadFromFile("resources/images/pausestroke60x60.png");
			N5->Enabled=true;
			N7->Enabled=true;
            firstMoveIsMade = false;
		}

		else {
			String stroke = "";
			if (image3MouseEnter) {
                stroke = "stroke";
			}

			if (pause) {
				pause = false;
				Timer1->Enabled=true;

				Image3->Picture->LoadFromFile("resources/images/pause"+stroke+"60x60.png");

			}
			else {
                pause = true;
				Timer1->Enabled=false;
				Image3->Picture->LoadFromFile("resources/images/play"+stroke+"60x60.png");
			}
		}
	}
}
//---------------------------------------------------------------------------

void TForm1::PlayOrStop(){    //delete?
	if (gameOpen) {
		if (pause) {
			Image3->Picture->LoadFromFile("resources/images/pausestroke60x60.png");
			Timer1->Enabled=true;
			pause = false;
		}
		else if (!pause){
			Image3->Picture->LoadFromFile("resources/images/playstroke60x60.png");
			Timer1->Enabled=false;
			pause = true;

		}
	}
}
//---------------------------------------------------------------------------

void TForm1::ChangeCardsStacksByRightClick() {
	bool nCMFW = false; //noCardsMoveFromWaste
	bool nCMFT0 = false; //noCardsMoveFromTableau0
	bool nCMFT1 = false;
	bool nCMFT2 = false;
	bool nCMFT3 = false;
	bool nCMFT4 = false;
	bool nCMFT5 = false;
	bool nCMFT6 = false;
	bool AVP = false;    //additional verification passed
	int counter = 0;
	while (!AVP) {

		if (!waste->cards.empty()) {
			while (!waste->cards.empty() && !nCMFW) {
				if ((!foundationStacks[0]->cards.empty() && (waste->cards.back()->GetValue()-4)==foundationStacks[0]->cards.back()->GetValue()) || ((waste->cards.back()->GetValue())<5 && foundationStacks[0]->cards.size()==0)) {
					waste->cards.back()->SetParentStack(foundationStacks[0]);
					foundationStacks[0]->AddCard(waste->cards.back());
					waste->cards.back()->BringToFront();
					waste->RemoveCard(waste->cards.size()-1);
				}

				else if ((!foundationStacks[1]->cards.empty() && (waste->cards.back()->GetValue()-4)==foundationStacks[1]->cards.back()->GetValue()) || ((waste->cards.back()->GetValue())<5 && foundationStacks[1]->cards.size()==0)) {
					waste->cards.back()->SetParentStack(foundationStacks[1]);
					foundationStacks[1]->AddCard(waste->cards.back());
					waste->cards.back()->BringToFront();
					waste->RemoveCard(waste->cards.size()-1);
				}

				else if ((!foundationStacks[2]->cards.empty() && (waste->cards.back()->GetValue()-4)==foundationStacks[2]->cards.back()->GetValue()) || ((waste->cards.back()->GetValue())<5 && foundationStacks[2]->cards.size()==0)) {
					waste->cards.back()->SetParentStack(foundationStacks[2]);
					foundationStacks[2]->AddCard(waste->cards.back());
					waste->cards.back()->BringToFront();
					waste->RemoveCard(waste->cards.size()-1);
				}

				else if ((!foundationStacks[3]->cards.empty() && (waste->cards.back()->GetValue()-4)==foundationStacks[3]->cards.back()->GetValue()) || ((waste->cards.back()->GetValue())<5 && foundationStacks[3]->cards.size()==0)) {
					waste->cards.back()->SetParentStack(foundationStacks[3]);
					foundationStacks[3]->AddCard(waste->cards.back());
					waste->cards.back()->BringToFront();
					waste->RemoveCard(waste->cards.size()-1);
				}
				else {
					nCMFW = true;
				}
			}
		}
		else {
			nCMFW = true;
		}

		Tableau* tableau0 = dynamic_cast<Tableau*>(tableauStacks[0]);
		Tableau* tableau1 = dynamic_cast<Tableau*>(tableauStacks[1]);
		Tableau* tableau2 = dynamic_cast<Tableau*>(tableauStacks[2]);
		Tableau* tableau3 = dynamic_cast<Tableau*>(tableauStacks[3]);
		Tableau* tableau4 = dynamic_cast<Tableau*>(tableauStacks[4]);
		Tableau* tableau5 = dynamic_cast<Tableau*>(tableauStacks[5]);
		Tableau* tableau6 = dynamic_cast<Tableau*>(tableauStacks[6]);

		if (!tableau0->cards.empty()) {
			while (!tableau0->cards.empty() && !nCMFT0) {
				if ((!foundationStacks[0]->cards.empty() && (tableau0->cards.back()->GetValue()-4)==foundationStacks[0]->cards.back()->GetValue()) || ((tableau0->cards.back()->GetValue())<5 && foundationStacks[0]->cards.size()==0)) {
					tableau0->cards.back()->SetParentStack(foundationStacks[0]);
					foundationStacks[0]->AddCard(tableau0->cards.back());
				}

				else if ((!foundationStacks[1]->cards.empty() && (tableau0->cards.back()->GetValue()-4)==foundationStacks[1]->cards.back()->GetValue()) || ((tableau0->cards.back()->GetValue())<5 && foundationStacks[1]->cards.size()==0)) {
					tableau0->cards.back()->SetParentStack(foundationStacks[1]);
					foundationStacks[1]->AddCard(tableau0->cards.back());
				}

				else if ((!foundationStacks[2]->cards.empty() && (tableau0->cards.back()->GetValue()-4)==foundationStacks[2]->cards.back()->GetValue()) || ((tableau0->cards.back()->GetValue())<5 && foundationStacks[2]->cards.size()==0)) {
					tableau0->cards.back()->SetParentStack(foundationStacks[2]);
					foundationStacks[2]->AddCard(tableau0->cards.back());
				}

				else if ((!foundationStacks[3]->cards.empty() && (tableau0->cards.back()->GetValue()-4)==foundationStacks[3]->cards.back()->GetValue()) || ((tableau0->cards.back()->GetValue())<5 && foundationStacks[3]->cards.size()==0)) {
					tableau0->cards.back()->SetParentStack(foundationStacks[3]);
					foundationStacks[3]->AddCard(tableau0->cards.back());
				}
				else {
					nCMFT0 = true;
				}
				if (!nCMFT0) {
					tableau0->cards.back()->BringToFront();
					tableau0->RemoveCard();
					if (!tableau0->cards.empty()) {
						tableau0->cards.back()->SetCardOpen(true);
						tableau0->cards.back()->SetCardPicture(tableau0->cards.back()->GetValue(),tableau0->cards.back()->GetCardOpen());
					}
				}
			}
		}
		else {
			nCMFT0 = true;
		}

		if (!tableau1->cards.empty()) {
			while (!tableau1->cards.empty() && !nCMFT1) {
				if ((!foundationStacks[0]->cards.empty() && (tableau1->cards.back()->GetValue()-4)==foundationStacks[0]->cards.back()->GetValue()) || ((tableau1->cards.back()->GetValue())<5 && foundationStacks[0]->cards.size()==0)) {
					tableau1->cards.back()->SetParentStack(foundationStacks[0]);
					foundationStacks[0]->AddCard(tableau1->cards.back());
				}

				else if ((!foundationStacks[1]->cards.empty() && (tableau1->cards.back()->GetValue()-4)==foundationStacks[1]->cards.back()->GetValue()) || ((tableau1->cards.back()->GetValue())<5 && foundationStacks[1]->cards.size()==0)) {
					tableau1->cards.back()->SetParentStack(foundationStacks[1]);
					foundationStacks[1]->AddCard(tableau1->cards.back());
				}

				else if ((!foundationStacks[2]->cards.empty() && (tableau1->cards.back()->GetValue()-4)==foundationStacks[2]->cards.back()->GetValue()) || ((tableau1->cards.back()->GetValue())<5 && foundationStacks[2]->cards.size()==0)) {
					tableau1->cards.back()->SetParentStack(foundationStacks[2]);
					foundationStacks[2]->AddCard(tableau1->cards.back());
				}

				else if ((!foundationStacks[3]->cards.empty() && (tableau1->cards.back()->GetValue()-4)==foundationStacks[3]->cards.back()->GetValue()) || ((tableau1->cards.back()->GetValue())<5 && foundationStacks[3]->cards.size()==0)) {
					tableau1->cards.back()->SetParentStack(foundationStacks[3]);
					foundationStacks[3]->AddCard(tableau1->cards.back());
				}
				else {
					nCMFT1 = true;
				}
				if (!nCMFT1) {
					tableau1->cards.back()->BringToFront();
					tableau1->RemoveCard();
					if (!tableau1->cards.empty()) {
						tableau1->cards.back()->SetCardOpen(true);
						tableau1->cards.back()->SetCardPicture(tableau1->cards.back()->GetValue(),tableau1->cards.back()->GetCardOpen());
					}
				}
			}
		}
		else {
			nCMFT1 = true;
		}

		if (!tableau2->cards.empty()) {
			while (!tableau2->cards.empty() && !nCMFT2) {
				if ((!foundationStacks[0]->cards.empty() && (tableau2->cards.back()->GetValue()-4)==foundationStacks[0]->cards.back()->GetValue()) || ((tableau2->cards.back()->GetValue())<5 && foundationStacks[0]->cards.size()==0)) {
					tableau2->cards.back()->SetParentStack(foundationStacks[0]);
					foundationStacks[0]->AddCard(tableau2->cards.back());
				}

				else if ((!foundationStacks[1]->cards.empty() && (tableau2->cards.back()->GetValue()-4)==foundationStacks[1]->cards.back()->GetValue()) || ((tableau2->cards.back()->GetValue())<5 && foundationStacks[1]->cards.size()==0)) {
					tableau2->cards.back()->SetParentStack(foundationStacks[1]);
					foundationStacks[1]->AddCard(tableau2->cards.back());
				}

				else if ((!foundationStacks[2]->cards.empty() && (tableau2->cards.back()->GetValue()-4)==foundationStacks[2]->cards.back()->GetValue()) || ((tableau2->cards.back()->GetValue())<5 && foundationStacks[2]->cards.size()==0)) {
					tableau2->cards.back()->SetParentStack(foundationStacks[2]);
					foundationStacks[2]->AddCard(tableau2->cards.back());
				}

				else if ((!foundationStacks[3]->cards.empty() && (tableau2->cards.back()->GetValue()-4)==foundationStacks[3]->cards.back()->GetValue()) || ((tableau2->cards.back()->GetValue())<5 && foundationStacks[3]->cards.size()==0)) {
					tableau2->cards.back()->SetParentStack(foundationStacks[3]);
					foundationStacks[3]->AddCard(tableau2->cards.back());
				}
				else {
					nCMFT2 = true;
				}
				if (!nCMFT2) {
					tableau2->cards.back()->BringToFront();
					tableau2->RemoveCard();
					if (!tableau2->cards.empty()) {
						tableau2->cards.back()->SetCardOpen(true);
						tableau2->cards.back()->SetCardPicture(tableau2->cards.back()->GetValue(),tableau2->cards.back()->GetCardOpen());
					}
				}
			}
		}
		else {
			nCMFT2 = true;
		}

		if (!tableau3->cards.empty()) {
			while (!tableau3->cards.empty() && !nCMFT3) {
				if ((!foundationStacks[0]->cards.empty() && (tableau3->cards.back()->GetValue()-4)==foundationStacks[0]->cards.back()->GetValue()) || ((tableau3->cards.back()->GetValue())<5 && foundationStacks[0]->cards.size()==0)) {
					tableau3->cards.back()->SetParentStack(foundationStacks[0]);
					foundationStacks[0]->AddCard(tableau3->cards.back());
				}

				else if ((!foundationStacks[1]->cards.empty() && (tableau3->cards.back()->GetValue()-4)==foundationStacks[1]->cards.back()->GetValue()) || ((tableau3->cards.back()->GetValue())<5 && foundationStacks[1]->cards.size()==0)) {
					tableau3->cards.back()->SetParentStack(foundationStacks[1]);
					foundationStacks[1]->AddCard(tableau3->cards.back());
				}

				else if ((!foundationStacks[2]->cards.empty() && (tableau3->cards.back()->GetValue()-4)==foundationStacks[2]->cards.back()->GetValue()) || ((tableau3->cards.back()->GetValue())<5 && foundationStacks[2]->cards.size()==0)) {
					tableau3->cards.back()->SetParentStack(foundationStacks[2]);
					foundationStacks[2]->AddCard(tableau3->cards.back());
				}

				else if ((!foundationStacks[3]->cards.empty() && (tableau3->cards.back()->GetValue()-4)==foundationStacks[3]->cards.back()->GetValue()) || ((tableau3->cards.back()->GetValue())<5 && foundationStacks[3]->cards.size()==0)) {
					tableau3->cards.back()->SetParentStack(foundationStacks[3]);
					foundationStacks[3]->AddCard(tableau3->cards.back());
				}
				else {
					nCMFT3 = true;
				}
				if (!nCMFT3) {
					tableau3->cards.back()->BringToFront();
					tableau3->RemoveCard();
					if (!tableau3->cards.empty()) {
						tableau3->cards.back()->SetCardOpen(true);
						tableau3->cards.back()->SetCardPicture(tableau3->cards.back()->GetValue(),tableau3->cards.back()->GetCardOpen());
					}
				}
			}
		}
		else {
			nCMFT3 = true;
		}

		if (!tableau4->cards.empty()) {
			while (!tableau4->cards.empty() && !nCMFT4) {
				if ((!foundationStacks[0]->cards.empty() && (tableau4->cards.back()->GetValue()-4)==foundationStacks[0]->cards.back()->GetValue()) || ((tableau4->cards.back()->GetValue())<5 && foundationStacks[0]->cards.size()==0)) {
					tableau4->cards.back()->SetParentStack(foundationStacks[0]);
					foundationStacks[0]->AddCard(tableau4->cards.back());
				}

				else if ((!foundationStacks[1]->cards.empty() && (tableau4->cards.back()->GetValue()-4)==foundationStacks[1]->cards.back()->GetValue()) || ((tableau4->cards.back()->GetValue())<5 && foundationStacks[1]->cards.size()==0)) {
					tableau4->cards.back()->SetParentStack(foundationStacks[1]);
					foundationStacks[1]->AddCard(tableau4->cards.back());;
				}

				else if ((!foundationStacks[2]->cards.empty() && (tableau4->cards.back()->GetValue()-4)==foundationStacks[2]->cards.back()->GetValue()) || ((tableau4->cards.back()->GetValue())<5 && foundationStacks[2]->cards.size()==0)) {
					tableau4->cards.back()->SetParentStack(foundationStacks[2]);
					foundationStacks[2]->AddCard(tableau4->cards.back());
				}

				else if ((!foundationStacks[3]->cards.empty() && (tableau4->cards.back()->GetValue()-4)==foundationStacks[3]->cards.back()->GetValue()) || ((tableau4->cards.back()->GetValue())<5 && foundationStacks[3]->cards.size()==0)) {
					tableau4->cards.back()->SetParentStack(foundationStacks[3]);
					foundationStacks[3]->AddCard(tableau4->cards.back());
				}
				else {
					nCMFT4 = true;
				}
				if (!nCMFT4) {
					tableau4->cards.back()->BringToFront();
					tableau4->RemoveCard();
					if (!tableau4->cards.empty()) {
						tableau4->cards.back()->SetCardOpen(true);
						tableau4->cards.back()->SetCardPicture(tableau4->cards.back()->GetValue(),tableau4->cards.back()->GetCardOpen());
					}
				}
			}
		}
		else {
			nCMFT4 = true;
		}
		if (!tableau5->cards.empty()) {
			while (!tableau5->cards.empty() && !nCMFT5) {
				if ((!foundationStacks[0]->cards.empty() && (tableau5->cards.back()->GetValue()-4)==foundationStacks[0]->cards.back()->GetValue()) || ((tableau5->cards.back()->GetValue())<5 && foundationStacks[0]->cards.size()==0)) {
					tableau5->cards.back()->SetParentStack(foundationStacks[0]);
					foundationStacks[0]->AddCard(tableau5->cards.back());
				}

				else if ((!foundationStacks[1]->cards.empty() && (tableau5->cards.back()->GetValue()-4)==foundationStacks[1]->cards.back()->GetValue()) || ((tableau5->cards.back()->GetValue())<5 && foundationStacks[1]->cards.size()==0)) {
					tableau5->cards.back()->SetParentStack(foundationStacks[1]);
					foundationStacks[1]->AddCard(tableau5->cards.back());
				}

				else if ((!foundationStacks[2]->cards.empty() && (tableau5->cards.back()->GetValue()-4)==foundationStacks[2]->cards.back()->GetValue()) || ((tableau5->cards.back()->GetValue())<5 && foundationStacks[2]->cards.size()==0)) {
					tableau5->cards.back()->SetParentStack(foundationStacks[2]);
					foundationStacks[2]->AddCard(tableau5->cards.back());
				}

				else if ((!foundationStacks[3]->cards.empty() && (tableau5->cards.back()->GetValue()-4)==foundationStacks[3]->cards.back()->GetValue()) || ((tableau5->cards.back()->GetValue())<5 && foundationStacks[3]->cards.size()==0)) {
					tableau5->cards.back()->SetParentStack(foundationStacks[3]);
					foundationStacks[3]->AddCard(tableau5->cards.back());
				}
				else {
					nCMFT5 = true;
				}
				if (!nCMFT5) {
					tableau5->cards.back()->BringToFront();
					tableau5->RemoveCard();
					if (!tableau5->cards.empty()) {
						tableau5->cards.back()->SetCardOpen(true);
						tableau5->cards.back()->SetCardPicture(tableau5->cards.back()->GetValue(),tableau5->cards.back()->GetCardOpen());
					}
				}
			}
		}
		else {
			nCMFT5 = true;
		}

		if (!tableau6->cards.empty()) {
			while (!tableau6->cards.empty() && !nCMFT6) {
				if ((!foundationStacks[0]->cards.empty() && (tableau6->cards.back()->GetValue()-4)==foundationStacks[0]->cards.back()->GetValue()) || ((tableau6->cards.back()->GetValue())<5 && foundationStacks[0]->cards.size()==0)) {
					tableau6->cards.back()->SetParentStack(foundationStacks[0]);
					foundationStacks[0]->AddCard(tableau6->cards.back());
				}

				else if ((!foundationStacks[1]->cards.empty() && (tableau6->cards.back()->GetValue()-4)==foundationStacks[1]->cards.back()->GetValue()) || ((tableau6->cards.back()->GetValue())<5 && foundationStacks[1]->cards.size()==0)) {
					tableau6->cards.back()->SetParentStack(foundationStacks[1]);
					foundationStacks[1]->AddCard(tableau6->cards.back());
				}

				else if ((!foundationStacks[2]->cards.empty() && (tableau6->cards.back()->GetValue()-4)==foundationStacks[2]->cards.back()->GetValue()) || ((tableau6->cards.back()->GetValue())<5 && foundationStacks[2]->cards.size()==0)) {
					tableau6->cards.back()->SetParentStack(foundationStacks[2]);
					foundationStacks[2]->AddCard(tableau6->cards.back());
				}

				else if ((!foundationStacks[3]->cards.empty() && (tableau6->cards.back()->GetValue()-4)==foundationStacks[3]->cards.back()->GetValue()) || ((tableau6->cards.back()->GetValue())<5 && foundationStacks[3]->cards.size()==0)) {
					tableau6->cards.back()->SetParentStack(foundationStacks[3]);
					foundationStacks[3]->AddCard(tableau6->cards.back());
				}
				else {
					nCMFT6 = true;
				}
				if (!nCMFT6) {
					tableau6->cards.back()->BringToFront();
					tableau6->RemoveCard();
					if (!tableau6->cards.empty()) {
						tableau6->cards.back()->SetCardOpen(true);
						tableau6->cards.back()->SetCardPicture(tableau6->cards.back()->GetValue(),tableau6->cards.back()->GetCardOpen());
					}
				}
			}
		}
		else {
			nCMFT6 = true;
		}

		if (nCMFW && nCMFT0 && nCMFT1 && nCMFT2 && nCMFT3 && nCMFT4 && nCMFT5 && nCMFT6) {
			nCMFW = false;
			nCMFT0 = false;
			nCMFT1 = false;
			nCMFT2 = false;
			nCMFT3 = false;
			nCMFT4 = false;
			nCMFT5 = false;
			nCMFT6 = false;
			counter++;
			if (counter==19) {
				AVP=true;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if (Button == mbRight) {
		ChangeCardsStacksByRightClick();
	}
}
//---------------------------------------------------------------------------

void TForm1::AddStacksAndCards(){
	stock = new Stock(0,130,5,this);
	waste = new Waste(1,281,5,this);
	for (int stackNum = 0; stackNum < 4; ++stackNum) {
		foundationStacks.push_back(new Foundation(stackNum+2,583+151*stackNum,5,this));
	}
	for (int stackNum = 0; stackNum < 7; ++stackNum) {
		tableauStacks.push_back(new Tableau (stackNum+6,130+151*stackNum,160,this));
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
//---------------------------------------------------------------------------

void TForm1::DeleteStacksAndCards(){
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
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_SPACE) {
		ManageTimer();
	}
}
//---------------------------------------------------------------------------

void TForm1::CreateGameSnapshot() {
	Waste* wasteSnapshot = new Waste(*waste);
	Stock* stockSnapshot = new Stock(*stock);
	wasteGameSnapshots.push_back(wasteSnapshot);
	stockGameSnapshots.push_back(stockSnapshot);
	std::vector<Foundation*> foundationStacksSnapshot;
	std::vector<Tableau*> tableauStacksSnapshot;


	for (Foundation* foundation : foundationStacks) {
		foundationStacksSnapshot.push_back(new Foundation(*foundation));
	}
	foundationStacksGameSnapshots.push_back(foundationStacksSnapshot);

	for (Tableau* tableau : tableauStacks) {
		tableauStacksSnapshot.push_back(new Tableau(*tableau));
	}
	tableauStacksGameSnapshots.push_back(tableauStacksSnapshot);
}
//---------------------------------------------------------------------------

void TForm1::GetGameSnapshot() {
	DeleteStacksAndCards();
	stock = new Stock(*stockGameSnapshots.back());
	stock->Show();
	waste = new Waste(*wasteGameSnapshots.back());
	waste->Show();

	for (int stackNum = 0; stackNum < 4; ++stackNum) {
		foundationStacks.push_back(new Foundation(*foundationStacksGameSnapshots.back()[stackNum]));
		foundationStacks.back()->Show();
	}

	for (int stackNum = 0; stackNum < 7; ++stackNum) {
		tableauStacks.push_back(new Tableau(*tableauStacksGameSnapshots.back()[stackNum]));
		tableauStacks.back()->Show();
	}


	for (Card* card : stock->cards) {
		card->Show();
	}


	for (Card* card : waste->cards) {
		card->Show();
	}

	for (int stackNum = 0; stackNum < 4; ++stackNum) {
		for (Card* card : foundationStacks[stackNum]->cards) {
			card->Show();
		}
	}


	for (int stackNum = 0; stackNum < 7; ++stackNum) {
		for (Card* card : tableauStacks[stackNum]->cards) {
			card->Show();
		}
	}



	delete stockGameSnapshots.back();
	stockGameSnapshots.pop_back();
	delete wasteGameSnapshots.back();
	wasteGameSnapshots.pop_back();
	for (Foundation* foundation : foundationStacksGameSnapshots.back()) {
		delete foundation;
	}
	foundationStacksGameSnapshots.pop_back();

	for (Tableau* tableau : tableauStacksGameSnapshots.back()) {
		delete tableau;
	}
	tableauStacksGameSnapshots.pop_back();

}
//---------------------------------------------------------------------------

void TForm1::ClearGameSnapshots() {
	for (Stock* stockSnapshot : stockGameSnapshots) {
		delete stockSnapshot;
	}
	stockGameSnapshots.clear();

	for (Waste* wasteSnapshot : wasteGameSnapshots) {
		delete wasteSnapshot;
	}
	wasteGameSnapshots.clear();

	for (std::vector<Foundation*>& foundationSnapshot : foundationStacksGameSnapshots) {
		for (Foundation* foundation : foundationSnapshot) {
			delete foundation;
		}
	}
	foundationStacksGameSnapshots.clear();

	for (std::vector<Tableau*>& tableauSnapshot : tableauStacksGameSnapshots) {
		for (Tableau* tableau : tableauSnapshot) {
			delete tableau;
		}
	}
	tableauStacksGameSnapshots.clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7Click(TObject *Sender)
{
   //	GetGameSnapshot();
}
//---------------------------------------------------------------------------

void TForm1::CountGame(String username) {
	std::ifstream stats("data/Users/stats.txt");
	std::vector<std::string> lines;

    if (!username.IsEmpty()) {
        std::string searchStr = "u:" + std::string(AnsiString(username).c_str()) + ";";
        std::string line;

		while (std::getline(stats, line)) {
			if (line.find(searchStr) != std::string::npos) {
				std::size_t cPos = line.find("c:");

				int cValue = std::stoi(line.substr(cPos + 2, line.find(";", cPos) - (cPos + 2))) + 1;
				line.replace(cPos + 2, line.find(";", cPos) - (cPos + 2), std::to_string(cValue));
            }
			lines.push_back(line);
        }
		stats.close();

        std::ofstream outStats("data/Users/stats.txt");
        for (const auto& updatedLine : lines) {
			outStats << updatedLine << "\n";
		}
		outStats.close();
	}
}
//---------------------------------------------------------------------------

