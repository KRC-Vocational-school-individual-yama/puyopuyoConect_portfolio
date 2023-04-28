#include "puyo.h"
#include"field.h"
#include"puyogame.h"
#include"../source/scene.h"
#include"../source/scenemanager.h"

PuyoPlayer::PuyoPlayer(Scene* sc)
	:Object(sc)
	,puyo(nullptr)
	,se(nullptr)
	,keyDir(KeyDirs::up)
	,keyMoveStop(false)
	,keyRotateStop(false)
	,fallOn(false)
	,fallSpeed(25)
{}
PuyoPlayer::~PuyoPlayer(){
	delete puyo;
}
void PuyoPlayer::Init(){
	//puyo = new Puyo();
	puyo = nullptr;
	se = GetScene()->Invoke<PuyoSe>();
}
void PuyoPlayer::Update(){
	if (puyo == nullptr)return;
	puyo->dir = DirtoVec2(keyDir);
	DebugMove();
}
void PuyoPlayer::Draw() {
	puyo->Draw();
	//Vec2 disppos = PuyoField::GetGridPos(puyo->pos.y,puyo->pos.x);
	//Vec2 disppos2 = PuyoField::GetGridPos(puyo->pos.y+puyo->dir.y,puyo->pos.x+puyo->dir.x);
	////ぷよの描画
	//int cIndex = puyo->color;
	//int cIndex2 = puyo->color2;
	//int color = PuyoPlayerConfig::colorTable[cIndex];
	//int color2 = PuyoPlayerConfig::colorTable[cIndex2];
	//DrawCircle(disppos.x, disppos.y, PuyoFieldConfig::puyoSize , color, true);
	//DrawCircle(disppos2.x, disppos2.y, PuyoFieldConfig::puyoSize , color2, true);
}

bool PuyoPlayer::Instance(){
	delete puyo;
	puyo = nullptr;
	keyDir = KeyDirs::up;
	keyMoveStop = false;
	keyRotateStop = false;
	fallOn = false;
	fallSpeed = 25;
	puyo = new Puyo();

	//puyo->color = 0;
	//puyo->color2 = 0;

	if (!MoveCheck(0, 1)) {//下にぷよがある
		return false;
	}

	return true;
}

bool PuyoPlayer::Move(){
	KeyState();
	Rotate();
	int nowTime=SceneManager::GetFrame();
	if (fallOn) {
		if (nowTime%fallSpeed != 0)return true;
	}
	else {
		if (nowTime%25 != 0) return true;
	}
	
	if (MoveCheck(0, 1)) {
		puyo->pos.y++;
	}
	else {
		return false;
		//GetScene()->Invoke<PuyoGame>()->ChangeMode(PuyoGame::Mode::setfield);
	}
	return true;
}

void PuyoPlayer::FieldIn() {
	if (puyo == nullptr)return;
	GetScene()->Invoke<PuyoField>()->SetField(puyo->pos, puyo->color);
	Vec2 pos = { puyo->pos.x + puyo->dir.x,puyo->pos.y + puyo->dir.y };
	GetScene()->Invoke<PuyoField>()->SetField(pos, puyo->color2);
	delete puyo;
	puyo = nullptr;
}

Puyo PuyoPlayer::GetPuyoPlayer(){
	if (puyo == nullptr)return Puyo();//何もないを返す。
	return *puyo;
}

void PuyoPlayer::DebugMove(){
	bool enterkey = CheckHitKey(KEY_INPUT_RETURN);
	if (enterkey ) {
		GetScene()->Invoke<PuyoField>()->SetField(puyo->pos,puyo->color);
		Vec2 pos = { puyo->pos.x+puyo->dir.x,puyo->pos.y+puyo->dir.y };
		GetScene()->Invoke<PuyoField>()->SetField(pos,puyo->color2);
	}
}

void PuyoPlayer::KeyState() {
	bool upkey = CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W);
	bool downkey = CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S);
	bool leftkey = CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A);
	bool rightkey = CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D);
	bool allkey = upkey || downkey || leftkey || rightkey;
	int moveDir = -1;
	if (upkey && !keyMoveStop)moveDir = KeyDirs::up;
	//if (downkey && !keyMoveStop)moveDir = KeyDirs::down;
	fallOn = downkey;
	if (downkey) {
		fallSpeed--;
		if (fallSpeed< 2)fallSpeed = 2;
	}
	else {
		fallSpeed = 25;
	}
	if (leftkey && !keyMoveStop) {
		se->LeftTrunSe();
		moveDir = KeyDirs::left;
	}
	if (rightkey && !keyMoveStop) {
		se->RightTrunSe();
		moveDir = KeyDirs::right;
	}
	keyMoveStop = allkey;

	Vec2 vec = DirtoVec2(moveDir);


	if (MoveCheck(vec.x, 0)) {
		puyo->pos.x += vec.x;
	}
	if (MoveCheck(0, vec.y)) {
		puyo->pos.y += vec.y;
	}
}

bool PuyoPlayer::MoveCheck(int _x,int _y){
	Vec2 nowpos	={puyo->pos.x,puyo->pos.y};
	Vec2 nowpos2={puyo->dir.x,puyo->dir.y};
	nowpos2.x += nowpos.x;
	nowpos2.y += nowpos.y;
	nowpos.x += _x;
	nowpos.y += _y;
	nowpos2.x += _x;
	nowpos2.y += _y;
	bool flag=GetScene()->Invoke<PuyoField>()->WallJudge(nowpos.y,nowpos.x);
	bool flag2=GetScene()->Invoke<PuyoField>()->WallJudge(nowpos2.y,nowpos2.x);
	if (!flag && !flag2)return true;

	return false;
}


void PuyoPlayer::Rotate(){
	bool leftRotate = CheckHitKey(KEY_INPUT_Q);
	bool rightRotate = CheckHitKey(KEY_INPUT_E);
	if (leftRotate && !keyRotateStop) {
		int nextDir = keyDir - 1;
		if (RotateChack(nextDir)) {
			se->LeftTrunSe();
			keyDir--;
		}
	}
	if (rightRotate && !keyRotateStop) {
		int nextDir = keyDir + 1;
		if (RotateChack(nextDir)) {//動かせるかチェック
			se->RightTrunSe();
			keyDir++;
		}
	}
	keyRotateStop = leftRotate || rightRotate;

	if (keyDir < 0)keyDir = KeyDirs::left;
	if (keyDir > KeyDirs::left)keyDir = 0;
	
}

bool PuyoPlayer::RotateChack(int _keyDir) {
	if (_keyDir < 0)_keyDir = KeyDirs::left;
	if (_keyDir > KeyDirs::left)_keyDir = 0;
	Vec2 nextDir = DirtoVec2(_keyDir);
	Vec2 nextPos = {};
	nextPos.x=puyo->pos.x + nextDir.x;
	nextPos.y=puyo->pos.y + nextDir.y;
	bool wall = GetScene()->Invoke<PuyoField>()->WallJudge(nextPos.y, nextPos.x);
	if (!wall)return true;
	return false;
}

Vec2 PuyoPlayer::DirtoVec2(int _keyDir){
	switch (_keyDir){
	case KeyDirs::up:
		return {0,-1};
		break;
	case KeyDirs::down:
		return { 0,1 };
		break;
	case KeyDirs::right:
		return { 1,0 };
		break;
	case KeyDirs::left:
		return { -1,0 };
		break;
	default:
		return {0,0};
		break;
	}
}
void Puyo::Draw(){
	if (this == nullptr)return;
	Vec2 disppos = PuyoField::GetGridPos(pos.y, pos.x);
	Vec2 disppos2 = PuyoField::GetGridPos(pos.y + dir.y, pos.x + dir.x);
	//ぷよの描画
	int cIndex = color;
	int cIndex2 = color2;
	int color = PuyoPlayerConfig::colorTable[cIndex];
	int color2 = PuyoPlayerConfig::colorTable[cIndex2];
	DrawCircle(disppos.x, disppos.y, PuyoFieldConfig::puyoSize, color, true);
	DrawCircle(disppos2.x, disppos2.y, PuyoFieldConfig::puyoSize, color2, true);

}
