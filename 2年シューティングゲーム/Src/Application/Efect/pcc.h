#pragma once

class C_pcc
{
public:
	C_pcc(){}
	~C_pcc() { Release(); }

	// 初期設定
	void Init(Math::Vector2 p_pos);

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D(int a);

private:
	void Release();		// 解放処理

	bool Moveflg = false;

	float alpha;

	KdTexture m_tex;

	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_rotationMat;	//回転行列
	Math::Matrix m_mat;			//行列

	Math::Vector2 m_pos;		//座標
	Math::Vector2 m_size;		//サイズ

	Math::Rectangle rect;	//切り取り範囲

};
