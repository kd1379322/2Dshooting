#pragma once

#include"EnemyBase.h"

class C_Orange :public C_EnemyBase
{
public:
	C_Orange(){}
	~C_Orange()override { Release(); }

	void Init();

	void Update();

	void Draw2D();

	int CheckColor(int i);


private:
	float m_moveSpeedX = -18.0f;


};

