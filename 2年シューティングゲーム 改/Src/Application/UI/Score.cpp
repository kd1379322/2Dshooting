#include "Score.h"

void C_Score::Init()
{
	m_tex.Load("Texture/Digit.png");
	m_score = 0;
	m_combo = 0;
	m_comboflg = false;
}

void C_Score::Update()
{
	if (m_comboflg)
	{
		m_combo_cnt++;
		if (m_combo_cnt >= 180)
		{
			m_combo = 0;
			m_comboflg = false;
		}
	}

	unsigned long tmp = m_score;

	for (int i = MAX_DIGITS - 1; i >= 0; --i)
	{
		// 下位の桁から抽出し、配列に格納
		m_digits[i] = tmp % 10;
		tmp /= 10;
	}

	// 行列更新（そのままでOK）
	for (int i = 0; i < MAX_DIGITS; ++i)
	{
		m_pos[i].x = 260 + (i * 128 * 0.3f);
		m_pos[i].y = 320;
		Math::Matrix scale = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
		Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);

		m_mat[i] = scale * trans;
	}
}

void C_Score::Draw2D()
{

	for (int i = 0; i < MAX_DIGITS; ++i)
	{		
		// 数字
		if (m_digits[i] == 0)
		{
			m_rect = { 128 * 9, 0, 128, 256 };
		}
		else
		{
			m_rect = { 128 * (m_digits[i] - 1), 0, 128, 256 };
		}

		SHADER.m_spriteShader.SetMatrix(m_mat[i]);
		SHADER.m_spriteShader.DrawTex(&m_tex, m_rect, 1.0f);
	}
}

void C_Score::ScoreUp()
{
	if(m_combo < 5)
	{
		m_score += 100;
	}
	else if (m_combo < 10)
	{
		m_score += 300;
	}
	else if (m_combo < 20)
	{
		m_score += 500;
	}
	else if (m_combo >= 20)
	{
		m_score += 1000;
	}

	m_combo++;
	m_combo_cnt = 0;
	m_comboflg = true;
}

void C_Score::Release()
{
	m_tex.Release();
}
