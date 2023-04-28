#include "backScene.h"
#include"../source/scenemanager.h"
SlotBackScene::SlotBackScene(Scene* sc)
	:Object(sc)
{}
SlotBackScene::~SlotBackScene(){

}
void SlotBackScene::Init(){

}
void SlotBackScene::Update(){
	bool backKey = CheckHitKey(KEY_INPUT_T);
	if (!backKey) return;
	SceneManager::ChangeScene("Title");
}
void SlotBackScene::Draw(){

}
