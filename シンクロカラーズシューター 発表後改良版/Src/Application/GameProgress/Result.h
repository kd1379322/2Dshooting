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

	void SetScore(int s,int life);

	bool GetNextScene() {return	m_dispScore == m_score;}
private:
	void Release();		// 解放処理

	int m_score = 0;

	int f_life = 0;

	bool Bonusflg = false;

	int m_waitCnt = 0;   // 待機フレーム
	float t_Alpha = 0.0f;
	float t_alphaAdd = 0.01f;

	int Rk[3];

	KdTexture m_Resulttex;
	KdTexture m_r_Tex;			//画像用	

	KdTexture m_n_Tex;			//画像用	
	KdTexture m_t_Tex;			//画像用	

	Math::Vector2 m_pos;		//座標

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_rotationMat;	//回転行列
	Math::Matrix m_mat;			//行列

	Math::Matrix m_r_mat;		//行列
	Math::Matrix m_t_mat;		//行列
	Math::Matrix m_b_mat;		//行列

	// ===== 表示 =====
	static const int MAX_DIGITS = 7;
	int m_digits[MAX_DIGITS] = {};
	unsigned long m_dispScore = 0; 

	// ===== 描画関連 =====
	KdTexture m_numtex;
	Math::Rectangle m_rect;

	Math::Vector2 m_numpos[MAX_DIGITS] = {};
	Math::Matrix m_nummat[MAX_DIGITS];

	Math::Color color;

	float h_sc = 0.5f;
	float h_scAdd = -0.05f;

};

