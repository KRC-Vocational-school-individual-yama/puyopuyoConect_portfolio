#pragma once
#include"../source/object.h"
#include<vector>
#include"field.h"
namespace PuyoHorizontalLinkConfig {
	static const int fieldHeight = PuyoFieldConfig::fieldHeight-2;
	static const int fieldWidth = PuyoFieldConfig::fieldWidth - 3;
}

class PuyoHorizontalLink :public Object {
public:
	PuyoHorizontalLink(Scene* sc);
	~PuyoHorizontalLink();
	void Init()override;
	void Update()override;
	void Draw()override;


private:
	int IndexChange(int _y,int _x);

	PuyoField* field;
	std::vector<int>isLink;
};