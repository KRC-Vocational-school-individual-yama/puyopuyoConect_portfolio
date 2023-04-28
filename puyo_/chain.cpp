#include "chain.h"
#include<string>
#include"../source/colorhsv.h"
#include"../source/scenemanager.h"
PuyoChain::PuyoChain(Scene* sc)
	:Object(sc)
	,nowChain(0)
	,maxChain(0)
	,color(0xffffff)
	,maxColor(0xffffff)
{}
PuyoChain::~PuyoChain(){
}
void PuyoChain::Init(){
}
void PuyoChain::Update() {
	color = NowColors(nowChain);
	maxColor = NowColors(maxChain);

}
void PuyoChain::Draw(){
	std::string str = "";
	str = std::to_string(nowChain)+ "òAçΩ";
	DrawFormatString(400,400,color,str.c_str());
	str.erase();
	str = "ç≈ëÂ"+std::to_string(maxChain)+ "òAçΩ";
	DrawFormatString(400,450,maxColor,str.c_str());
}

void PuyoChain::Increment(){
	nowChain++;
	if (maxChain < nowChain)maxChain = nowChain;
}

void PuyoChain::Refresh(){
	nowChain = 0;
}

int PuyoChain::NowColors(int conbo){
	if (conbo < 2)
		return 0xffffff;
	if (conbo > 10)
		return color::GetHSV(SceneManager::GetFrame() % 360, 255, 255);;
	int num = (conbo - 1) * 15;
	return color::GetHSV(num%360,255,255);
}
