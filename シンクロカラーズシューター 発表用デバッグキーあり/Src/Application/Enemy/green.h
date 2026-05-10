#pragma once

#include"EnemyBase.h"

class C_Green :public C_EnemyBase
{
public:
	C_Green(){}
	~C_Green()override { Release(); }

	void Init();

	void Update();

	void Draw2D();

	int CheckColor(int i);


private:
	float m_moveSpeedX = -12.0f;

};

