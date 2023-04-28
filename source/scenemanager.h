#pragma once
#include<string>

class Scene;
class SceneChanger;

namespace SceneManager {
	void Init();
	void Update();
	void Draw();
	void Delete();

	void ChangeScene(std::string sceneName);
	int GetFrame();
}