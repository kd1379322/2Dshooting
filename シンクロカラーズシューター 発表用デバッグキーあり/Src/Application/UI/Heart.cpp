#include "Heart.h"

void C_Heart::Init()
{
	m_tex.Load("Texture/player.png");

	animcnt = 0;
	Alpha = 1.0f;
	for(int i = 0;i<3;i++)
	{
		m_scale[i] = {0.8f,0.8f};
		m_pos[i].x = -600 + (i * 64);
		m_pos[i].y = 320;

	
		m_scaleMat[i] = Math::Matrix::CreateScale(m_scale[i].x, m_scale[i].y, 0);
		m_transMat[i] = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
		m_mat[i] = m_scaleMat[i] * m_transMat[i];
	}
}

void C_Heart::Update()
{
	if (Alpha <= 1.0f)
	{
		Alpha += 0.02f;
	}

	for (int i = 0;i < 3;i++)
	{
		m_scaleMat[i] = Math::Matrix::CreateScale(m_scale[i].x, m_scale[i].y, 0);
		m_transMat[i] = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
		m_mat[i] = m_scaleMat[i] * m_transMat[i];
	}
}

void C_Heart::Draw2D(int hp)
{

	Math::Rectangle rect;

	for (int i = 0; i < 3; i++)
	{
		if (i < hp)
		{
			// 満タンハート
			rect = { 0, 0, 64, 64 };
			SHADER.m_spriteShader.SetMatrix(m_mat[i]);
			SHADER.m_spriteShader.DrawTex(&m_tex, rect, Alpha);
		}
		else
		{
			// 空ハート
			//rect = { 32, 0, 13, 12 };
		}

	
	}

}

void C_Heart::DownAlpha(Math::Vector2 p_pos)
{
	const float x = (m_pos[1].x - p_pos.x) * 0.5f; // 横だけ縮める
	const float y = m_pos[1].y - p_pos.y;

	const float z = sqrt(x * x + y * y);

	if (z < 64)
	{
		Alpha = 0.1f;
	}

}

void C_Heart::Relese()
{
	m_tex.Release();
}
