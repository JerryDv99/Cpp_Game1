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

	system("title 박준형 v0.6");

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
	//SetPosition(30, 21, (char*)"안녕", 14);
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

	SetPosition(44, 12, (char*)"당신의 이름은... : ", 139);
	scanf("%s", Buffer);

	if (strcmp(Buffer, "고길동") == 0)
	{
		SetPosition(60 - (strlen("그래, 내가 바로 고씨 집안 차남 고길동이다") / 2), 14, (char*)"그래, 내가 바로 고씨 집안 차남 고길동이다", 139);
	}
	else
		SetPosition(60 - (strlen("내 이름을 왜 멋대로 정하지? 할아버지께서 지어주신 내 이름은 고길동이다") / 2), 14, (char*)"내 이름을 왜 멋대로 정하지? 할아버지께서 지어주신 내 이름은 고길동이다", 132);

	Sleep(1500);
	char* pName = (char*)malloc(7);

	strcpy(pName, "고길동");

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
	_Obj->Name = (char*)"쌍문동 촉법소년";

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
	_Obj->Name = (char*)"해골 사냥꾼";

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
	_Obj->Name = (char*)"흑마법사 도X너";

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
	_Obj->Name = (char*)"해골 킹";

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
	_Obj->Name = (char*)"인성파탄공룡 X리";

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
	SetPosition(MWidth, MHeight - 1, (char*)"┌ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┐", 11);
	SetPosition(MWidth, MHeight, (char*)"ㅣ                       ㅣ", 11);
	SetPosition(MWidth, MHeight + 1, (char*)"ㅣ       메     뉴       ㅣ", 11);
	SetPosition(MWidth, MHeight + 2, (char*)"ㅣ                       ㅣ", 11);
	SetPosition(MWidth, MHeight + 3, (char*)"ㅣ       1. 플레이       ㅣ", 11);
	SetPosition(MWidth, MHeight + 4, (char*)"ㅣ                       ㅣ", 11);
	SetPosition(MWidth, MHeight + 5, (char*)"ㅣ       2. 종  료       ㅣ", 11);
	SetPosition(MWidth, MHeight + 6, (char*)"ㅣ                       ㅣ", 11);
	SetPosition(MWidth, MHeight + 7, (char*)"└ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┘", 11);
	SetPosition(MWidth + 10, MHeight + 8, (char*)"입력 : ", 11);
	scanf("%d", &i);
	Sleep(1000);
	SceneState++;

	return 1;
}

void StoryScene()
{
	system("cls");
	int Height = 5;

	SetPosition((120 / 2) - (strlen("'고길동 밥줘'") / 2), Height, (char*)"'고길동 밥줘'", 15);
	Sleep(800);
	SetPosition((120 / 2) - (strlen("몇 년 전 딸아이가 주워온 그 녀석, 처음엔 불쌍해서 며칠 재워준단 생각이었지만") / 2), Height + 2, (char*)"몇 년 전 딸아이가 주워온 그 녀석, 처음엔 불쌍해서 며칠 재워준단 생각이었지만");
	Sleep(800);
	SetPosition((120 / 2) - (strlen("오자마자 집안의 물건을 다 부수더니 떠나긴 커녕 점점 패거리까지 늘었고 갈수록 패악질이 심해졌다.") / 2), Height + 4, (char*)"오자마자 집안의 물건을 다 부수더니 떠나긴 커녕 점점 패거리까지 늘었고 갈수록 패악질이 심해졌다.");
	Sleep(800);
	SetPosition((120 / 2) - (strlen("'저...둘X야 이제 좀 나가주면 안되겠니?' '아잇! 초능력 맛 좀 볼래? 처신 잘 하라고'") / 2), Height + 6, (char*)"'저...둘X야 이제 좀 나가주면 안되겠니?' '아잇! 초능력 맛 좀 볼래? 처신 잘 하라고'");
	Sleep(800);
	SetPosition((120 / 2) - (strlen("이젠 나를 가정부 이하의 취급을 하는 녀석들...") / 2) + 1, Height + 8, (char*)"이젠 나를 가정부 이하의 취급을 하는 녀석들...");
	Sleep(800);
	SetPosition((120 / 2) - (strlen("기나긴 모멸과 핍박, 이제 인내의 시간은 끝났다. 창고로 가 봉인해둔 검을 집어든다.") / 2) + 1, Height + 10, (char*)"기나긴 모멸과 핍박, 이제 인내의 시간은 끝났다. 창고로 가 봉인해둔 검을 집어든다.");
	Sleep(800);
	SetPosition((120 / 2) - (strlen("아아... 이 서늘하고도 묵직한 감각... 2년만이군") / 2), Height + 12, (char*)"아아... 이 서늘하고도 묵직한 감각... 2년만이군");
	Sleep(800);
	SetPosition((120 / 2) - (strlen("'검성' 고길동으로 돌아갈 때다") / 2) - 1, Height + 16, (char*)"'검성' 고길동으로 돌아갈 때다", 12);
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
	SetPosition((120 / 2) - (strlen("오랜만의 실전인 만큼 그 때의 감각을 떠올릴 필요가 있겠어") / 2), Height, (char*)"오랜만의 실전인 만큼 그 때의 감각을 떠올릴 필요가 있겠어", 15);
	Sleep(500);
	SetPosition(Width + 11, Height + 2, ((char*)"야생의 "));
	SetPosition(Width + 11 + strlen("야생의 "), Height + 2, _Enemy->Name, 12);
	SetPosition(Width + 11 + strlen("야생의 ") + strlen(_Enemy->Name), Height + 2, (char*)"이(가) 나타났다!", 15);

	Sleep(500);
	SetPosition((120 / 2) - (strlen("선빵필승! 속도가 빠른 쪽이 선공권을 가지지") / 2), Height + 4, (char*)"선빵필승! 속도가 빠른 쪽이 선공권을 가지지", 11);
	Sleep(500);
	SetPosition((120 / 2) - (strlen("속도가 느려도 일반 공격 대신 스킬을 사용하면 먼저 공격할 수 있다") / 2), Height + 5, (char*)"속도가 느려도 일반 공격 대신 스킬을 사용하면 먼저 공격할 수 있다", 12);
	Sleep(500);
	SetPosition((120 / 2) - (strlen("스킬을 사용하기 위해 필요한 마나는 5를 가지고 시작하며, 매 턴이 끝나면 2의 마나를 추가로 얻는다") / 2), Height + 6, (char*)"스킬을 사용하기 위해 필요한 마나는 5를 가지고 시작하며, 매 턴이 끝나면 2의 마나를 추가로 얻는다", 11);
	Sleep(500);
	SetPosition((120 / 2) - (strlen("자~ 드가자 !") / 2), Height + 8, (char*)"자~ 드가자 !");
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
	SetPosition(nWidth, Height, (char*)"이  름");
	SetPosition(Width, Height, _Player->Name, 11);
	SetPosition(nWidth + 1, Height + 1, (char*)"H  P");
	SetPositionI(Width, Height + 1, _Player->Info.HP, 11);
	SetPosition(nWidth + 1, Height + 2, (char*)"M  P");
	SetPositionI(Width, Height + 2, _Player->Info.MP, 11);
	SetPosition(nWidth, Height + 3, (char*)"공격력");
	SetPositionI(Width, Height + 3, _Player->Info.ATK, 11);
	SetPosition(nWidth, Height + 4, (char*)"방어력");
	SetPositionI(Width, Height + 4, _Player->Info.DEF, 11);
	SetPosition(nWidth, Height + 5, (char*)"레  벨");
	SetPositionI(Width, Height + 5, _Player->Info.Level, 11);
	SetPosition(nWidth, Height + 6, (char*)"속  도");
	SetPositionI(Width, Height + 6, _Player->Info.Speed, 11);
	SetPosition(Width + 20, Height + 3, (char*)"V  S", 12);

}

void EStatScene(OBJECT* _Enemy)
{
	int nWidth = 75;
	int Width = 82;
	int Height = 21;
	SetPosition(nWidth, Height, (char*)"이  름");
	SetPosition(Width, Height, _Enemy->Name, 12);
	SetPosition(nWidth + 1, Height + 1, (char*)"H  P");
	SetPositionI(Width, Height + 1, _Enemy->Info.HP, 12);
	SetPosition(nWidth + 1, Height + 2, (char*)"M  P");
	SetPositionI(Width, Height + 2, _Enemy->Info.MP, 12);
	SetPosition(nWidth, Height + 3, (char*)"공격력");
	SetPositionI(Width, Height + 3, _Enemy->Info.ATK, 12);
	SetPosition(nWidth, Height + 4, (char*)"방어력");
	SetPositionI(Width, Height + 4, _Enemy->Info.DEF, 12);
	SetPosition(nWidth, Height + 5, (char*)"레  벨");
	SetPositionI(Width, Height + 5, _Enemy->Info.Level, 12);
	SetPosition(nWidth, Height + 6, (char*)"속  도");
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
		SetPosition(Width + strlen(_Player->Name), Height + 5, (char*)"의 공격! ");
		SetPosition(Width + strlen(_Player->Name) + strlen("의 공격! "), Height + 5, _Enemy->Name, 12);
		SetPosition(Width + strlen(_Player->Name) + strlen("의 공격! ") + strlen(_Enemy->Name), Height + 5, (char*)"은(는) ");
		SetPositionI(Width + strlen(_Player->Name) + strlen("의 공격! ") + strlen(_Enemy->Name) + strlen("은(는) "), Height + 5, dmg, 12);
		SetPosition(Width + strlen(_Player->Name) + strlen("의 공격! ") + strlen(_Enemy->Name) + strlen("은(는) ") + sizeof(dmg), Height + 5, (char*)"의 데미지를 입었다 !");
		_Enemy->Info.HP -= dmg;
	}
	else
	{
		SetPosition(Width, Height + 5, _Player->Name, 11);
		SetPosition(Width + strlen(_Player->Name), Height + 5, (char*)"의 공격은 그리 효과적이지 못했다, 1의 데미지를 입혔다", 15);
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
		SetPosition(Width + strlen(_Enemy->Name), Height + 5, (char*)"의 공격! ");
		SetPosition(Width + strlen(_Enemy->Name) + strlen("의 공격! "), Height + 5, _Player->Name, 11);
		SetPosition(Width + strlen(_Enemy->Name) + strlen("의 공격! ") + strlen(_Player->Name), Height + 5, (char*)"은(는) ");
		SetPositionI(Width + strlen(_Enemy->Name) + strlen("의 공격! ") + strlen(_Player->Name) + strlen("은(는) "), Height + 5, dmg, 12);
		SetPosition(Width + strlen(_Enemy->Name) + strlen("의 공격! ") + strlen(_Player->Name) + strlen("은(는) ") + sizeof(dmg), Height + 5, (char*)"의 데미지를 입었다 !");

		_Player->Info.HP -= dmg;
	}
	else
	{
		SetPosition(Width + 5, Height + 5, _Enemy->Name, 12);
		SetPosition(Width + 5 + strlen(_Enemy->Name), Height + 5, (char*)"의 공격은 그리 효과적이지 못했다, 1의 데미지를 입혔다", 15);
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
		SetPosition((120 / 2) - (strlen("하세기!") / 2), Height + 3, (char*)"하세기!", 14);
		Sleep(1000);
		SetPosition(Width + 4, Height + 6, _Enemy->Name, 12);
		SetPosition(Width + 4 + strlen(_Enemy->Name), Height + 6, (char*)"에게 ", 15);
		SetPositionI(Width + 4 + strlen(_Enemy->Name) + strlen("에게 "), Height + 6, s1 - _Enemy->Info.DEF, 12);
		SetPosition(Width + 4 + strlen(_Enemy->Name) + strlen("에게 ") + sizeof(s1 - _Enemy->Info.DEF), Height + 6, (char*)"의 데미지를 입혔다 !", 15);
		_Enemy->Info.HP -= s1 - _Enemy->Info.DEF;
		_Player->Info.MP -= 1;
		break;
	case 2:
		SetPosition((120 / 2) - (strlen("그래 !") / 2), Height + 3, (char*)"그래 !", 14);
		SetPosition(Width + 6, Height + 6, _Player->Name, 11);
		SetPosition(Width + 6 + strlen(_Player->Name), Height + 6, (char*)"이 방어자세를 취했다");
		_Player->Info.MP -= 3;
		break;
	case 3:
		SetPosition((120 / 2) - (strlen("울어라 지옥참마도 !") / 2), Height + 3, (char*)"울어라 지옥참마도 !", 12);
		Sleep(1000);
		SetPosition(Width, Height + 6, _Enemy->Name, 12);
		SetPosition(Width + strlen(_Enemy->Name), Height + 6, (char*)"에게 ", 15);
		SetPositionI(Width + strlen(_Enemy->Name) + strlen("에게 "), Height + 6, s3 - _Enemy->Info.DEF, 12);
		SetPosition(Width + 1 + strlen(_Enemy->Name) + strlen("에게 ") + sizeof(s3 - _Enemy->Info.DEF), Height + 6, (char*)"의 데미지를 입혔다 !", 15);

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
	SetPosition(Width + strlen(_Enemy->Name), Height + 3, (char*)"이(가) 공격했지만 ", 15);
	Sleep(500);
	SetPosition(Width + strlen(_Enemy->Name) + strlen("이(가) 공격했지만 "), Height + 3, _Player->Name, 11);
	SetPosition(Width + strlen(_Enemy->Name) + strlen("이(가) 공격했지만 ") + strlen(_Player->Name), Height + 3, (char*)"은 튕겨내고 반격했다 !", 15);
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
		SetPosition((120 / 2) - (strlen("1. 공격 2. 스킬 3. 도망") / 2) - 2, Height + 8, (char*)"1. 공격 2. 스킬 3. 도망", 14);
		SetPosition((120 / 2) - (strlen("나의 선택 : ") / 2) - 1, Height + 9, (char*)"나의 선택 : ", 14);
		scanf("%d", &i);

		switch (i)
		{
		case 3:
			srand(time(NULL));
			if (_Enemy->Info.ATK == 222)
			{
				system("cls");
				PlayerScene();
				SetPosition((120 / 2) - (strlen("저 녀석은 존재해선 안되는 생물이다") / 2), Height + 2, (char*)"저 녀석은 존재해선 안되는 생물이다", 11);
				Sleep(1000);
				SetPosition((120 / 2) - (strlen("내 손으로 마무리 짓겠어") / 2), Height + 4, (char*)"내 손으로 마무리 짓겠어", 11);
				Sleep(1000);
				i = 1;
			}
			else if (rand() % 2 == 0 && _Player->Info.Gold >= 1000)
			{
				system("cls");
				PlayerScene();
				SetPosition((120 / 2) - (strlen("바닥에 동전을 뿌려 적의 주의를 끄는데 성공했지만 1000원을 잃었다 ㅠㅠ") / 2),
					Height + 2, (char*)"바닥에 동전을 뿌려 적의 주의를 끄는데 성공했지만 1000원을 잃었다 ㅠㅠ", 12);
				Sleep(1000);
				_Player->Info.Gold -= 1000;
				SetPosition(Width + 5, Height + 4, (char*)"현재 수중에 남은 돈 : ");
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
				SetPosition(Width + 7, Height + 4, (char*)"아뿔싸, 들켜버렸군...");
				Sleep(1000);
				SetPosition(Width - 3, Height + 6, _Player->Name, 11);
				SetPosition(Width + 6, Height + 6, (char*)"은 하는 수 없이 전투태세를 취했다");
				Sleep(1000);
				system("cls");
				PlayerScene();
				i = 1;
			}
		case 1:
			if (_Player->Info.Speed > _Enemy->Info.Speed)
			{
				SetPositionI(57, Height + 5, turn, 14);
				SetPosition(59, Height + 5, (char*)"턴");
				Sleep(500);
				SetPosition(Width + 6, Height + 6, _Player->Name, 11);
				SetPosition(Width + 6 + strlen(_Player->Name), Height + 6, (char*)"의 선제공격 !");
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
				SetPosition(59, Height + 5, (char*)"턴");
				Sleep(500);
				SetPosition(Width + 6, Height + 6, _Enemy->Name, 12);
				SetPosition(Width + 6 + strlen(_Enemy->Name), Height + 6, (char*)"의 선제공격 !");
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
				SetPosition((120 / 2) - (strlen("둘의 실력이 비슷해 동전 던지기로 선공을 결정하기로 했다") / 2), Height + 10, (char*)"둘의 실력이 비슷해 동전 던지기로 선공을 결정하기로 했다", 14);
				Sleep(1000);
				if (rand() % 2 == 0)
				{
					SetPositionI(57, Height + 5, turn, 14);
					SetPosition(59, Height + 5, (char*)"턴");
					SetPosition(Width + 6, Height + 6, _Player->Name, 11);
					SetPosition(Width + 6 + strlen(_Player->Name), Height + 6, (char*)"의 선제공격 !");

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
					SetPosition(59, Height + 5, (char*)"턴");
					SetPosition(Width + 6, Height + 6, _Enemy->Name, 12);
					SetPosition(Width + 6 + strlen(_Enemy->Name), Height + 6, (char*)"의 선제공격 !");

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
			SetPosition(Width - 16, Height + 2, (char*)"1. 1스킬 : 적에게 200% 의 데미지, 소모 마나 1", 14);
			Sleep(200);
			SetPosition(Width - 16, Height + 3, (char*)"2. 2스킬 : 적의 다음 공격을 튕겨내고 100%의 방어 무시 데미지, 소모 마나 3", 14);
			Sleep(200);
			SetPosition(Width - 16, Height + 4, (char*)"3. 3스킬 : 필살기를 사용해 2000% 데미지, 소모 마나 8", 14);
			Sleep(200);
			SetPosition(Width + 6, Height + 6, (char*)"이외의 아무 키를 눌러 취소 : ");
			scanf("%d", &j);
			if (j > 0 && j <= 3)
			{
				if (_Player->Info.MP >= 1 && j == 1)
				{
					system("cls");
					PlayerScene();
					SetPositionI(57, Height + 5, turn, 14);
					SetPosition(59, Height + 5, (char*)"턴");
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
					SetPosition(59, Height + 5, (char*)"턴");
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
					SetPosition(59, Height + 5, (char*)"턴");
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
					SetPosition((120 / 2) - (strlen("마나가 부족합니다. 다시 선택하세요") / 2), Height + 3, (char*)"마나가 부족합니다. 다시 선택하세요");
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

	SetPosition(39, Height, (char*)"전투 승리! ", 14);
	SetPosition(39 + strlen("전투 승리! "), Height, _Enemy->Name, 12);
	SetPosition(39 + strlen("전투 승리! ") + strlen(_Enemy->Name), Height, (char*)"은(는) 흙으로 돌아갔다 ", 14);
	Sleep(1000);

	if ((_Player->Info.EXP += _Enemy->Info.EXP) < 100)
	{
		SetPosition(40, Height + 2, (char*)"경험치 ", 15);
		SetPositionI(48, Height + 2, _Enemy->Info.EXP);
		SetPosition(48 + sizeof(_Enemy->Info.EXP), Height + 2, (char*)"상승 ! 현재 경험치 : ", 15);
		SetPositionI(48 + sizeof(_Enemy->Info.EXP) + strlen("상승 ! 현재 경험치 : "), Height + 2, _Player->Info.EXP);
		Sleep(1000);
	}
	else if ((_Player->Info.EXP += _Enemy->Info.EXP) >= 100)
	{
		int ex = ((_Player->Info.EXP += _Enemy->Info.EXP) % 100);
		for (int i = 0; i < ((_Player->Info.EXP += _Enemy->Info.EXP) / 100); i++)
		{
			PlayerLvUp(_Player);
		}
		SetPosition(46, Height + 2, (char*)"레벨 업! 현재 레벨 : ", 14);
		SetPositionI(46 + strlen("레벨 업! 현재 레벨 : "), Height + 2, _Player->Info.Level, 11);
		SetPosition(46 + strlen("레벨 업! 현재 레벨 : ") + sizeof(_Player->Info.Level), Height + 2, (char*)"Lv", 14);
		Sleep(1000);

		_Player->Info.EXP = ex;
		SetPosition(51, Height + 4, (char*)"현재 경험치 : ", 15);
		SetPositionI(51 + strlen("현재 경험치 : "), Height + 4, _Player->Info.EXP);
		Sleep(1000);
	}
	_Player->Info.Gold += _Enemy->Info.Gold;
	SetPosition(32, Height + 6, _Enemy->Name, 12);
	SetPosition(32 + strlen(_Enemy->Name), Height + 6, (char*)"이(가) 가지고 있던 ", 15);
	SetPositionI(32 + strlen(_Enemy->Name) + strlen("이(가) 가지고 있던 "), Height + 6, _Enemy->Info.Gold, 14);
	SetPosition(33 + strlen(_Enemy->Name) + strlen("이(가) 가지고 있던 ") + sizeof(_Enemy->Info.Gold), Height + 6, (char*)"원을 전리품으로 챙겼다");
	Sleep(500);
	SetPosition(50, Height + 8, (char*)"현재 소지금 : ");
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
	SetPosition((120 / 2) - (strlen("윽... 분하다") / 2), Height, (char*)"윽... 분하다", 11);
	Sleep(1000);
	SetPosition((120 / 2) - (strlen("재도전 하시겠습니까? 1을 입력해 1000원을 내고 재도전 , 이외의 키 입력으로 게임 종료 : ") / 2), Height + 1, (char*)"재도전 하시겠습니까? 1을 입력해 1000원을 내고 재도전 , 이외의 키 입력으로 게임 종료 : ", 12);
	scanf("%d", &i);

	if (i == 1 && _Player->Info.Gold >= 1000)
	{
		i = 1;
		_Player->Info.Gold -= 1000;
	}
	else if (_Player->Info.Gold < 1000)
	{
		SetPosition((120 / 2) - (strlen("지불할 금액이 부족하네요") / 2), Height + 2, (char*)"지불할 금액이 부족하네요", 14);
		Sleep(1000);
		SetPosition((120 / 2) - (strlen("게임을 종료합니다") / 2), Height + 3, (char*)"게임을 종료합니다.", 12);
		Sleep(2000);
		exit(NULL);
	}
	else
	{
		SetPosition((120 / 2) - (strlen("게임을 종료합니다.") / 2), Height, (char*)"게임을 종료합니다.", 12);
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
	SetPosition(Width + 5, Height + 20, (char*)"┌ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┐", 15);
	SetPosition(Width + 5, Height + 21, (char*)"ㅣ                                                                                                 ㅣ");
	SetPosition(Width + 5, Height + 21, (char*)"ㅣ                                                                                                 ㅣ");
	SetPosition(Width + 5, Height + 22, (char*)"ㅣ                                                                                                 ㅣ");
	SetPosition(Width + 5, Height + 23, (char*)"ㅣ                                                                                                 ㅣ");
	SetPosition(Width + 5, Height + 24, (char*)"ㅣ                                                                                                 ㅣ");
	SetPosition(Width + 5, Height + 25, (char*)"ㅣ                                                                                                 ㅣ");
	SetPosition(Width + 5, Height + 26, (char*)"ㅣ                                                                                                 ㅣ");
	SetPosition(Width + 5, Height + 27, (char*)"ㅣ                                                                                                 ㅣ");
	SetPosition(Width + 5, Height + 28, (char*)"ㅣ                                                                                                 ㅣ");
	SetPosition(Width + 5, Height + 29, (char*)"ㅣ                                                                                                 ㅣ");
	SetPosition(Width + 5, Height + 30, (char*)"ㅣ                                                                                                 ㅣ");
	SetPosition(Width + 5, Height + 31, (char*)"ㅣ                                                                                                 ㅣ");
	SetPosition(Width + 5, Height + 32, (char*)"└ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┘");
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

	SetPosition(Width, Height - 1, (char*)"다음 전투를 위해 이동하던 중 방랑상인 마이콜을 만났다", 15);
	Sleep(500);
	SetPosition(Width, Height, (char*)"마이콜의 잡화상에 오신것을 환영합니다 길동 아저씨, 같이 싸웠던 전우시니 특별히 할인가로 드릴게요", 14);
	Sleep(1000);
	SetPosition(Width, Height + 2, (char*)"마이콜의 잡화상 : ", 14);
	Sleep(500);
	SetPosition(eWidth, Height + 2, (char*)"1.  숯  돌   : 공격력 + ", 14);
	SetPositionI(eWidth + 24, Height + 2, _stg * atk, 12);
	SetPosition(eWidth + 29, Height + 2, (char*)", 가격 : ", 14);
	SetPositionI(eWidth + 38, Height + 2, _stg * w1, 12);
	Sleep(500);
	SetPosition(eWidth, Height + 3, (char*)"2. 후라이팬  : 방어력 + ", 14);
	SetPositionI(eWidth + 24, Height + 3, _stg * def, 12);
	SetPosition(eWidth + 29, Height + 3, (char*)", 가격 : ", 14);
	SetPositionI(eWidth + 38, Height + 3, _stg * w2, 12);
	Sleep(500);
	SetPosition(eWidth, Height + 4, (char*)"3.우황청심환 : 체  력 + ", 14);
	SetPositionI(eWidth + 24, Height + 4, _stg * hp, 12);
	SetPosition(eWidth + 29, Height + 4, (char*)", 가격 : ", 14);
	SetPositionI(eWidth + 38, Height + 4, _stg * w3, 12);
	Sleep(500);
	SetPosition(eWidth, Height + 5, (char*)"4. 슬 리 퍼  : 속  도 + ", 14);
	SetPositionI(eWidth + 24, Height + 5, _stg * spd, 12);
	SetPosition(eWidth + 29, Height + 5, (char*)", 가격 : ", 14);
	SetPositionI(eWidth + 38, Height + 5, _stg * w4, 12);
	Sleep(500);
	SetPosition(Width, Height + 7, (char*)"현재 소지금 : ", 15);
	SetPositionI(Width + 14, Height + 7, _Player->Info.Gold, 14);
	Sleep(500);
	SetPosition(Width + 20, Height + 7, (char*)"원, 구매를 원하지 않으면 1 ~ 4 이외의 키를 입력 : ", 15);


	scanf("%d", &i);

	if (i == 1)
	{
		if (_Player->Info.Gold >= _stg * w1)
		{
			_Player->Info.ATK += _stg * atk;
			_Player->Info.Gold -= _stg * w1;
			SetPosition(Width, Height + 8, (char*)"감사합니다 호갱님!", 14);
			Sleep(500);
			SetPosition(Width, Height + 9, (char*)"뭔가 찜찜하다... 현재 소지금 : ", 15);
			SetPositionI(Width + 32, Height + 9, _Player->Info.Gold, 14);
			Sleep(1000);
		}
		else
		{
			SetPosition(Width, Height + 8, (char*)"저런...빈털털이시군요? 나가실 문은 오른쪽입니다~", 12);
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
			SetPosition(Width, Height + 8, (char*)"감사합니다 호갱님!", 14);
			Sleep(500);
			SetPosition(Width, Height + 9, (char*)"뭔가 찜찜하다... 현재 소지금 : ", 15);
			SetPositionI(Width + 32, Height + 9, _Player->Info.Gold, 14);
			Sleep(1000);
		}
		else
		{
			SetPosition(Width, Height + 8, (char*)"저런...돈이 부족하시군요? 나가실 문은 오른쪽입니다~", 12);
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
			SetPosition(Width, Height + 8, (char*)"감사합니다 호갱님!", 14);
			Sleep(500);
			SetPosition(Width, Height + 9, (char*)"뭔가 찜찜하다... 현재 소지금 : ", 15);
			SetPositionI(Width + 32, Height + 9, _Player->Info.Gold, 14);
			Sleep(1000);
		}
		else
		{
			SetPosition(Width, Height + 8, (char*)"저런...돈이 부족하시군요? 나가실 문은 오른쪽입니다~", 12);
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
			SetPosition(Width, Height + 8, (char*)"감사합니다 호갱님!", 14);
			Sleep(500);
			SetPosition(Width, Height + 9, (char*)"뭔가 찜찜하다... 현재 소지금 : ", 15);
			Sleep(1000);
			SetPositionI(Width + 32, Height + 9, _Player->Info.Gold, 14);
		}
		else
		{
			SetPosition(Width, Height + 8, (char*)"저런...돈이 부족하시군요? 나가실 문은 오른쪽입니다~", 12);
			Sleep(1000);
			i = 0;
		}
	}
	else
	{
		SetPosition(Width, Height + 8, (char*)"에이 형씨 ~ 이 바닥에서 쿨거래는 기본이에요  ! ", 14);
		Sleep(500);
		SetPosition(Width, Height + 9, (char*)"물건의 상태가 좋지 않아 거래를 취소하고 발걸음을 옮겼다", 15);
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
		SetPosition(Width, Height, (char*)"전투를 끝낸 당신을 희동이가 반겨준다");
		Sleep(1000);
		SetPosition(Width, Height + 1, (char*)"희동이의 응원 : ");
		Sleep(500);
		SetPosition(Width, Height + 3, (char*)"1. 다음 전투에서 공격력 30% 증가 버프", 14);
		Sleep(500);
		SetPosition(Width, Height + 4, (char*)"2. 다음 전투에서 방어력 30% 증가 버프", 14);
		Sleep(500);
		SetPosition(Width, Height + 5, (char*)"3. 다음 전투에서 속도 10 증가 버프", 14);
		Sleep(500);
		SetPosition(Width, Height + 7, (char*)"버프 선택 : ");
		scanf("%d", &i);
		if (i < 1 || i > 4)
		{
			SetPosition(Width + 15, Height + 7, (char*)"다시 선택하세요", 12);
			Sleep(500);
			i = 0;
		}
		else
		{
			SetPosition((120 / 2) - (strlen("고모부 힘내!") / 2), Height + 8, (char*)"고모부 힘내!", 15);
			Sleep(500);
			SetPosition((120 / 2) - (strlen("희동이의 응원에 힘이 솟는다") / 2), Height + 9, (char*)"희동이의 응원에 힘이 솟는다", 11);
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
	SetPosition(60 - (strlen("선 넘네...") / 2), Height, (char*)"선 넘네...", 12);
	Sleep(1000);
	SetPosition(60 - (strlen("젓밥 고길동이 날 이렇게까지 꼴받게 하다니") / 2), Height + 2, (char*)"젓밥 고길동이 날 이렇게까지 꼴받게 하다니", 12);
	Sleep(1000);
	SetPosition(59 - (strlen("내가 직접 정신교육부터 다시 해주지") / 2), Height + 4, (char*)"내가 직접 정신교육부터 다시 해주지", 12);
	Sleep(1000);
	SetPosition(60 - (strlen("드디어 여기까지 왔다...") / 2), Height + 8, (char*)"드디어 여기까지 왔다...", 11);
	Sleep(500);
	SetPosition(60 - (strlen("녀석을 없애고 가정의 평화를 되찾는거다 !") / 2), Height + 10, (char*)"녀석을 없애고 가정의 평화를 되찾는거다 !", 11);
	Sleep(1500);
}

void EndingScene(OBJECT* _Player, int _count)
{
	int Height = 11;

	system("cls");
	SetPosition(60 - (strlen("이런...말도 안되는...") / 2), Height, (char*)"이런...말도 안되는...", 12);
	Sleep(1000);
	SetPosition(60 - (strlen("...엄...마...") / 2), Height + 2, (char*)"...엄...마...", 12);
	Sleep(1000);
	SetPosition(60 - (strlen("사악한 외계 도마뱀을 물리쳤다 !") / 2), Height + 4, (char*)"사악한 외계 도마뱀을 물리쳤다 !", 15);
	Sleep(1000);
	SetPosition(60 - (strlen("드디어 끝난건가") / 2), Height + 6, (char*)"드디어 끝난건가", 11);
	Sleep(1000);
	SetPosition(60 - (strlen("벌써부터 마음이 안정되는 기분이군...") / 2), Height + 8, (char*)"벌써부터 마음이 안정되는 기분이군...", 11);
	Sleep(1000);
	SetPosition(60 - (strlen("집으로 돌아가자 오늘 밤은 파티다 !") / 2), Height + 10, (char*)"집으로 돌아가자 오늘 밤은 파티다 !", 11);
	Sleep(1000);
	SetPosition(60 - (strlen("게임 클리어 !") / 2), Height + 12, (char*)"게임 클리어 !", 14);
	Sleep(1000);
	SetPosition(51, Height + 14, (char*)"총 플레이타임 : ", 15);
	SetPositionI(51 + strlen("총 플레이타임 : "), Height + 14, _count / 10000, 14);
	SetPosition(51 + strlen("총 플레이타임 : ") + sizeof(_count / 10000), Height + 14, (char*)"초", 15);
	Sleep(1000);
	SetPosition(54, Height + 16, (char*)"최고 레벨 : ", 15);
	SetPositionI(54 + strlen("최종 레벨 : "), Height + 16, _Player->Info.Level, 14);
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