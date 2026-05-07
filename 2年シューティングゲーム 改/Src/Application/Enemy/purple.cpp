#include "Purple.h"

void C_Purple::Init()
{
	m_Tex.Load("Texture/enemy.png");

	color = { 1,0,1,1 };		//紫

	Moveflg = false;

	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Purple::Update()
{
	if (!Moveflg)return;

	

	if (anm % 60 == 0)
	{
		

	}

	Math::Vector2 enemyMove = m_playerpos - m_pos;
	enemyMove.Normalize();
	m_pos.y += enemyMove.y * m_moveSpeedY;
	m_pos.x += m_moveSpeedX;

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

void C_Purple::Draw2D()
{
	if (!Moveflg)return;

	//プレイヤーの描画
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex_Color(&m_Tex, rect, color);//画像の描画
}

int C_Purple::CheckColor(int i)
{
	if (i == 1)
	{
		return 2;
	}
	else if(i == 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

