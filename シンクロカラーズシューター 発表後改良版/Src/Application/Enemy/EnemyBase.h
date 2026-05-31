#pragma once

enum Color_code
{
	Red,
	Blue,
	Yellow,
	Null
};

class C_EnemyBase
{
public:
	C_EnemyBase(){}
	virtual ~C_EnemyBase(){}

	// 初期設定
	virtual void Init();



	//出現処理
	void App(const std::vector<std::shared_ptr<C_EnemyBase>>& p_list);
	void PosApp(Math::Vector2 p_pos);


	// 更新処理
	virtual void Update();

	// 描画処理
	virtual void Draw2D();

	//ランダムな位置に出現
	float RandomApp(const std::vector<std::shared_ptr<C_EnemyBase>>& p_list);

	bool BulletHit(Math::Vector2 p_pos);


	bool GetMflg() { return Moveflg; }

	//int CheckColor(int i,int j);

	virtual int CheckColor(int i);

	Math::Vector2 Getpos() { return m_pos; }

	void Kill();

	void SetPpos(Math::Vector2 p_pos) { m_playerpos = p_pos; }

	void ColorApp();

	Color_code GetCode() { return code; }

protected:

	void Release();		// 解放処理

	void Knockback();

	Color_code code = Null;

	const float m_moveSpeed = -2.0f;	//移動速度

	const float ScreenTop = 360 - 128;
	const float ScreenBottom = -360 + 128;
	const float ScreenLeft = -640;
	const float ScreenRight = 640;

	const float Size = 64;

	bool Moveflg = false;		//行動用フラグ
	bool Colorflg = false;		//行動用フラグ

	int anm = 0;

	KdTexture m_Tex;			//画像用	

	Math::Vector2 m_pos = {704,0};		//座標
	Math::Vector2 m_playerpos = {0,0};		//座標

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_rotationMat;	//回転行列
	Math::Matrix m_mat;			//行列

	Math::Rectangle rect;	//切り取り範囲

	Math::Color color;
	Math::Color O_color;

	float KnockBackX = 40.0f;
	bool KnockBackflg = false;
};

