#pragma once
#include<vector>
#include"../source/object.h"
#include"field.h"
//子機
class PuyoConnectRect :public Object{
public:
	PuyoConnectRect(Scene* sc);
	~PuyoConnectRect();
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	void On() { connectOn=true; }

	bool Connect();
	void DataSaab();
	void DataReceive();
	void DisConnect();
private:
	char StrBuf[PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth];    // データバッファ
	IPDATA Ip;        // 接続用ＩＰアドレスデータ
	int port;
	int NetHandle, LostHandle;        // ネットワークハンドル
	int DataLength;        // 受信データ量保存用変数
	std::vector<int> field2p;
	bool connectOn;
};
