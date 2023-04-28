#pragma once
//#include"../source/object.h"
#include"field.h"
#include<string>
#include<vector>

class PuyoSave {
public:
	PuyoSave();
	~PuyoSave();
	static std::vector<int> Load(std::string _pass);
	static void Save(std::string _pass, std::vector<int> _field);

private:
	
};