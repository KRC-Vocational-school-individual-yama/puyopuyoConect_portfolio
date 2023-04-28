#pragma once
#include"../source/object.h"
#include"reel.h"
#include<string>
#include<vector>
struct FontDisp {
	Vec2 pos;
	std::string str;
	int color;
	bool active;
	void Draw();
};
class Strings {
public:
	 Strings();
	~Strings();
	void Init();
	void Update();
	void Draw();
	void SetPos(Vec2 pos,int num=0);
	int GetSize() {return resizenumber;}
	int GetmyFontSize() { return fontsize; }
private:
	void ButtonInputASD();
	void ButtonInputSpace();
	void JudgeSpaceDisp();

	enum class ButtonNumbers {
		KeyIsA=0,
		KeyIsS,
		KeyIsD,
		KeyIsSpace,
		KeyIsMax
	};
	std::vector<FontDisp> font;
	std::vector<bool>button;
	const int resizenumber;
	const int fontsize;

	int spaceDispCount;
};

class UiInterface :public Object{
public:
	UiInterface(Scene* sc);
	~UiInterface()override;
	void Init()override;
	void Update()override;
	void Draw()override;
private:
	Strings keyDownFont;
	Slot* slot;
};