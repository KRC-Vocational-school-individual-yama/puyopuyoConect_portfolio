#pragma once
#include"scene.h"

//最初の切り替えの為だけのシーン
class FarstOneScene :public Scene {
public:
	FarstOneScene();
	~FarstOneScene() override;
	void Init()		;
	void Update()	override;
	void Draw()		override;

	//つまり何もしないシーン
};