#pragma once
#include"../source/object.h"
#include"puyo.h"
#include"field.h"
class PuyoNavigation :public Object{
public:
	PuyoNavigation(Scene* sc);
	~PuyoNavigation();
	void Init()override;
	void Update()override;
	void Draw()override;

	void NaviOn() { isActive = true; }
	void NaviOff() { isActive = false; }

private:
	void NavisDown(int i,int j,Vec2& _pos);
	void Coherent();//í“ÂÎçáÇÌÇπ

	PuyoField* field;
	Puyo navi;
	Vec2 secondPos;
	bool isActive;
};