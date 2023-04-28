#pragma once
#include"../source/object.h"
#include<vector>
#include"field.h"
//親機
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
	char StrBuf[PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth];    // データバッファ
	IPDATA Ip;        // 接続用ＩＰアドレスデータ
	int NetHandle;        // ネットワークハンドル
	int DataLength;        // 受信データ量保存用変数
	std::vector<int> field2p;
	bool connectOn;
};