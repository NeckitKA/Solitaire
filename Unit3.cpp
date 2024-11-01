//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
	Login();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button2Click(TObject *Sender)
{
	Register();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button3Click(TObject *Sender)
{
	GetUserData(Edit1->Text,Edit2->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button4Click(TObject *Sender)
{
	SaveUserData(Edit1->Text,Edit2->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button5Click(TObject *Sender)
{
    CancelLoginOrRegistration();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
	Label3->Caption="";
    CancelLoginOrRegistration();
}
//---------------------------------------------------------------------------

void TForm3::Login(){
	Button1->Visible=false;
	Button2->Visible=false;
	Button3->Visible=true;
	Button4->Visible=false;
	Button5->Visible=true;

	Edit1->Visible=true;
	Edit2->Visible=true;

	Label1->Visible=true;
	Label2->Visible=true;
}
//---------------------------------------------------------------------------

void TForm3::Register(){
	Button1->Visible=false;
	Button2->Visible=false;
	Button3->Visible=false;
	Button4->Visible=true;
	Button5->Visible=true;

	Edit1->Visible=true;
	Edit2->Visible=true;

	Label1->Visible=true;
	Label2->Visible=true;
}
//---------------------------------------------------------------------------

void TForm3::loginCompleted(){
	CancelLoginOrRegistration();
	this->ModalResult=mrYes;
}
//---------------------------------------------------------------------------

void TForm3::CancelLoginOrRegistration(){
	Button1->Visible=true;
	Button2->Visible=true;
	Button3->Visible=false;
	Button4->Visible=false;
	Button5->Visible=false;

	Edit1->Visible=false;
	Edit2->Visible=false;

	Edit1->Text="";
	Edit2->Text="";

	Label1->Visible=false;
	Label2->Visible=false;
	Label3->Visible=false;
}
//---------------------------------------------------------------------------

void TForm3::GetUserData(String username, String password){
	if (findUser(username)==1){
		std::ifstream credentials("data/Users/credentials.txt");
		if (!credentials.is_open()) {
			Label3->Visible=true;
			Label3->Caption="���� credentials.txt ����������";
		}
		else {
			if (!username.IsEmpty() && !password.IsEmpty()){
				std::string searchStr = "u:"+
				  std::string(AnsiString(username).c_str())+";p:"+
				  std::string(AnsiString(password).c_str())+";";
				std::string line;
				while (std::getline(credentials, line)) {
					if (line.find(searchStr) != std::string::npos) {
						Label3->Visible=true;
						Label3->Caption="���� ��������";
						credentials.close();
						TForm1* mainForm = dynamic_cast<TForm1*>(Application->MainForm);
						mainForm->user=username;
						loginCompleted();
					}
				}
				credentials.close();
			}
			else{
				Label3->Visible=true;
				Label3->Caption="��������� ��� ����";
			}
		}
	}
	else if (findUser(username)==2) {
		Label3->Visible=true;
		Label3->Caption="���� credentials.txt ����������";
	}
	else if (findUser(username)==0 && !username.IsEmpty() &&
	 !password.IsEmpty()) {
		Label3->Visible=true;
		Label3->Caption="������������ ��� ��� ������";
	}
	else{
		Label3->Visible=true;
		Label3->Caption="��������� ��� ����";
	}
}
//---------------------------------------------------------------------------

void TForm3::SaveUserData(UnicodeString username, UnicodeString password){
	if (findUser(username)==0) {
		std::ofstream credentials("data/Users/credentials.txt",ios::app);
		std::ofstream stats("data/Users/stats.txt",ios::app);
		if (credentials.is_open() && stats.is_open()) {
			if (!username.IsEmpty() && !password.IsEmpty()) {
				credentials << "u:" << AnsiString(username).c_str() << ";p:" << AnsiString(password).c_str() << ";\n";
				credentials.close();
				stats<<"u:" << AnsiString(username).c_str() <<  ";c:0;w:0;\n";
				stats.close();
                TForm1* mainForm = dynamic_cast<TForm1*>(Application->MainForm);
				mainForm->user=username;
				loginCompleted();
			}
			else{
				Label3->Visible=true;
				Label3->Caption="��������� ��� ����";
			}
		}
		else {
			Label3->Visible=true;
			Label3->Caption="���� credentials.txt ��� stats.txt ����������";
		}
	}
	else if (findUser(username)==2) {
		Label3->Visible=true;
		Label3->Caption="���� credentials.txt ����������";
	}
	else{
		Label3->Visible=true;
		Label3->Caption="��� ������";
	}
}
//---------------------------------------------------------------------------

int TForm3::findUser(UnicodeString username){
	std::ifstream credentials("data/Users/credentials.txt");
	if (!credentials.is_open()) {
		return 2;
	}
	std::string searchStr = "u:"+std::string(AnsiString(username).c_str())+";";
	std::string line;
	while (std::getline(credentials, line)) {
		if (line.find(searchStr) != std::string::npos) {
			credentials.close();
			return 1;
		}
	}
	credentials.close();
	return 0;
}
//---------------------------------------------------------------------------
