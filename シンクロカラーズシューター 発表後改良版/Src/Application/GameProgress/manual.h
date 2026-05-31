#pragma once

class C_Manual
{
public:
	C_Manual(){}
	~C_Manual(){}

	void Init();
	void Update();
	void Draw();

private:
	void Relese();

	int i;

	bool RightKeyFlg;
	bool LeftKeyFlg;

	static const int page = 4;
	KdTexture m_pageTex[page];

	KdTexture m_t_Tex;

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列

	Math::Matrix m_mat;			//行列
	Math::Matrix m_lmat;			//行列
	Math::Matrix m_rmat;			//行列
	Math::Matrix m_tmat;			//行列

	float s_Alpha = 1.0f;
	float s_alphaAdd = -0.01f;
};
