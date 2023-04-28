#pragma once
#include"../source/object.h"

class PuyoLinks :public Object {
public:
	PuyoLinks(Scene* sc);
	~PuyoLinks();
	void Init()override;
	void Update()override;
	void Draw()override;

private:
	//PuyoHorizontalLink* hLink;
	//PuyoVerticalLink* vLink;
};
