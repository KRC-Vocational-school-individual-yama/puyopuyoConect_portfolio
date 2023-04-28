#include "uiinterface.h"
#include"../source/scene.h"

void FontDisp::Draw(){
	DrawFormatString(pos.x,pos.y,color,str.c_str());
}

Strings::Strings()
	:font()
	,button()
	,resizenumber(static_cast<int>(Strings::ButtonNumbers::KeyIsMax))
	, fontsize(64)
	, spaceDispCount(0)
{}
Strings::~Strings(){

}
void Strings::Init(){
	font.resize(resizenumber);
	button.resize(resizenumber);
	for (int i = 0; i < font.size(); i++) {
		if (i > static_cast<int>(Strings::ButtonNumbers::KeyIsSpace))
			break;
		font[i].pos = {0,0};
		font[i].color = 0xffffff;
		font[i].str = "";
		font[i].active = true;
		button[i] = false;
	}
	font[static_cast<int>(Strings::ButtonNumbers::KeyIsA)].str = "A";
	font[static_cast<int>(Strings::ButtonNumbers::KeyIsS)].str = "S";
	font[static_cast<int>(Strings::ButtonNumbers::KeyIsD)].str = "D";
	int indexSpace = static_cast<int>(Strings::ButtonNumbers::KeyIsSpace);
	font[indexSpace].pos = { 0,0 };
	font[indexSpace].color = 0xaaaaaa;
	font[indexSpace].str = "Space";
	font[indexSpace].active = false;
}
void Strings::Update(){


	ButtonInputASD();
	ButtonInputSpace();
	

	JudgeSpaceDisp();
}
void Strings::Draw(){
#ifdef _DEBUG
	printfDx("%d",GetFontSize());
#endif
	int oldFontSize = DxLib::GetFontSize();
	SetFontSize(fontsize);
	for (auto beeline :font) {
		if (!beeline.active)continue;
		beeline.Draw();
	}
	SetFontSize(oldFontSize);
}
void Strings::SetPos(Vec2 pos,int num){
		font[num].pos = pos;
}
void Strings::ButtonInputASD(){
bool keyA = CheckHitKey(KEY_INPUT_A);
int index = static_cast<int>(Strings::ButtonNumbers::KeyIsA);
	if (keyA&&!button[index]) {
		font[index].active = false;
	}
	button[index] = keyA;

	bool keyS = CheckHitKey(KEY_INPUT_S);
	index = static_cast<int>(Strings::ButtonNumbers::KeyIsS);
	if (keyS&&!button[index]) {
		font[index].active = false;
	}
	button[index] = keyS;

	bool keyD = CheckHitKey(KEY_INPUT_D);
	index = static_cast<int>(Strings::ButtonNumbers::KeyIsD);
	if (keyD&&!button[index]) {
		font[index].active = false;
	}
	button[index] = keyD;
}
void Strings::ButtonInputSpace(){
if (CheckHitKey(KEY_INPUT_SPACE)) {
		for (int i = 0; i < font.size(); i++) {
			if (i == static_cast<int>(Strings::ButtonNumbers::KeyIsSpace))
				break;
			if (font[i].active)continue;
			font[i].active = true;
			button[i]=true;
		}
	}
}
void Strings::JudgeSpaceDisp(){
	int indexA = static_cast<int>(Strings::ButtonNumbers::KeyIsA);
	int indexS = static_cast<int>(Strings::ButtonNumbers::KeyIsS);
	int indexD = static_cast<int>(Strings::ButtonNumbers::KeyIsD);
	int indexSpace = static_cast<int>(Strings::ButtonNumbers::KeyIsSpace);
	bool flag = !font[indexA].active&&!font[indexS].active;
	bool flag2 = !font[indexA].active && !font[indexD].active;
	bool fsuccess = flag && flag2;
	
	font[indexSpace].active=false;
	if(!fsuccess)spaceDispCount = 0;

	if (!fsuccess)return;
	spaceDispCount++;

	if (spaceDispCount < static_cast<int>(60 * 1.7f))return;
	font[indexSpace].active = true;
}

UiInterface::UiInterface(Scene* sc)
	:Object(sc)
	,keyDownFont()
	,slot()
{}
UiInterface::~UiInterface(){
	
}
void UiInterface::Init(){
	keyDownFont.Init();
	slot = dynamic_cast<Slot*>(GetScene()->Invoke<Slot>());
	Vec2 pos = {0,0};
	for (int i = 0; i < keyDownFont.GetSize(); i++) {
		pos = slot->Slot::GetPos(i);
		pos.x -= keyDownFont.GetmyFontSize()/3.f;
		pos.y = 100.f;
	keyDownFont.SetPos(pos,i);
	}

	int index = keyDownFont.GetSize()-1;
	pos = slot->Slot::GetPos(0);
	pos.x -= keyDownFont.GetmyFontSize()/3.f;
	pos.y = 400.f;
	keyDownFont.SetPos(pos, index);

}
void UiInterface::Update(){
	keyDownFont.Update();

}
void UiInterface::Draw(){
	keyDownFont.Draw();

	std::string kaisetu = "ASDキー　　　で　それぞれ止める\n";
	kaisetu += "Spaceキー　　で　リセット\n";
	kaisetu += "\n";
	kaisetu += "Tキー　　　　で　タイトルへ\n";

	DrawFormatString(50, 100, 0xffffff, kaisetu.c_str());
}

