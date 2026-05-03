#include "Result.h"
#include <algorithm>

void C_Result::Init()
{
	m_Resulttex.Load("Texture/Result.png");
	m_b_Tex.Load("Texture/pixelart_starfield.png");
	m_numtex.Load("Texture/Digit.png");
	m_r_Tex.Load("Texture/Rank__.png");
	m_pos = { 0,100 };
	m_dispScore = 0;
}

void C_Result::Update()
{
	

	Backgroundpos.x -= 8;
	if (Backgroundpos.x < -640)
	{
		Backgroundpos.x = 640;
	}

	// --- 2秒待機（60FPS想定） ---
	if (m_waitCnt < 60)
	{
		m_waitCnt++;
	}
	else
	{
		// --- SPACEでスキップ ---
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_dispScore = m_score;
		}

		// --- カウントアップ ---
		if (m_dispScore < m_score)
		{
			int add = (m_score - m_dispScore) / 10;

			if (add < 100)
			{
				add = 100;
			}

			m_dispScore += add;

			if (m_dispScore > m_score)
			{
				m_dispScore = m_score;
			}
		}
	}

	unsigned long tmp = m_dispScore;

	for (int i = MAX_DIGITS - 1; i >= 0; --i)
	{
		// 下位の桁から抽出し、配列に格納
		m_digits[i] = tmp % 10;
		tmp /= 10;
	}

	// 行列更新（そのままでOK）
	for (int i = 0; i < MAX_DIGITS; ++i)
	{
		m_numpos[i].x = -80 + (i * 128 * 0.3f);
		m_numpos[i].y = 125;
		Math::Matrix scale = Math::Matrix::CreateScale(0.3f, 0.3f, 1);
		Math::Matrix trans = Math::Matrix::CreateTranslation(m_numpos[i].x, m_numpos[i].y, 0);

		m_nummat[i] = scale * trans;
	}

	m_scaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 0);
	m_transMat = Math::Matrix::CreateTranslation(Backgroundpos.x, Backgroundpos.y, 0);
	m_b_mat = m_scaleMat * m_transMat;

	m_scaleMat = Math::Matrix::CreateScale(0.5f, 0.5f, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;

	m_scaleMat = Math::Matrix::CreateScale(0.4f, 0.4f, 0);
	m_transMat = Math::Matrix::CreateTranslation(20, 40, 0);
	m_r_mat = m_scaleMat * m_transMat;
}

void C_Result::Draw2D()
{
	Math::Rectangle rect;
	rect = { 0, 0, 1280 * 2, 720 };

	SHADER.m_spriteShader.SetMatrix(m_b_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_b_Tex, rect, 1.0f);//画像の描画

	rect = { 0,0,1774,887 };

	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_Resulttex, rect, 1.0f);//画像の描画

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

		SHADER.m_spriteShader.SetMatrix(m_nummat[i]);
		SHADER.m_spriteShader.DrawTex(&m_numtex, m_rect, 1.0f);
	}

	rect = {0,0,300,234};

	SHADER.m_spriteShader.SetMatrix(m_r_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_r_Tex, rect, 1.0f);//画像の描画
}

void C_Result::Release()
{
	m_Resulttex.Release();
	m_b_Tex.Release();
	m_numtex.Release();

}
