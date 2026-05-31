#pragma once

class C_Backgraund
{
public:
	C_Backgraund(){}
	~C_Backgraund() { Release(); }

	void Init();
	void Update();
	void Draw(bool diff);

private:
	void Release();

	KdTexture m_backgroundTex;
	KdTexture m_background2Tex;

	Math::Vector2 Backgroundpos = { 0,0 };

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_rotationMat;	//回転行列
	Math::Matrix m_mat;			//行列
};

