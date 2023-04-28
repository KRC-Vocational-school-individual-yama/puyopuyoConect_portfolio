#include "field.h"
#include"puyo.h"
#include"../source/scenemanager.h"
#include"../source/scene.h"
#include"chain.h"
#include"save.h"

PuyoField::PuyoField(Scene* sc)
	:Object(sc)
	,fields()

{}
PuyoField::~PuyoField(){
	
}
void PuyoField::Init(){
	fields.clear();
	
	//fields[IndexChange(1,1)] = 1;
	//fields[IndexChange(1,2)] = 2;
	//fields[IndexChange(1,3)] = 3;
	//fields[IndexChange(1,4)] = 4;
	

	fields=PuyoSave::Load("save/puyoField_SaveData.csv");
	if (!fields.empty())return;
	Reset();
	//fields = {
	//	-1,-1,-1,-1,-1,-1,-1,-1,
	//	-1,0,0,0,0,0,2,-1,
	//	-1,0,0,0,3,4,1,-1,
	//	-1,0,0,0,1,3,4,-1,
	//	-1,2,0,1,3,4,1,-1,
	//	-1,3,0,1,3,4,1,-1,
	//	-1,3,4,2,1,3,1,-1,
	//	-1,4,2,1,3,2,2,-1,
	//	-1,3,4,2,1,3,2,-1,
	//	-1,3,4,2,1,3,1,-1,
	//	-1,2,1,4,3,1,1,-1,
	//	-1,2,2,1,4,3,3,-1,
	//	-1,1,1,4,4,3,1,-1,
	//	-1,-1,-1,-1,-1,-1,-1,-1
	//};
}
void PuyoField::Update(){
	if (fields.empty())return;
#ifdef _DEBUG
	//int a = fields[IndexChange(2,5)];
#endif
}
void PuyoField::Draw(){
	if (fields.empty())return;
	for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
		for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {

			int index = IndexChange(i, j);
			int gridRadius = PuyoFieldConfig::gridSize / 2;
			bool thisIsFill = fields[index] == -1;
			Vec2 disppos = GetGridPos(i,j);
			//盤面の描画
			if (thisIsFill) {

			DrawBox(disppos.x - gridRadius + 1, disppos.y - gridRadius + 1,
				disppos.x + gridRadius - 1, disppos.y + gridRadius - 1, 0xeeeeee, thisIsFill);
			}

			//固定後ぷよの描画
			if (fields[index] == -1)continue;
			if (fields[index] == 0)continue;
			int cIndex = fields[index]-1;
			//if (cIndex < 0)cIndex = 0;
			int color =  PuyoPlayerConfig::colorTable[cIndex];
			//DrawCircle(disppos.x, disppos.y, PuyoFieldConfig::puyoSize , color, true);
			DrawOval(disppos.x, disppos.y, PuyoFieldConfig::puyoSize,PuyoFieldConfig::puyoSize, color, true);
		}
	}
}

bool PuyoField::FallDown() {
	bool end = false;
	int endcount = 0;
	int nowcount = 0;
		for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
			for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {
				if (fields[IndexChange(i, j)] == -1)continue;
				nowcount++;
				
				bool nowfield = fields[IndexChange(i, j)] != 0;
				bool downfiled = fields[IndexChange(i + 1, j)] == 0;
				if (!nowfield || !downfiled) {
					endcount++;
					continue;
				}
				int temp = fields[IndexChange(i, j)];
				fields[IndexChange(i + 1, j)] = temp;
				fields[IndexChange(i, j)] = 0;
			}
		}
		if (endcount == nowcount)return true;
		return false;
}

bool PuyoField::Erase(){
	const int maxIndex = PuyoFieldConfig::fieldWidth * PuyoFieldConfig::fieldHeight;
	int labelcount = 1;
	std::vector<int>delCheck;
	std::vector<int>delCheckSize;
	delCheck.resize(maxIndex);
	delCheckSize.resize(maxIndex);
	// 初期化
	for (int i = 0; i < maxIndex; i++) {
		delCheck[i] = 0;
		delCheckSize[i] = 0;
	}
	// ラベリング（連結した塊ごとに番号を割り振る）
	for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
		for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {
			if (fields[IndexChange(i, j)] == -1)continue;
			if (fields[IndexChange(i, j)] == 0)continue;

			int target = fields[IndexChange(i, j)];
			int targetLeft = fields[IndexChange(i - 1, j)];
			int targetUp = fields[IndexChange(i, j - 1)];

			if (target == targetLeft) {
				int label = delCheck[IndexChange(i - 1, j)];
				delCheck[IndexChange(i, j)] = label;
				if (target == targetUp) {
					int oldLabel = delCheck[IndexChange(i, j - 1)];
					for (int k = 0; k < delCheck.size(); k++) {
						//古いラベルの数字を新しいのに全て入れ替え
						if (delCheck[k] == oldLabel) delCheck[k] = label;
					}
				}
			}
			else if (target == targetUp) {
				delCheck[IndexChange(i, j)] = delCheck[IndexChange(i, j - 1)];
			}
			else {
				++labelcount;
				delCheck[IndexChange(i, j)] = labelcount;
			}

		}
	}
	// 連結サイズチェック
	for (int i = 0; i < delCheck.size(); i++) {
		delCheckSize[delCheck[i]]++;
	}
	bool erase = false;
	for (int i = 1; i <= labelcount; i++) {
		// 4連結以上で消去
		if (delCheckSize[i] < 4) continue;
			GetScene()->Invoke<PuyoChain>()->Increment();
			for (int k = 0; k < maxIndex; k++) {
				if (delCheck[k] == i) {
					fields[k] = 0;
					erase = true;
				}
			}

	}
	return erase;
}
void PuyoField::Save(){
	PuyoSave::Save("save/puyoField_SaveData.csv",fields);
}
void PuyoField::Reset(){

	int maxIndex = PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth;
	std::vector<int>initialize(maxIndex, 0);
	for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
		for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {
			int index = IndexChange(i, j);
			initialize[index] = 0;

			bool widthzero = j == 0;
			bool heightzero = i == 0;
			bool widthmax = j == PuyoFieldConfig::fieldWidth - 1;
			bool heightmax = i == PuyoFieldConfig::fieldHeight - 1;
			if (widthzero || heightzero || widthmax || heightmax)
				initialize[index] = -1;
		}
	}
	fields=initialize;
}

int PuyoField::IndexChange(int i,int j){
	int index= j + i * PuyoFieldConfig::fieldWidth;
	if (index < 0)index = 0;
	if (index >= PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth)
		index = PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth-1;
	return index;
}

//int PuyoField::IndexChange(Vec2 _puyoPos){
//	int index = _puyoPos.x + _puyoPos.y * PuyoFieldConfig::fieldWidth;
//	if (index < 0)index = 0;
//	if (index >= PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth)
//		index = PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth - 1;
//	return index;
//}

bool PuyoField::WallJudge(int i, int j){
	if(fields[IndexChange(i,j)]!=0)
		return true;

	return false;
}

Vec2 PuyoField::GetGridPos(int i, int j){
	int index = IndexChange(i, j);
	int x = PuyoFieldConfig::gridSize * j;
	int y = PuyoFieldConfig::gridSize * i;
	int gridRadius = PuyoFieldConfig::gridSize / 2;

	Vec2 disppos = { 100 + x,100 + y };
	disppos.x -= gridRadius;
	disppos.y -= gridRadius;

	return disppos;
}

int PuyoField::GetGridInside(int _y, int _x){
	if (fields.empty())return -1;

	int index = IndexChange(_y, _x);
	return fields[index];
}

void PuyoField::SetField(Vec2 pos, int colorNumber){
	fields[IndexChange(pos.y,pos.x)]=colorNumber+1;
}

