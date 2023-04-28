#include "slotscene.h"
#include"effect.h"
#include"uiinterface.h"
#include"reel.h"
#include"backScene.h"

SlotScene::SlotScene(){
	Create<Slot>();
	Create<UiInterface>();
	Create<Effect>();
	Create<SlotBackScene>();
}
SlotScene::~SlotScene(){
}
