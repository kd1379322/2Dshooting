#include "radar.h"

void C_radar::Init()
{
	m_tex.Load("Texture/Circle.png");

	m_pos = { 0,0 };
	m_size = { 1.0f,1.0f };
	Moveflg = false;
	alpha = 1.0f;
	color = { 1,1,1,alpha };
	rect = { 0,0,64,64 };

	m_colorTime = 0.0f;  
}

void C_radar::Update()
{
	if (!Moveflg)return;

	m_size += { 0.8f, 0.8f };
	alpha -= 0.05f;

	// 虹色変化
	m_colorTime += 0.5f;

	float r = (sinf(m_colorTime) + 1.0f) * 0.5f;
	float g = (sinf(m_colorTime + 2.094f) + 1.0f) * 0.5f; // 120度ずらす
	float b = (sinf(m_colorTime + 4.188f) + 1.0f) * 0.5f; // 240度ずらす

	color = { r, g, b, alpha };

	if (alpha < 0.0f)
	{
		alpha = 0.0f;  
		m_size = { 0,0 };
		Moveflg = false;
	}

	m_scaleMat = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_radar::Draw2D()
{
	if (!Moveflg)return;

	color.A(alpha);

	D3D.SetBlendState(BlendMode::Add);

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex_Color(&m_tex, rect, color);

	D3D.SetBlendState(BlendMode::Alpha);
}

void C_radar::App(Math::Vector2 p_pos)
{
	m_pos = p_pos;
	Moveflg = true;
	alpha = 1.0f;
	m_size = { 1.0f,1.0f };

	m_colorTime = 0.0f;   // 色変化リセット
}

void C_radar::Release()
{
	m_tex.Release();
}