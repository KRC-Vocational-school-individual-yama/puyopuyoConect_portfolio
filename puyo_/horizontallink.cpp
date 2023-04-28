#include "horizontallink.h"
#include"../source/scene.h"
#include"puyo.h"

PuyoHorizontalLink::PuyoHorizontalLink(Scene* sc)
	:Object(sc)
	, field(nullptr)
	, isLink()
{}
PuyoHorizontalLink ::~PuyoHorizontalLink() {

}
void PuyoHorizontalLink::Init() {
	field = GetScene()->Invoke<PuyoField>();

	int maxIndex = PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth;
	isLink.resize(maxIndex, 0);




}
void PuyoHorizontalLink::Update() {
	for (int i = 0; i < isLink.size(); i++)
		isLink[i] = 0;
	if (field == nullptr) 
		field = GetScene()->Invoke<PuyoField>();
	if (field == nullptr)
		return;// field = GetScene()->Invoke<PuyoField>();
	for (int i = 0; i < PuyoHorizontalLinkConfig ::fieldHeight; i++) {
		for (int j = 0; j < PuyoHorizontalLinkConfig ::fieldWidth; j++) {
			int _x = j + 1;
			int _y = i + 1;
			int one = field->GetGridInside(_y, _x);
			int two = field->GetGridInside(_y, _x + 1);
			if (one == -1)continue;
			if (one == 0)continue;
			if (two == -1)continue;
			if (two == 0)continue;
			if (one != two)continue;
			isLink[IndexChange(i, j)] = one;
		}
	}


}
void PuyoHorizontalLink::Draw() {
	if (field == nullptr)return;// field = GetScene()->Invoke<PuyoField>();
	for (int i = 0; i < PuyoHorizontalLinkConfig ::fieldHeight; i++) {
		for (int j = 0; j < PuyoHorizontalLinkConfig ::fieldWidth; j++) {

			int index = IndexChange(i, j);
			if (isLink[index] == 0)continue;

			Vec2 pos = PuyoField::GetGridPos(i + 1, j + 1);
			int girdRadius = PuyoFieldConfig::gridSize / 2;
			pos.x += girdRadius;
			//pos.y += girdRadius;
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

int PuyoHorizontalLink::IndexChange(int i, int j) {
	int index = j + i * PuyoHorizontalLinkConfig ::fieldWidth;
	if (index < 0)index = 0;
	if (index >= PuyoHorizontalLinkConfig ::fieldHeight * PuyoHorizontalLinkConfig ::fieldWidth)
		index = PuyoHorizontalLinkConfig ::fieldHeight * PuyoHorizontalLinkConfig ::fieldWidth - 1;
	return index;
}
