#include"effect.h"
#include"../source/scene.h"

EmitterExprosion::EmitterExprosion()
	:circle()
	,velocity()
	,nonmovecount()
	,active()
	,colorH()
{}
EmitterExprosion::~EmitterExprosion() {
	for (int i = 0; i < circlenum; i++) {
		delete circle[i];
	}
}
void EmitterExprosion::Init() {
	circle.resize(circlenum);
	velocity.resize(circlenum);
	nonmovecount.resize(circlenum);
	active.resize(circlenum);
	for (int i = 0; i < circle.size(); i++) {
		circle[i] = new CircleEffect();
		colorH[i] = 0;
	}
	Reset();
}
void EmitterExprosion::Reset() {
	for (int i = 0; i < circle.size(); i++) {
		circle[i]->param.pos.x = SCREEN_WIDTH / 2.0f;//GetRand(400) + 100;
		circle[i]->param.pos.y = SCREEN_HEIGHT / 2.0f;//GetRand(300) + 100;
		circle[i]->param.radius = 5;
		//colorH[i]=0;
		circle[i]->param.color = color::GetHSV(colorH[i], 255, 255);
		velocity[i].x = GetRand(50) - GetRand(50);
		velocity[i].y = GetRand(25) - GetRand(50);
		nonmovecount[i] = 0;
		active[i] = false;
	}
}
void EmitterExprosion::Update() {
	for (int i = 0; i < circle.size(); i++) {
		if (!active[i])continue;
		Gravity(i);
		Move(i);
		NaturalLifeTime(i);
		Resistance(i);
		BoundGround(i);
		BoundWall(i);
		ColorChange(i);
	}
}
void EmitterExprosion::Draw()
{
	for (int i = 0; i < circle.size(); i++) {
		if (!active[i]) continue;
		circle[i]->Draw();
	}
}
void EmitterExprosion::On() {
	for (int i = 0; i < circlenum; i++) {
		if (active[i])continue;
		active[i] = true;
	}
}
void EmitterExprosion::Off() {
	for (int i = 0; i < circlenum; i++) {
		if (!active[i])continue;
		active[i] = false;
	}
}
void EmitterExprosion::SetPos(Vectwo pos) {
	for (int i = 0; i < circlenum; i++) {
		circle[i]->param.pos = pos;
	}
}
void EmitterExprosion::NaturalLifeTime(int& i) {
	bool notmoveflag = (int)velocity[i].x == 0 && (int)velocity[i].y == 0;
	if (!notmoveflag)return;
	nonmovecount[i]++;
	if (nonmovecount[i] > 60) {
		active[i] = false;
	}
}
void EmitterExprosion::Move(int& i) {
	circle[i]->param.pos.x += velocity[i].x;
	circle[i]->param.pos.y += velocity[i].y;

}
void EmitterExprosion::Resistance(int& i) {
	velocity[i].x *= resistance;
	velocity[i].y *= resistance;
}
void EmitterExprosion::Gravity(int& i) {
	velocity[i].y += gravity;
}
void EmitterExprosion::BoundGround(const int& i) {
	if (velocity[i].y <= 0.0f) return;
	if (circle[i]->param.pos.y > ground) {
		circle[i]->param.pos.y = ground;
		float decelerate = 0.2f + GetRand(5) / 10.0f;//Œ¸‘¬
		velocity[i].y *= -1 * decelerate;
		velocity[i].x *= resistance;
	}

}
void EmitterExprosion::BoundWall(int& i) {
	if (circle[i]->param.pos.x < 0 + circle[i]->param.radius) {
		circle[i]->param.pos.x = 0 + circle[i]->param.radius;
		velocity[i].x *= -1;
	}
	if (circle[i]->param.pos.x > SCREEN_WIDTH - circle[i]->param.radius) {
		circle[i]->param.pos.x = SCREEN_WIDTH - circle[i]->param.radius;
		velocity[i].x *= -1;
	}
}
void EmitterExprosion::ColorChange(int i) {
	colorH[i]++;
	if (colorH[i] >= 360) {
		colorH[i] = 0;
	}
	circle[i]->param.color = color::GetHSV(colorH[i], 255, 255);
}

Effect::Effect(Scene* sc)
	:Object(sc)
	,slot()
	,emitter()
	,keystop(false)
	,resetflag(false)
	,count(0)
	,mousex(SCREEN_WIDTH /2)
	,mousey(SCREEN_HEIGHT/2)
{}
Effect::~Effect()
{
	delete[] emitter;

}
void Effect::Init(){
	//SetMouseDispFlag(FALSE);
	SetMousePoint(mousex, mousey);
	emitter = new EmitterExprosion[effectnum];
	//Vectwo p = {GetRand(600)+100,GetRand(400)+100};
	Vectwo p = { mousex,mousey };
	for (int i = 0; i < effectnum; i++) {

		emitter[i].Init();
		emitter[i].Off();
		emitter[i].SetPos(p);
	}
	resetflag = false;
	count = 0;

	slot = dynamic_cast<Slot*>(GetScene()->Invoke<Slot>());
}
void Effect::Update()
{
	GetMousePoint(&mousex, &mousey);
	count++;
	if (!slot->GetSuccess()) {
		resetflag = true;
		count = 0;
	}
	if (slot == nullptr)return;
	if (!slot->GetSuccess())return;
	EffectUpdate();
	ManualOn();
	AutoOn();
}
void Effect::Draw()
{
	if (slot == nullptr)return;
	if (!slot->GetSuccess())return;
	for (int i = 0; i < effectnum; i++) {
		emitter[i].Draw();
	}
}
void  Effect::EffectReset(int i) {
	emitter[i].Reset();
	//emitter[i].On();
	//Vectwo p = { GetRand(600) + 100,GetRand(400) + 100 };
	Vectwo p = { mousex,mousey };
	emitter[i].SetPos(p);
}
void  Effect::ManualOn() {
	bool key = CheckHitKey(KEY_INPUT_R);
	if (key && !keystop) {
		resetflag = true;
		count = 0;
	}
	keystop = key;
	
}
void  Effect::AutoOn() {
	int i = count / 30 % effectnum;
	emitter[i].Reset();
	Vectwo p = { mousex,mousey };
	emitter[i].SetPos(p);
	emitter[i].On();
}
void Effect::EffectUpdate() {
	for (int i = 0; i < effectnum; i++) {
		if (count / 5 % (i + 1) == i)
			emitter[i].On();
		emitter[i].Update();
		if (!resetflag)continue;
		EffectReset(i);
	}
	resetflag = false;
}
