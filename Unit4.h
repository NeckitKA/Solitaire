//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <fstream>
#include <string>
//---------------------------------------------------------------------------

struct Player {
		std::string username;
		int gamesPlayed;
		int wins;
};

class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TStringGrid *StringGrid1;
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	void GetUserStats(String username);
	void FillLeaderboard();

public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
