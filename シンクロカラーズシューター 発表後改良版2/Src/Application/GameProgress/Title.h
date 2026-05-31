#pragma once

class C_Title
{
public:
	C_Title(){}
	~C_Title() { Release(); }

	// 初期設定
	void Init();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D(bool diff);
private:
	void Release();		// 解放処理


	KdTexture m_Titletex;
	KdTexture m_Tex;			//画像用	

	KdTexture m_s_Tex;			//画像用	
	KdTexture m_t_Tex;			//画像用	

	Math::Vector2 m_pos;		//座標

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_rotationMat;	//回転行列
	Math::Matrix m_mat;			//行列

	Math::Matrix m_s_mat;		//
	Math::Matrix m_t_mat;		//
	Math::Matrix m_h_mat;		//


	Math::Rectangle rect;	//切り取り範囲

	Math::Color color;

	
	float h_sc = 1.0f;
	float h_scAdd = -0.05f;

	float s_Alpha = 1.0f;
	float s_alphaAdd = -0.01f;
	
	int anm = 0;

};

