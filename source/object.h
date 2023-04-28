#pragma once
#include<string>
#include<DxLib.h>
#include"common.h"
#include"scenemanager.h"
#include"colorhsv.h"

class Scene;

class Object {
public:
			Object(Scene* sc):scene(sc),name("") {}
	virtual ~Object()		=default;
	virtual void Init()		=0;
	virtual void Update()	=0;
	virtual void Draw()		=0;

	void SetName(std::string _name) { name = _name; }

	Scene* GetScene() { return scene; }
	std::string GetName() { return name; }
	
private:
	Scene* scene;
	std::string name;

};
/*
	object�N���X�ɕK�v�Ȃ��Ƃ�
	�E���O�A
	�E�����V�[���A
	�E�A�N�e�B�u
	�E��L���ꂼ��� get set �֐�
	�E��b�̃R���X�g���N�^�A�f�X�g���N�^�i�R ���̂܂� �f virtual�j
	�E��b��Start,Updae,Draw �֐��ivirtual =0�j
*/