#include "Mosaic.h"

void C_Mosaic::Init()
{
	m_tex.Load("Texture/Mosaic.png");
	m_pos = { 0,0 };
	m_scale = { 1,1 };
	Alpha = 1.0f;
	flg = true;
	MaxAlpha = true;
	MinAlpha = false;
}

void C_Mosaic::Update()
{
	if (flg)
	{
		if (Alpha < 1.0f)
		{
			Alpha += 0.02f;
		}

	}
	else 
	{
		if (Alpha > 0.0f)
		{
			Alpha -= 0.02f;
		}
	}

	if (Alpha >= 1.0f) {
		MaxAlpha = true;
	}
	else {
		MaxAlpha = false;
	}
	
	if (Alpha <= 0.0f) {
		MinAlpha = true;
	}
	else
	{
		MinAlpha = false;
	}

	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Mosaic::Draw()
{
	
	Math::Rectangle rect = { 0,0,1280,720 };
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_tex, rect, Alpha);//画像の描画
}

void C_Mosaic::Up()
{
	flg = true;
}

void C_Mosaic::Down()
{
	flg = false;
}

void C_Mosaic::Release()
{
	m_tex.Release();
}
