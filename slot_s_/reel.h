#pragma once
#include"../source/object.h"
#include<vector>

struct ReelShape  {
	enum class Shape {
		circle,
		triangle,
		square,
		pentagon,
		hexagon,
		heptagon,
		octagon,
		nonagon,
		max,
	};
	float x, y,r;
	int color;
	bool fill;
	Shape shape;
	void Draw();
};
struct Vec2;
class Reel  {
public:
	Reel();
	~Reel();
	void Init();
	void Update();
	void Draw();
	void DebugDraw();//（後で消す
	int GetStopimg() {return graphnum;}
	void SetStopKey(int key) { keynumber = key; }
	void SetPos(float pos);
	Vec2 GetReelPos();
private:
	void VectorsResize();//std::vectorのサイズ確保
	void ShapesMenberSet();//変数代入
	void ButtonStop();//リール回転を止める
	void ButtonReStert();//リール回転を再開
	void ReelNowStop();//止まっている
	void ReelStopMove();//ボタンが押された
	void ReelNowMove();//リールを動かす
	void ReelAllMoves();//リール動き処理を統括
	void DispInValue();//見えるように代入

	std::vector<std::vector<ReelShape>>shapes;
	const int speed=13;
	const int ReelsMaxNum=3;
	const int GraphSize = 75;
	const int ReelSize = static_cast<int>(ReelShape::Shape::max) * GraphSize;
	bool keystop;
	bool button;
	bool reelstop;
	float y;
	int yvec;
	int graphnum;
	int keynumber;

	int framecountdebug;
};
class Slot :public Object {
public:
	Slot(Scene* sc);
	~Slot()override;
	void Init()override;
	void Update()override;
	void Draw()override;
	bool GetSuccess() { return success; }
	Vec2 GetPos(int slotnumber);
private:
	void ReStartReel();
	void DebugDraw();
	std::vector<Reel*>reels;
	std::vector<int> num;
	const int ReelsNum = 3;
	bool success;
	
};