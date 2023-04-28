#include "scene.h"
#include"object.h"
Scene::Scene(){
	objects.clear();
	objectsDraw.clear();
	rankChange = false;
}
Scene::~Scene(){
	AllDestroy();
}
void Scene::Update(){
	//初期化
	UpdateInInitialization();
	//破棄
	UpdadeInDestory();
	
	//更新
	for (auto it = objects.begin(); it != objects.end();it++) {
		/*ObjectParam& node = *it;
		node.object->Update();*/
		(*it).object->Update();
	}

	//描画順番変更
	if (!rankChange)return;
	DispChanger();
	rankChange = false;
}
void Scene::Draw(){
	//描画
	for (auto node : objectsDraw) {
		node.object->Draw();
	}
}

Object* Scene::Create(Object* obj, std::string name){
	ObjectParam node;
	node.object = obj;
	node.wantInit = true;
	node.object->SetName(name);
	objects.emplace_back(node);//リストに追加
	rankChange = true;//入れ替え要請

	return obj;
}
Object* Scene::Invoke(std::string name){
	for (auto& node : objects) {
		if (name != node.object->GetName())continue;
		return node.object;
	}
	return nullptr;
}
void Scene::Destroy(std::string name){
	for (auto it = objects.begin(); it != objects.end(); it++) {
		ObjectParam& node = *it;
		if (name != node.object->GetName())continue;
		//DestoryDrawObject(node.object);
		delete node.object;
		node.object = nullptr;
		objects.erase(it);
		DispChanger();
		return;
	}
	
}
void Scene::Destroy(Object* obj) {
	for (auto it = objects.begin(); it != objects.end();it++ ) {
		ObjectParam& node = *it;
		if (obj != node.object)continue;
		 delete node.object;
		 node.object = nullptr;
		// DestoryDrawObject(obj);
		 objects.erase(it);
		 DispChanger();
		 return;
	}
}
void Scene::ChangeDispRank(Object* obj, int rank) {
	for (auto& node : objects) {
		if (obj != node.object)continue;
		node.dispRank = rank;
		rankChange = true;
		return;
	}
}

void Scene::DestoryDrawObject(Object* obj){
	for (auto it = objectsDraw.begin(); it != objectsDraw.end(); it++) {
		ObjectParam& node = *it;
		if (obj != node.object)continue;
		delete node.object;
		node.object = nullptr;
		objectsDraw.erase(it);
		return;
	}
}
bool Scene::DispSort(const ObjectParam & rank1,const ObjectParam & rank2){
		return rank1.dispRank < rank2.dispRank;
}
void Scene::DispChanger(){
	objectsDraw.clear();
	objectsDraw = objects;
	objectsDraw.sort(DispSort);//上昇順（昇順 1 2 3 ...
}
void Scene::AllDestroy(){
	for (auto& node : objects) {
		delete node.object;
	}
	/*objects.clear();
	objectsDraw.clear();*/
}
void Scene::UpdateInInitialization() {
	for (auto it = objects.begin(); it != objects.end(); it++) {
		ObjectParam& node = *it;

		if (!node.wantInit)continue;
		node.object->Init();
		node.wantInit = false;
		//(*it).object->Init();
	}
}
void Scene::UpdadeInDestory() {
	for (auto it = objects.begin(); it != objects.end(); it++) {
		ObjectParam& node = *it;

		if (!node.wantMyExplosion)continue;
		delete node.object;
		node.object = nullptr;
	}
}



