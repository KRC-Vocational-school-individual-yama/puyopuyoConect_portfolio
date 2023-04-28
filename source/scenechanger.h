#pragma once
#include<string>

class Scene;

class SceneChanger {
public:
	Scene* StartScene();

	Scene* Changer(std::string name);
};