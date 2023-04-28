#pragma once

#include"../source/object.h"
#include"field.h"

class PuyoConnect : public Object {
public:
	PuyoConnect(Scene* sc);
	~PuyoConnect();
	void Init();
	void Update();
	void Draw();

	void Saab();	//�ʐM�e��
	void Receive();	//�ʐM�q��
	void ConnectEnd();//�ʐM�I��
private:
	void SaabOn();	//�ʐM�e��
	void ReceiveOn();	//�ʐM�q��
	void DataSaab();
	void DataReceive();

	IPDATA ip;
	std::string sendData;
	std::vector<int>field2p;
	int port;
	int netHandle;
	//char receiveData[PuyoFieldConfig::fieldHeight*PuyoFieldConfig::fieldWidth+2];
	char* receiveData;
	bool isReceive;
	bool isSaab;
};
