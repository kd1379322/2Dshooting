#pragma once

#include"EnemyBase.h"

class C_Purple :public C_EnemyBase
{
public:
	C_Purple(){}
	~C_Purple()override { Release(); }

	void Init();

	void Update();

	void Draw2D();

	int CheckColor(int i);


private:
	float m_moveSpeedY = 8.0f;
	float m_moveSpeedX = -6.0f;
};

