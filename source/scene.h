#pragma once
#include<string>
#include<list>

class Object;
//ベース 基盤 大元
class Scene {
public:
	Scene();
	virtual ~Scene();
	virtual void Update();
	virtual void Draw();

	template <class Class>
	Class* Create() {
		Class* obj = new Class(this);//ここで生成
		ObjectParam node;
		node.object = obj;
		node.wantInit = true;
		objects.emplace_back(node);//リストに追加
		rankChange = true;//入れ替え要請
		return obj;
	};
	template <class Class>
	Class* Create(std::string name) {
		Class* obj = new Class(this);//ここで生成
		ObjectParam node;
		node.object = obj;
		node.object->SetName(name);
		node.wantInit = true;
		objects.emplace_back(node);//リストに追加
		rankChange = true;//入れ替え要請
		return obj;
	};
	template <class Class>
	Class* Invoke() const {
		for (auto& node : objects) {
			//ここでキャストできなければ結果がnullptrになる
			Class* obj = dynamic_cast<Class*>(node.object);
			if (obj != nullptr)
				return obj;
		}
		return nullptr;
	}

	Object* Create(Object* obj,std::string name="");
	Object* Invoke(std::string name);
	void Destroy(std::string name);
	void Destroy(Object* obj);
	//template <class Class>
	//void Destroy(std::string name) {
	//	for (auto it = objects.begin(); it != objects.end(); it++) {
	//		ObjectParam& node = *it;
	//		Class* obj = dynamic_cast<Class*>(node.object);
	//		//if (name != node.object->GetName())continue;
	//		if (name != obj->GetName())continue;
	//		delete node.object;
	//		node.object = nullptr;
	//		objects.erase(it);
	//		return;
	//	}
	//}
	void ChangeDispRank(Object* obj,int rank);

private:

	//objectに持たせたくない者たち
	struct ObjectParam {
		bool wantInit;//object初期化予約
		bool wantMyExplosion;//object破棄予約
		int dispRank;//draw優先順位
		Object*object;//例のobject
		
		ObjectParam()
			:wantInit(false)
			, wantMyExplosion(false)
			, object(nullptr)
			, dispRank(0)
		{}
	};
	
	std::list<ObjectParam>objects;//臨時保管
	std::list<ObjectParam>objectsDraw;//臨時保管（描画用
	bool rankChange;//描画順変更予約



	void AllDestroy();//デストラクタでの破棄
	void UpdateInInitialization(); //初期化
	void UpdadeInDestory();//破棄
	void DestoryDrawObject(Object* obj);//破棄時描画用のやつも消すため
	static bool DispSort(const ObjectParam & rank1,const ObjectParam & rank2);//入れ替え用
	void DispChanger();
};

/*
	Sceneクラスに必要なことは
	・objectクラスの作成
	・objectクラスの取得
	・objectクラスの破棄
	・Updateで上記それらの処理
*/
