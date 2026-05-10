#include "pcc.h"

void C_pcc::Init()
{
	m_tex.Load("Texture/pcc.png");

	m_pos = { 0,0 };
	m_size = { 1.0f,1.0f };
	Moveflg = false;
	alpha = 1.0f;
	color = { 1,0,0,alpha };
	rect = { 0,0,64,64 };
}

void C_pcc::Update()
{
	if (!Moveflg)return;

	m_size += {0.5f,0.5f};
	alpha -= 0.05f;

	if (alpha < 0.0f)
	{
		alpha == 0.0f;
		Moveflg = false;
	}

	m_scaleMat = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_pcc::Draw2D()
{
	if (!Moveflg)return;

	//if (!Moveflg)return;
	color.A(alpha);

	D3D.SetBlendState(BlendMode::Add);	//加算合成

	//プレイヤーの描画
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex_Color(&m_tex, rect, color);//画像の描画

	D3D.SetBlendState(BlendMode::Alpha);	//半透明
}

void C_pcc::App(Math::Vector2 p_pos,int a)
{
	m_pos = p_pos;
	Moveflg = true;
	alpha = 1.0f;
	m_size = { 1.0f,1.0f };

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

}

void C_pcc::Release()
{
	m_tex.Release();
}
