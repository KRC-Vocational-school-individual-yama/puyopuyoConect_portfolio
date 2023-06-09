#include "reel.h"
#include"../source/config.h"
#include"uiinterface.h"

void ReelShape::Draw(){
	switch (shape)	{
	case ReelShape::Shape::circle:
		DrawCircleAA(x,y,r,20,color,fill,5);
		break;
	case ReelShape::Shape::triangle:
		DrawCircleAA(x, y, r, 3, color, fill,5);
		break;
	case ReelShape::Shape::square:
		DrawCircleAA(x, y, r, 4, color, fill,5);
		break;
	case ReelShape::Shape::pentagon:
		DrawCircleAA(x, y, r, 5, color, fill,5);
		break;
	case ReelShape::Shape::hexagon:
		DrawCircleAA(x, y, r, 6, color, fill,5);
		break;
	case ReelShape::Shape::heptagon:
		DrawCircleAA(x, y, r, 7, color, fill,5);
		break;
	case ReelShape::Shape::octagon:
		DrawCircleAA(x, y, r, 8, color, fill,5);
		break;
	case ReelShape::Shape::nonagon:
		DrawCircleAA(x, y, r, 9, color, fill,5);
		break;
	default:
		DrawCircleAA(x, y, r, 20, 0xaaaaaa, fill,5);
		break;
	}
}

Reel::Reel():
	shapes(),
	y(0),
	yvec(0),
	keystop(false),
	button(false),
	reelstop(false),
	graphnum(-1),
	keynumber(KEY_INPUT_F)
	, framecountdebug(0)
{}
Reel::~Reel(){

}
void Reel::Init(){
	VectorsResize();
	ShapesMenberSet();
}
void Reel::Update(){
	framecountdebug++;
	//ボタン処理
	ButtonStop();
	ButtonReStert();

	//リールの動き処理
	ReelAllMoves();

	//リール位置代入
	DispInValue();

}
void Reel::Draw() {
	for (auto j : shapes) {
		for (auto i : j) {
			i.Draw();
		}
	}
}

void Reel::SetPos(float pos){
	for (int j = 0; j < shapes.size(); j++) {
		for (int i = 0; i < shapes[j].size(); i++) {
			shapes[j][i].x = pos;
			shapes[j][i].y = 0;
			/*
			shapes[j][i].r = 25;
			shapes[j][i].color = color::GetHSV(30 * i, 255, 255);
			shapes[j][i].fill = false;
			shapes[j][i].shape = static_cast<ReelShape::Shape>(i);
			*/
		}
	}
}
Vec2 Reel::GetReelPos(){
	Vec2 pos;
	pos.x = shapes[0][0].x;
	pos.y = shapes[0][0].y;

	return pos;
}

void Reel::VectorsResize(){
	shapes.resize(ReelsMaxNum);
	const int index = static_cast<int>(ReelShape::Shape::max);
	for (int i = 0; i < shapes.size(); i++) {
		shapes[i].resize(index);		
	}
}

void Reel::ShapesMenberSet() {

	yvec = speed;
	y = 0.0f;

	for (int j = 0; j < shapes.size(); j++) {
		for (int i = 0; i < shapes[j].size(); i++) {
			shapes[j][i].x = -1;
			shapes[j][i].y = -1;
			shapes[j][i].r = 25;
			int hue = 30 * i;//色相
			shapes[j][i].color = color::GetHSV(hue, 255, 255);
			shapes[j][i].fill = false;
			shapes[j][i].shape = static_cast<ReelShape::Shape>(i);

			//float stertPostyousei = 0;
			//y = stertPostyousei + i * GraphSize;
		}
	}
}
void Reel::ButtonStop() {
	bool key = CheckHitKey(keynumber);
	bool buttonInput = key && !keystop;
	keystop = key;
	if (!buttonInput)return;
	button = true;
}
void Reel::ButtonReStert() {
	bool spaceInput = CheckHitKey(KEY_INPUT_SPACE);
	if (!spaceInput)return;
	graphnum = -1;
	button = false;
	reelstop = false;
	yvec = speed;
		
}
void Reel::ReelNowStop() {
	if (!reelstop) return;
	//位置の固定をしようとしてたが必要あるか微妙
	/*const int stopnum = static_cast<int>(ReelShape::Shape::max);
	for (int t = 0; t < stopnum; t++) {
		const float reelheight = stopnum * 75;
		int height = static_cast<int>(reelheight / stopnum);
		int stoppos = t * height;
		if (y[j][0] != stoppos) continue;
		y[j][i] = stoppos;
		return;
	}*/
}
void Reel::ReelStopMove() {

	if (!button) return;

	//移動量の減少
	--yvec;
	if (yvec < 1)yvec = 1;

	//止まるまで動く
	ReelNowMove();

	//止まる位置
	const int stopnum = static_cast<int>(ReelShape::Shape::max);
	for (int t = 0; t < stopnum * 2; t++) {
		const float reelheight = stopnum * 75;
		int height = reelheight / stopnum;
		int stoppos = t * height;
		if (y == stoppos) {
			reelstop = true;
			y = stoppos;

			graphnum = static_cast<int>((y - reelheight) / height);
			if (graphnum < 0)graphnum *= -1;
			if (graphnum >= stopnum)graphnum -= stopnum;

			break;
		}
	}
}
void Reel::ReelNowMove() {

	//下へ移動
	y += yvec;

	//折り返し
	if (y <= ReelSize-speed) return;

	//位置の初期化
	y = 0;
	
}
void Reel::ReelAllMoves(){
	//if (framecountdebug % 3 != 0)return;
	//止まっている時
	ReelNowStop();
	if (reelstop)return;

	//止まるフラグ立った後の移動
	ReelStopMove();
	if (button)return;

	//通常移動
	ReelNowMove();

}
void Reel::DispInValue() {
	int tyouseiPos = 300;
	for (int j=0; j < ReelsMaxNum; j++) {
		for (int i = 0; i < shapes[0].size(); i++) {
			int zurasi = ReelSize * j;
			int graphzurasi = i * GraphSize;
			shapes[j][i].y = y - zurasi+graphzurasi+ tyouseiPos;
		}
	}
}

void Reel::DebugDraw(){
	printfDx("pos=     %.0f\n",y);
	printfDx("disppos= %.0f\n",shapes[0][0].y);
	//printfDx("graphnum=%d\n",GetStopimg());
switch (graphnum){
	case static_cast<int>(ReelShape::Shape::circle):
		printfDx("graphnum=%d 正円\n", GetStopimg());
		break;
	case static_cast<int>(ReelShape::Shape::triangle):
		printfDx("graphnum=%d 三角\n", GetStopimg());
		break;
	case static_cast<int>(ReelShape::Shape::square):
		printfDx("graphnum=%d 四角\n", GetStopimg());
		break;
	case static_cast<int>(ReelShape::Shape::pentagon):
		printfDx("graphnum=%d 五角\n", GetStopimg());
		break;
	case static_cast<int>(ReelShape::Shape::hexagon):
		printfDx("graphnum=%d 六角\n", GetStopimg());
		break;
	case static_cast<int>(ReelShape::Shape::heptagon):
		printfDx("graphnum=%d 七角\n", GetStopimg());
		break;
	case static_cast<int>(ReelShape::Shape::octagon):
		printfDx("graphnum=%d 八角\n", GetStopimg());
		break;
	case static_cast<int>(ReelShape::Shape::nonagon):
		printfDx("graphnum=%d 九角\n", GetStopimg());
		break;
	default:
		printfDx("graphnum=%d 動中\n", GetStopimg());
		break;
	}
}

Slot::Slot(Scene* sc)
	:Object(sc)
	,reels()
	,success(false)
	,num()
{}

Slot::~Slot(){
	for (int i = 0; i < reels.size(); i++) {
		delete reels[i];
	}
}

void Slot::Init(){
	reels.resize(ReelsNum);
	num.resize(ReelsNum);
	for (int i = 0; i < reels.size(); i++) {
		reels[i] = new Reel();
		reels[i]->Init();
		reels[i]->SetPos(400.f+i*60);
		reels[i]->SetStopKey(-1);
		num[i] = -1;
	}
	//止めるキーの設定
	reels[0]->SetStopKey(KEY_INPUT_A);
	reels[1]->SetStopKey(KEY_INPUT_S);
	reels[2]->SetStopKey(KEY_INPUT_D);
}

void Slot::Update(){
	//リールの動き
	for (auto& i : reels) {
		i->Update();
	}

	//揃い判定
	bool flag1 = false;
	bool flag2 = false;
	for (int i = 0; i < ReelsNum; i++) {
		num[i] = reels[i]->GetStopimg();
		if (num[i] < 0)continue;
		flag1 = num[0]==num[1];
		flag2 = num[0] == num[2];
		
		if (flag1&&flag2) {
			success = true;
		}
	}
	//リセット
	ReStartReel();

}

void Slot::Draw(){
	//リールの描画
	for (auto i : reels) {
		i->Draw();
	}

	//黒い隠し
	int tyousei = 75;
	DrawBox(0,0, SCREEN_WIDTH,300-tyousei,0x000000,true);
	DrawBox(0,300+ tyousei, SCREEN_WIDTH,600,0x000000,true);

	//DebugDraw();
}

Vec2 Slot::GetPos(int slotnumber) {
	switch (slotnumber) {
	case 0:
		return reels[slotnumber]->GetReelPos();
		break;
	case 1:
		return reels[slotnumber]->GetReelPos();
		break;
	case 2:
		return reels[slotnumber]->GetReelPos();
		break;
	default:
		return Vec2{ 0,0 };
		break;
	}
}

void Slot::ReStartReel(){
bool key=CheckHitKey(KEY_INPUT_SPACE);
	if (key) {
		success = false;
	}
}

void Slot::DebugDraw(){
	for (auto i : reels) {
		i->DebugDraw();
	}
	printfDx("揃い　%s\n",success?"ON" :"OFF");
}
