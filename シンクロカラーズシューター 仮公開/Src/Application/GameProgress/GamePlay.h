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

class C_damage;

class C_edmecut;

class C_Selectkey;

class C_Countdown;

class C_Text;

class C_GamePlay
{
public:
	C_GamePlay() {}
	~C_GamePlay() { Release(); }

	// 初期設定
	void Init();

	// 更新処理
	void Update(bool p_diff);

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	void EnemyApp(
		int p_RespawnNum,
		int p_dist,
		int p_CheckSec,
		std::vector<std::shared_ptr<C_EnemyBase>>& p_list);

	bool GetResultGo_T() { return NextScene; }

	int GetRastScore() { return score_tmp; }


	void Reset();

private:

	void Release();		// 解放処理

	void Circle(Math::Vector2 p_pos, int a);
	void Edmecut(Math::Vector2 p_pos);

	int m_waitCnt = 0;   // 待機フレーム
	int m_waitEndCnt = 0;   // 待機フレーム

	bool diff = false;

	bool Debug = false;

	int GameCnt;
	std::shared_ptr<C_Player> m_player = nullptr;

	std::vector<std::shared_ptr<C_EnemyBase>> m_enemyList;
	std::vector<std::shared_ptr<C_EnemyBase>> m_multi_enemyList;

	static const int cpyMax = 30;
	std::shared_ptr<C_EnemyBase> m_copyenemy[cpyMax] = {nullptr};

	std::shared_ptr<C_Heart> m_heart = nullptr;
	std::shared_ptr<C_Dying> m_dying = nullptr;
	std::shared_ptr<C_pcc> m_pcc = nullptr;
	std::shared_ptr<C_Timer>m_timer = nullptr;
	std::shared_ptr<C_Score>m_score = nullptr;
	std::shared_ptr<C_damage>m_damage = nullptr;
	std::shared_ptr<C_Selectkey>m_selectkey = nullptr;
	std::shared_ptr<C_Countdown>m_countdown = nullptr;
	std::shared_ptr<C_Text>m_text = nullptr;

	static const int efctMax = 15;
	std::shared_ptr<C_edmecut>m_edmecut[efctMax] = { nullptr };

	static const int CircleMax = 15;
	std::shared_ptr<C_Circle> m_circle[CircleMax] = { nullptr };


	static const int MaxBullet = 10;
	std::shared_ptr<C_Bullet> m_Bullet[MaxBullet];

	bool Bulletkeyflg = true;			//弾発射キーフラグ
	int BulletCnt = 0;
	Math::Color BulletColor;
	int BulletColorNumber = 1;

	Math::Vector2 Backgroundpos = { 0,0 };

	bool Timeup = false;
	bool NextScene = false;

	int score_tmp = 0;

	const float ScreenTop = 360 - 128;
	const float ScreenBottom = -360 + 128;
	const float ScreenLeft = -640;
	const float ScreenRight = 640;

	const float Size = 64;
};

