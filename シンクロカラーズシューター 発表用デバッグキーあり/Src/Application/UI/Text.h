#pragma once

class C_Text
{
public:
	C_Text(){}
	~C_Text() { Release(); }

	void Init();            // 初期化
	void Update();			// 秒を受け取る
	void Draw2D();          // 描画

	void Limit30();
	void Limit60();

	void TimeUpApp();
	void GameoverApp();

	void RemStamina1();

private:
	void Release();

	int cnt = 0;

	int type = 0;

	int blinkCnt = 0;   // 点滅用カウンタ

	float Alpha = 0.0f;

	bool Moveflg = false;

	bool isFading = false;  // フェード中かどうか

	Math::Rectangle rect = { 0,0,80,150 };

	Math::Vector2 m_pos = { 0,0 };
	Math::Vector2 m_scale = { 1.0f,1.0f };
	Math::Matrix m_scaleMat;	//拡大行列
	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_mat;
	KdTexture m_tex;			//画像用	

};
