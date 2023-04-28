#include "se.h"

PuyoSe::PuyoSe(Scene* sc)
	:Object(sc)
	,se()
	,keystop(false)
	,sound(-1)
{}
PuyoSe::~PuyoSe(){
	for (auto it = se.begin(); it < se.end(); it++) {
		int obj = (*it);
		if (obj == -1)continue;
		DeleteSoundMem(obj);
	}
}
void PuyoSe::Init(){
	SeLoad("sound/早送り・時間経過_1.mp3");
	SeLoad("sound/早送り・時間経過_2.mp3");
	for (int i = 0; i < se.size();i++) {
		int vol = ParsentVolume(75);
		ChangeVolumeSoundMem(vol,se[i]);
	}

	sound = LoadSoundMem("sound/早送り・時間経過_1.mp3");
}
void PuyoSe::Update(){
	Debug();
}
void PuyoSe::Draw(){

}

void PuyoSe::LeftTrunSe(){
	PlaySoundMem(se[0],DX_PLAYTYPE_BACK);
}
void PuyoSe::RightTrunSe(){
	PlaySoundMem(se[1], DX_PLAYTYPE_BACK);
}
int PuyoSe::SeLoad(char* _pass){
	int loadSe=LoadSoundMem(_pass);
	se.emplace_back(loadSe);

	return loadSe;
}

int PuyoSe::ParsentVolume(int _num){
	float parsent = static_cast<float>(_num) / 100;
	int volume = static_cast<int>(255 * parsent);
	return volume;
}

void PuyoSe::Debug() {
	bool hitKey = CheckHitKey(KEY_INPUT_J);
	bool hitKey2 = CheckHitKey(KEY_INPUT_K);
	if (hitKey && !keystop) {
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
	}
	if (hitKey2 && !keystop) {
		PlaySoundMem(se[1], DX_PLAYTYPE_BACK);
	}
	keystop = hitKey || hitKey2;
}
