//---------------------------------------------------------------------------

#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <fstream>
//---------------------------------------------------------------------------
class TForm5 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Memo1ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);

private:	// User declarations
	void OutputUserManualToMemo(){
		std::ifstream usermanual("resources/texts/usermanual.txt");
		if (usermanual.is_open()) {
			std::string line;
			while (std::getline(usermanual, line)) {
				Memo1->Lines->Add(line.c_str());
			}
			usermanual.close();
		}
		else {
            Memo1->Lines->Add("Файл usermanual.txt не найден");
		}
	}
public:		// User declarations
	__fastcall TForm5(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm5 *Form5;
//---------------------------------------------------------------------------
#endif
