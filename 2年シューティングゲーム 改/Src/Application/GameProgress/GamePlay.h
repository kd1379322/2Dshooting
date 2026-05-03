#pragma once

//==============================
//　前方宣言
//==============================

class C_Player;

class C_Bullet;

class C_EnemyBase;

class C_Heart;

class C_Dying;

class C_pcc;

class C_Circle;

class C_Timer;

class C_Score;

class C_GamePlay
{
public:
	C_GamePlay() {}
	~C_GamePlay() { Release(); }

	// 初期設定
	void Init();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	bool GetResultGo_T() { return Timeup; }

	int GetRastScore() { return score_tmp; }

	void Reset();

private:

	void Release();		// 解放処理

	void Circle(Math::Vector2 p_pos, int a);

	KdTexture m_backgroundTex;

	int GameCnt;
	std::shared_ptr<C_Player> m_player = nullptr;

	std::vector<std::shared_ptr<C_EnemyBase>> m_enemyList;

	static const int cpyMax = 15;
	std::shared_ptr<C_EnemyBase> m_copyenemy[cpyMax] = {nullptr};

	std::shared_ptr<C_Heart> m_heart = nullptr;
	std::shared_ptr<C_Dying> m_dying = nullptr;
	std::shared_ptr<C_pcc> m_pcc = nullptr;
	std::shared_ptr<C_Timer>m_timer = nullptr;
	std::shared_ptr<C_Score>m_score = nullptr;


	static const int CircleMax = 15;
	std::shared_ptr<C_Circle> m_circle[CircleMax] = { nullptr };

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_rotationMat;	//回転行列
	Math::Matrix m_mat;			//行列

	static const int MaxBullet = 10;
	std::shared_ptr<C_Bullet> m_Bullet[MaxBullet];

	bool Bulletkeyflg = true;			//弾発射キーフラグ
	int BulletCnt = 0;
	Math::Color BulletColor;
	int BulletColorNumber = 1;

	Math::Vector2 Backgroundpos = { 0,0 };

	bool Timeup = false;

	int score_tmp = 0;
};

