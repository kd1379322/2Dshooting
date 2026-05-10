#pragma once

class C_Bullet
{
public:
	C_Bullet(){}
	~C_Bullet() { Release(); }

	// 初期設定
	void Init();

	void App(Math::Vector2 p_pos,int p_bcn);

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	int Getbcn(){ return bcn; }

	bool GetMflg() { return Moveflg; }

	Math::Vector2 Getpos() { return m_pos; }

	void HitEnemy() { Moveflg = false; }
private:

	// 解放
	void Release();

	const float m_moveSpeed = 32.0f;	//移動速度

	const float ScreenTop = 360;
	const float ScreenBottom = -360;
	const float ScreenLeft = -640;
	const float ScreenRight = 640;

	const float Size = 64;

	int bcn = 1;

	bool Moveflg;					//行動用フラグ

	KdTexture m_Tex;			//画像用	

	Math::Vector2 m_pos;		//座標

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_rotationMat;	//回転行列
	Math::Matrix m_mat;			//プレイヤー行列

	Math::Rectangle rect;	//プレイヤー切り取り範囲

	Math::Color color;

};

