#pragma once

class C_EfectBase
{
public:
	C_EfectBase(){}
	virtual ~C_EfectBase() { Release(); }

	virtual void Init();

	virtual void Update();

	virtual void Draw();

	virtual void App(Math::Vector2 p_pos);
	
	bool GetMflg() { return Moveflg; }

protected:

	virtual void Release();		// 解放処理

	bool Moveflg = false;

	int anm = 0;

	float alpha = 1.0f;

	KdTexture m_tex;

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_rotationMat;	//回転行列
	Math::Matrix m_mat;			//行列

	Math::Vector2 m_pos = {0,0};		//座標
	Math::Vector2 m_size = {1,1};		//サイズ

	Math::Rectangle rect;	//切り取り範囲

};

