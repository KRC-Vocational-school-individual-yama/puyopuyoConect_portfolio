#include "send.h"
#include"../source/scene.h"
#include"puyo.h"
PuyoConnectSend::PuyoConnectSend(Scene* sc)
    :Object(sc)
    ,StrBuf()
    ,Ip()
    ,NetHandle()
    ,DataLength()
    ,field2p()
    ,connectOn(false)
{}
PuyoConnectSend::~PuyoConnectSend(){

}
void PuyoConnectSend::Init(){
    NetHandle = -1;
    //192.168.  1.  15    ����������pc�́@IPv4
    //127.  0.  0.  1     ���������w��IPv4
    //25.11.194.136       ��hamachi ����������IPv4
    //25.41.213.206       ��hamachi ��������IPv4
  //�ڑ����IP�A�h���X���w��
    Ip.d1 = 127;
    Ip.d2 = 0;
    Ip.d3 = 0;
    Ip.d4 = 1;
    field2p.resize(PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth);
    field2p.clear();
}
void PuyoConnectSend::Update(){
    if (connectOn) {
        DataSaab();
        DataReceive();
    }
    //if (SceneManager::GetFrame() % 60 != 0) return;
    //field2p.clear();
}
void PuyoConnectSend::Draw() {
    if (field2p.empty())return;
#ifdef _DEBUG 
    for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
        for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {

            int index = PuyoField::IndexChange(i, j);
            int gridRadius = PuyoFieldConfig::gridSize / 2;
            DrawFormatString(400 + i * 16, 200 + j * 16, 0xffffff, "%d\n", field2p[index]);
        }
    }DrawFormatString(100, 350, 0xffffff, "%d", field2p.size());
#endif

    DrawBox(400, 0, 800, 600, 0x000000, true);
    for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
        for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {
            int offSet = 400;

            int index = PuyoField::IndexChange(i, j);
            int gridRadius = PuyoFieldConfig::gridSize / 2;
            bool thisIsFill = field2p[index] == -1;
            Vec2 disppos = PuyoField::GetGridPos(i, j);
            disppos.x += offSet;
            //�Ֆʂ̕`��
            if (thisIsFill) {

                DrawBox(disppos.x - gridRadius + 1, disppos.y - gridRadius + 1,
                    disppos.x + gridRadius - 1, disppos.y + gridRadius - 1, 0xeeeeee, thisIsFill);
            }

            //�Œ��Ղ�̕`��
            if (field2p[index] == -1)continue;
            if (field2p[index] == 0)continue;
            int cIndex = field2p[index] - 1;
            if (cIndex < 0)cIndex = 0;
            if (cIndex > 3)cIndex = 3;
            int color = PuyoPlayerConfig::colorTable[cIndex];
            //DrawCircle(disppos.x, disppos.y, PuyoFieldConfig::puyoSize , color, true);
            DrawOval(disppos.x, disppos.y, PuyoFieldConfig::puyoSize, PuyoFieldConfig::puyoSize, color, true);
        }
    }
}

bool PuyoConnectSend::Connect(){

    //strbufs.clear();

    // �ʐM���m��
    NetHandle = ConnectNetWork(Ip, 9850);
    if (NetHandle != -1) {
        return true;
#ifdef _DEBUG
        DrawFormatString(100, 100, 0xffffff, "�ʐM�ڑ�����");
#endif
    }
    else {
#ifdef _DEBUG
        DrawFormatString(100, 100, 0xffffff, "�ʐM�ڑ���");
#endif
    }
    return false;
}

void PuyoConnectSend::DataSaab() {
    if (SceneManager::GetFrame() % 60 != 0) return;
    if (GetLostNetWork() == NetHandle)return;

    std::string str = "";

    for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
        for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {
            int index = PuyoField::IndexChange(i, j);
            int gridNumber = GetScene()->Invoke<PuyoField>()->GetGridInside(i, j);
            if (gridNumber == -1) {
                str += std::to_string(0).c_str();
            }
            else {
                str += std::to_string(gridNumber);
            }
        }
    }


    // �f�[�^���M
    int StrLength = str.size()+1;
    NetWorkSend(NetHandle, &StrLength, sizeof(int));
    NetWorkSend(NetHandle, str.c_str(),StrLength);

#ifdef _DEBUG
    DrawFormatString(100, 100, 0xffffff, "�f�[�^���M");
#endif

}
void PuyoConnectSend::DataReceive() {
    if (GetLostNetWork() == NetHandle)return;
    if (GetNetWorkDataLength(NetHandle) > sizeof(int)) {
        // �f�[�^������̂�҂�

        NetWorkRecvToPeek(NetHandle, &DataLength, sizeof(int));
        if (DataLength + 4 <= GetNetWorkDataLength(NetHandle)) {
            // �f�[�^��M
            NetWorkRecv(NetHandle, &DataLength, sizeof(int));
            NetWorkRecv(NetHandle, StrBuf, DataLength);    // �f�[�^���o�b�t�@�Ɏ擾
            
            field2p.clear();
            //�󂯎��f�[�^���H
            for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
                for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {
                    int index = PuyoField::IndexChange(i, j);
                    char character = StrBuf[index];
                    std::string strOne= "";
                    strOne[0] = StrBuf[index];
                    int inside = std::atoi(strOne.c_str());
                    field2p.emplace_back(inside);
                }
            }

            //�ǂ����ւ�
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
            DataLength = 0;
        }

#ifdef _DEBUG
        DrawFormatString(100, 100, 0xffffff, "�f�[�^��M");
#endif
    }
}
void PuyoConnectSend::DisConnect() {
   // if (GetLostNetWork() != NetHandle)return;
    // �ڑ���f��
    CloseNetWork(NetHandle);
#ifdef _DEBUG
    DrawFormatString(100, 100, 0xffffff, "�ʐM�ؒf");
#endif

}
