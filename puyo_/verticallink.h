#pragma once
#include"../source/object.h"
#include<vector>
#include"field.h"
namespace PuyoVerticalLinkConfig {
	static const int fieldHeight = PuyoFieldConfig::fieldHeight - 3;
	static const int fieldWidth = PuyoFieldConfig::fieldWidth - 2;
}


class PuyoVerticalLink :public Object{
public:
	PuyoVerticalLink(Scene* sc);
	~PuyoVerticalLink();
	void Init()override;
	void Update()override;
	void Draw()override;

private:
	int IndexChange(int _y, int _x);

	PuyoField* field;
	std::vector<int>isLink;
};