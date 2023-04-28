#pragma once
#include"../source/object.h"
#include<vector>

class PuyoSe :public Object{
public:
	PuyoSe(Scene* sc);
	~PuyoSe();
	void Init()override;
	void Update()override;
	void Draw()override;

	void LeftTrunSe();
	void RightTrunSe();

private:
	int SeLoad(char* _pass);
	int ParsentVolume(int _num);//1Å`255 Å® 1Å`100

	void Debug();

	std::vector<int>se;
	int sound;
	bool keystop;
};