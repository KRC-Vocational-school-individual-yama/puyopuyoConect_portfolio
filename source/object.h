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
	objectクラスに必要なことは
	・名前、
	・所属シーン、
	・アクティブ
	・上記それぞれの get set 関数
	・基礎のコンストラクタ、デストラクタ（コ そのまま デ virtual）
	・基礎のStart,Updae,Draw 関数（virtual =0）
*/