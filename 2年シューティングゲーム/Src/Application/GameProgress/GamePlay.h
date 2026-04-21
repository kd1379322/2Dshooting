#pragma once

class C_Player;
class C_EnemyBase;
class C_Bullet;

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
	C_Player *m_player;
	KdTexture m_playerTex;		//プレイヤー画像

	C_EnemyBase *m_enemy;
	KdTexture m_enemyTex;

	static const int MaxBullet = 10;
	C_Bullet *m_Bullet[MaxBullet];
	KdTexture m_BulletTex;			//画像用	
	bool Bulletkeyflg;			//弾発射キーフラグ
	int BulletCnt;
};

