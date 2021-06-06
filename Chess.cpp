#include<iostream>
#include<fstream>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include<math.h>
using namespace std;
#define Black 0
#define Capacity 8
int rpos, cpos;
#define White 1
void getRowColbyLeftClick(int& rpos, int& cpos);
void gotoRowCol(int rpos, int cpos);
void In_It(char Board[][Capacity], int& Turn, char Player_Name[][30]);
void Saved_Game(char Board[][Capacity], int& Turn, char Player_Name[][30]);
void Print_Board(char Board[][Capacity], int Turn, char Player_Name[][30]);
void Display_Turn_Message(char Name[]);
void Ask_For_Selection(int& SRI, int& SCI);
bool Is_Black_Piece(char Symbol);
bool Is_White_Piece(char Symbol);
bool Is_Valid_Selection(char S_Symbol, int Turn, int SRI, int SCI);
void Ask_For_Destination(int& ERI, int& ECI);
bool Is_Valid_Destination(char E_Symbol, int Turn, int ERI, int ECI);
void Make_Move_On_Board(char B[][Capacity], int SRI, int SCI, int ERI, int ECI);
void Turn_Change(int& Turn);
bool North_South_Movement(int SRI, int SCI, int ERI, int ECI);
bool East_West_Movement(int SRI, int SCI, int ERI, int ECI);
bool Sloppy_Movement(int SRI, int SCI, int ERI, int ECI);
bool North_South_Path_Clear(char Board[][Capacity],int SRI, int SCI, int ERI, int ECI);
bool East_West_Path_Clear(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI);
bool Sloppy_Move_Path_Clear(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI);
bool Is_Legal_Move(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI);
bool Rook_Move(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI);
bool Bishop_Move(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI);
bool Queen_Move(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI);
bool Horse_Move(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI);
bool King_Move(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI);
bool Pawn_Move_Black(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI);
bool Pawn_Move_White(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI);
void Pawn_Promotion(char Board[][Capacity]);
bool isCursorKeyPressed();
void Undo_Reading(char Board[][Capacity], int& Turn, char Player_Name[][30]);
void Undo_Writing(char Board[][Capacity], int& Turn, char Player_Name[][30]);
void Highlight(char Board[8][8], int SRI, int SCI, int Turn);

int main()
{
srand(time(0));
char Board[Capacity][Capacity],Test[Capacity][Capacity],Undo[Capacity][Capacity];
char S_Symbol, E_Symbol, Choice,Undo_Choice;
char Player_Name[2][30];
int Turn, SRI, SCI, ERI, ECI, DSRI, DSCI;
cout << "Do you want to play the saved game?";
cin >> Choice;
if (Choice == 'N' || Choice == 'n')
{
In_It(Board, Turn, Player_Name);
Print_Board(Board, Turn, Player_Name);
Undo_Reading(Board, Turn, Player_Name);
Display_Turn_Message(Player_Name[Turn]);

do
{
do
{
Ask_For_Selection(SRI, SCI);
if ((SRI == 2 && SCI == 30) || (SRI == 2 && SCI == 31) || (SRI == 2 && SCI == 32) || (SRI == 2 && SCI == 33))
goto label;
S_Symbol = Board[SRI][SCI];
} while (!Is_Valid_Selection(S_Symbol, Turn, SRI, SCI));

if (Is_Valid_Selection(S_Symbol, Turn, SRI, SCI))
{
Print_Board(Board, Turn, Player_Name);
Highlight(Board, SRI, SCI, Turn);
Display_Turn_Message(Player_Name[Turn]);
gotoRowCol(SRI, SCI);
}
            do
{
Ask_For_Destination(ERI, ECI);
if ((ERI == 2 && ECI == 30) || (ERI == 2 && ECI == 31) || (ERI == 2 && ECI == 32) || (ERI == 2 && ECI == 33))
goto label;
E_Symbol = Board[ERI][ECI];
if (!Is_Valid_Destination(E_Symbol, Turn, ERI, ECI) && Is_Valid_Selection(E_Symbol, Turn, ERI, ECI))
{
SRI = ERI;
SCI = ECI;
S_Symbol = E_Symbol;
Print_Board(Board, Turn, Player_Name);
Highlight(Board, SRI, SCI, Turn);
Display_Turn_Message(Player_Name[Turn]);
gotoRowCol(SRI, SCI);
}
} while (!Is_Valid_Destination(E_Symbol, Turn, ERI, ECI));
if (Is_Legal_Move(Board, SRI, SCI, ERI, ECI))
{
Undo_Reading(Board,Turn,Player_Name);
Make_Move_On_Board(Board, SRI, SCI, ERI, ECI);
Pawn_Promotion(Board);
Print_Board(Board, Turn, Player_Name);
label:
if ((SRI == 2 && SCI == 30) || (SRI == 2 && SCI == 31) || (SRI == 2 && SCI == 32) || (SRI == 2 && SCI == 33))
{
Undo_Writing(Board, Turn, Player_Name);
Print_Board(Board, Turn, Player_Name);
}
else
Turn_Change(Turn);
Print_Board(Board, Turn, Player_Name);


Display_Turn_Message(Player_Name[Turn]);
}
} while (true);
}
if (Choice == 'Y' || Choice == 'y')
{
Saved_Game(Board, Turn, Player_Name);
Print_Board(Board, Turn, Player_Name);
Turn_Change(Turn);
Display_Turn_Message(Player_Name[Turn]);
do
{
do
{
Ask_For_Selection(SRI, SCI);
if ((SRI == 2 && SCI == 30) || (SRI == 2 && SCI == 31) || (SRI == 2 && SCI == 32) || (SRI == 2 && SCI == 33))
goto label_1;
S_Symbol = Board[SRI][SCI];
} while (!Is_Valid_Selection(S_Symbol, Turn, SRI, SCI));
if (Is_Valid_Selection(S_Symbol, Turn, SRI, SCI))
{
Print_Board(Board, Turn, Player_Name);
Highlight(Board, SRI, SCI, Turn);
Display_Turn_Message(Player_Name[Turn]);
gotoRowCol(SRI, SCI);
}
do
{
Ask_For_Destination(ERI, ECI);
E_Symbol = Board[ERI][ECI];
if ((ERI == 2 && ECI == 30) || (ERI == 2 && ECI == 31) || (ERI == 2 && ECI == 32) || (ERI == 2 && ECI == 33))
goto label;
if (!Is_Valid_Destination(E_Symbol, Turn, ERI, ECI) && Is_Valid_Selection(E_Symbol, Turn, ERI, ECI))
{
SRI = ERI;
SCI = ECI;
S_Symbol = E_Symbol;
Print_Board(Board, Turn, Player_Name);
Highlight(Board, SRI, SCI, Turn);
Display_Turn_Message(Player_Name[Turn]);
gotoRowCol(SRI, SCI);
}
} while (!Is_Valid_Destination(E_Symbol, Turn, ERI, ECI));
if (Is_Legal_Move(Board, SRI, SCI, ERI, ECI))
{
Undo_Reading(Board, Turn, Player_Name);
Make_Move_On_Board(Board, SRI, SCI, ERI, ECI);
Pawn_Promotion(Board);
Print_Board(Board, Turn, Player_Name);
label_1:
if ((SRI == 2 && SCI == 30) || (SRI == 2 && SCI == 31) || (SRI == 2 && SCI == 32) || (SRI == 2 && SCI == 33))
{
Undo_Writing(Board, Turn, Player_Name);
Print_Board(Board, Turn, Player_Name);
}
else
   Turn_Change(Turn);
Display_Turn_Message(Player_Name[Turn]);
}
} while (true);
}
    return 0;
}
void Undo_Reading(char Board[][Capacity], int& Turn, char Player_Name[][30])
{
ofstream fout("Undo.txt");
for (int ri = 0;ri < 8;ri++)
{
for (int ci = 0;ci < 8;ci++)
{
fout << Board[ri][ci];
}
fout << endl;
}
fout << Turn;
fout << Player_Name[0];
fout << ".";
fout << Player_Name[1];
fout << ".";
}
void Undo_Writing(char Board[][Capacity], int& Turn, char Player_Name[][30])
{
ifstream fin("Undo.txt");
for (int ri = 0;ri < 8;ri++)
{
for (int ci = 0;ci < 8;ci++)
{
fin >> Board[ri][ci];
}
}
fin >> Turn;
fin.getline(Player_Name[0], 30, '.');
fin.getline(Player_Name[1], 30, '.');
}
bool isCursorKeyPressed()
{
char key;
key = GetAsyncKeyState(90);
if (key == 1)
{
return true;
}
return false;
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
DWORD Events;
INPUT_RECORD InputRecord;
SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
do
{
ReadConsoleInput(hInput, &InputRecord, 1, &Events);
if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
{
cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
break;
}
} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
COORD scrn;
HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
scrn.X = cpos;
scrn.Y = rpos;
SetConsoleCursorPosition(hOuput, scrn);
}
void In_It(char Board[][Capacity], int& Turn, char Player_Name[][30])
{
ifstream Rdr("Board.txt");
for (int ri = 0;ri < 8;ri++)
{
for (int ci = 0;ci < 8;ci++)
{
Rdr >> Board[ri][ci];
}
}
cout << "Enter player_1's name :";
cin >> Player_Name[0];
    cout << "Enter player_2's name :";
cin >> Player_Name[1];
Turn = rand() % 2;
}
void Saved_Game(char Board[][Capacity], int& Turn, char Player_Name[][30])
{
ifstream fin("Save.txt");

for (int ri = 0;ri < 8;ri++)
{
for (int ci = 0;ci < 8;ci++)
{
fin >> Board[ri][ci];
}
}
fin >> Turn;
fin.getline(Player_Name[0],30,'.');
fin.getline(Player_Name[1], 30, '.');
}
void Print_Board(char Board[][Capacity], int Turn, char Player_Name[][30])
{
ofstream fout("Save.txt");
system("cls");
for (int ri = 0;ri < 8;ri++)
{
for (int ci = 0;ci < 8;ci++)
{
cout << Board[ri][ci];
fout << Board[ri][ci] ;
}
cout << endl;
}
fout << Turn;
fout << Player_Name[0];
fout << ".";
fout << Player_Name[1];
fout << ".";
gotoRowCol(2, 30);
cout << "Undo";
gotoRowCol(10, 2);
}
void Display_Turn_Message(char Name[])
{
gotoRowCol(10, 2);
cout << endl<< Name << "!" << endl;
}
void Ask_For_Selection(int& SRI, int& SCI)
{
getRowColbyLeftClick(SRI,SCI );
gotoRowCol(SRI,SCI);
}
bool Is_Black_Piece(char Symbol)
{
return 'A' <= Symbol && Symbol <= 'Z';
}
bool Is_White_Piece(char Symbol)
{
return 'a' <= Symbol && Symbol <= 'z';
}
bool Is_Valid_Selection(char S_Symbol, int Turn,int SRI,int SCI)
{
if (SRI >= 0 && SRI < 8 && SCI >= 0 && SCI < 8)
{
if (Turn == Black)
return Is_Black_Piece(S_Symbol);
else
return Is_White_Piece(S_Symbol);
}
else
{
return false;
}
}
void Ask_For_Destination(int& ERI, int& ECI)
{
getRowColbyLeftClick(ERI, ECI);
gotoRowCol(ERI,ECI);
}
bool Is_Valid_Destination(char E_Symbol, int Turn, int ERI, int ECI)
{
if (ERI >= 0 && ERI < 8 && ECI >= 0 && ECI < 8)
{
if (Turn == Black)
{
if (Is_Black_Piece(E_Symbol))
return false;
}
if (Turn == White)
{
if (Is_White_Piece(E_Symbol))
return false;
}
return true;
}
else
return false;
}
void Make_Move_On_Board(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI)
{
Board[ERI][ECI] = Board[SRI][SCI];
Board[SRI][SCI] = '-';
}
void Turn_Change(int& Turn)
{
Turn = (Turn + 1)%2;
}
bool North_South_Movement(int SRI, int SCI, int ERI, int ECI)
{
return((SCI == ECI) && (SRI != ERI));
}
bool East_West_Movement(int SRI, int SCI, int ERI, int ECI)
{
return((SRI == ERI) && (SCI != ECI));
}
bool Sloppy_Movement(int SRI, int SCI, int ERI, int ECI)
{
int Delta_R, Delta_C;
Delta_R = ERI - SRI;
Delta_C = ECI - SCI;
return (abs(Delta_R) == abs(Delta_C));
}
bool North_South_Path_Clear(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI)
{
int RS, RE;
if (SRI < ERI)
{
RS = SRI + 1;
RE = ERI - 1;
}
else
{
RS = ERI + 1;
RE = SRI - 1;
}
for (int R = RS;R <= RE;R++)
{
if (Board[R][SCI] != '-')
return false;
}
return true;
}
bool East_West_Path_Clear(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI)
{
int CS, CE;
if (SCI < ECI)
{
CS = SCI + 1;
CE = ECI - 1;
}
else
{
CS = ECI + 1;
CE = SCI - 1;
}
for (int C = CS;C <= CE;C++)
{
if (Board[SRI][C] != '-')
return false;
}
return true;
}
bool Sloppy_Move_Path_Clear(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI)
{
int Delta_R, Delta_C;
Delta_R = ERI - SRI;
Delta_C = ECI - SCI;
for (int i = 1;i < abs(Delta_R);i++)
{
if ((Delta_R > 0) && (Delta_C < 0))
{
if (Board[SRI + i][SCI - i] != '-')
return false;
   }
if ((Delta_R < 0) && (Delta_C < 0))
{
if (Board[SRI - i][SCI - i] != '-')
return false;
}
if ((Delta_R > 0) && (Delta_C > 0))
{
if (Board[SRI + i][SCI + i] != '-')
return false;
}
if ((Delta_R < 0) && (Delta_C > 0))
{
if (Board[SRI - i][SCI + i] != '-')
return false;
}
}
return true;
}
bool Is_Legal_Move(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI)
{
switch (Board[SRI][SCI])
{
case 'R':
case 'r':
return Rook_Move(Board, SRI, SCI, ERI, ECI);
case 'H':
case 'h':
return Horse_Move(Board, SRI, SCI, ERI, ECI);
case 'B':
case 'b':
return Bishop_Move(Board, SRI, SCI, ERI, ECI);
case 'Q':
case 'q':
return Queen_Move(Board, SRI, SCI, ERI, ECI);
case 'K':
case 'k':
return King_Move(Board, SRI, SCI, ERI, ECI);
case 'P':
return Pawn_Move_Black(Board, SRI, SCI, ERI, ECI);
case 'p':
return Pawn_Move_White(Board, SRI, SCI, ERI, ECI);
}
}
bool Rook_Move(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI)
{
return ((North_South_Movement(SRI, SCI, ERI, ECI)) && (North_South_Path_Clear(Board, SRI, SCI, ERI, ECI))||
(East_West_Movement(SRI, SCI, ERI, ECI)) && (East_West_Path_Clear(Board, SRI, SCI, ERI, ECI)));
}
bool Bishop_Move(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI)
{
return ((Sloppy_Movement(SRI, SCI, ERI, ECI)) && (Sloppy_Move_Path_Clear(Board, SRI, SCI, ERI, ECI)));
}
bool Queen_Move(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI)
{
return ((Bishop_Move(Board, SRI, SCI, ERI, ECI)) || (Rook_Move(Board, SRI, SCI, ERI, ECI)));
}
bool Horse_Move(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI)
{
int Delta_R = abs(ERI - SRI);
int Delta_C = abs(ECI - SCI);
return(((Delta_R == 1) && (Delta_C == 2)) || ((Delta_R == 2) && (Delta_C == 1)));
}
bool King_Move(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI)
{
int Delta_R = abs(ERI - SRI);
int Delta_C = abs(ECI - SCI);
return (((Delta_R == 0) && (Delta_C == 1)) || ((Delta_R == 1) && (Delta_C == 0)) || ((Delta_R == 1) && (Delta_C == 1)));
}
bool Pawn_Move_Black(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI)
{
if ((SRI == ERI - 1) && (ECI == SCI) && (Board[ERI][ECI] == '-'))
{
return true;
}
else if ((SRI == 1) && (ERI == SRI + 2) && (ECI == SCI) && (Board[ERI][ECI] == '-') && (Board[ERI - 1][ECI] == '-'))
{
return true;
}
else if (SRI == ERI - 1 && (ECI - 1 == SCI || ECI + 1 == SCI) && Is_White_Piece(Board[ERI][ECI]))
{
return true;
}
return false;
}
bool Pawn_Move_White(char Board[][Capacity], int SRI, int SCI, int ERI, int ECI)
{
if ((SRI == ERI + 1) && (ECI == SCI) && (Board[ERI][ECI] == '-'))
{
return true;
}
else if ((SRI == 6) && (ERI == SRI - 2) && (ECI == SCI) && (Board[ERI][ECI] == '-') && (Board[ERI+1][ECI] == '-'))
{
return true;
}
else if (SRI == ERI + 1 && (ECI - 1 == SCI || ECI + 1 == SCI) && Is_Black_Piece(Board[ERI][ECI]))
{
return true;
}
return false;
}
void Pawn_Promotion(char Board[][Capacity])
{
for (int i = 0;i <= 7;i++)
{
if (Board[7][i] == 'P')
{
char S_Choice;
system("cls");
cout << endl<<"Which piece you want in your game?";
cin >> S_Choice;
if (S_Choice == 'H' || S_Choice == 'h')
Board[7][i] = 'H';
else if (S_Choice == 'Q' || S_Choice == 'q')
Board[7][i] = 'Q';
else if (S_Choice == 'B' || S_Choice == 'b')
Board[7][i] = 'B';
else if (S_Choice == 'R' || S_Choice == 'r')
Board[7][i] = 'R';
else
i = 0;
}
if (Board[0][i] == 'p')
{
char S_Choice;
system("cls");
cout << "Which piece you want in your game?";
cin >> S_Choice;
if (S_Choice == 'H' || S_Choice == 'h')
Board[0][i] = 'h';
else if (S_Choice == 'Q' || S_Choice == 'q')
Board[0][i] = 'q';
else if (S_Choice == 'B' || S_Choice == 'b')
Board[0][i] = 'b';
else if (S_Choice == 'R' || S_Choice == 'r')
Board[0][i] = 'r';
else
i = 0;
}
}
}
void Highlight(char Board[8][8], int SRI, int SCI, int Turn)
{
for (int ri = 0; ri < 8; ri++) {
for (int ci = 0; ci < 8; ci++) {
if (Is_Legal_Move(Board, SRI, SCI, ri, ci))
{
gotoRowCol(ri,ci);
if (Board[ri][ci] == '-')
cout << "*";
else
cout << Board[ri][ci];
}
}
}
gotoRowCol(SRI, SCI);
}
