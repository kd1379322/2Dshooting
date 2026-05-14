#include "Backgraund.h"

void C_Backgraund::Init()
{
	m_backgroundTex.Load("Texture/pixelart_starfield.png");
	m_background2Tex.Load("Texture/image.png");
}

void C_Backgraund::Update()
{
	//==============================
	// 背景
	//==============================
	Backgroundpos.x -= 8;
	if (Backgroundpos.x < -640)
	{
		Backgroundpos.x = 640;
	}

	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_transMat = Math::Matrix::CreateTranslation(Backgroundpos.x, Backgroundpos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Backgraund::Draw(bool diff)
{
	Math::Rectangle rect = { 0, 0, 1280 * 2, 720 };

	// 行列のセット
	SHADER.m_spriteShader.SetMatrix(m_mat);

	// 背景描画
	if (diff)
	{
		SHADER.m_spriteShader.DrawTex(&m_background2Tex, rect, 1.0f);
	}
	else
	{
		SHADER.m_spriteShader.DrawTex(&m_backgroundTex, rect, 1.0f);
	}
}


void C_Backgraund::Release()
{
	m_backgroundTex.Release();
}
