#include "navigation.h"
#include"../source/scene.h"

PuyoNavigation::PuyoNavigation(Scene* sc)
	:Object(sc)
	,field(nullptr)
	,navi()
	,secondPos()
	,isActive(true)
{}
PuyoNavigation::~PuyoNavigation(){

}
void PuyoNavigation::Init(){
	navi = GetScene()->Invoke<PuyoPlayer>()->GetPuyoPlayer();
	field = GetScene()->Invoke<PuyoField>();
	secondPos = {navi.pos.x+navi.dir.x,navi.pos.y+navi.dir.y};
}
void PuyoNavigation::Update() {
	if (!isActive)return;
	navi = GetScene()->Invoke<PuyoPlayer>()->GetPuyoPlayer();
	secondPos = { navi.pos.x + navi.dir.x,navi.pos.y + navi.dir.y };

	for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
		for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {
			
			NavisDown(i,j,navi.pos);
			NavisDown(i,j,secondPos);
		}
	}

	Coherent();
}
void PuyoNavigation::Draw(){
	if (!isActive)return;
	Vec2 disppos = PuyoField::GetGridPos(navi.pos.y, navi.pos.x);
	Vec2 disppos2 = PuyoField::GetGridPos(secondPos.y, secondPos.x);
	//‚Õ‚æ‚Ì•`‰æ
	int cIndex = navi.color;
	int cIndex2 = navi.color2;
	int color = PuyoPlayerConfig::colorTable[cIndex];
	int color2 = PuyoPlayerConfig::colorTable[cIndex2];
	DrawCircle(disppos.x, disppos.y, PuyoFieldConfig::puyoSize / 2, color, true);
	DrawCircle(disppos2.x, disppos2.y, PuyoFieldConfig::puyoSize / 2, color2, true);

}

void PuyoNavigation::NavisDown(int i, int j, Vec2& _pos){
	if(field==nullptr)field = GetScene()->Invoke<PuyoField>();
	int nowGrid = field->GetGridInside(_pos.y, _pos.x);
	int downGrid = field->GetGridInside(_pos.y + 1, _pos.x);
	if (downGrid != 0)return;

	_pos.y++;
}

void PuyoNavigation::Coherent(){
if (navi.pos.x != secondPos.x)return;
	secondPos.y += navi.dir.y;
	if (navi.dir.y != 1)return;
	secondPos.y += -1;
	navi.pos.y  += -1;
}

