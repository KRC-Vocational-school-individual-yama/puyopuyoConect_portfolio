#pragma once
#include<string>
#include<list>

class Object;
//�x�[�X ��� �匳
class Scene {
public:
	Scene();
	virtual ~Scene();
	virtual void Update();
	virtual void Draw();

	template <class Class>
	Class* Create() {
		Class* obj = new Class(this);//�����Ő���
		ObjectParam node;
		node.object = obj;
		node.wantInit = true;
		objects.emplace_back(node);//���X�g�ɒǉ�
		rankChange = true;//����ւ��v��
		return obj;
	};
	template <class Class>
	Class* Create(std::string name) {
		Class* obj = new Class(this);//�����Ő���
		ObjectParam node;
		node.object = obj;
		node.object->SetName(name);
		node.wantInit = true;
		objects.emplace_back(node);//���X�g�ɒǉ�
		rankChange = true;//����ւ��v��
		return obj;
	};
	template <class Class>
	Class* Invoke() const {
		for (auto& node : objects) {
			//�����ŃL���X�g�ł��Ȃ���Ό��ʂ�nullptr�ɂȂ�
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

	//object�Ɏ����������Ȃ��҂���
	struct ObjectParam {
		bool wantInit;//object�������\��
		bool wantMyExplosion;//object�j���\��
		int dispRank;//draw�D�揇��
		Object*object;//���object
		
		ObjectParam()
			:wantInit(false)
			, wantMyExplosion(false)
			, object(nullptr)
			, dispRank(0)
		{}
	};
	
	std::list<ObjectParam>objects;//�Վ��ۊ�
	std::list<ObjectParam>objectsDraw;//�Վ��ۊǁi�`��p
	bool rankChange;//�`�揇�ύX�\��



	void AllDestroy();//�f�X�g���N�^�ł̔j��
	void UpdateInInitialization(); //������
	void UpdadeInDestory();//�j��
	void DestoryDrawObject(Object* obj);//�j�����`��p�̂����������
	static bool DispSort(const ObjectParam & rank1,const ObjectParam & rank2);//����ւ��p
	void DispChanger();
};

/*
	Scene�N���X�ɕK�v�Ȃ��Ƃ�
	�Eobject�N���X�̍쐬
	�Eobject�N���X�̎擾
	�Eobject�N���X�̔j��
	�EUpdate�ŏ�L�����̏���
*/
