#pragma once
#include"Application/Player/Player.h"
#include"Application/Enemy/EnemyBase.h"

class C_GamePlay
{
public:
	C_GamePlay(){}
	~C_GamePlay(){}

	// 初期設定
	void Init();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

private:
	int GameCnt;
	C_Player m_player;

	KdTexture m_playerTex;		//プレイヤー画像

	C_EnemyBase m_enemy;

	KdTexture m_enemyTex;
};

