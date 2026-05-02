#pragma once

class C_Heart
{
public:
	C_Heart(){}
	~C_Heart(){}

	void Init();
	void Update();
	void Draw2D(int hp);

private:

	int animcnt;				//アニメーション用
	int movecnt;				//移動用
	bool Moveflg;				//行動フラグ

	KdTexture m_tex;			//画像行列
	Math::Vector2 m_pos[3];		//座標
	Math::Vector2 m_scale[3];		//大きさ
	Math::Matrix m_scaleMat[3];	//拡大行列
	Math::Matrix m_transMat[3];	//移動行列
	Math::Matrix m_mat[3];			//敵行列

};
