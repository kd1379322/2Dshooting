#pragma once

#include"EnemyBase.h"

class C_Red :public C_EnemyBase
{
public:
	C_Red(){}
	~C_Red()override { Release(); }

	void Update();

	bool CheckColor(int i);


private:
	

};

