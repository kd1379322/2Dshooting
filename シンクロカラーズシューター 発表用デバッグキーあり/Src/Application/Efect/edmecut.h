#pragma once

#include"EfectBase.h"

class C_edmecut :public C_EfectBase
{
public:
	C_edmecut(){}
	~C_edmecut()override { Release(); }

	void Init()override;

	void Update()override;

	void Draw() override;

	void App(Math::Vector2 p_pos)override;
private:
	void Release()override;		// 解放処理
	const int FRAME_W = 305;
	const int FRAME_H = 383;
	const int FRAME_COL = 9; // 横
	const int FRAME_ROW = 5;  // 縦
	const int FRAME_MAX = FRAME_COL * FRAME_ROW; // 60
};
