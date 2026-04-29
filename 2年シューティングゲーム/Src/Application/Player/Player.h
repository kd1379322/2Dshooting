#pragma once

class C_Player
{
public:
	C_Player(){}
	~C_Player() {}

	// 初期設定
	void Init();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D(int i);

	// GUI処理
	void ImGuiUpdate();

	Math::Vector2 Getpos() { return m_pos; }
	
	bool GetMflg() { return Moveflg; }

	//void SetTex(KdTexture* tex) { m_PlayerTex = tex; }

	bool EnemyHit(Math::Vector2 p_pos);
private:

	const float m_moveSpeed = 16.0f;	//移動速度

	const float ScreenTop = 360;	
	const float ScreenBottom = -360;	
	const float ScreenLeft = -640;	
	const float ScreenRight = 640;	

	const float PlayerSize = 32;	
	
	bool Moveflg = true;					//行動用フラグ

	bool DamegeIframes = false;
	int DamegeIframesCnt = 0;

	float playerAlpha = 1.0f;
	int Hp = MHp;						//HP
	static const int MHp = 3;	//HPの最大値

	KdTexture m_Tex;			//画像用	

	Math::Vector2 m_pos;		//座標

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_rotationMat;	//回転行列
	Math::Matrix m_mat;			//プレイヤー行列

	Math::Rectangle rect;	//プレイヤー切り取り範囲


};

