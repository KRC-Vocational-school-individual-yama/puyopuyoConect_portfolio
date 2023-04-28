#include "connectmode.h"
#include"connect.h"
#include"../source/scene.h"

PuyoConnectMode::PuyoConnectMode(Scene* sc)
	:Object(sc)
	,send(nullptr)
	,rect(nullptr)
	,mode(Mode::parentOrChild)
	,nowConnect(false)
	,off(false)
{}
PuyoConnectMode::~PuyoConnectMode(){

}
void PuyoConnectMode::Init(){
}
void PuyoConnectMode::Update(){
	

	switch (mode){
	case PuyoConnectMode::Mode::parentOrChild:

		if (CheckHitKey(KEY_INPUT_N) && !nowConnect) {
	send = GetScene()->Invoke<PuyoConnectSend>();
			mode = Mode::send;
		}
		if(CheckHitKey(KEY_INPUT_M) && !nowConnect){
	rect = GetScene()->Invoke<PuyoConnectRect>();
			mode = Mode::rect;
		}

		if (CheckHitKey(KEY_INPUT_B)) {
			mode = Mode::connectEnd;
		}

		break;
	case PuyoConnectMode::Mode::send:
		nowConnect= send->Connect();
		break;
	case PuyoConnectMode::Mode::rect:
		nowConnect = rect->Connect();
		break;
	case PuyoConnectMode::Mode::connectEnd:
		if (nullptr != send)
			send->DisConnect();
		if (nullptr != rect)
			rect->DisConnect();
		nowConnect = false;
		off = true;
		break;
	default:
		break;
	}

	if (nowConnect) {
		if (nullptr != send)
			send->On();
		if (nullptr != rect)
			rect->On();
		off = nowConnect;
	}
}
void PuyoConnectMode::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 240);
	DrawBox(0, 0, 800, 600, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (mode == Mode::parentOrChild) {

		int oldFontSize = GetFontSize();
		SetFontSize(64);
		DrawFormatString(100, 200, 0xffffff, "通信画面");
		SetFontSize(oldFontSize);

		std::vector<std::string>str;
		if ( !nowConnect) {
		str.emplace_back("Nキー　で　参加する人");
		str.emplace_back("Mキー　で　部屋を開く人");
		}
		str.emplace_back("Bキー　で　中断");
		for (int i = 0; i < str.size(); i++) {
			int space = i * GetFontSize() * 2;
			DrawFormatString(100, 350 + space, 0xffffff, str[i].c_str());
		}
	}
	else {
		int oldFontSize = GetFontSize();
		SetFontSize(64);
		DrawFormatString(100, 200, 0xffffff, "通信中");
		SetFontSize(oldFontSize);
	}

}
