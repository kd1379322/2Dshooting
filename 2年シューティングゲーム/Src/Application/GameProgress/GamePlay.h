#pragma once

#include"Application/Player/Player.h"
#include"Application/Player/Bullet.h"
#include"Application/Enemy/EnemyBase.h"

class C_pcc;

class C_GamePlay
{
public:
	C_GamePlay(){}
	~C_GamePlay() { Release(); }

	// 初期設定
	void Init();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

private:

	void Release();		// 解放処理


	KdTexture m_backgroundTex;

	int GameCnt;
	C_Player m_player;
	KdTexture m_playerTex;		//プレイヤー画像

	static const int MaxEnemy = 18;
	C_EnemyBase m_enemy[MaxEnemy];

	static const int MaxcloneEnemy = 9;
	C_EnemyBase m_cloneEnemy[MaxcloneEnemy];

	KdTexture m_enemyTex;

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_rotationMat;	//回転行列
	Math::Matrix m_mat;			//行列

	static const int MaxBullet = 10;
	C_Bullet m_Bullet[MaxBullet];
	KdTexture m_BulletTex;			//画像用	
	bool Bulletkeyflg;			//弾発射キーフラグ
	int BulletCnt;
	Math::Color BulletColor;
	int BulletColorNumber;

	Math::Vector2 Backgroundpos = { 0,0 };

	std::shared_ptr<C_pcc> m_pcc = nullptr;
};

