#pragma once
#include"../source/object.h"
#include<vector>
#include"field.h"
//�e�@
class PuyoConnectSend:public Object{
public:
	PuyoConnectSend(Scene* sc);
	~PuyoConnectSend();
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	void On() { connectOn = true; }

	bool Connect();
	void DataSaab();
	void DataReceive();
	void DisConnect();
private:
	char StrBuf[PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth];    // �f�[�^�o�b�t�@
	IPDATA Ip;        // �ڑ��p�h�o�A�h���X�f�[�^
	int NetHandle;        // �l�b�g���[�N�n���h��
	int DataLength;        // ��M�f�[�^�ʕۑ��p�ϐ�
	std::vector<int> field2p;
	bool connectOn;
};