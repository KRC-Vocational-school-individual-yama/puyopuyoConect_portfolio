#pragma once
#include"scene.h"

//�ŏ��̐؂�ւ��ׂ̈����̃V�[��
class FarstOneScene :public Scene {
public:
	FarstOneScene();
	~FarstOneScene() override;
	void Init()		;
	void Update()	override;
	void Draw()		override;

	//�܂艽�����Ȃ��V�[��
};