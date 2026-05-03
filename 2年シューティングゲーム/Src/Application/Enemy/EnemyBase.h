#pragma once

class C_EnemyBase
{
public:
	C_EnemyBase(){}
	virtual ~C_EnemyBase(){}

	// 初期設定
	void Init();



	//出現処理
	void App();
	void PosApp(Math::Vector2 p_pos);

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D(int i);

	//ランダムな位置に出現
	float RandomApp();

	bool BulletHit(Math::Vector2 p_pos);


	bool GetMflg() { return Moveflg; }

	int CheckColor(int i,int j);

	bool CheckColor(int i);

	Math::Vector2 Getpos() { return m_pos; }

protected:

	void Release();		// 解放処理

	const float m_moveSpeed = -4.0f;	//移動速度

	const float ScreenTop = 360;
	const float ScreenBottom = -360;
	const float ScreenLeft = -640;
	const float ScreenRight = 640;

	const float Size = 64;

	bool Moveflg = false;		//行動用フラグ

	int anm = 0;

	KdTexture m_Tex;			//画像用	

	Math::Vector2 m_pos;		//座標

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_rotationMat;	//回転行列
	Math::Matrix m_mat;			//行列

	Math::Rectangle rect;	//切り取り範囲


};

