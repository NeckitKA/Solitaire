//---------------------------------------------------------------------------

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
	Label1->Caption="�����: "+mainForm->Label1->Caption;
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
	Form7->ModalResult=mrYes;
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Button2Click(TObject *Sender)
{
	Application->MainForm->Close();
}
//---------------------------------------------------------------------------


void TForm7::GetAndUpdateUserStats(String username) {
    std::ifstream stats("data/Users/stats.txt");
	std::vector<std::string> lines;

    if (!username.IsEmpty()) {
        std::string searchStr = "u:" + std::string(AnsiString(username).c_str()) + ";";
        std::string line;

		while (std::getline(stats, line)) {
            if (line.find(searchStr) != std::string::npos) {
                std::size_t cPos = line.find("c:");
                std::size_t wPos = line.find("w:");

				int cValue = std::stoi(line.substr(cPos + 2, line.find(";", cPos) - (cPos + 2))) + 1;
				int wValue = std::stoi(line.substr(wPos + 2, line.find(";", wPos) - (wPos + 2))) + 1;

                line.replace(cPos + 2, line.find(";", cPos) - (cPos + 2), std::to_string(cValue));
                line.replace(wPos + 2, line.find(";", wPos) - (wPos + 2), std::to_string(wValue));

                Label2->Caption = "���������� ���: " + IntToStr(cValue);
                Label3->Caption = "��������: " + IntToStr(wValue);
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

void __fastcall TForm7::FormShow(TObject *Sender)
{
	TForm1* mainform = dynamic_cast<TForm1*>(Application->MainForm);
	GetAndUpdateUserStats(mainform->user);
}
//---------------------------------------------------------------------------

void __fastcall TForm7::FormClose(TObject *Sender, TCloseAction &Action)
{
    TForm1* mainForm = dynamic_cast<TForm1*>(Application->MainForm);
	if (mainForm->gameOpen) {
		mainForm->DeleteStacksAndCards();
	}
	mainForm->PrepareFormForGame();
	mainForm->AddStacksAndCards();
}
//---------------------------------------------------------------------------

