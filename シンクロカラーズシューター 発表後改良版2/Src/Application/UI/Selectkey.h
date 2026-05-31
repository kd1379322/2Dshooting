#pragma once

class C_Selectkey
{
public:
	C_Selectkey(){}
	~C_Selectkey() { Relese(); }

	void Init();
	void Update();
	void Draw();

	void DownAlpha(Math::Vector2 p_pos);

private:
	void Relese();

	float Alpha = 1.0f;

	Math::Vector2 m_pos;
	Math::Vector2 m_scale;
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_mat;
	KdTexture m_tex;			//画像用	
};

