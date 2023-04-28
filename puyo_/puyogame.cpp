#include "puyogame.h"
#include"../source/scenemanager.h"
#include"../source/scene.h"
#include"links.h"
PuyoGame::PuyoGame(Scene* sc)
	:Object(sc)
	,puyo(nullptr)
	,field(nullptr)
	,chain(nullptr)
	,navi(nullptr)
	,score(nullptr)
	,send(nullptr)
	,rect(nullptr)
	,connectMode(nullptr)
	,nowMode(Mode::start)
	,nextMode(Mode::start)
	,oldMode(Mode::start)
	,batankyu("")
	, batankyuOn(false)
	,keystop(false)
	, saveKeyStop(false)
{}
PuyoGame::~PuyoGame(){
	GetScene()->Destroy("ぷよの繋がり");
}
void PuyoGame::Init(){
	puyo=GetScene()->Create<PuyoPlayer>();
	field=GetScene()->Create<PuyoField>();
	chain=GetScene()->Create<PuyoChain>();
	navi = GetScene()->Create<PuyoNavigation>();
	GetScene()->Create<PuyoLinks>("ぷよの繋がり");
	//GetScene()->Create<PuyoLinks>();
	score=GetScene()->Create<PuyoScore>();
	send = GetScene()->Create<PuyoConnectSend>();
	rect = GetScene()->Create<PuyoConnectRect>();
	GetScene()->ChangeDispRank(field, -5);
	GetScene()->ChangeDispRank(puyo, 1);
	nowMode = Mode::start;
	nextMode = Mode::start;
}
void PuyoGame::Update() {
	bool flag=SceneManager::GetFrame() % 30 == 0;
	if (!CheckHitKey(KEY_INPUT_SPACE))flag = true;
	if(flag)
	switch (nowMode) {
	case PuyoGame::Mode::start:

		nextMode = Mode::instance;
		break;
	case PuyoGame::Mode::instance:
		chain->Refresh();
		if (puyo->Instance()) {
			navi->NaviOn();
			nextMode = Mode::move;
		}
		else {
			nextMode = Mode::gameover;
		}
		break;
	case PuyoGame::Mode::move:
		if (!puyo->Move()) {
			navi->NaviOff();
			nextMode = Mode::setfield;
			//ここでフィールド情報送信
		}
		else {
			score->DefaultUp();
		}
		if (CheckHitKey(KEY_INPUT_LSHIFT)) {
			navi->NaviOff();
			nextMode = Mode::setfield;
			//ここでフィールド情報送信
		}
		//ムーブではプレイヤーの情報送信
		break;
	case PuyoGame::Mode::setfield:
		puyo->FieldIn();
		nextMode = Mode::falldown;
		break;
	case PuyoGame::Mode::falldown:
		if(field->FallDown())
		nextMode = Mode::erase;
		break;
	case PuyoGame::Mode::erase:
		if (SceneManager::GetFrame() % 20 == 0) {

			if (field->Erase()) {
				nextMode = Mode::falldown;
				score->EraseCalc();

			}
			else {
				nextMode = Mode::instance;

			score->EraseUp();
			}
		}

		break;
	case PuyoGame::Mode::gameover:
		batankyu = "バタンキュー";
		batankyuOn = true;
		if (CheckHitKey(KEY_INPUT_R)&&!keystop) {
			Destroyer();
			Init();
			
			batankyuOn = false;
			batankyu = "";

		}
		keystop = CheckHitKey(KEY_INPUT_R);
		break;
	case PuyoGame::Mode::connect:
		if (CheckHitKey(KEY_INPUT_TAB)
			||connectMode->GetOff()
			) {
			nextMode = oldMode;
			GetScene()->Destroy(connectMode);
			connectMode = nullptr;
		}
		break;
	default:
		//bug
		break;
	}

	GoConnectScreen();
	ChangeBackScene();

	bool saveKey = CheckHitKey(KEY_INPUT_SPACE);
	if (saveKey && !saveKeyStop) {
		field->Save();
	}
	saveKeyStop = saveKey;

	if(nowMode!=nextMode)
	nowMode = nextMode;
}
void PuyoGame::Draw(){
	std::string kaisetu  = "WASDまたは十字キー　 で　移動\n";
				kaisetu += "Qキー　　　　　　　　で　左回転\n";
				kaisetu += "Eキー　　　　　　　　で　右回転\n";
				kaisetu += "LShiftキー　　　　　 で　すぐ設置\n";
				kaisetu += "Rキー　　　　　　　　で　バタンキュー時に\n";
				kaisetu += "　　　　　　　　　　　　　　　　　　リセット\n";
				kaisetu += "\n";
				kaisetu += "Spaceキー　　　　　　で　デバッグ&セーブ\n";
				kaisetu += "Oキー　　　　　　　　で　通信画面\n";
				kaisetu += "Tキー　　　　　　　　で　タイトルへ\n";
	
	DrawFormatString(400,100,0xffffff,kaisetu.c_str());

	int fontSize = GetFontSize();

	if (batankyuOn)SetFontSize(96);
	int color = 0x000000;
	float num = 5.f;
	Vec2 tyousei = {num,num };
	Vec2 pos = {150,250};
	SousyokuDraw(pos,num,color,batankyu);

	color = 0xffffff;
	DrawFormatString(pos.x, pos.y, color, batankyu.c_str());
	SetFontSize(fontSize);

	if(CheckHitKey(KEY_INPUT_SPACE))
	DebugDraw();
}

void PuyoGame::ChangeMode(Mode _mode){
	nextMode = _mode;
}

void PuyoGame::DebugDraw(){
std::string mozi = "";
	switch (nowMode)
	{
	case PuyoGame::Mode::start:
		mozi = "start";
		break;
	case PuyoGame::Mode::instance:
		mozi = "instance";
		break;
	case PuyoGame::Mode::setfield:
		mozi = "setfield";
		break;
	case PuyoGame::Mode::move:
		mozi = "move";
		break;
	case PuyoGame::Mode::falldown:
		mozi = "falldown";
		break;
	case PuyoGame::Mode::erase:
		mozi = "erase";
		break;
	case PuyoGame::Mode::gameover:
		mozi = "gameover";
		break;
	default:
		mozi = "bug";
		break;
	}
	DrawFormatString(400,425,0xffffff,mozi.c_str());
}
void PuyoGame::SousyokuDraw(Vec2 pos,float num,int color, std::string _str){
	Vec2 tyousei = {num,num};
	Vec2 disp = { pos.x + tyousei.x,pos.y + tyousei.y };
	DrawFormatString(disp.x, disp.y, color, _str.c_str());
	tyousei = { -num,-num };
	disp = { pos.x + tyousei.x,pos.y + tyousei.y };
	DrawFormatString(disp.x, disp.y, color, _str.c_str());
	tyousei = { -num,num };
	disp = { pos.x + tyousei.x,pos.y + tyousei.y };
	DrawFormatString(disp.x, disp.y, color, _str.c_str());
	tyousei = { num,-num };
	disp = { pos.x + tyousei.x,pos.y + tyousei.y };
	DrawFormatString(disp.x, disp.y, color, _str.c_str());

}
void PuyoGame::GoConnectScreen() {
	bool oKey = CheckHitKey(KEY_INPUT_O);
	bool change = oKey && !connectKeyStop;
	bool isMode = Mode::connect != nowMode;
	if (change &&isMode) {
		nextMode = Mode::connect;
		oldMode = nowMode;
		if (connectMode == nullptr) {
			connectMode = GetScene()->Create<PuyoConnectMode>();
			GetScene()->ChangeDispRank(connectMode, 2);
		}
	}
	connectKeyStop = oKey;
}
void PuyoGame::ChangeBackScene(){
	bool backKey = CheckHitKey(KEY_INPUT_T);
	if (!backKey)return;
	//Destroyer();
	SceneManager::ChangeScene("Title");
}

void PuyoGame::Destroyer(){
	GetScene()->Destroy(puyo);
	GetScene()->Destroy(navi);
	GetScene()->Destroy(field);
	GetScene()->Destroy(chain);
	//GetScene()->Destroy<PuyoLinks>("繋がり");
	GetScene()->Destroy("ぷよの繋がり");
	GetScene()->Destroy(score);
	GetScene()->Destroy(send);
	GetScene()->Destroy(rect);
}

