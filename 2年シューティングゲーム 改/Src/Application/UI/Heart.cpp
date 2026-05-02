#include "Heart.h"

void C_Heart::Init()
{
	m_tex.Load("Texture/Heart.png");

	animcnt = 0;
	
	for(int i = 0;i<3;i++)
	{
		m_scale[i] = {4,4};
		m_pos[i].x = -600 + (i * 64);
		m_pos[i].y = 320;

	
		m_scaleMat[i] = Math::Matrix::CreateScale(m_scale[i].x, m_scale[i].y, 0);
		m_transMat[i] = Math::Matrix::CreateTranslation(m_pos[i].x, m_pos[i].y, 0);
		m_mat[i] = m_scaleMat[i] * m_transMat[i];
	}
}

void C_Heart::Update()
{
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
			rect = { 0, 0, 13, 12 };

		}
		else
		{
			// 空ハート
			rect = { 32, 0, 13, 12 };
		}

		SHADER.m_spriteShader.SetMatrix(m_mat[i]);
		SHADER.m_spriteShader.DrawTex(&m_tex, rect, 1.0f);
	}

}