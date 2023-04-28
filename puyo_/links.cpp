#include "links.h"
#include"../source/scene.h"
#include"horizontallink.h"
#include"verticallink.h"
PuyoLinks::PuyoLinks(Scene* sc)
	:Object(sc)
	//,hLink(nullptr)
	//,vLink(nullptr)
{}
PuyoLinks::~PuyoLinks(){
	GetScene()->Destroy("Œq‚ª‚è‚Ì…•½");
	GetScene()->Destroy("Œq‚ª‚è‚Ì‚’¼");
}
void PuyoLinks::Init(){
	GetScene()->Create<PuyoHorizontalLink>(	"Œq‚ª‚è‚Ì…•½");
	GetScene()->Create<PuyoVerticalLink>(	"Œq‚ª‚è‚Ì‚’¼");
}

void PuyoLinks::Update()
{
}

void PuyoLinks::Draw()
{
}
