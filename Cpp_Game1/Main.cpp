#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
#include <cstdio>

const int Scene_Logo = 0;
const int Scene_Main = 1;
const int Scene_Story = 2;
const int Scene_Stage = 3;
const int Scene_Ending = 4;
const int Scene_Exit = 5;

int SceneState = 0;

int i = 0;
int turn = 0;

typedef struct sInfo
{
	int HP;
	int MP;

	int ATK;
	int DEF;

	int Level;
	int Speed;

	int EXP;
	int Gold;

} INFO;

typedef struct tagObject
{
	char* Name;
	INFO Info;
} OBJECT;

typedef struct Buff
{
	int ATKBF;
	int DEFBF;

	int EXPBF;
	int GoldBF;

}BUFF;

typedef struct Shop
{
	int Sword;
	int Armor;

	int Shoes;
	int Amulet;

}SHOP;

char* SetName();
void InitializePlayer(OBJECT* _Obj);
void InitializeEnemy1(OBJECT* _Obj);
void InitializeEnemy2(OBJECT* _Obj);
void InitializeEnemy3(OBJECT* _Obj);
void InitializeEnemy4(OBJECT* _Obj);
void InitializeEnemy5(OBJECT* _Obj);

void SceneManager(OBJECT* _Player, OBJECT* _Enemy1, OBJECT* _Enemy2, OBJECT* _Enemy3, OBJECT* _Enemy4, OBJECT* _Enemy5, int _count);

void LogoScene();
int MainScene();
void StoryScene();
void Tutorial(OBJECT* _Enemy);
void StageScene(OBJECT* _Player, OBJECT* _Enemy1, OBJECT* _Enemy2, OBJECT* _Enemy3, OBJECT* _Enemy4, OBJECT* _Enemy5);
int Turn(OBJECT* _Player, OBJECT* _Enemy);
void PlayerAtk(OBJECT* _Player, OBJECT* _Enemy);
void EnemyAtk(OBJECT* _Enemy, OBJECT* _Player);
void PlayerSkill(OBJECT* _Player, OBJECT* _Enemy, int _skill);
void Parrying(OBJECT* _Player, OBJECT* _Enemy);
void BattleScene(OBJECT* _Player, OBJECT* _Enemy, int _buff);
void BattleResult(OBJECT* _Player, OBJECT* _Enemy);
void PlayerLvUp(OBJECT* _Player);
void PlayerScene();
void PStatScene(OBJECT* _Player);
void EStatScene(OBJECT* _Enemy);

void ShopScene(OBJECT* _Player, int _str);
int BuffScene();
void EndingScene(OBJECT* _Player, int _count);
int FailScene(OBJECT* _Player);
void ExitScene(int _col1, int _col2);
void BossScene();

void SetPosition(int _x, int _y, char* _str, int _Color = 15);
void SetPositionI(int _x, int _y, int _value, int _Color = 15);
void SetColor(int _Color);
void HideCursor();

int main(void)
{
	HideCursor();

	system("mode con:cols=120 lines=33");

	system("title ������ v0.6");

	system("color 81");

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player);

	OBJECT* Enemy1 = (OBJECT*)malloc(sizeof(OBJECT));
	OBJECT* Enemy2 = (OBJECT*)malloc(sizeof(OBJECT));
	OBJECT* Enemy3 = (OBJECT*)malloc(sizeof(OBJECT));
	OBJECT* Enemy4 = (OBJECT*)malloc(sizeof(OBJECT));
	OBJECT* Enemy5 = (OBJECT*)malloc(sizeof(OBJECT));
	InitializeEnemy1(Enemy1);
	InitializeEnemy2(Enemy2);
	InitializeEnemy3(Enemy3);
	InitializeEnemy4(Enemy4);
	InitializeEnemy5(Enemy5);

	DWORD dwTime = GetTickCount();
	//SetPosition(30, 21, (char*)"�ȳ�", 14);
	SceneManager(Player, Enemy1, Enemy2, Enemy3, Enemy4, Enemy5, dwTime);

	free(Player);
	free(Enemy1);
	free(Enemy2);
	free(Enemy3);
	free(Enemy4);
	free(Enemy5);

	return 0;
}

char* SetName()
{

	char Buffer[128] = "";

	SetPosition(44, 12, (char*)"����� �̸���... : ", 139);
	scanf("%s", Buffer);

	if (strcmp(Buffer, "��浿") == 0)
	{
		SetPosition(60 - (strlen("�׷�, ���� �ٷ� �� ���� ���� ��浿�̴�") / 2), 14, (char*)"�׷�, ���� �ٷ� �� ���� ���� ��浿�̴�", 139);
	}
	else
		SetPosition(60 - (strlen("�� �̸��� �� �ڴ�� ������? �Ҿƹ������� �����ֽ� �� �̸��� ��浿�̴�") / 2), 14, (char*)"�� �̸��� �� �ڴ�� ������? �Ҿƹ������� �����ֽ� �� �̸��� ��浿�̴�", 132);

	Sleep(1500);
	char* pName = (char*)malloc(7);

	strcpy(pName, "��浿");

	return pName;
}

void InitializePlayer(OBJECT* _Player)
{
	_Player->Name = SetName();

	_Player->Info.HP = 200;
	_Player->Info.MP = 5;
	_Player->Info.ATK = 50;
	_Player->Info.DEF = 10;
	_Player->Info.Level = 1;
	_Player->Info.Speed = 3;
	_Player->Info.EXP = 0;
	_Player->Info.Gold = 5000;

}

void InitializeEnemy1(OBJECT* _Obj)
{
	_Obj->Name = (char*)"�ֹ��� �˹��ҳ�";

	_Obj->Info.HP = 100;
	_Obj->Info.MP = 0;
	_Obj->Info.ATK = 20;
	_Obj->Info.DEF = 10;
	_Obj->Info.Level = 1;
	_Obj->Info.Speed = 1;
	_Obj->Info.EXP = 120;
	_Obj->Info.Gold = 2000;
}

void InitializeEnemy2(OBJECT* _Obj)
{
	_Obj->Name = (char*)"�ذ� ��ɲ�";

	_Obj->Info.HP = 400;
	_Obj->Info.MP = 0;
	_Obj->Info.ATK = 50;
	_Obj->Info.DEF = 5;
	_Obj->Info.Level = 3;
	_Obj->Info.Speed = 3;
	_Obj->Info.EXP = 330;
	_Obj->Info.Gold = 5000;
}

void InitializeEnemy3(OBJECT* _Obj)
{
	_Obj->Name = (char*)"�渶���� ��X��";

	_Obj->Info.HP = 1000;
	_Obj->Info.MP = 5;
	_Obj->Info.ATK = 150;
	_Obj->Info.DEF = 50;
	_Obj->Info.Level = 9;
	_Obj->Info.Speed = 10;
	_Obj->Info.EXP = 1150;
	_Obj->Info.Gold = 10000;
}

void InitializeEnemy4(OBJECT* _Obj)
{
	_Obj->Name = (char*)"�ذ� ŷ";

	_Obj->Info.HP = 3000;
	_Obj->Info.MP = 5;
	_Obj->Info.ATK = 250;
	_Obj->Info.DEF = 50;
	_Obj->Info.Level = 30;
	_Obj->Info.Speed = 30;
	_Obj->Info.EXP = 1850;
	_Obj->Info.Gold = 30000;
}

void InitializeEnemy5(OBJECT* _Obj)
{
	_Obj->Name = (char*)"�μ���ź���� X��";

	_Obj->Info.HP = 22222;
	_Obj->Info.MP = 22;
	_Obj->Info.ATK = 222;
	_Obj->Info.DEF = 222;
	_Obj->Info.Level = 222;
	_Obj->Info.Speed = 222;
	_Obj->Info.EXP = 2222;
	_Obj->Info.Gold = 222222;
}

void SceneManager(OBJECT* _Player, OBJECT* _Enemy1, OBJECT* _Enemy2, OBJECT* _Enemy3, OBJECT* _Enemy4, OBJECT* _Enemy5, int _count)
{
	switch (SceneState)
	{
	case Scene_Logo:
		LogoScene();

	case Scene_Main:
		MainScene();

	case Scene_Story:
		StoryScene();
		SceneState++;

	case Scene_Stage:
		StageScene(_Player, _Enemy1, _Enemy2, _Enemy3, _Enemy4, _Enemy5);

	case Scene_Ending:
		EndingScene(_Player, _count);

	case Scene_Exit:
		ExitScene(11, 14);
		break;
	}
}

void LogoScene()
{
	system("cls");
	int Width = 10;
	int Height = 0;

	SetPosition(Width, Height + 1, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&#GP555555555PGB&@@@@@@@@", 10);
	SetPosition(Width, Height + 2, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&P55PPGGGGGGGGGPP555G#@@@@@", 10);
	SetPosition(Width, Height + 3, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BJPGGGGGGGGGGGGGGGGGGP55B@@@", 10);
	SetPosition(Width, Height + 4, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#?GGGGGGGGGGGGGGGGGGGGGGPYY&@", 10);
	SetPosition(Width, Height + 5, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Y5GGGGGGGGGGGGGGGGGGGGGGGGP?&", 10);
	SetPosition(Width, Height + 6, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@?GGGGPPGGGGGGGGGGGGGGGGGGGGY5", 10);
	SetPosition(Width, Height + 7, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#B#J5GGJJ77GGGGGGGGGGGGGGGGGGGP?", 10);
	SetPosition(Width, Height + 8, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@5Y55YYGP~:~YGGGGGGGGGGGGGGGGGGGG?", 10);
	SetPosition(Width, Height + 9, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@5YGGGP5J5GG55GP55JPGGGGGGGGGGGGG5Y", 10);
	SetPosition(Width, Height + 10, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&@@@@@@&?GGGG5Y#@@@@PYP?~~!PYPGGGGGGGGGG?#", 10);
	SetPosition(Width, Height + 11, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&BGPP55555555PP575GGGPJ#@@@@GJG!.!YB?PGGGGGGGGPJG@", 10);
	SetPosition(Width, Height + 12, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#P555PPGGGGGGGGGGGPJ?5GGGGYPGP55GGGP5P5GGGGGGGGPJJ?B@", 10);
	SetPosition(Width, Height + 13, (char*)"@@@@@@@@@@@@@@@@@@@@@@&GPPPPPB@@@@@@@@@&####&&5YPGGGGGGGGGGGGGGGGJBB?YGGGGGPGGGGGGGG55GGGG5JYY?G@YY@", 10);
	SetPosition(Width, Height + 14, (char*)"@@@@@@@@@@@@@@@@@@@@&PY5PGGGP5YG@@@@@BGGB#&#J?PGGGGGGGGGGGGGGGGGGJ5G#P7YPGGGGGGGGGGP?5GGYJ5G&@@@B5&@", 10);
	SetPosition(Width, Height + 15, (char*)"@@@@@@@@@@@@@@@@@@@#J5GGGGGGGGG5J&@BPG&@@@&Y5GGGGGGGGGPYJ5PP555PGG5P55PPYYY5PGGGGGGYP@@G?&@@@&BPB@@@", 10);
	SetPosition(Width, Height + 16, (char*)"@@@@@@@@@@@@@@@@@@#?PGGGGGGGGGGGP?5G@@@@@@J5GGGGGGP55PPGB@@@@@#GY5GGGGGGGGP5YYY55YJY&@&?JPBGYJ#@@@@@", 10);
	SetPosition(Width, Height + 17, (char*)"@@@@@@@@@@@@@@@@@@Y5GGGGGGGGGGGGYY&@@@@@@#?GGGGGPYP#@@@@@@@@@@@@@GJGGGGGGGGGGGPPPPGPJGY5GPPPGJB@@@@@", 10);
	SetPosition(Width, Height + 18, (char*)"@@@@@@@@@@@@@@@@@B?GGGGGGGGGGGGYY@@@@@@@@@JPGGGPJ&@@@@@@@@@@@@@@@@GJGGGGGGGGGGGGGGGGG7JGGGGGGG?#@@@@", 10);
	SetPosition(Width, Height + 19, (char*)"@@@@@@@@@@@@@@@@@55GGGGGGGGGGG5!#@@@@@@@@GJJGGGPY@@@@@@@@@@@@@@@@@&?GGGGGGGGGGGGGGGGG5GGGGGGGGPJ@@@@", 10);
	SetPosition(Width, Height + 20, (char*)"@@@@@@@@@@@@@@@@@?GGGGGGGGGPY5!?&@@@@@@@5YGGGGG?G@@@@@@@@@@@@@@@@@PYGGGGGGGGGGGGGGGGGGGGGGGGGGG?#@@@", 10);
	SetPosition(Width, Height + 21, (char*)"@@@@@@@@@@@@@@@@#JGGGGGGGGPY#@5P#@@@@@@&?GGPGGGJG@@@@@@@@@@@@@@@@&?GGGGGGGGGGGGGGGGGGGGGGGGGGGGYP@@@", 10);
	SetPosition(Width, Height + 22, (char*)"@@@@@@@@@@@@@@@@#?P555555575GGYJBG5B@@@@5Y575?5YG@@@@@@@@@@@@@@@BJPGGGGGGGGGGGGGGGGGGGGGGGGGGGGJG@@@", 10);
	SetPosition(Width, Height + 23, (char*)"BPBGGBB#@@@@BPYJJ7J5PPPPPPPPPPGY5Y?J5GB@@#GP5B@@@@@@@@@@@@@@@#P55GGGGGGGGGGGGPP5YPGGGGGGGGGGGGPJ@@@@", 10);
	SetPosition(Width, Height + 24, (char*)"?&@@&&#B5JGY?Y5PGGGGGGGGGGGGGGGGGGGGGP5YG&@@@@@@@@@@@@@@@&BP55PGGGGGGGGGGPP55Y5P5PY555555555555&@@@@", 10);
	SetPosition(Width, Height + 25, (char*)"G5@@@@@@&?JPGGGGGGGGGGGGGGGGGGGGGGGGGGGGP55PPGBBBBBBGGPP555PGGGGGGGGGG5!JPGB&@@@@@&&#######&&@@@@@@@", 10);
	SetPosition(Width, Height + 26, (char*)"@5G@@@@@@@YYGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGPPPPPPPPPPPGGGGGGGGGGGP5YYY555G@@@@@@@@@@@@@@@@@@@@@@@@@", 10);
	SetPosition(Width, Height + 27, (char*)"@@5B@@@@@@@PYGGGGGGGGGGGGGGGGGGGGGGGGGGGGPGGGGGGGGGGGGGGGGGGPGP5YYY5GGGGGG5YG@@@@@@@@@@@@@@@@@@@@@@@", 10);
	SetPosition(Width, Height + 28, (char*)"@@@GPB@@@@@@JPGGGGGGGGGGGGGGPPP55555Y5PP5?JPP555555555555555??J55PPPPPP55555J@@@@@@@@@@@@@@@@@@@@@@@", 10);
	SetPosition(Width, Height + 29, (char*)"@@@@&BPP@@@@55GGGGGPP555555PPGB#####55PB#&@@@@@&&&&&&&&&&&&@@&BGGGGGBBB####&@@@@@@@@@@@@@@@@@@@@@@@@", 10);
	Sleep(2000);
	system("cls");
	/*SetPosition(Width + 5, Height + 1, (char*)"@@@@@@@@@@@@@@@@@@@@GPPPPPPG&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 2, (char*)"@@@@@@#BB@@@@@@@@@@PPGGGGGGPPG&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 3, (char*)"@@@@@#GGJ#@@@@@@@@@5GPJ5GGGGGP5@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 4, (char*)"@@@@@@#YPP5&@@@@@@#5GP?Y5JJGGGY&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 5, (char*)"@@@@@@@B5GPP&@@@@@P5PJG@5YYGP5G@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 6, (char*)"@@@@@@@@5PGG5#@@@@@GJ55YPG55G#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 7, (char*)"@@@@@@@@#P5YP5&@@@@&P555PP5&@@@@@@@@@@@@@@@@@&BG&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 8, (char*)"@@@@@@@@&@&B#&&&&&#@@@&G##&@@@@@@@@@@@@@@@&BPJG#G#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 9, (char*)"@@@@@@&&@@&&&@@@&&#P#&&&@@@@@@@@@@@@@@@BGGPPPPB##&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 10, (char*)"@@@@@@&@@&@@@@@@@@&?7GP&&&&&&&@@@@@@@@#YGGGP5@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 11, (char*)"@&@@@@&@&&@@@@@&&#P5?~~P@@@&&&&&&&@@@@&5PPPB&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 12, (char*)"5PPG#@@&@@@@@B5?5B&@&G5Y&@@&@@&&&@@&@@@&GG@@@@@@@@@@BPP#@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 13, (char*)"B5GGPPGB&@@@@PG&@@@@@@&G5G###@@@@&@@@@@@@@@@@@@#5YPJ~^^!Y&@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 14, (char*)"@&PPGGJ!B&@@@G#@@@@@@@@&GPP5?P@@@@@@@@@@@@@@@@@?^^^^~~~~^7&@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 15, (char*)"@@@#GGYG@#@@@@P@@@@@@@@@&GGG7~B@@@@@@@@@@&##&&B7?5BGJ~~~~^Y@@@@@@@@@@@@@@@@@@#BB");
	SetPosition(Width + 5, Height + 16, (char*)"@@@@@@@@@&&@@@G&@@@@@@@@@&GGP?Y@@@@@@@@@B#@&#GPG@@G&@BJ~~~!&@@@@@@@@@@@@@&#BG#&@");
	SetPosition(Width + 5, Height + 17, (char*)"@@@@@@@@@@&&@@G&@@@@@@@@@@GGGPP@@@@@@@@@G@@@@@GB&&PPP#BP?^7@@@@@@@@@@@&#BB##@@@@");
	SetPosition(Width + 5, Height + 18, (char*)"@@@@@@@@@@@@&@&G&@@@@@@@@@GGP5@@@@@@@@@@B&@@&BBBGGYG#&#B@5G@@@@@@@&&&GBBB@@@@@@@");
	SetPosition(Width + 5, Height + 19, (char*)"@@@@@@@@&BPG#&@&P5#@@@@@@&GPG&@@@@@@@@@@&B@@@P5BGBP#@@B&@@@@@@&&######&@@@@@@@@@");
	SetPosition(Width + 5, Height + 20, (char*)"@@@@@@BPPPP5YB&@@&BP#&@&&GGPB@@@@@@@@@@@@BG@@BG&&@@B##@@@&&#######&&@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 21, (char*)"@@@&BGYPGPGB&&@&@@@@###BPPGG5#@@@@@@@&@@@BBB&@@##&#PPB&#####&#&&@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 22, (char*)"@@@GPPGPPP@@@@@@&@@@@@@@@P5GG5#@@@@@&BB@&B&BP#@@BB&PGP##&&&@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 23, (char*)"@@@@@@@@&@@@@@@@@@@@@@@@@@G5GP5@@@@@B@G#&B@@@##BPGBGPB&@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 24, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@GPGPPG@@#&@P##G#@@@@&P#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 25, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&@@B@#G@@GB#@@@@&B@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 26, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&B&B@B@@@##@@@@&B@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 27, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@B#@@@B&@@G#@@@@&B@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 28, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##B&&#@@@@&#@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	Sleep(3000);
	system("cls");*/
	SetPosition(Width + 5, Height + 1, (char*)"                    ~!!!!!!~.", 12);
	SetPosition(Width + 5, Height + 2, (char*)"      :^^          !!~~~~~~!!~.", 12);
	SetPosition(Width + 5, Height + 3, (char*)"     :~~J:         7~!J7~~~~~!7", 12);
	SetPosition(Width + 5, Height + 4, (char*)"      :?!!7.      :7~!Y?7JJ~~~?.", 12);
	SetPosition(Width + 5, Height + 5, (char*)"       ^7~!!.     !7!J~ 7??~!7~", 12);
	SetPosition(Width + 5, Height + 6, (char*)"        7!~~7:     ~J77?!~77~:", 12);
	SetPosition(Width + 5, Height + 7, (char*)"        :!7?!7.    .!777!!7.                 .^~.", 12);
	SetPosition(Width + 5, Height + 8, (char*)"        . .^:.....:   .~::.               .^!J~:~:", 12);
	SetPosition(Width + 5, Height + 9, (char*)"      ..  ...   ..:!:...               ^~~!!!!^::.", 12);
	SetPosition(Width + 5, Height + 10, (char*)"      .  .        .Y5~!.......        :?~~~!7", 12);
	SetPosition(Width + 5, Height + 11, (char*)" .    . ..     ..:!7YGG!   .......    .7!!!^.", 12);
	SetPosition(Width + 5, Height + 12, (char*)"7!!~:  .     ^7Y7^. .~7?.  .  ...  .   .~~          ^!!:", 12);
	SetPosition(Width + 5, Height + 13, (char*)"^7~~!!~^.    !~.      .~7~:::    .             :7?!JGBBP?.", 12);
	SetPosition(Width + 5, Height + 14, (char*)" .!!~~JP^.   ~:        .~!!7Y!                 YBBBBGGGGB5.", 12);
	SetPosition(Width + 5, Height + 15, (char*)"   :~~?~ :    !         .~~~5G^          .::..^5Y7^~JGGGGB?                  :^^", 12);
	SetPosition(Width + 5, Height + 16, (char*)"         ..   ~.         .~~!Y?         ^: .:~!~  ~. ^JGGGP.             .:^~:.", 12);
	SetPosition(Width + 5, Height + 17, (char*)"          ..  ~.          ~~~!!         ~     ~^..!!!:^!YB5           .:^^::", 12);
	SetPosition(Width + 5, Height + 18, (char*)"            . .~.         ~~!7          ^.  .^^^~~?~:.:^ 7~       ...~^^^", 12);
	SetPosition(Width + 5, Height + 19, (char*)"        .^!~:. .!7:      .~!~.          .^   !7^~^!:  ^.      ..::::::.", 12);
	SetPosition(Width + 5, Height + 20, (char*)"      ^!!!!7?^.  .^!:. ..~~!^            ^~  ^~..  ^::   ..:::::::..", 12);
	SetPosition(Width + 5, Height + 21, (char*)"   .^~?!~!~^.. .    :::^!!~~7:       .   ^^^.  ::.:!!^.:::::.:..", 12);
	SetPosition(Width + 5, Height + 22, (char*)"   ~!!~!!!      .        !7~~7:     .^^ .^.^!:  ^^.!~!::...", 12);
	SetPosition(Width + 5, Height + 23, (char*)"        .                 ~7~!7     ^ ~:.^   ::^!~^~!^.", 12);
	SetPosition(Width + 5, Height + 24, (char*)"                           ~!~!!~  :. !::~:    .!:", 12);
	SetPosition(Width + 5, Height + 25, (char*)"                            .....  ^ :~  ~^:    .^", 12);
	SetPosition(Width + 5, Height + 26, (char*)"                                  .^.^ ^   ::    .^", 12);
	SetPosition(Width + 5, Height + 27, (char*)"                                   ^:   ^.  ~:    .^", 12);
	SetPosition(Width + 5, Height + 28, (char*)"                                         ::^..:    .:", 12);


	Sleep(2000);

	SceneState++;
}

int MainScene()
{

	system("cls");
	int Width = 7;
	int MWidth = 47;
	int Height = 2;
	int MHeight = 20;
	int i = 0;

	SetPosition(Width, Height + 1, (char*)"                    ##                        ##                        ##", 8);
	SetPosition(Width, Height + 2, (char*)"    ########        ##      ############      ##      ###########       ##        ################", 8);
	SetPosition(Width, Height + 3, (char*)"  ###      ### #######           ##           ##              ##        ##        ##", 8);
	SetPosition(Width, Height + 4, (char*)"  ##        ##      ##           ##           ##             ##         ##        ##  ", 8);
	SetPosition(Width, Height + 5, (char*)"  ##        ##      ##          ####      ######           ###          ##        ################", 8);
	SetPosition(Width, Height + 6, (char*)"  ###      ### #######        ###  ###        ##       ####             ##               ##", 8);
	SetPosition(Width, Height + 7, (char*)"     ######         ##      ###      ###      ##      ##                ##    ########################", 8);
	SetPosition(Width, Height + 8, (char*)"                                              ##", 8);
	SetPosition(Width, Height + 9, (char*)"      ################          ##            ##         ################           ############", 8);
	SetPosition(Width, Height + 10, (char*)"                    ##          ##                                     ##         ###          ###   ", 8);
	SetPosition(Width, Height + 11, (char*)"                    ##          ##                        ###############         ##            ##   ", 8);
	SetPosition(Width, Height + 12, (char*)"                    ##          ##                        ##                      ###          ###", 8);
	SetPosition(Width, Height + 13, (char*)"                    ##          ################          ################          ############", 8);
	Sleep(1000);

	SetPosition(Width, Height + 1, (char*)"                    ##                        ##                        ##", 14);
	SetPosition(Width, Height + 2, (char*)"    ########        ##      ############      ##      ###########       ##        ################", 14);
	SetPosition(Width, Height + 3, (char*)"  ###      ### #######           ##           ##              ##        ##        ##", 14);
	SetPosition(Width, Height + 4, (char*)"  ##        ##      ##           ##           ##             ##         ##        ##  ", 14);
	SetPosition(Width, Height + 5, (char*)"  ##        ##      ##          ####      ######           ###          ##        ################", 14);
	SetPosition(Width, Height + 6, (char*)"  ###      ### #######        ###  ###        ##       ####             ##               ##", 14);
	SetPosition(Width, Height + 7, (char*)"     ######         ##      ###      ###      ##      ##                ##    ########################", 14);
	SetPosition(Width, Height + 8, (char*)"                                              ##", 14);
	SetPosition(Width, Height + 9, (char*)"      ################          ##            ##         ################           ############", 14);
	SetPosition(Width, Height + 10, (char*)"                    ##          ##                                     ##         ###          ###   ", 14);
	SetPosition(Width, Height + 11, (char*)"                    ##          ##                        ###############         ##            ##   ", 14);
	SetPosition(Width, Height + 12, (char*)"                    ##          ##                        ##                      ###          ###", 14);
	SetPosition(Width, Height + 13, (char*)"                    ##          ################          ################          ############", 14);


	Sleep(1000);
	SetPosition(MWidth, MHeight - 1, (char*)"���ѤѤѤѤѤѤѤѤѤѤѤѦ�", 11);
	SetPosition(MWidth, MHeight, (char*)"��                       ��", 11);
	SetPosition(MWidth, MHeight + 1, (char*)"��       ��     ��       ��", 11);
	SetPosition(MWidth, MHeight + 2, (char*)"��                       ��", 11);
	SetPosition(MWidth, MHeight + 3, (char*)"��       1. �÷���       ��", 11);
	SetPosition(MWidth, MHeight + 4, (char*)"��                       ��", 11);
	SetPosition(MWidth, MHeight + 5, (char*)"��       2. ��  ��       ��", 11);
	SetPosition(MWidth, MHeight + 6, (char*)"��                       ��", 11);
	SetPosition(MWidth, MHeight + 7, (char*)"���ѤѤѤѤѤѤѤѤѤѤѤѦ�", 11);
	SetPosition(MWidth + 10, MHeight + 8, (char*)"�Է� : ", 11);
	scanf("%d", &i);
	Sleep(1000);
	SceneState++;

	return 1;
}

void StoryScene()
{
	system("cls");
	int Height = 5;

	SetPosition((120 / 2) - (strlen("'��浿 ����'") / 2), Height, (char*)"'��浿 ����'", 15);
	Sleep(800);
	SetPosition((120 / 2) - (strlen("�� �� �� �����̰� �ֿ��� �� �༮, ó���� �ҽ��ؼ� ��ĥ ����ش� �����̾�����") / 2), Height + 2, (char*)"�� �� �� �����̰� �ֿ��� �� �༮, ó���� �ҽ��ؼ� ��ĥ ����ش� �����̾�����");
	Sleep(800);
	SetPosition((120 / 2) - (strlen("���ڸ��� ������ ������ �� �μ����� ������ Ŀ�� ���� �аŸ����� �þ��� ������ �о����� ��������.") / 2), Height + 4, (char*)"���ڸ��� ������ ������ �� �μ����� ������ Ŀ�� ���� �аŸ����� �þ��� ������ �о����� ��������.");
	Sleep(800);
	SetPosition((120 / 2) - (strlen("'��...��X�� ���� �� �����ָ� �ȵǰڴ�?' '����! �ʴɷ� �� �� ����? ó�� �� �϶��'") / 2), Height + 6, (char*)"'��...��X�� ���� �� �����ָ� �ȵǰڴ�?' '����! �ʴɷ� �� �� ����? ó�� �� �϶��'");
	Sleep(800);
	SetPosition((120 / 2) - (strlen("���� ���� ������ ������ ����� �ϴ� �༮��...") / 2) + 1, Height + 8, (char*)"���� ���� ������ ������ ����� �ϴ� �༮��...");
	Sleep(800);
	SetPosition((120 / 2) - (strlen("�⳪�� ���� �̹�, ���� �γ��� �ð��� ������. â��� �� �����ص� ���� ������.") / 2) + 1, Height + 10, (char*)"�⳪�� ���� �̹�, ���� �γ��� �ð��� ������. â��� �� �����ص� ���� ������.");
	Sleep(800);
	SetPosition((120 / 2) - (strlen("�ƾ�... �� �����ϰ� ������ ����... 2�⸸�̱�") / 2), Height + 12, (char*)"�ƾ�... �� �����ϰ� ������ ����... 2�⸸�̱�");
	Sleep(800);
	SetPosition((120 / 2) - (strlen("'�˼�' ��浿���� ���ư� ����") / 2) - 1, Height + 16, (char*)"'�˼�' ��浿���� ���ư� ����", 12);
	Sleep(3000);

	SceneState++;
}

void StageScene(OBJECT* _Player, OBJECT* _Enemy1, OBJECT* _Enemy2, OBJECT* _Enemy3, OBJECT* _Enemy4, OBJECT* _Enemy5)
{

	int i = 0;
	srand(time(NULL));
	PlayerScene();
	Tutorial(_Enemy1);
	PlayerScene();

	BattleScene(_Player, _Enemy1, i);
	if (rand() % 2 == 0)
		ShopScene(_Player, 1);
	else
		i = BuffScene();

	BattleScene(_Player, _Enemy2, i);
	if (rand() % 2 == 0)
		ShopScene(_Player, 2);
	else
		i = BuffScene();

	BattleScene(_Player, _Enemy3, i);
	if (rand() % 2 == 0)
		ShopScene(_Player, 3);
	else
		i = BuffScene();

	BattleScene(_Player, _Enemy4, i);
	if (rand() % 2 == 0)
		ShopScene(_Player, 4);
	else
		i = BuffScene();

	BossScene();
	BattleScene(_Player, _Enemy5, i);
	SceneState++;
}

void Tutorial(OBJECT* _Enemy)
{
	int Width = 30;
	int Height = 22;
	SetPosition((120 / 2) - (strlen("�������� ������ ��ŭ �� ���� ������ ���ø� �ʿ䰡 �ְھ�") / 2), Height, (char*)"�������� ������ ��ŭ �� ���� ������ ���ø� �ʿ䰡 �ְھ�", 15);
	Sleep(500);
	SetPosition(Width + 11, Height + 2, ((char*)"�߻��� "));
	SetPosition(Width + 11 + strlen("�߻��� "), Height + 2, _Enemy->Name, 12);
	SetPosition(Width + 11 + strlen("�߻��� ") + strlen(_Enemy->Name), Height + 2, (char*)"��(��) ��Ÿ����!", 15);

	Sleep(500);
	SetPosition((120 / 2) - (strlen("�����ʽ�! �ӵ��� ���� ���� �������� ������") / 2), Height + 4, (char*)"�����ʽ�! �ӵ��� ���� ���� �������� ������", 11);
	Sleep(500);
	SetPosition((120 / 2) - (strlen("�ӵ��� ������ �Ϲ� ���� ��� ��ų�� ����ϸ� ���� ������ �� �ִ�") / 2), Height + 5, (char*)"�ӵ��� ������ �Ϲ� ���� ��� ��ų�� ����ϸ� ���� ������ �� �ִ�", 12);
	Sleep(500);
	SetPosition((120 / 2) - (strlen("��ų�� ����ϱ� ���� �ʿ��� ������ 5�� ������ �����ϸ�, �� ���� ������ 2�� ������ �߰��� ��´�") / 2), Height + 6, (char*)"��ų�� ����ϱ� ���� �ʿ��� ������ 5�� ������ �����ϸ�, �� ���� ������ 2�� ������ �߰��� ��´�", 11);
	Sleep(500);
	SetPosition((120 / 2) - (strlen("��~ �尡�� !") / 2), Height + 8, (char*)"��~ �尡�� !");
	Sleep(3000);
}

void BattleScene(OBJECT* _Player, OBJECT* _Enemy, int _buff)
{
	int i = 1;
	int exit = 0;
	int hp = _Player->Info.HP;
	int atk = _Player->Info.ATK;
	int def = _Player->Info.DEF;
	int spd = _Player->Info.Speed;

	if (_buff == 1)
	{
		_Player->Info.ATK *= 1.3;
	}
	else if (_buff == 2)
	{
		_Player->Info.DEF *= 1.3;
	}
	else if (_buff == 3)
	{
		_Player->Info.Speed += 10;
	}
	while (i)
	{
		int turn;
		for (turn = 1; _Player->Info.HP > 0 && _Enemy->Info.HP > 0; turn++)
		{
			exit = Turn(_Player, _Enemy);
			if (exit == 1)
			{
				_Player->Info.ATK = atk;
				_Player->Info.DEF = def;
				_Player->Info.Speed = spd;
				i = 0;
				break;
			}
		}
		_Player->Info.MP = 5;
		if (_Enemy->Info.HP <= 0)
		{
			_Player->Info.ATK = atk;
			_Player->Info.DEF = def;
			_Player->Info.Speed = spd;
			_Player->Info.HP = hp;
			BattleResult(_Player, _Enemy);
			i = 0;
			break;
		}
		else if (_Player->Info.HP <= 0)
		{
			int j = FailScene(_Player);
			if (j == 1)
				_Player->Info.HP = hp;
			break;
		}

	}

	_buff = 0;
}

void PStatScene(OBJECT* _Player)
{
	int nWidth = 30;
	int Width = 37;
	int Height = 21;
	SetPosition(nWidth, Height, (char*)"��  ��");
	SetPosition(Width, Height, _Player->Name, 11);
	SetPosition(nWidth + 1, Height + 1, (char*)"H  P");
	SetPositionI(Width, Height + 1, _Player->Info.HP, 11);
	SetPosition(nWidth + 1, Height + 2, (char*)"M  P");
	SetPositionI(Width, Height + 2, _Player->Info.MP, 11);
	SetPosition(nWidth, Height + 3, (char*)"���ݷ�");
	SetPositionI(Width, Height + 3, _Player->Info.ATK, 11);
	SetPosition(nWidth, Height + 4, (char*)"����");
	SetPositionI(Width, Height + 4, _Player->Info.DEF, 11);
	SetPosition(nWidth, Height + 5, (char*)"��  ��");
	SetPositionI(Width, Height + 5, _Player->Info.Level, 11);
	SetPosition(nWidth, Height + 6, (char*)"��  ��");
	SetPositionI(Width, Height + 6, _Player->Info.Speed, 11);
	SetPosition(Width + 20, Height + 3, (char*)"V  S", 12);

}

void EStatScene(OBJECT* _Enemy)
{
	int nWidth = 75;
	int Width = 82;
	int Height = 21;
	SetPosition(nWidth, Height, (char*)"��  ��");
	SetPosition(Width, Height, _Enemy->Name, 12);
	SetPosition(nWidth + 1, Height + 1, (char*)"H  P");
	SetPositionI(Width, Height + 1, _Enemy->Info.HP, 12);
	SetPosition(nWidth + 1, Height + 2, (char*)"M  P");
	SetPositionI(Width, Height + 2, _Enemy->Info.MP, 12);
	SetPosition(nWidth, Height + 3, (char*)"���ݷ�");
	SetPositionI(Width, Height + 3, _Enemy->Info.ATK, 12);
	SetPosition(nWidth, Height + 4, (char*)"����");
	SetPositionI(Width, Height + 4, _Enemy->Info.DEF, 12);
	SetPosition(nWidth, Height + 5, (char*)"��  ��");
	SetPositionI(Width, Height + 5, _Enemy->Info.Level, 12);
	SetPosition(nWidth, Height + 6, (char*)"��  ��");
	SetPositionI(Width, Height + 6, _Enemy->Info.Speed, 12);
}

void PlayerAtk(OBJECT* _Player, OBJECT* _Enemy)
{
	int Width = 32;
	int Height = 21;

	system("cls");
	PlayerScene();

	if (_Player->Info.ATK > _Enemy->Info.DEF)
	{
		int dmg = _Player->Info.ATK - _Enemy->Info.DEF;
		SetPosition(Width, Height + 5, _Player->Name, 11);
		SetPosition(Width + strlen(_Player->Name), Height + 5, (char*)"�� ����! ");
		SetPosition(Width + strlen(_Player->Name) + strlen("�� ����! "), Height + 5, _Enemy->Name, 12);
		SetPosition(Width + strlen(_Player->Name) + strlen("�� ����! ") + strlen(_Enemy->Name), Height + 5, (char*)"��(��) ");
		SetPositionI(Width + strlen(_Player->Name) + strlen("�� ����! ") + strlen(_Enemy->Name) + strlen("��(��) "), Height + 5, dmg, 12);
		SetPosition(Width + strlen(_Player->Name) + strlen("�� ����! ") + strlen(_Enemy->Name) + strlen("��(��) ") + sizeof(dmg), Height + 5, (char*)"�� �������� �Ծ��� !");
		_Enemy->Info.HP -= dmg;
	}
	else
	{
		SetPosition(Width, Height + 5, _Player->Name, 11);
		SetPosition(Width + strlen(_Player->Name), Height + 5, (char*)"�� ������ �׸� ȿ�������� ���ߴ�, 1�� �������� ������", 15);
		_Enemy->Info.HP -= 1;
	}
	Sleep(1000);
}

void EnemyAtk(OBJECT* _Enemy, OBJECT* _Player)
{
	int Width = 32;
	int Height = 21;

	system("cls");
	PlayerScene();

	if (_Enemy->Info.ATK > _Player->Info.DEF)
	{
		int dmg = _Enemy->Info.ATK - _Player->Info.DEF;
		SetPosition(Width, Height + 5, _Enemy->Name, 12);
		SetPosition(Width + strlen(_Enemy->Name), Height + 5, (char*)"�� ����! ");
		SetPosition(Width + strlen(_Enemy->Name) + strlen("�� ����! "), Height + 5, _Player->Name, 11);
		SetPosition(Width + strlen(_Enemy->Name) + strlen("�� ����! ") + strlen(_Player->Name), Height + 5, (char*)"��(��) ");
		SetPositionI(Width + strlen(_Enemy->Name) + strlen("�� ����! ") + strlen(_Player->Name) + strlen("��(��) "), Height + 5, dmg, 12);
		SetPosition(Width + strlen(_Enemy->Name) + strlen("�� ����! ") + strlen(_Player->Name) + strlen("��(��) ") + sizeof(dmg), Height + 5, (char*)"�� �������� �Ծ��� !");

		_Player->Info.HP -= dmg;
	}
	else
	{
		SetPosition(Width + 5, Height + 5, _Enemy->Name, 12);
		SetPosition(Width + 5 + strlen(_Enemy->Name), Height + 5, (char*)"�� ������ �׸� ȿ�������� ���ߴ�, 1�� �������� ������", 15);
		_Player->Info.HP -= 1;
	}
	Sleep(1000);
}


void PlayerSkill(OBJECT* _Player, OBJECT* _Enemy, int _skill)
{
	int s1 = _Player->Info.ATK * 2;
	int s3 = _Player->Info.ATK * 20;

	int Width = 38;
	int Height = 21;

	system("cls");
	PlayerScene();

	switch (_skill)
	{
	case 1:
		SetPosition((120 / 2) - (strlen("�ϼ���!") / 2), Height + 3, (char*)"�ϼ���!", 14);
		Sleep(1000);
		SetPosition(Width + 4, Height + 6, _Enemy->Name, 12);
		SetPosition(Width + 4 + strlen(_Enemy->Name), Height + 6, (char*)"���� ", 15);
		SetPositionI(Width + 4 + strlen(_Enemy->Name) + strlen("���� "), Height + 6, s1 - _Enemy->Info.DEF, 12);
		SetPosition(Width + 4 + strlen(_Enemy->Name) + strlen("���� ") + sizeof(s1 - _Enemy->Info.DEF), Height + 6, (char*)"�� �������� ������ !", 15);
		_Enemy->Info.HP -= s1 - _Enemy->Info.DEF;
		_Player->Info.MP -= 1;
		break;
	case 2:
		SetPosition((120 / 2) - (strlen("�׷� !") / 2), Height + 3, (char*)"�׷� !", 14);
		SetPosition(Width + 6, Height + 6, _Player->Name, 11);
		SetPosition(Width + 6 + strlen(_Player->Name), Height + 6, (char*)"�� ����ڼ��� ���ߴ�");
		_Player->Info.MP -= 3;
		break;
	case 3:
		SetPosition((120 / 2) - (strlen("���� ���������� !") / 2), Height + 3, (char*)"���� ���������� !", 12);
		Sleep(1000);
		SetPosition(Width, Height + 6, _Enemy->Name, 12);
		SetPosition(Width + strlen(_Enemy->Name), Height + 6, (char*)"���� ", 15);
		SetPositionI(Width + strlen(_Enemy->Name) + strlen("���� "), Height + 6, s3 - _Enemy->Info.DEF, 12);
		SetPosition(Width + 1 + strlen(_Enemy->Name) + strlen("���� ") + sizeof(s3 - _Enemy->Info.DEF), Height + 6, (char*)"�� �������� ������ !", 15);

		_Enemy->Info.HP -= s3 - _Enemy->Info.DEF;
		_Player->Info.MP -= 8;
		break;
	}
	Sleep(1000);
}

void Parrying(OBJECT* _Player, OBJECT* _Enemy)
{
	int s2 = _Player->Info.ATK;

	int Width = 30;
	int Height = 21;

	system("cls");
	PlayerScene();

	SetPosition(Width, Height + 3, _Enemy->Name, 12);
	SetPosition(Width + strlen(_Enemy->Name), Height + 3, (char*)"��(��) ���������� ", 15);
	Sleep(500);
	SetPosition(Width + strlen(_Enemy->Name) + strlen("��(��) ���������� "), Height + 3, _Player->Name, 11);
	SetPosition(Width + strlen(_Enemy->Name) + strlen("��(��) ���������� ") + strlen(_Player->Name), Height + 3, (char*)"�� ƨ�ܳ��� �ݰ��ߴ� !", 15);
	Sleep(500);
	SetPosition(Width + 26, Height + 6, (char*)" - ", 12);
	SetPositionI(Width + 28, Height + 6, s2, 12);
	_Enemy->Info.HP -= _Player->Info.ATK;
	Sleep(1000);
}

int Turn(OBJECT* _Player, OBJECT* _Enemy)
{
	int i = 0;
	int j = 0;
	int loop = 1;
	int turn = 1;
	int exit = 0;
	int Width = 40;
	int Height = 21;

	system("cls");
	PlayerScene();

	PStatScene(_Player);
	EStatScene(_Enemy);

	while (loop)
	{
		SetPosition((120 / 2) - (strlen("1. ���� 2. ��ų 3. ����") / 2) - 2, Height + 8, (char*)"1. ���� 2. ��ų 3. ����", 14);
		SetPosition((120 / 2) - (strlen("���� ���� : ") / 2) - 1, Height + 9, (char*)"���� ���� : ", 14);
		scanf("%d", &i);

		switch (i)
		{
		case 3:
			srand(time(NULL));
			if (_Enemy->Info.ATK == 222)
			{
				system("cls");
				PlayerScene();
				SetPosition((120 / 2) - (strlen("�� �༮�� �����ؼ� �ȵǴ� �����̴�") / 2), Height + 2, (char*)"�� �༮�� �����ؼ� �ȵǴ� �����̴�", 11);
				Sleep(1000);
				SetPosition((120 / 2) - (strlen("�� ������ ������ ���ھ�") / 2), Height + 4, (char*)"�� ������ ������ ���ھ�", 11);
				Sleep(1000);
				i = 1;
			}
			else if (rand() % 2 == 0 && _Player->Info.Gold >= 1000)
			{
				system("cls");
				PlayerScene();
				SetPosition((120 / 2) - (strlen("�ٴڿ� ������ �ѷ� ���� ���Ǹ� ���µ� ���������� 1000���� �Ҿ��� �Ф�") / 2),
					Height + 2, (char*)"�ٴڿ� ������ �ѷ� ���� ���Ǹ� ���µ� ���������� 1000���� �Ҿ��� �Ф�", 12);
				Sleep(1000);
				_Player->Info.Gold -= 1000;
				SetPosition(Width + 5, Height + 4, (char*)"���� ���߿� ���� �� : ");
				SetPositionI(Width + 27, Height + 4, _Player->Info.Gold, 14);
				Sleep(1000);
				exit = 1;
				loop = 0;
				break;
			}
			else
			{
				system("cls");
				PlayerScene();
				SetPosition(Width + 7, Height + 4, (char*)"�ƻԽ�, ���ѹ��ȱ�...");
				Sleep(1000);
				SetPosition(Width - 3, Height + 6, _Player->Name, 11);
				SetPosition(Width + 6, Height + 6, (char*)"�� �ϴ� �� ���� �����¼��� ���ߴ�");
				Sleep(1000);
				system("cls");
				PlayerScene();
				i = 1;
			}
		case 1:
			if (_Player->Info.Speed > _Enemy->Info.Speed)
			{
				SetPositionI(57, Height + 5, turn, 14);
				SetPosition(59, Height + 5, (char*)"��");
				Sleep(500);
				SetPosition(Width + 6, Height + 6, _Player->Name, 11);
				SetPosition(Width + 6 + strlen(_Player->Name), Height + 6, (char*)"�� �������� !");
				Sleep(500);
				PlayerAtk(_Player, _Enemy);
				Sleep(1000);
				if (_Enemy->Info.HP >= 0)
					EnemyAtk(_Enemy, _Player);

				Sleep(1000);
				_Player->Info.MP += 2;
				_Enemy->Info.MP += 2;

				system("cls");
				PlayerScene();
				PStatScene(_Player);
				EStatScene(_Enemy);
				Sleep(1000);
				turn++;
				break;
			}
			else if (_Player->Info.Speed < _Enemy->Info.Speed)
			{
				SetPositionI(57, Height + 5, turn, 14);
				SetPosition(59, Height + 5, (char*)"��");
				Sleep(500);
				SetPosition(Width + 6, Height + 6, _Enemy->Name, 12);
				SetPosition(Width + 6 + strlen(_Enemy->Name), Height + 6, (char*)"�� �������� !");
				Sleep(500);
				EnemyAtk(_Enemy, _Player);
				Sleep(1000);
				if (_Player->Info.HP >= 0)
					PlayerAtk(_Player, _Enemy);

				Sleep(1000);
				_Player->Info.MP += 2;
				_Enemy->Info.MP += 2;

				system("cls");
				PlayerScene();
				PStatScene(_Player);
				EStatScene(_Enemy);
				Sleep(1000);
				turn++;
				break;
			}
			else
			{
				srand(time(NULL));
				SetPosition((120 / 2) - (strlen("���� �Ƿ��� ����� ���� ������� ������ �����ϱ�� �ߴ�") / 2), Height + 10, (char*)"���� �Ƿ��� ����� ���� ������� ������ �����ϱ�� �ߴ�", 14);
				Sleep(1000);
				if (rand() % 2 == 0)
				{
					SetPositionI(57, Height + 5, turn, 14);
					SetPosition(59, Height + 5, (char*)"��");
					SetPosition(Width + 6, Height + 6, _Player->Name, 11);
					SetPosition(Width + 6 + strlen(_Player->Name), Height + 6, (char*)"�� �������� !");

					PlayerAtk(_Player, _Enemy);
					Sleep(1000);
					if (_Enemy->Info.HP >= 0)
						EnemyAtk(_Enemy, _Player);

					Sleep(1000);
					_Player->Info.MP += 2;
					_Enemy->Info.MP += 2;

					system("cls");
					PlayerScene();
					PStatScene(_Player);
					EStatScene(_Enemy);
					Sleep(1000);
					turn++;
					break;
				}
				else
				{
					SetPositionI(57, Height + 5, turn, 14);
					SetPosition(59, Height + 5, (char*)"��");
					SetPosition(Width + 6, Height + 6, _Enemy->Name, 12);
					SetPosition(Width + 6 + strlen(_Enemy->Name), Height + 6, (char*)"�� �������� !");

					EnemyAtk(_Enemy, _Player);
					Sleep(1000);
					if (_Player->Info.HP >= 0)
						PlayerAtk(_Player, _Enemy);

					Sleep(1000);
					_Player->Info.MP += 2;
					_Enemy->Info.MP += 2;

					system("cls");
					PlayerScene();
					PStatScene(_Player);
					EStatScene(_Enemy);
					Sleep(1000);
					turn++;
					break;
				}
			}
			break;
		case 2:
			system("cls");
			PlayerScene();
			SetPosition(Width - 16, Height + 2, (char*)"1. 1��ų : ������ 200% �� ������, �Ҹ� ���� 1", 14);
			Sleep(200);
			SetPosition(Width - 16, Height + 3, (char*)"2. 2��ų : ���� ���� ������ ƨ�ܳ��� 100%�� ��� ���� ������, �Ҹ� ���� 3", 14);
			Sleep(200);
			SetPosition(Width - 16, Height + 4, (char*)"3. 3��ų : �ʻ�⸦ ����� 2000% ������, �Ҹ� ���� 8", 14);
			Sleep(200);
			SetPosition(Width + 6, Height + 6, (char*)"�̿��� �ƹ� Ű�� ���� ��� : ");
			scanf("%d", &j);
			if (j > 0 && j <= 3)
			{
				if (_Player->Info.MP >= 1 && j == 1)
				{
					system("cls");
					PlayerScene();
					SetPositionI(57, Height + 5, turn, 14);
					SetPosition(59, Height + 5, (char*)"��");
					Sleep(1000);
					PlayerSkill(_Player, _Enemy, j);
					Sleep(1000);
					if (_Enemy->Info.HP > 0)
						EnemyAtk(_Enemy, _Player);

					Sleep(1000);
					_Player->Info.MP += 2;
					_Enemy->Info.MP += 2;

					system("cls");
					PlayerScene();
					PStatScene(_Player);
					EStatScene(_Enemy);
					Sleep(1000);
					turn++;
				}
				else if (_Player->Info.MP >= 3 && j == 2)
				{
					system("cls");
					PlayerScene();
					SetPositionI(57, Height + 5, turn, 14);
					SetPosition(59, Height + 5, (char*)"��");
					Sleep(1000);

					PlayerSkill(_Player, _Enemy, j);
					Sleep(1000);
					Parrying(_Player, _Enemy);
					Sleep(1000);
					_Player->Info.MP += 2;
					_Enemy->Info.MP += 2;

					system("cls");
					PlayerScene();
					PStatScene(_Player);
					EStatScene(_Enemy);
					Sleep(1000);
					turn++;
				}
				else if (_Player->Info.MP >= 8 && j == 3)
				{
					system("cls");
					PlayerScene();
					SetPositionI(57, Height + 5, turn, 14);
					SetPosition(59, Height + 5, (char*)"��");
					Sleep(1000);

					PlayerSkill(_Player, _Enemy, j);
					Sleep(1000);
					if (_Enemy->Info.HP > 0)
						EnemyAtk(_Enemy, _Player);
					Sleep(1000);
					_Player->Info.MP += 2;
					_Enemy->Info.MP += 2;

					system("cls");
					PlayerScene();
					PStatScene(_Player);
					EStatScene(_Enemy);
					Sleep(1000);
					turn++;
				}
				else
				{
					system("cls");
					PlayerScene();
					SetPosition((120 / 2) - (strlen("������ �����մϴ�. �ٽ� �����ϼ���") / 2), Height + 3, (char*)"������ �����մϴ�. �ٽ� �����ϼ���");
					Sleep(500);
					system("cls");
					PlayerScene();
					PStatScene(_Player);
					EStatScene(_Enemy);
					break;
				}
			}
			else
				break;
			break;
		}
		if (_Player->Info.HP <= 0 || _Enemy->Info.HP <= 0)
		{
			loop = 0;
			break;
		}
	}

	return exit;

}

void BattleResult(OBJECT* _Player, OBJECT* _Enemy)
{
	int Height = 22;

	system("cls");
	PlayerScene();

	SetPosition(39, Height, (char*)"���� �¸�! ", 14);
	SetPosition(39 + strlen("���� �¸�! "), Height, _Enemy->Name, 12);
	SetPosition(39 + strlen("���� �¸�! ") + strlen(_Enemy->Name), Height, (char*)"��(��) ������ ���ư��� ", 14);
	Sleep(1000);

	if ((_Player->Info.EXP += _Enemy->Info.EXP) < 100)
	{
		SetPosition(40, Height + 2, (char*)"����ġ ", 15);
		SetPositionI(48, Height + 2, _Enemy->Info.EXP);
		SetPosition(48 + sizeof(_Enemy->Info.EXP), Height + 2, (char*)"��� ! ���� ����ġ : ", 15);
		SetPositionI(48 + sizeof(_Enemy->Info.EXP) + strlen("��� ! ���� ����ġ : "), Height + 2, _Player->Info.EXP);
		Sleep(1000);
	}
	else if ((_Player->Info.EXP += _Enemy->Info.EXP) >= 100)
	{
		int ex = ((_Player->Info.EXP += _Enemy->Info.EXP) % 100);
		for (int i = 0; i < ((_Player->Info.EXP += _Enemy->Info.EXP) / 100); i++)
		{
			PlayerLvUp(_Player);
		}
		SetPosition(46, Height + 2, (char*)"���� ��! ���� ���� : ", 14);
		SetPositionI(46 + strlen("���� ��! ���� ���� : "), Height + 2, _Player->Info.Level, 11);
		SetPosition(46 + strlen("���� ��! ���� ���� : ") + sizeof(_Player->Info.Level), Height + 2, (char*)"Lv", 14);
		Sleep(1000);

		_Player->Info.EXP = ex;
		SetPosition(51, Height + 4, (char*)"���� ����ġ : ", 15);
		SetPositionI(51 + strlen("���� ����ġ : "), Height + 4, _Player->Info.EXP);
		Sleep(1000);
	}
	_Player->Info.Gold += _Enemy->Info.Gold;
	SetPosition(32, Height + 6, _Enemy->Name, 12);
	SetPosition(32 + strlen(_Enemy->Name), Height + 6, (char*)"��(��) ������ �ִ� ", 15);
	SetPositionI(32 + strlen(_Enemy->Name) + strlen("��(��) ������ �ִ� "), Height + 6, _Enemy->Info.Gold, 14);
	SetPosition(33 + strlen(_Enemy->Name) + strlen("��(��) ������ �ִ� ") + sizeof(_Enemy->Info.Gold), Height + 6, (char*)"���� ����ǰ���� ì���");
	Sleep(500);
	SetPosition(50, Height + 8, (char*)"���� ������ : ");
	SetPositionI(64, Height + 8, _Player->Info.Gold, 14);

	Sleep(2000);
}

void PlayerLvUp(OBJECT* _Player)
{
	_Player->Info.HP += 80;
	_Player->Info.ATK += 20;
	_Player->Info.DEF += 5;
	_Player->Info.Level += 1;
	_Player->Info.Speed += 3;
	_Player->Info.EXP = 0;
}

int FailScene(OBJECT* _Player)
{
	system("cls");
	PlayerScene();
	int i = 0;
	int Width = 50;
	int Height = 23;
	SetPosition((120 / 2) - (strlen("��... ���ϴ�") / 2), Height, (char*)"��... ���ϴ�", 11);
	Sleep(1000);
	SetPosition((120 / 2) - (strlen("�絵�� �Ͻðڽ��ϱ�? 1�� �Է��� 1000���� ���� �絵�� , �̿��� Ű �Է����� ���� ���� : ") / 2), Height + 1, (char*)"�絵�� �Ͻðڽ��ϱ�? 1�� �Է��� 1000���� ���� �絵�� , �̿��� Ű �Է����� ���� ���� : ", 12);
	scanf("%d", &i);

	if (i == 1 && _Player->Info.Gold >= 1000)
	{
		i = 1;
		_Player->Info.Gold -= 1000;
	}
	else if (_Player->Info.Gold < 1000)
	{
		SetPosition((120 / 2) - (strlen("������ �ݾ��� �����ϳ׿�") / 2), Height + 2, (char*)"������ �ݾ��� �����ϳ׿�", 14);
		Sleep(1000);
		SetPosition((120 / 2) - (strlen("������ �����մϴ�") / 2), Height + 3, (char*)"������ �����մϴ�.", 12);
		Sleep(2000);
		exit(NULL);
	}
	else
	{
		SetPosition((120 / 2) - (strlen("������ �����մϴ�.") / 2), Height, (char*)"������ �����մϴ�.", 12);
		Sleep(2000);
		exit(NULL);
	}
	return i;
}

void PlayerScene()
{
	int Width = 5;
	int Height = 0;
	system("cls");
	SetPosition(Width, Height + 1, (char*)"******************************************************************************", 11);
	SetPosition(Width + strlen("******************************************************************************"), Height + 1, (char*)"***************", 15);
	SetPosition(Width + strlen("******************************************************************************::::.......::::"), Height + 1, (char*)"*****************", 11);
	SetPosition(Width, Height + 2, (char*)"*********", 11);
	SetPosition(Width + 9, Height + 2, (char*)"****", 15);
	SetPosition(Width + strlen("********....:"), Height + 2, (char*)"***************************************************************", 11);
	SetPosition(Width + strlen("********....:***************************************************************"), Height + 2, (char*)"*******************", 15);
	SetPosition(Width + strlen("********....:***************************************************************::::...........::::"), Height + 2, (char*)"***************", 11);
	SetPosition(Width, Height + 3, (char*)"********", 11);
	SetPosition(Width + 8, Height + 3, (char*)"*******", 15);
	SetPosition(Width + strlen("********.... : "), Height + 3, (char*)"************************************************************", 11);
	SetPosition(Width + strlen("********.... : ************************************************************"), Height + 3, (char*)"**********************", 15);
	SetPosition(Width + strlen("********.... : ************************************************************::::...........::::***"), Height + 3, (char*)"*************", 11);
	SetPosition(Width, Height + 4, (char*)"******", 11);
	SetPosition(Width + 6, Height + 4, (char*)"***************", 15);
	SetPosition(Width + strlen("****** : .......:: : "), Height + 4, (char*)"**************************************************", 11);
	SetPosition(Width + strlen("****** : .......:: : **************************************************"), Height + 4, (char*)"*******************************", 15);
	SetPosition(Width + strlen("****** : .......:: : **************************************************: .............:::::::::::: : "), Height + 4, (char*)"*********", 11);
	SetPosition(Width, Height + 5, (char*)"***", 11);
	SetPosition(Width + 3, Height + 5, (char*)"********************", 15);
	SetPosition(Width + strlen("***::.......:::::::: : "), Height + 5, (char*)"*********************************************", 11);
	SetPosition(Width + strlen("***::.......:::::::: : *********************************************"), Height + 5, (char*)"************************************", 15);
	SetPosition(Width + strlen("***::.......:::::::: : *********************************************: ............:::::::::::::::::: : "), Height + 5, (char*)"*******", 11);
	SetPosition(Width, Height + 6, (char*)"**", 11);
	SetPosition(Width + 2, Height + 6, (char*)"********************", 15);
	SetPosition(Width + strlen("**: .....:::::::::: : "), Height + 6, (char*)"*********************************************", 11);
	SetPosition(Width + strlen("**: .....:::::::::: : *********************************************"), Height + 6, (char*)"*************************************", 15);
	SetPosition(Width + strlen("**: .....:::::::::: : *********************************************: .......::::::::::::::::::::::::::::"), Height + 6, (char*)"******", 11);
	SetPosition(Width, Height + 7, (char*)"*************************", 11);
	SetPosition(Width + strlen("*************************"), Height + 7, (char*)"*************", 15);
	SetPosition(Width + strlen("************************* ::......::::"), Height + 7, (char*)"*****************************", 11);
	SetPosition(Width + strlen("************************* ::......::::*****************************"), Height + 7, (char*)"**********", 15);
	SetPosition(Width + strlen("************************* ::......::::***************************** ::* :: : "), Height + 7, (char*)"*********************************", 11);
	SetPosition(Width, Height + 8, (char*)"***********************", 11);
	SetPosition(Width + strlen("***********************"), Height + 8, (char*)"*****************", 15);
	SetPosition(Width + strlen("***********************: .......::::::::"), Height + 8, (char*)"*******************************************************************", 11);
	SetPosition(Width + strlen("***********************: .......::::::::*******************************************************************"), Height + 8, (char*)"***", 15);
	SetPosition(Width, Height + 9, (char*)"***************************", 11);
	SetPosition(Width + strlen("***************************"), Height + 9, (char*)"**********", 15);
	SetPosition(Width + strlen("*************************** :::::: : "), Height + 9, (char*)"******************************************************************", 11);
	SetPosition(Width + strlen("*************************** :::::: : ******************************************************************"), Height + 9, (char*)"*******", 15);
	SetPosition(Width, Height + 10, (char*)"**********");
	SetPosition(Width + 10, Height + 10, (char*)"*********************************************************", 11);
	SetPosition(Width + strlen(": ...:::: *********************************************************"), Height + 10, (char*)"********", 15);
	SetPosition(Width + strlen(": ...:::: *********************************************************::..:: :"), Height + 10, (char*)"**************************", 11);
	SetPosition(Width + strlen(": ...:::: *********************************************************::..:: : *************************"), Height + 10, (char*)"*********", 15);
	SetPosition(Width, Height + 11, (char*)"**************");
	SetPosition(Width + 13, Height + 11, (char*)"**************************************************", 11);
	SetPosition(Width + strlen("....:::::::::**************************************************"), Height + 11, (char*)"******************", 15);
	SetPosition(Width + strlen("....:::::::::**************************************************: ........:::::: :"), Height + 11, (char*)"*****************************", 11);
	SetPosition(Width, Height + 12, (char*)"***********", 15);
	SetPosition(Width + 11, Height + 12, (char*)"***************************************************", 11);
	SetPosition(Width + 62, Height + 12, (char*)"****************", 15);
	SetPosition(Width + 78, Height + 12, (char*)"********************************", 11);
	SetPosition(Width, Height + 13, (char*)"****", 15);
	SetPosition(Width + 4, Height + 13, (char*)"******************************************************************", 11);
	SetPosition(Width + strlen("::::******************************************************************"), Height + 13, (char*)"****", 15);
	SetPosition(Width + strlen("::::******************************************************************::::"), Height + 13, (char*)"************************************", 11);
	SetPosition(Width, Height + 14, (char*)"VVVVVVVVVVVVVVVVVVVV", 10);
	SetPosition(Width + strlen("VVVVVVVVVVVVVVVVVVVV"), Height + 14, (char*)"******************************************************", 11);
	SetPosition(Width + strlen("VVVVVVVVVVVVVVVVVVVV******************************************************"), Height + 14, (char*)"VVVVVFFIIIIIIIIIIIIIIIFIIIIIIIIIIIII", 10);
	SetPosition(Width, Height + 15, (char*)"IIIIMMMMMMMMIIMFVFIMIIMIIIIVVVVV************* VVVVVVVVFFIIIIIIMIMMIMIMIMIIMIMIIIIIIIIMMMMIIIIMI* VVMMIIIIIIIII", 10);
	SetPosition(Width, Height + 16, (char*)"MMMMMMMMMMMMMMMMIMMMMMMMIVFMMMMMMMMMMMMMMIVMMMMMMMMMMMMMMMMMFVIMMMMMMMIVVIMMMMMMMMMMMVVIMMMMMMMMMMMMMMMMMMMMMM", 10);
	SetPosition(Width, Height + 17, (char*)"NNNNNVVVMNNNNNNNNNNNNNNNMIMNNNNNNNNNNNNNNNNNNNNNNNMIINNNNNNNIIMNNNNNNNNMMNNNNNNNNNNNNNNNNNNNNNNNMVVINNNNNNNNNN", 10);
	SetPosition(Width, Height + 18, (char*)"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNMMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNMFVMNNNNNNNMMNNNNNNNNNNN", 10);
	SetPosition(Width, Height + 19, (char*)"$$$$$$$$$$$$NIN$$$$$$NFIN$$$$$$$$$$$$$NMN$$$$$$$$$$$$$$$$$$$$$$$$IVF$$$$$$$$$$$$NIN$$$$NNN$$$$$$$$$NIM$$$$$$$$", 10);
	//SetPosition(Width, Height + 20, (char*)"$$$$$$$$$$$$$$$$$$$$$$N$$$$$$$$$$$$$$$MIM$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$N$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 10);
	SetPosition(Width + 5, Height + 20, (char*)"���ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѦ�", 15);
	SetPosition(Width + 5, Height + 21, (char*)"��                                                                                                 ��");
	SetPosition(Width + 5, Height + 21, (char*)"��                                                                                                 ��");
	SetPosition(Width + 5, Height + 22, (char*)"��                                                                                                 ��");
	SetPosition(Width + 5, Height + 23, (char*)"��                                                                                                 ��");
	SetPosition(Width + 5, Height + 24, (char*)"��                                                                                                 ��");
	SetPosition(Width + 5, Height + 25, (char*)"��                                                                                                 ��");
	SetPosition(Width + 5, Height + 26, (char*)"��                                                                                                 ��");
	SetPosition(Width + 5, Height + 27, (char*)"��                                                                                                 ��");
	SetPosition(Width + 5, Height + 28, (char*)"��                                                                                                 ��");
	SetPosition(Width + 5, Height + 29, (char*)"��                                                                                                 ��");
	SetPosition(Width + 5, Height + 30, (char*)"��                                                                                                 ��");
	SetPosition(Width + 5, Height + 31, (char*)"��                                                                                                 ��");
	SetPosition(Width + 5, Height + 32, (char*)"���ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѦ�");
}

void ShopScene(OBJECT* _Player, int _stg)
{
	system("cls");
	PlayerScene();
	int i = 0;

	int atk = 40;
	int def = 30;
	int hp = 70;
	int spd = 5;

	int w1 = 4000;
	int w2 = 3500;
	int w3 = 3500;
	int w4 = 3000;

	int Width = 13;
	int eWidth = 40;
	int Height = 22;

	SetPosition(Width, Height - 1, (char*)"���� ������ ���� �̵��ϴ� �� ������� �������� ������", 15);
	Sleep(500);
	SetPosition(Width, Height, (char*)"�������� ��ȭ�� ���Ű��� ȯ���մϴ� �浿 ������, ���� �ο��� ����ô� Ư���� ���ΰ��� �帱�Կ�", 14);
	Sleep(1000);
	SetPosition(Width, Height + 2, (char*)"�������� ��ȭ�� : ", 14);
	Sleep(500);
	SetPosition(eWidth, Height + 2, (char*)"1.  ��  ��   : ���ݷ� + ", 14);
	SetPositionI(eWidth + 24, Height + 2, _stg * atk, 12);
	SetPosition(eWidth + 29, Height + 2, (char*)", ���� : ", 14);
	SetPositionI(eWidth + 38, Height + 2, _stg * w1, 12);
	Sleep(500);
	SetPosition(eWidth, Height + 3, (char*)"2. �Ķ�����  : ���� + ", 14);
	SetPositionI(eWidth + 24, Height + 3, _stg * def, 12);
	SetPosition(eWidth + 29, Height + 3, (char*)", ���� : ", 14);
	SetPositionI(eWidth + 38, Height + 3, _stg * w2, 12);
	Sleep(500);
	SetPosition(eWidth, Height + 4, (char*)"3.��Ȳû��ȯ : ü  �� + ", 14);
	SetPositionI(eWidth + 24, Height + 4, _stg * hp, 12);
	SetPosition(eWidth + 29, Height + 4, (char*)", ���� : ", 14);
	SetPositionI(eWidth + 38, Height + 4, _stg * w3, 12);
	Sleep(500);
	SetPosition(eWidth, Height + 5, (char*)"4. �� �� ��  : ��  �� + ", 14);
	SetPositionI(eWidth + 24, Height + 5, _stg * spd, 12);
	SetPosition(eWidth + 29, Height + 5, (char*)", ���� : ", 14);
	SetPositionI(eWidth + 38, Height + 5, _stg * w4, 12);
	Sleep(500);
	SetPosition(Width, Height + 7, (char*)"���� ������ : ", 15);
	SetPositionI(Width + 14, Height + 7, _Player->Info.Gold, 14);
	Sleep(500);
	SetPosition(Width + 20, Height + 7, (char*)"��, ���Ÿ� ������ ������ 1 ~ 4 �̿��� Ű�� �Է� : ", 15);


	scanf("%d", &i);

	if (i == 1)
	{
		if (_Player->Info.Gold >= _stg * w1)
		{
			_Player->Info.ATK += _stg * atk;
			_Player->Info.Gold -= _stg * w1;
			SetPosition(Width, Height + 8, (char*)"�����մϴ� ȣ����!", 14);
			Sleep(500);
			SetPosition(Width, Height + 9, (char*)"���� �����ϴ�... ���� ������ : ", 15);
			SetPositionI(Width + 32, Height + 9, _Player->Info.Gold, 14);
			Sleep(1000);
		}
		else
		{
			SetPosition(Width, Height + 8, (char*)"����...�������̽ñ���? ������ ���� �������Դϴ�~", 12);
			Sleep(1000);
			i = 0;
		}
	}
	else if (i == 2)
	{
		if (_Player->Info.Gold >= _stg * w2)
		{
			_Player->Info.DEF += _stg * def;
			_Player->Info.Gold -= _stg * w2;
			SetPosition(Width, Height + 8, (char*)"�����մϴ� ȣ����!", 14);
			Sleep(500);
			SetPosition(Width, Height + 9, (char*)"���� �����ϴ�... ���� ������ : ", 15);
			SetPositionI(Width + 32, Height + 9, _Player->Info.Gold, 14);
			Sleep(1000);
		}
		else
		{
			SetPosition(Width, Height + 8, (char*)"����...���� �����Ͻñ���? ������ ���� �������Դϴ�~", 12);
			Sleep(1000);
			i = 0;
		}
	}
	else if (i == 3)
	{
		if (_Player->Info.Gold >= _stg * w3)
		{
			_Player->Info.HP += _stg * hp;
			_Player->Info.Gold -= _stg * w3;
			SetPosition(Width, Height + 8, (char*)"�����մϴ� ȣ����!", 14);
			Sleep(500);
			SetPosition(Width, Height + 9, (char*)"���� �����ϴ�... ���� ������ : ", 15);
			SetPositionI(Width + 32, Height + 9, _Player->Info.Gold, 14);
			Sleep(1000);
		}
		else
		{
			SetPosition(Width, Height + 8, (char*)"����...���� �����Ͻñ���? ������ ���� �������Դϴ�~", 12);
			Sleep(1000);
			i = 0;
		}
	}
	else if (i == 4)
	{
		if (_Player->Info.Gold >= _stg * w4)
		{
			_Player->Info.Speed += _stg * spd;
			_Player->Info.Gold -= _stg * w4;
			SetPosition(Width, Height + 8, (char*)"�����մϴ� ȣ����!", 14);
			Sleep(500);
			SetPosition(Width, Height + 9, (char*)"���� �����ϴ�... ���� ������ : ", 15);
			Sleep(1000);
			SetPositionI(Width + 32, Height + 9, _Player->Info.Gold, 14);
		}
		else
		{
			SetPosition(Width, Height + 8, (char*)"����...���� �����Ͻñ���? ������ ���� �������Դϴ�~", 12);
			Sleep(1000);
			i = 0;
		}
	}
	else
	{
		SetPosition(Width, Height + 8, (char*)"���� ���� ~ �� �ٴڿ��� ��ŷ��� �⺻�̿���  ! ", 14);
		Sleep(500);
		SetPosition(Width, Height + 9, (char*)"������ ���°� ���� �ʾ� �ŷ��� ����ϰ� �߰����� �Ű��", 15);
		Sleep(1000);
	}


	Sleep(1000);
}

int BuffScene()
{
	system("cls");
	PlayerScene();
	int i = 0;
	int lp = 1;
	int Width = 39;
	int Height = 21;

	while (lp)
	{
		SetPosition(Width, Height, (char*)"������ ���� ����� ���̰� �ݰ��ش�");
		Sleep(1000);
		SetPosition(Width, Height + 1, (char*)"������ ���� : ");
		Sleep(500);
		SetPosition(Width, Height + 3, (char*)"1. ���� �������� ���ݷ� 30% ���� ����", 14);
		Sleep(500);
		SetPosition(Width, Height + 4, (char*)"2. ���� �������� ���� 30% ���� ����", 14);
		Sleep(500);
		SetPosition(Width, Height + 5, (char*)"3. ���� �������� �ӵ� 10 ���� ����", 14);
		Sleep(500);
		SetPosition(Width, Height + 7, (char*)"���� ���� : ");
		scanf("%d", &i);
		if (i < 1 || i > 4)
		{
			SetPosition(Width + 15, Height + 7, (char*)"�ٽ� �����ϼ���", 12);
			Sleep(500);
			i = 0;
		}
		else
		{
			SetPosition((120 / 2) - (strlen("���� ����!") / 2), Height + 8, (char*)"���� ����!", 15);
			Sleep(500);
			SetPosition((120 / 2) - (strlen("������ ������ ���� �ڴ´�") / 2), Height + 9, (char*)"������ ������ ���� �ڴ´�", 11);
			lp = 0;
		}
	}

	Sleep(2000);

	return i;
}

void BossScene()
{
	int Height = 11;

	system("cls");
	SetPosition(60 - (strlen("�� �ѳ�...") / 2), Height, (char*)"�� �ѳ�...", 12);
	Sleep(1000);
	SetPosition(60 - (strlen("���� ��浿�� �� �̷��Ա��� �ùް� �ϴٴ�") / 2), Height + 2, (char*)"���� ��浿�� �� �̷��Ա��� �ùް� �ϴٴ�", 12);
	Sleep(1000);
	SetPosition(59 - (strlen("���� ���� ���ű������� �ٽ� ������") / 2), Height + 4, (char*)"���� ���� ���ű������� �ٽ� ������", 12);
	Sleep(1000);
	SetPosition(60 - (strlen("���� ������� �Դ�...") / 2), Height + 8, (char*)"���� ������� �Դ�...", 11);
	Sleep(500);
	SetPosition(60 - (strlen("�༮�� ���ְ� ������ ��ȭ�� ��ã�°Ŵ� !") / 2), Height + 10, (char*)"�༮�� ���ְ� ������ ��ȭ�� ��ã�°Ŵ� !", 11);
	Sleep(1500);
}

void EndingScene(OBJECT* _Player, int _count)
{
	int Height = 11;

	system("cls");
	SetPosition(60 - (strlen("�̷�...���� �ȵǴ�...") / 2), Height, (char*)"�̷�...���� �ȵǴ�...", 12);
	Sleep(1000);
	SetPosition(60 - (strlen("...��...��...") / 2), Height + 2, (char*)"...��...��...", 12);
	Sleep(1000);
	SetPosition(60 - (strlen("����� �ܰ� �������� �����ƴ� !") / 2), Height + 4, (char*)"����� �ܰ� �������� �����ƴ� !", 15);
	Sleep(1000);
	SetPosition(60 - (strlen("���� �����ǰ�") / 2), Height + 6, (char*)"���� �����ǰ�", 11);
	Sleep(1000);
	SetPosition(60 - (strlen("������� ������ �����Ǵ� ����̱�...") / 2), Height + 8, (char*)"������� ������ �����Ǵ� ����̱�...", 11);
	Sleep(1000);
	SetPosition(60 - (strlen("������ ���ư��� ���� ���� ��Ƽ�� !") / 2), Height + 10, (char*)"������ ���ư��� ���� ���� ��Ƽ�� !", 11);
	Sleep(1000);
	SetPosition(60 - (strlen("���� Ŭ���� !") / 2), Height + 12, (char*)"���� Ŭ���� !", 14);
	Sleep(1000);
	SetPosition(51, Height + 14, (char*)"�� �÷���Ÿ�� : ", 15);
	SetPositionI(51 + strlen("�� �÷���Ÿ�� : "), Height + 14, _count / 10000, 14);
	SetPosition(51 + strlen("�� �÷���Ÿ�� : ") + sizeof(_count / 10000), Height + 14, (char*)"��", 15);
	Sleep(1000);
	SetPosition(54, Height + 16, (char*)"�ְ� ���� : ", 15);
	SetPositionI(54 + strlen("���� ���� : "), Height + 16, _Player->Info.Level, 14);
	Sleep(1500);

	SceneState++;
}

void ExitScene(int _col1, int _col2)
{
	int Width = 60 - (strlen("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@") / 2);
	int Height = 10;
	system("cls");
	system("color 08");

	SetPosition(0, 1, (char*)"                                                    &G?^::::~?B                 ", _col1);
	SetPosition(0, 2, (char*)"                                                  #?^::::::::::~P               ", _col1);
	SetPosition(0, 3, (char*)"                     &#G5J?7 J                  #7::::::::::::::.!&             ", _col1);
	SetPosition(0, 4, (char*)"                 P.??????? J                   5::::::::::::::::::~J~           ", _col1);
	SetPosition(0, 5, (char*)"                 J J5PB&& :?                  J.:::::::::::::::::::::7?5&       ", _col1);
	SetPosition(0, 6, (char*)"                 J:       :?                 Y.::::::::::::::::^^^:::::^~7JB    ", _col1);
	SetPosition(0, 7, (char*)"                 J:       :?                G:::::::::::~7J5GB##&G::::::::::~&  ", _col1);
	SetPosition(0, 8, (char*)"                 J:  &!7J7YJ               &^:::::::!?5#&&###&&&&P:::::::::::&  ", _col1);
	SetPosition(0, 9, (char*)"             57??.:  ^:JJJJY               Y.::::!J###&#&&#&#&&&&G:::::::::^B   ", _col1);
	SetPosition(0, 10, (char*)"           5&JJJJJ  &?7J7Y                 ^::^5&&#&&&&&&&&&&&&&&#::::::::J&    ", _col1);
	SetPosition(0, 11, (char*)"           &!!?7^#                        B.^P   &B&B #G&B&#B &&&&!::::^Y&      ", _col1);
	SetPosition(0, 12, (char*)"                                          PY      G& # B&##B & &&&G:~7Y#        ", _col1);
	SetPosition(0, 13, (char*)"                                          Y       G &## &&& &BB &&&#&&&G&       ", _col1);
	SetPosition(0, 14, (char*)"                                                  G&&#GBBB#&&BB#&&&####&        ", _col1);
	SetPosition(0, 15, (char*)"                                             B####&&&&&&&&&&& #GG&B#            ", _col1);
	SetPosition(0, 16, (char*)"                                             ! ! ##BB##GB###  #B#&B&            ", _col1);
	SetPosition(0, 17, (char*)"                                              BBG ! ! ! ! ! ! &&&&G             ", _col1);
	SetPosition(0, 18, (char*)"                                                &##&&&&&&&&&&&&&&##             ", _col1);
	SetPosition(0, 19, (char*)"                                                  &##&&&&&&&&&&&##              ", _col1);
	SetPosition(0, 20, (char*)"                                                     &###&&&&&#G#               ", _col1);
	SetPosition(0, 21, (char*)"                                                       &GP#BBB& #&              ", _col1);
	SetPosition(0, 22, (char*)"                                                     &#JYBB&&PG#B&&&&           ", _col1);
	SetPosition(0, 23, (char*)"                                                   &&#5G5 &#PGG5G    &&         ", _col1);
	SetPosition(0, 24, (char*)"                                                  #  5GB5BGGGGGBPB     #&       ", _col1);
	SetPosition(0, 25, (char*)"                                                &&  GGGGGGGGGGGGBY#     &&      ", _col1);
	SetPosition(0, 26, (char*)"                                               &&  B5BGGGGGGGGGGP5&B&    &&     ", _col1);
	SetPosition(0, 27, (char*)"                                               && BYPGGGGGGGGGGJPPP       #     ", _col1);
	SetPosition(0, 28, (char*)"                                                 #YJGGGGGGGGGGGJGBB&   &&&      ", _col1);
	SetPosition(0, 29, (char*)"                                                  #5BGGGGPPPPGGP5GG#&&&         ", _col1);
	SetPosition(0, 30, (char*)"                                                  PGGGGGGGPPPPGGGP5             ", _col1);
	SetPosition(0, 31, (char*)"                                                  &5PGBBBBBBBBBGP55             ", _col1);
	Sleep(3000);
	system("cls");
	SetPosition(Width, Height + 2, (char*)"   ###############  ######    ######  ###############           ##############  ########     ######  ###############    ", _col2);
	SetPosition(Width, Height + 3, (char*)"   ###############  ######    ######  ###############           ##############  #########    ######  ################   ", _col2);
	SetPosition(Width, Height + 4, (char*)"   ###############  ######    ######  #######                   #######         ##########   ######  #######  #######   ", _col2);
	SetPosition(Width, Height + 5, (char*)"        #####       ################  ##############            #############   ###########  ######  #######  #######   ", _col2);
	SetPosition(Width, Height + 6, (char*)"        #####       ################  ##############            #############   ###### ############  #######  #######   ", _col2);
	SetPosition(Width, Height + 7, (char*)"        #####       ######    ######  #######                   #######         ######  ###########  #######  #######   ", _col2);
	SetPosition(Width, Height + 8, (char*)"        #####       ######    ######  #######                   #######         ######    #########  #######  #######   ", _col2);
	SetPosition(Width, Height + 9, (char*)"        #####       ######    ######  ###############           ##############  ######      #######  ################   ", _col2);
	SetPosition(Width, Height + 10, (char*)"        #####       ######    ######  ###############           ##############  ######        #####  ###############    ", _col2);
	Sleep(3000);
}

void SetPosition(int _x, int _y, char* _str, int _Color)
{
	COORD Pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	SetColor(_Color);

	printf_s("%s", _str);
}

void SetPositionI(int _x, int _y, int _value, int _Color)
{
	COORD Pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	SetColor(_Color);

	char Buffer[128] = "";
	_itoa(_value, Buffer, 10);

	char* pStr = (char*)malloc(strlen(Buffer));
	strcpy(pStr, Buffer);

	printf_s("%s", pStr);
}

void SetColor(int _Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO Info;

	Info.dwSize = 1;
	Info.bVisible = false;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}