#pragma once

class C_Text
{
public:
	C_Text(){}
	~C_Text() { Release(); }

	void Init();            // 初期化
	void Update();			// 秒を受け取る
	void Draw2D();          // 描画

	void TimeUpApp();

private:
	void Release();

	int cnt = 0;

	int type = 0;

	float Alpha = 0.0f;

	bool Moveflg = false;

	Math::Rectangle rect = { 0,0,80,150 };

	Math::Vector2 m_pos = { 0,0 };
	Math::Vector2 m_scale = { 1.0f,1.0f };
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_mat;
	KdTexture m_tex;			//画像用	

};
