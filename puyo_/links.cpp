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
	GetScene()->Destroy("�q����̐���");
	GetScene()->Destroy("�q����̐���");
}
void PuyoLinks::Init(){
	GetScene()->Create<PuyoHorizontalLink>(	"�q����̐���");
	GetScene()->Create<PuyoVerticalLink>(	"�q����̐���");
}

void PuyoLinks::Update()
{
}

void PuyoLinks::Draw()
{
}
