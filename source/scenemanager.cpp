#include "scenemanager.h"
#include"scene.h"
#include"scenechanger.h"

namespace {
	std::string nowSceneName;//現在のシーン
	std::string nextSceneName;//次のシーン
	Scene* scene;//使うやつ
	SceneChanger* changer;
	int frameCounter;//カウンター
}

void SceneManager::Init(){
	nowSceneName	="";
	nextSceneName	="";
	frameCounter = 0;
	changer = new SceneChanger();

	scene = changer->StartScene();
}
void SceneManager::Update() {
	frameCounter++;
	//シーンの入れ替え処理
	if (nowSceneName != nextSceneName) {
		if (scene != nullptr)
			delete scene;
		scene = nullptr;
		nowSceneName = nextSceneName;
		scene = changer->Changer(nextSceneName);
	}

	//シーン更新
	if (scene != nullptr)
		scene->Update();
}
void SceneManager::Draw() {
	if (scene != nullptr)
		scene->Draw();//描画
}
void SceneManager::Delete(){
	if (scene != nullptr) {//中身があるなら削除
		delete scene;
		scene = nullptr;
	}
}
void SceneManager::ChangeScene(std::string sceneName){
	nextSceneName = sceneName;
}
int SceneManager::GetFrame(){
	return frameCounter;
}

