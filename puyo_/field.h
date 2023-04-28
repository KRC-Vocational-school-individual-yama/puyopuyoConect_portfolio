#pragma once
#include"../source/object.h"
#include<vector>

namespace PuyoFieldConfig{
	static const int puyoSize = 12;
	static const int gridSize = 32;
	static const int fieldHeight = 12 + 2;
	static const int fieldWidth = 6 + 2;
}

class PuyoField :public Object{
public:
	PuyoField(Scene* sc);
	~PuyoField();
	void Init()override;
	void Update()override;
	void Draw()override;

	bool FallDown();
	bool Erase();
	void Save();

	static int IndexChange(int _y,int _x);//1.2.3...
	//static int IndexChange(Vec2 _puyoPos);//1.2.3...
	static Vec2 GetGridPos(int _y,int _x);//1.2.3...
	int GetGridInside(int _y,int _x);
	void SetField(Vec2 pos,int colorNumber);
	bool WallJudge(int _y,int _x);//•Ç‚È‚çtrue


private:
	void Reset();

	std::vector<int>fields;

};

