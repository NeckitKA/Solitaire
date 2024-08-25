//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
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
	PlayOrStop(gameOpen,false);
	Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N10Click(TObject *Sender)
{
	PlayOrStop(gameOpen,false);
	Form3->ShowModal();
    ProcessModalFormResult(Form3->ModalResult);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N11Click(TObject *Sender)
{
	LogoutAccount();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N13Click(TObject *Sender)
{
	PlayOrStop(gameOpen,false);
	Form4->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N14Click(TObject *Sender)
{
	PlayOrStop(gameOpen,false);
	Form5->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N15Click(TObject *Sender)
{
	PlayOrStop(gameOpen,false);
	Form6->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1Click(TObject *Sender)
{
	PlayOrStop(gameOpen,false);
	Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2Click(TObject *Sender)
{
	PlayOrStop(gameOpen,false);
	RegisterOrOpenStatistics(N10->Enabled, Form3, Form4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image3Click(TObject *Sender)
{
	PlayOrStop(gameOpen,true);
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

void __fastcall TForm1::Image3MouseEnter(TObject *Sender)
{
	if (pause) {
		Image3->Picture->LoadFromFile("resources/images/playstroke60x60.png");
	}
	else {
		Image3->Picture->LoadFromFile("resources/images/pausestroke60x60.png");
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

void __fastcall TForm1::Image3MouseLeave(TObject *Sender)
{
	if (pause) {
		Image3->Picture->LoadFromFile("resources/images/play60x60.png");
	}
	else {
		Image3->Picture->LoadFromFile("resources/images/pause60x60.png");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Play();
	AddStacksAndCards();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Close();
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
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
    if (gameOpen) {
		DeleteStacksAndCards();
	}
    Play();
	AddStacksAndCards();
}
//---------------------------------------------------------------------------

// my

void TForm1::ProcessModalFormResult(TModalResult result){
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
		ProcessModalFormResult(Form3->ModalResult);
	}
	else {
		Form4->ShowModal();
	}
}
//---------------------------------------------------------------------------

void TForm1::Play(){
	Timer1->Enabled=true;
	Button1->Visible=false;
	Button2->Visible=false;
	Image3->Visible=true;
	Label1->Visible=true;
	gameOpen = true;
}
//---------------------------------------------------------------------------

void TForm1::PlayOrStop(bool gameOpen, bool I3){
		if (gameOpen) {
			if (pause && I3) {
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

Stack* TForm1::GetStockStack() const
{
	return stock;
}

Stack* TForm1::GetWasteStack() const
{
    return waste;
}
