#pragma once
#include"EfectBase.h"

class C_damage :public C_EfectBase
{
public:
	C_damage() {};
	~C_damage()override { Release(); };

	void Init()override;

	void Update()override;

	void Draw() override;

	void App(Math::Vector2 p_pos)override;

private:
	void Release()override;		// 解放処理
	const int FRAME_W = 108;
	const int FRAME_H = 116;
	const int FRAME_COL = 10; // 横
	const int FRAME_ROW = 8;  // 縦
	const int FRAME_MAX = FRAME_COL * FRAME_ROW; // 60
};

