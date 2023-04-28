#include <DxLib.h>
#include"app.h"
#include"config.h"

void LoadInit() {
	SetOutApplicationLogValidFlag(LOGSET_MODE);//ログの書き出し設定
	ChangeWindowMode(WINDOW_MODE);	//ウィンドウモードにする
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//ウィンドウサイズを設定する
	SetWindowSizeExtendRate(WINDOW_EXTEND);//ウィンドウ拡大率
	//SetWindowSizeChangeEnableFlag(TRUE);//途中大きさ変更あり
	SetWindowStyleMode(WINDOW_STYLE);//ウィンドウの最大化ボタンを機能させる。
	//SetUseIMEFlag(true);// ＩＭＥを使用するかどうかを設定する
	SetWindowText(WINDOW_NAME);
	SetAlwaysRunFlag(TRUE);//ウィンドウが非アクティブでも動くか
}

//プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LoadInit();
	
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

		
	//SetAlwaysRunFlag(TRUE);//ウィンドウがアクティブではない状態でも動く
	//SetUseZBuffer3D(TRUE);
	//SetWriteZBuffer3D(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ


	//最初に１回呼ぶ
	App::Init();

	//メイン処理
#if true
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		clsDx();
		ClearDrawScreen();	//裏画面の描画を全て消去
		App::Update();
		App::Draw();
		ScreenFlip();		//裏画面と表画面の入替
	}
#else
	while (true) {
		App::Update();
		ClearDrawScreen();
		App::Draw();
		if (ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE) != 0)
			break;
		ScreenFlip();
}
#endif
	App::Delete();

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
