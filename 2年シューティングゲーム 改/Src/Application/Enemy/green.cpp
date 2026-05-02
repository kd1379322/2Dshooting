#include "green.h"

void C_Green::Init()
{
	m_Tex.Load("Texture/enemy.png");

	color = { 0,1,0,1 };		//緑

	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Green::Update()
{
	if (!Moveflg)return;

	m_pos.x += m_moveSpeedX;
	m_pos.y += sinf(anm * 0.1f) * 10.0f;

	if (m_pos.x < ScreenLeft - Size)
	{
		Moveflg = false;
	}

	anm++;
	if (anm == 30) {
		rect = { 64,0,64,64 };
	}
	else if (anm == 60)
	{
		anm = 0;
		rect = { 0,0,64,64 };
	}

	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Green::Draw2D()
{
	if (!Moveflg)return;

	//プレイヤーの描画
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex_Color(&m_Tex, rect, color);//画像の描画
}

int C_Green::CheckColor(int i)
{
	if (i == 2)
	{
		Moveflg = false;
		return 3;
	}
	else if (i == 3)
	{
		Moveflg = false;
		return 2;
	}
	else
	{
		return 0;
	}
}

