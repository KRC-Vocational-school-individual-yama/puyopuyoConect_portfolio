#include "connect.h"
#include"../source/scene.h"
#include"field.h"
#include"puyo.h"
PuyoConnect::PuyoConnect(Scene* sc)
	:Object(sc)
	,ip()
	,port(9850)
	,netHandle(-1)
	,sendData()
	,receiveData()
	,field2p()
	,isSaab(false)
	,isReceive(false)
{}
PuyoConnect::~PuyoConnect(){
	if (netHandle == -1)return;
	CloseNetWork(netHandle);
}
void PuyoConnect::Init(){
	ip.d1 = 127;
	ip.d2 = 0;
	ip.d3 = 0;
	ip.d4 = 1;

}
void PuyoConnect::Update() {
	SaabOn();
	ReceiveOn();
	
	if (netHandle == -1) return;
	//送信
	DataSaab();
	
	//受信
	DataReceive();



}
void PuyoConnect::Draw(){
	if (netHandle == -1) {
		DrawFormatString(600, 400, 0xdddddd, "未接続");
		return;
	}
	else {
		DrawFormatString(600, 400, 0xdddddd, "接続");
	}

	if (field2p.empty())return;
	DrawBox(800/2,0,800,600,0x000000,true);

	for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
		for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {
			int offSet = 400;

			int index = PuyoField::IndexChange(i, j);
			int gridRadius = PuyoFieldConfig::gridSize / 2;
			bool thisIsFill = field2p[index] == -1;
			Vec2 disppos = PuyoField::GetGridPos(i, j);
			disppos.x += offSet;
			//盤面の描画
			if (thisIsFill) {

				DrawBox(disppos.x - gridRadius + 1, disppos.y - gridRadius + 1,
					disppos.x + gridRadius - 1, disppos.y + gridRadius - 1, 0xeeeeee, thisIsFill);
			}
			
			//固定後ぷよの描画
			if (field2p[index] == -1)continue;
			if (field2p[index] == 0)continue;
			int cIndex = field2p[index] - 1;
			//if (cIndex < 0)cIndex = 0;
			int color = PuyoPlayerConfig::colorTable[cIndex];
			//DrawCircle(disppos.x, disppos.y, PuyoFieldConfig::puyoSize , color, true);
			DrawOval(disppos.x, disppos.y, PuyoFieldConfig::puyoSize, PuyoFieldConfig::puyoSize, color, true);
		}
	}

}

void PuyoConnect::Saab(){
	isSaab = true;
}
void PuyoConnect::Receive() {
	isReceive = true;
}

void PuyoConnect::ConnectEnd(){
	if (netHandle == -1) return;
	CloseNetWork(netHandle);
	netHandle = -1;
	field2p.clear();
}

void PuyoConnect::SaabOn(){
	if (!isSaab)return;
		netHandle = ConnectNetWork(ip, port);
		isSaab = false;

	
}
void PuyoConnect::ReceiveOn(){
	if (!isReceive)return;
		PreparationListenNetWork(port);
		netHandle = GetNewAcceptNetWork();
		isReceive = false;
	
}

	//送信
void PuyoConnect::DataSaab(){
	//データ入れ
	sendData.clear();
	for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
		for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {
			int index = PuyoField::IndexChange(i, j);
			int gridNumber= GetScene()->Invoke<PuyoField>()->GetGridInside(i,j);
			if (gridNumber == -1) {
				sendData += std::to_string(0).c_str();
			}
			else {
			sendData += std::to_string(gridNumber);
			}
		}
	}

	int sendSize = sendData.size() + 1;
	NetWorkSend(netHandle, sendData.c_str(), sendSize);

}

void PuyoConnect::DataReceive(){
	//受信
	int dataLength = -1;
	dataLength = GetNetWorkDataLength(netHandle);
	if (dataLength == 0)return;
	//char* ReceiveDatas=new char[dataLength];
	receiveData=new char[dataLength];
	NetWorkRecv(netHandle, receiveData, dataLength);

	//受け取りデータ加工
	for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
		for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {
			int index = PuyoField::IndexChange(i, j);
			int gridNumber = GetScene()->Invoke<PuyoField>()->GetGridInside(i, j);
			int inside= receiveData[index];
			field2p.emplace_back(inside);
		}
	}
	//壁を入れ替え
	int maxIndex = PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth;
	for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
		for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {
			int index = PuyoField::IndexChange(i, j);

			bool widthzero = j == 0;
			bool heightzero = i == 0;
			bool widthmax = j == PuyoFieldConfig::fieldWidth - 1;
			bool heightmax = i == PuyoFieldConfig::fieldHeight - 1;
			if (widthzero || heightzero || widthmax || heightmax)
				field2p[index] = -1;
		}
	}
	delete[] receiveData;
}
