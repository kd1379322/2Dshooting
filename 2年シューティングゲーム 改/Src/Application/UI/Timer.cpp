#include "Timer.h"

void C_Timer::Init()
{
	m_tex.Load("Texture/Digit.png");
	m_totalTime = 120; // ← 2分（120秒）
	m_isFinish = false;
	m_frameCnt = 0;
}

void C_Timer::Update()
{
	if (m_isFinish) return;

	m_frameCnt++;

	// 60フレームで1秒減る（60FPS想定）
	if (m_frameCnt >= 60)
	{
		m_frameCnt = 0;

		if (m_totalTime > 0)
		{
			m_totalTime--;
		}
		else
		{
			m_totalTime = 0;
			m_isFinish = true;
		}
	}

	// 表示用に変換
	ConvertTime(m_totalTime);
	SetDigits();

	// 行列更新（そのままでOK）
	for (int i = 0; i < MAX_DIGITS; ++i)
	{
		m_pos[i].x = -380 + (i * 128*0.3f);
		m_pos[i].y = 320;
		Math::Matrix scale = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
		Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);

		m_mat[i] = scale * trans;
	}
}

//====================================
// 秒 → 分・秒
//====================================
void C_Timer::ConvertTime(int time)
{
	m_minutes = time / 60;
	m_seconds = time % 60;
}

//====================================
// 桁分解（mm:ss）
//====================================
void C_Timer::SetDigits()
{
	// 秒（下2桁）
	m_digits[4] = m_seconds % 10;
	m_digits[3] = m_seconds / 10;

	// 分（上2桁）
	m_digits[1] = m_minutes % 10;
	m_digits[0] = m_minutes / 10;

	// コロン位置
	m_digits[2] = -1;
}

//====================================
// 描画
//====================================
void C_Timer::Draw2D()
{
	for (int i = 0; i < MAX_DIGITS; ++i)
	{
		// コロン
		if (m_digits[i] == -1)
		{
			m_rect = { 128 * 10, 0, 128, 256 };
		}
		// 数字
		else if (m_digits[i] == 0)
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

void C_Timer::Release()
{
	m_tex.Release();
}