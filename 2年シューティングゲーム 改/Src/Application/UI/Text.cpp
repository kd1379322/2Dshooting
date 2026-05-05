#include "Text.h"

void C_Text::Init()
{
	m_tex.Load("Texture/Text_.png");
	Moveflg = false;
	Alpha = 0.0f;
	cnt = 0;
	type = 0;
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Text::Update()
{
	if (!Moveflg)return;

	if (type == 0)
	{

	}
	else
	{
		Alpha -= 0.005f;
		
	}

	if (Alpha <= 0.0f)
	{
		Moveflg = false;
	}

	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Text::Draw2D()
{
	if (!Moveflg)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_tex, rect, Alpha);//画像の描画
}

void C_Text::TimeUpApp()
{
	rect = {0,740,1280,190};
	Alpha = 1.0f;
	type = 0;
	Moveflg = true;
}


void C_Text::Release()
{
	m_tex.Release();
}
