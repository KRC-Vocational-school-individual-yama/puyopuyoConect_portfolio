#include "scenemanager.h"
#include"scene.h"
#include"scenechanger.h"

namespace {
	std::string nowSceneName;//���݂̃V�[��
	std::string nextSceneName;//���̃V�[��
	Scene* scene;//�g�����
	SceneChanger* changer;
	int frameCounter;//�J�E���^�[
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
	//�V�[���̓���ւ�����
	if (nowSceneName != nextSceneName) {
		if (scene != nullptr)
			delete scene;
		scene = nullptr;
		nowSceneName = nextSceneName;
		scene = changer->Changer(nextSceneName);
	}

	//�V�[���X�V
	if (scene != nullptr)
		scene->Update();
}
void SceneManager::Draw() {
	if (scene != nullptr)
		scene->Draw();//�`��
}
void SceneManager::Delete(){
	if (scene != nullptr) {//���g������Ȃ�폜
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

