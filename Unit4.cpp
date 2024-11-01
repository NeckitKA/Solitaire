//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void TForm4::GetUserStats(String username){
	std::ifstream stats("data/Users/stats.txt");

	if (!username.IsEmpty()) {
		std::string searchStr = "u:" + std::string(AnsiString(username).c_str()) + ";";
		std::string line;

		while (std::getline(stats, line)) {
			if (line.find(searchStr) != std::string::npos) {
				std::size_t cPos = line.find("c:");
				std::size_t wPos = line.find("w:");
				int cValue = std::stoi(line.substr(cPos + 2, line.find(";", cPos) - (cPos + 2)));
				int wValue = std::stoi(line.substr(wPos + 2, line.find(";", wPos) - (wPos + 2)));
				Label1->Caption="���������� ���: " + IntToStr(cValue);
				Label2->Caption="��������: " + IntToStr(wValue);
				break;
			}
		}
		stats.close();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormShow(TObject *Sender)
{
	TForm1* mainform = dynamic_cast<TForm1*>(Application->MainForm);
	GetUserStats(mainform->user);
	FillLeaderboard();
}
//---------------------------------------------------------------------------

void TForm4::FillLeaderboard() {
    std::ifstream statsFile("data/Users/stats.txt");
    if (!statsFile.is_open()) {
        ShowMessage("�� ������� ������� ���� stats.txt");
        return;
    }

    std::vector<Player> players;
    std::string line;

    // ��������� � ������ ������ ������ � stats.txt
    while (std::getline(statsFile, line)) {
        std::size_t userPos = line.find("u:");
        std::size_t cPos = line.find("c:");
        std::size_t wPos = line.find("w:");

        if (userPos == std::string::npos || cPos == std::string::npos || wPos == std::string::npos) {
            continue; // ���������� ������, ������� �� ������������� �������
        }

        Player player;
        player.username = line.substr(userPos + 2, line.find(";", userPos) - (userPos + 2));
        player.gamesPlayed = std::stoi(line.substr(cPos + 2, line.find(";", cPos) - (cPos + 2)));
        player.wins = std::stoi(line.substr(wPos + 2, line.find(";", wPos) - (wPos + 2)));

        players.push_back(player);
    }

    statsFile.close();

    // ��������� ������� �� ���������� ����� (wins) � ������� ��������
    std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.wins > b.wins;
    });

    // ������������ ����� �� 10 �������
    TStringGrid *grid = this->StringGrid1; // �������� �� ��� ������ TStringGrid
    grid->RowCount = 11; // 10 ����� ������� + 1 ������ ��� ���������

    // ������������� ���������
    grid->Cells[0][0] = "�";
    grid->Cells[1][0] = "��� ������������";
    grid->Cells[2][0] = "������";

    // ��������� ������� ���������������� �������
    for (int i = 0; i < 10 && i < players.size(); ++i) {
        grid->Cells[0][i + 1] = IntToStr(i + 1); // �����
        grid->Cells[1][i + 1] = players[i].username.c_str(); // ��� ������������
        grid->Cells[2][i + 1] = IntToStr(players[i].wins); // ���������� �����
	}
    grid->ColWidths[0] = 20;
    grid->ColWidths[1] = 110;
}
//---------------------------------------------------------------------------


