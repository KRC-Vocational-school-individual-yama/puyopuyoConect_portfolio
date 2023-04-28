#pragma once
#include"../source/object.h"
#include<string>
#include"puyo.h"
#include"field.h"
#include"chain.h"
#include"navigation.h"
#include"score.h"
#include"send.h"
#include"rect.h"
#include"connectmode.h"

class PuyoGame :public Object {
public:
	PuyoGame(Scene* sc);
	~PuyoGame();
	void Init()override;
	void Update()override;
	void Draw()override;
	
	enum class Mode {
		start
		,instance
		,setfield
		,move
		,falldown
		,erase
		,gameover
		,connect

	};
	void ChangeMode(Mode _mode);
	Mode GetMode() { return nowMode; }

private:
	void DebugDraw();
	void SousyokuDraw(Vec2 pos, float num, int color,std::string _str);
	void GoConnectScreen();
	void ChangeBackScene();
	void Destroyer();

	PuyoPlayer* puyo;
	PuyoField* field;
	PuyoChain* chain;
	PuyoNavigation* navi;
	PuyoScore* score;
	PuyoConnectRect* rect;
	PuyoConnectSend* send;
	PuyoConnectMode* connectMode;
	Mode nowMode;
	Mode nextMode;
	Mode oldMode;//ê⁄ë±Ç≈ÇµÇ©égÇÌÇ»Ç¢
	std::string batankyu;
	bool batankyuOn;
	bool keystop;
	bool saveKeyStop;
	bool connectKeyStop;
};