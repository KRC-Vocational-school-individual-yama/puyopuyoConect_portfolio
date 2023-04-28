#pragma once
#include"../source/object.h"
#include<vector>
#include"se.h"
namespace PuyoPlayerConfig {
	static const int colorTable[] = {
	0xff0000,
	0x00ff00,
	0x0000ff,
	0xffff00,
	};
}

class Puyo {
public:
	Puyo() 
		:pos({ 3,2 })
		,dir({ 0,-1 })
		,color(GetRand(3))
		,color2(GetRand(3))
	{}
	Vec2 pos;
	Vec2 dir;
	int color;
	int color2;
	void Draw();
};

class PuyoPlayer :public Object {
public:
	PuyoPlayer(Scene* sc);
	~PuyoPlayer();
	void Init()override;
	void Update()override;
	void Draw()override;

	bool Instance();//‰º‚É‰½‚à‚È‚¢‚È‚çtrue
	bool Move();//“®‚¯‚é‚È‚çtrue
	void FieldIn();
	Puyo GetPuyoPlayer();

private:
	void DebugMove();
	void KeyState();
	bool MoveCheck(int _x,int _y);//•Ç‚È‚çtrue
	void Rotate();
	bool RotateChack(int _keyDir);//‰ñ‚¹‚é‚È‚çtrue
	Vec2 DirtoVec2(int _keyDir);
	enum KeyDirs {
		up
		,right
		,down
		,left
	};
	Puyo* puyo;
	PuyoSe* se;
	int keyDir;
	bool keyMoveStop;
	bool keyRotateStop;
	bool fallOn;
	int fallSpeed;
};
