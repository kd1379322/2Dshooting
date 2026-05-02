#pragma once

#include"EnemyBase.h"

class C_Yellow :public C_EnemyBase
{
public:
	C_Yellow(){}
	~C_Yellow()override { Release(); }

	void Init();

	void Update();

	void Draw2D();

	int CheckColor(int i);


private:
	

};

