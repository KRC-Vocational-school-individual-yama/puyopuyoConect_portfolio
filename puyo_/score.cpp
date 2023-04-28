#include "score.h"
#include"../source/scene.h"
#include"chain.h"
#include"puyogame.h"

PuyoScore::PuyoScore(Scene* sc)
	:Object(sc)
	,score(0)
	,dispScore(0)
	,upScore(8)
	,dispUp(false)
{}
PuyoScore::~PuyoScore(){

}
void PuyoScore::Init(){

}
void PuyoScore::Update(){
	dispScore = score / 60;

}
void PuyoScore::Draw(){
	DrawScore({500,500});

	if (!dispUp)return;
	PuyoGame* game = GetScene()->Invoke<PuyoGame>();
	if (game == nullptr)return;
	if (game->GetMode() != PuyoGame::Mode::erase)return;
	DrawFormatString(450,500,0xffffff,"%d +",upScore);
}

void PuyoScore::DefaultUp(){
	score++;
}
void PuyoScore::EraseCalc(){
PuyoChain* chainClass=GetScene()->Invoke<PuyoChain>();
	if (chainClass == nullptr)return;
	int chain=chainClass->GetChain();

	if (chain < 0)return;

	dispUp = true;
	for (int i = 0; i < chain; i++) {
		
		i==0
			? upScore =8
			: upScore *= 2;
	}
}
void PuyoScore::EraseUp(){
	

	score += upScore *60;
	upScore =0;
	dispUp = false;
}

void PuyoScore::DrawScore(Vec2 pos){

	std::string str = "";
	str += RightString(dispScore,10000,false);
	str += "　スコア";
	DrawFormatString(pos.x,pos.y, 0xffffff, str.c_str());
}


std::string PuyoScore::RightString(int _num, int _keta, bool _zeroDisp) {
	std::string str = "";
	int scoreChange = 0;
	int scoreChangeold = 0;
	int count = 0;
	//右詰めの作業
	for (int i = _keta; i > 0; i /= 10) {
		int num = static_cast<int>((_num - scoreChangeold) / i);
		if (i > _num && !_zeroDisp) {
			if (num == 0) {
				str += " ";
			}
			else {
				str += std::to_string(num);
			}
		}
		else
		{
			str += std::to_string(num);
		}
		scoreChange = num * i;
		scoreChangeold += scoreChange;
		count++;
	}

	if (_num == 0) {
		str = "";
		for (int i = 0; i < count-1; i++) str += " ";
		str += "0";

		return str;
	}

	return str;
}
