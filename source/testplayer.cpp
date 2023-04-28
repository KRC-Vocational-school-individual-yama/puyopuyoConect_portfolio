#include "testplayer.h"
#include"config.h"

TestPlayer::TestPlayer(Scene* sc)
	:Object(sc)
	,en()
	,speed(5)
{}
TestPlayer::~TestPlayer(){
}
void TestPlayer::Init(){
	en.pos = {400,300};
	en.radius = 20;
}
void TestPlayer::Update() {
	bool up		= CheckHitKey(KEY_INPUT_W);
	bool down	= CheckHitKey(KEY_INPUT_S);
	bool left	= CheckHitKey(KEY_INPUT_A);
	bool right	= CheckHitKey(KEY_INPUT_D);
	bool speedUp= CheckHitKey(KEY_INPUT_LSHIFT);
	
	speedUp ? speed = 10 : speed = 5;

	if (up) {
		en.pos.y -= speed;
		if (en.pos.y < 0+en.radius) {
			en.pos.y = 0+en.radius;
		}
	}
	if (down) {
		en.pos.y += speed;
		if (en.pos.y > SCREEN_HEIGHT-en.radius) {
			en.pos.y = SCREEN_HEIGHT-en.radius;
		}
	}
	if (left) {
		en.pos.x -= speed;
		if (en.pos.x < 0+en.radius) {
			en.pos.x = 0+en.radius;
		}
	}
	if (right) {
		en.pos.x += speed;
		if (en.pos.x > SCREEN_WIDTH-en.radius) {
			en.pos.x = SCREEN_WIDTH-en.radius;
		}
	}
	



	bool flag = CheckHitKey(KEY_INPUT_SPACE);
	if (flag) {
		SceneManager::ChangeScene("Game");
	}
	flag = CheckHitKey(KEY_INPUT_R);
	if (flag) {
		SceneManager::ChangeScene("Slot");
	}
	flag = CheckHitKey(KEY_INPUT_P);
	if (flag) {
		SceneManager::ChangeScene("Puyo");
	}

}
void TestPlayer::Draw(){
	DrawCircleAA(en.pos.x,en.pos.y,en.radius,9,0xffffff,false,3.f);
	Vec2 poss = {100,100};
	DrawFormatString(poss.x,poss.y*1,0xffffff,"_現在_　　　　TitleScene　（仮");
	DrawFormatString(poss.x,poss.y*2,0xffffff,"Spaceキー　　 GameScene　 （仮");
	DrawFormatString(poss.x,poss.y*3,0xffffff,"Rキー　　　　 SlotScene　 （一旦完成");
	DrawFormatString(poss.x,poss.y*4,0xffffff,"Pキー　　　　 PuyoScene　 （作成中");
}
