#pragma once
#include"../source/object.h"

//https://jiyu-cho.com/puyopuyo-keisan

class PuyoScore :public Object {
public:
	PuyoScore(Scene* sc);
	~PuyoScore();
	void Init()override;
	void Update()override;
	void Draw()override;

	void DefaultUp();
	void EraseCalc();
	void EraseUp();
	
private:
	void DrawScore(Vec2 pos);
	//âEãlÇﬂÇÃçÏã∆
	std::string RightString(int num, int keta = 10000, bool zeroDisp = false);
	/*template <typename T>
	std::string RightString(T num, int keta= 10000,bool zeroDisp=false){
		std::string str = "";
		int scoreChange = 0;
		int scoreChangeold = 0;
		for (int i = keta; i > 0; i /= 10) {
			int num = static_cast<int>((num - scoreChangeold) / i);
			if (i > num && !zeroDisp) {

				if (num == 0) {
					str += " ";
				}
				else {
					str += std::to_string(num);
				}
			}
			else
			{
				str += std::to_string(num);
			}
			scoreChange = num * i;
			scoreChangeold += scoreChange;
		}
		return str;
	}*/
	int score;
	int dispScore;
	int upScore;
	bool dispUp;
};
