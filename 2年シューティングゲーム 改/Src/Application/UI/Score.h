#pragma once

class C_Score
{
public:
	C_Score(){}
	~C_Score() { Release(); }

	void Init();            // 初期化
	void Update();			// 更新
	void Draw2D();          // 描画

	void ScoreUp();
	int GetScore() { return m_score; }
	int GetCombo() { return m_combo; }
private:
	void Release();

	int m_score = 0;
	int m_combo = 0;

	int m_combo_cnt = 0;

	bool m_comboflg = false;

	// ===== 表示 =====
	static const int MAX_DIGITS = 10; 
	int m_digits[MAX_DIGITS] = {};

	// ===== 描画関連 =====
	KdTexture m_tex;
	Math::Rectangle m_rect;

	Math::Vector2 m_pos[MAX_DIGITS] = {};
	Math::Matrix m_mat[MAX_DIGITS];

	Math::Vector2 m_scale = { 0.3f,0.3f };

};

