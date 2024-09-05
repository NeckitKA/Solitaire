﻿//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit7.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm7 *Form7;
//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm7::FormActivate(TObject *Sender)
{
	TForm1* mainForm = dynamic_cast<TForm1*>(Application->MainForm);
	Label1->Caption="Время: "+mainForm->Label1->Caption;
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Button1Click(TObject *Sender)
{
	TForm1* mainForm = dynamic_cast<TForm1*>(Application->MainForm);
	if (mainForm->gameOpen) {
		mainForm->DeleteStacksAndCards();
	}
	mainForm->PrepareFormForGame();
	mainForm->AddStacksAndCards();
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Button2Click(TObject *Sender)
{
	Application->MainForm->Close();
}
//---------------------------------------------------------------------------
