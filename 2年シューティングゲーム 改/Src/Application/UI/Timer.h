#pragma once

class C_Timer
{
public:
	C_Timer() {}
	~C_Timer() { Release(); }

	void Init();            // 初期化
	void Update();			// 秒を受け取る
	void Draw2D();          // 描画

	bool GetFinish() { return m_isFinish; }

private:

	void Release();

	// ===== 時間 =====
	int m_minutes = 0;
	int m_seconds = 0;

	int m_totalTime = 0;   // 残り時間（秒）
	int m_frameCnt = 0;    // フレームカウント
	bool m_isFinish = false;


	// ===== 表示 =====
	static const int MAX_DIGITS = 5; // mm:ss
	int m_digits[MAX_DIGITS] = {};

	// ===== 描画関連 =====
	KdTexture m_tex;
	Math::Rectangle m_rect;

	Math::Vector2 m_pos[MAX_DIGITS] = {};
	Math::Matrix m_mat[MAX_DIGITS];

	Math::Vector2 m_scale = { 0.3f,0.3f };

	// ===== 内部処理 =====
	void ConvertTime(int time);
	void SetDigits();
};