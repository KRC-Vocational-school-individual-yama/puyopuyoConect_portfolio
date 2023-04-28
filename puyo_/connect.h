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

	void Saab();	//通信親側
	void Receive();	//通信子側
	void ConnectEnd();//通信終了
private:
	void SaabOn();	//通信親側
	void ReceiveOn();	//通信子側
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
