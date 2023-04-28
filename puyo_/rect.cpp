#include "rect.h"
#include"../source/scenemanager.h"
#include"../source/scene.h"
#include"puyo.h"
PuyoConnectRect::PuyoConnectRect(Scene* sc)
    :Object(sc)
    ,StrBuf()
    ,Ip()
    ,port()
    ,NetHandle()
    ,LostHandle()
    ,DataLength()
    , field2p()
    ,connectOn(false)
{}
PuyoConnectRect::~PuyoConnectRect(){

}
void PuyoConnectRect::Init(){
    NetHandle = -1;
    field2p.resize(PuyoFieldConfig::fieldHeight * PuyoFieldConfig::fieldWidth);
    field2p.clear();

}
void PuyoConnectRect::Update(){
    if (connectOn) {
        DataSaab();
        DataReceive();
    }
    //if (SceneManager::GetFrame() % 60 != 0) return;
    //field2p.clear();
}
void PuyoConnectRect::Draw() {
    if (field2p.empty())return;

#ifdef _DEBUG
    for (int i = 0; i < PuyoFieldConfig::fieldHeight; i++) {
        for (int j = 0; j < PuyoFieldConfig::fieldWidth; j++) {

            int index = PuyoField::IndexChange(i, j);
            int gridRadius = PuyoFieldConfig::gridSize / 2;
            DrawFormatString(400+i*16, 200 + j * 16, 0xffffff, "%d\n", field2p[index]);
        }
    }
    DrawFormatString(100, 350, 0xffffff, "%d", field2p.size());
#endif

    DrawBox(400,0,800,600,0x000000,true);
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

bool PuyoConnectRect::Connect(){

   
    // �ڑ����Ă���̂�҂�Ԃɂ���
    port = 9850;
    PreparationListenNetWork(port);

    // �ڑ����Ă��邩�d�r�b�L�[���������܂Ń��[�v
    if (NetHandle == -1) {

        // �V�����ڑ����������炻�̃l�b�g���[�N�n���h���𓾂�
        NetHandle = GetNewAcceptNetWork();
#ifdef _DEBUG
        DrawFormatString(100, 100, 0xffffff, "�ʐM�ڑ�");
#endif
    }
    
    // �ڑ�����Ă����玟�ɐi��
    if (NetHandle != -1){
        // �ڑ��̎�t���I������
        StopListenNetWork();

        // �ڑ����Ă����}�V���̂h�o�A�h���X�𓾂�
        GetNetWorkIP(NetHandle, &Ip);
#ifdef _DEBUG
        DrawFormatString(100, 100+GetFontSize()*1.5f, 0xffffff, "����m�F");
#endif
        return true;
    }
    return false;
}
void PuyoConnectRect::DataSaab() {
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
        int size = str.size() + 1;
        NetWorkSend(NetHandle, &size, sizeof(int));//�������M
        NetWorkSend(NetHandle, str.c_str(), size);//�f�[�^���M
#ifdef _DEBUG
        DrawFormatString(100, 100, 0xffffff, "�f�[�^���M");
#endif
}
void PuyoConnectRect::DataReceive() {
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
void PuyoConnectRect::DisConnect() {
    if (GetLostNetWork() != NetHandle)return;
        // ���肪�ʐM��ؒf����܂ő҂�
#ifdef _DEBUG
            DrawString(0, 16, "�ؒf���ł�", GetColor(255, 255, 255));
#endif
            // �V���ɐؒf���ꂽ�l�b�g���[�N�n���h���𓾂�
            LostHandle = GetLostNetWork();

            // �ؒf���ꂽ�ڑ������܂ŒʐM���Ă����肾�����ꍇ���[�v�𔲂���
        if(LostHandle == NetHandle){
        // �ؒf�m�F�\��
#ifdef _DEBUG
        DrawString(0, 16, "�ؒf���܂���", GetColor(255, 255, 255));
#endif
        }
#ifdef _DEBUG
        DrawFormatString(100, 100, 0xffffff, "�ʐM�ؒf");
#endif
}
