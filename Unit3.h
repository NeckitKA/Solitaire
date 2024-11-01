//---------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <fstream>
#include <string>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
    TEdit *Edit1;
	TEdit *Edit2;
    TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations

	void Login();
	void Register();
	void loginCompleted();
	void CancelLoginOrRegistration();
	void GetUserData(String username, String password);
	void SaveUserData(UnicodeString username, UnicodeString password);
	int findUser(UnicodeString username);

	//ios::in � ������� ���� � ������ ������ ������; ����� �������� ������� �� ��������� ��� ������� ifstream;
	//ios::out � ������� ���� � ������ ������ ������ (��� ���� ���������� � ������������ ����� ������������); ����� �������� ������� �� ��������� ��� ������� ofstream;
	//ios::app � ������� ���� � ������ ������ ������ � ����� �����;
	//ios::ate � ������������� � ����� ��� ��������� �����;
	//ios::trunc � �������� ����, ��� �� ���������� � ������ ios::out;
	//ios::nocreate � �� ��������� �������� �������� �����, ���� �� �� ����������;
	//ios::noreplace � �� ��������� ������������ ����

	//ifstream ���������
	//ofstream ��������
	//fstream ���������

public:		// User declarations
	__fastcall TForm3(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
