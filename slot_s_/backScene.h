#pragma once
#include"../source/object.h"

class SlotBackScene :public Object {
public:
	SlotBackScene(Scene* sc);
	~SlotBackScene();
	void Init();
	void Update();
	void Draw();

private:
	
};