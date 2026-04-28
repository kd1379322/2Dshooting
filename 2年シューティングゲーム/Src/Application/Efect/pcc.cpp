#include "pcc.h"

void C_pcc::Init()
{
	m_tex.Load("Texture/pcc_transparent.png");

	m_size = { 2.0f,2.0f };
	Moveflg = false;
	alpha = 1.0f;

	m_scaleMat = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_pcc::Update()
{
	//if (!Moveflg)return;

	m_size += {0.01f,0.01f};
	//alpha -= 0.01f;

	if (alpha < 0.0f)
	{
		alpha == 0.0f;
		Moveflg = false;
	}

	m_scaleMat = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_pcc::Draw2D(int a)
{
	//if (!Moveflg)return;

	Math::Color color;
	switch (a)
	{
	case 1:
		color = { 1,0,0,alpha };
		break;
	case 2:
		color = { 0,0,1,alpha };
		break;
	case 3:
		color = { 1,1,0,alpha };
		break;
	default:
		color = { 1,0,0,alpha };
		break;
	}

	//プレイヤーの描画
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex_Color(&m_tex, rect, color);//画像の描画
}

void C_pcc::App(Math::Vector2 p_pos)
{
	m_pos = p_pos;
	Moveflg = true;
	alpha = 1.0f;
	m_size = { 2.0f,2.0f };
}

void C_pcc::Release()
{
	m_tex.Release();
}
