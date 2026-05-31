#include "Selectkey.h"

void C_Selectkey::Init()
{
	m_tex.Load("Texture/key.png");
	m_scale = { 0.3f,0.3f };
	m_pos = { -390,-320 };
	Alpha = 1.0f;
}

void C_Selectkey::Update()
{
	if (Alpha <= 1.0f)
	{
		Alpha += 0.02f;
	}

	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Selectkey::Draw()
{
	Math::Rectangle rect = { 0,0,1600,186 };

	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_tex, rect, Alpha);//画像の描画
}

void C_Selectkey::DownAlpha(Math::Vector2 p_pos)
{
	const float x = (m_pos.x - p_pos.x) * 0.5f; // 横だけ縮める
	const float y = m_pos.y - p_pos.y;

	const float z = sqrt(x * x + y * y);

	if (z < 128)
	{
		Alpha = 0.1f;
	}
	

}

void C_Selectkey::Relese()
{
	m_tex.Release();
}
