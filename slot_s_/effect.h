#pragma once
#include"../source/object.h"
#include"../source/config.h"
#include<vector>
#include"reel.h"
struct Vectwo {
	float x;
	float y;
};
struct CircleParam {
	Vectwo pos;
	float radius;
	int color;
};
struct BoxParam {
	Vectwo pos;
	Vectwo size;
};
struct Image {
	Vectwo pos;
	Vectwo size;
	int img;
};
class Shape {
public:
	Shape() = default;
	~Shape() = default;
	virtual void Draw() = 0 {}
};

class CircleEffect :public Shape {
public:
	void CircleEffect::Draw() {
		DrawCircleAA(param.pos.x, param.pos.y, param.radius, 20, param.color);
	}
	CircleParam param;

};
class Box :public Shape {
public:
	void Draw() {
		float up = param.pos.y - param.size.y;
		float left = param.pos.x - param.size.x;
		float down = param.pos.y + param.size.y;
		float right = param.pos.x + param.size.x;
		DrawBoxAA(up, left, down, right, 0xffffff, true);
	}

	BoxParam param;
};
class EmitterExprosion
{
public:
	EmitterExprosion();
	~EmitterExprosion();
	void Init();
	void Reset();
	void Update();
	void Draw();
	void On();
	void Off();
	void SetPos(Vectwo pos);

private:
	void NaturalLifeTime(int& i);
	void Move(int& i);
	void Resistance(int& i);
	void Gravity(int& i);
	void BoundGround(const int& i);
	void BoundWall(int& i);
	void ColorChange(int i);

	std::vector<CircleEffect*>circle;
	std::vector<Vectwo>velocity;
	std::vector<int>nonmovecount;
	std::vector<bool>active;
	int colorH[30];
	const int circlenum = 30;
	const int ground = SCREEN_HEIGHT - 100;
	const float gravity = 0.6f;
	const float resistance = 0.98f;
};

class Effect :public Object{
public:
	Effect(Scene* sc);
	~Effect()override;
	void Init()override;
	void Update()override;
	void Draw()override;
private:
	void EffectReset(int i);
	void ManualOn();
	void EffectUpdate();
	void AutoOn();

	 const int effectnum = 10;
	EmitterExprosion* emitter;
	Slot* slot;
	bool keystop;
	bool resetflag ;
	int count;
	int mousex;
	int mousey; 
};			    