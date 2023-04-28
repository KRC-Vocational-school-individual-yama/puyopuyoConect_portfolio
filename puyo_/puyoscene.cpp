#include "puyoscene.h"
#include"puyogame.h"
#include"se.h"
PuyoScene::PuyoScene(){
	Create<PuyoGame>();
	Create<PuyoSe>();
}
PuyoScene::~PuyoScene(){
}
