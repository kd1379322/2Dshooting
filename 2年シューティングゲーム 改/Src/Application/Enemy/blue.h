#pragma once

#include"EnemyBase.h"

class C_Blue :public C_EnemyBase
{
public:
	C_Blue(){}
	~C_Blue()override { Release(); }

	void Init();

	void Update();

	void Draw2D();

	int CheckColor(int i);


private:
	

};

