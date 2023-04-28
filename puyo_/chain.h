#pragma once
#include"../source/object.h"

class PuyoChain :public Object{
public:
	PuyoChain(Scene * sc);
	~PuyoChain();
	void Init()override;
	void Update()override;
	void Draw()override;

	void Increment();
	void Refresh();

	int GetChain() { return nowChain; }

private:
	int NowColors(int conbo);
	int nowChain;
	int maxChain;
	int color;
	int maxColor;
};