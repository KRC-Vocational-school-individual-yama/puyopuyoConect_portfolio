#include "verticallink.h"
#include"../source/scene.h"
#include"puyo.h"

PuyoVerticalLink::PuyoVerticalLink(Scene* sc)
	:Object(sc)
	, field(nullptr)
	, isLink()
{}
PuyoVerticalLink::~PuyoVerticalLink(){
}
void PuyoVerticalLink::Init(){
	field = GetScene()->Invoke<PuyoField>();

	int maxIndex = PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth;
	isLink.resize(maxIndex, 0);
}
void PuyoVerticalLink::Update(){
	for (int i = 0; i < isLink.size(); i++)isLink[i] = 0;
	if (field == nullptr)field = GetScene()->Invoke<PuyoField>();
	if (field == nullptr)return;// field = GetScene()->Invoke<PuyoField>();
	for (int i = 0; i < PuyoVerticalLinkConfig::fieldHeight; i++) {
		for (int j = 0; j < PuyoVerticalLinkConfig::fieldWidth; j++) {
			int _x = j + 1;
			int _y = i + 1;
			int one = field->GetGridInside(_y, _x);
			int two = field->GetGridInside(_y+ 1, _x );
			if (one == -1)continue;
			if (one == 0)continue;
			if (two == -1)continue;
			if (two == 0)continue;
			if (one != two)continue;
			isLink[IndexChange(i, j)] = one;
		}
	}
}
void PuyoVerticalLink::Draw(){
	if (field == nullptr)return;// field = GetScene()->Invoke<PuyoField>();
	for (int i = 0; i < PuyoVerticalLinkConfig::fieldHeight; i++) {
		for (int j = 0; j < PuyoVerticalLinkConfig::fieldWidth; j++) {

			int index = IndexChange(i, j);
			if (isLink[index] == 0)continue;

			Vec2 pos = PuyoField::GetGridPos(i+1 , j+1 );
			int girdRadius = PuyoFieldConfig::gridSize / 2;
			//pos.x += girdRadius;
			pos.y += girdRadius;
			int sizeRadius = 10 / 2;
			Vec2 leftUp, rightDown;
			leftUp.x = pos.x - sizeRadius;
			leftUp.y = pos.y - sizeRadius;
			rightDown.x = pos.x + sizeRadius;
			rightDown.y = pos.y + sizeRadius;
			int colorIndex = isLink[index] - 1;
			int color = PuyoPlayerConfig::colorTable[colorIndex];
			DrawBox(leftUp.x, leftUp.y, rightDown.x, rightDown.y, color, true);
		}
	}
}

int PuyoVerticalLink::IndexChange(int i, int j){
	int index = j + i * PuyoVerticalLinkConfig::fieldWidth;
	if (index < 0)index = 0;
	if (index >= PuyoVerticalLinkConfig::fieldHeight * PuyoVerticalLinkConfig::fieldWidth)
		index = PuyoVerticalLinkConfig::fieldHeight * PuyoVerticalLinkConfig::fieldWidth - 1;
	return index;

	return 0;
}
