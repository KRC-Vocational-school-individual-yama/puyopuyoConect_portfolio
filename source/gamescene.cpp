#include "gamescene.h"

#include"scenemanager.h"
#include<DxLib.h>

GameScene::GameScene(){
}
GameScene::~GameScene(){

}

void GameScene::Update(){
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		SceneManager::ChangeScene("Title");
	}
}

void GameScene::Draw(){
	printfDx("�����Ȃ��̂�\n�G���^�[�L�[��\n�߂��Ă����");
}

