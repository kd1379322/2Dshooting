#pragma once

class C_Result
{
public:
	C_Result(){}
	~C_Result() { Release(); }

	void Init();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	void SetScore(int s) { m_score = s; }
private:
	void Release();		// 解放処理

	int m_score = 0;
	int m_waitCnt = 0;   // 待機フレーム

	KdTexture m_Resulttex;
	KdTexture m_r_Tex;			//画像用	
	KdTexture m_b_Tex;			//画像用	
	KdTexture m_n_Tex;			//画像用	

	Math::Vector2 m_pos;		//座標

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_rotationMat;	//回転行列
	Math::Matrix m_mat;			//行列
	Math::Matrix m_b_mat;		//行列
	Math::Matrix m_r_mat;		//行列

	// ===== 表示 =====
	static const int MAX_DIGITS = 10;
	int m_digits[MAX_DIGITS] = {};
	unsigned long m_dispScore = 0; 

	// ===== 描画関連 =====
	KdTexture m_numtex;
	Math::Rectangle m_rect;

	Math::Vector2 m_numpos[MAX_DIGITS] = {};
	Math::Matrix m_nummat[MAX_DIGITS];

	Math::Color color;

	Math::Vector2 Backgroundpos = { 0,0 };
};

