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
	GetScene()->Destroy("繋がりの水平");
	GetScene()->Destroy("繋がりの垂直");
}
void PuyoLinks::Init(){
	GetScene()->Create<PuyoHorizontalLink>(	"繋がりの水平");
	GetScene()->Create<PuyoVerticalLink>(	"繋がりの垂直");
}

void PuyoLinks::Update()
{
}

void PuyoLinks::Draw()
{
}
