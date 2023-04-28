#pragma once
#include"../source/object.h"
#include"send.h"
#include"rect.h"
class PuyoConnectMode :public Object{
public:
	PuyoConnectMode(Scene* sc);
	~PuyoConnectMode();
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	bool GetOff() { return off; }
private:
	enum class Mode {
		parentOrChild
		,send//親機←　参加する人
		,rect//子機←　実は部屋を開く人
		,connectEnd
	};
	Mode mode;
	PuyoConnectSend* send;
	PuyoConnectRect* rect;
	bool nowConnect;
	bool destroy;
	bool off;
};