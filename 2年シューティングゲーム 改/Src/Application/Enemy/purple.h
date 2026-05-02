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
	float m_moveSpeedY = 4.0f;
	float m_moveSpeedX = -12.0f;
};

