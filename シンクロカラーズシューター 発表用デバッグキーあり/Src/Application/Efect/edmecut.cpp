#include "edmecut.h"

void C_edmecut::Init()
{
	m_tex.Load("Texture/Effect_Impact_1_305x383.png");
	m_pos = { 0,0 };
	m_size = { 0.3f,0.3f };
	Moveflg = false;
	alpha = 1.0f;
	rect = { 0,0,108,116 };
	// 行列
	m_scaleMat = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_edmecut::Update()
{
	if (!Moveflg)return;

	anm++;

	// フレーム番号
	int frame = anm;

	if (frame >= FRAME_MAX)
	{
		anm = 0;
		Moveflg = false;
		return;
	}

	int col = frame % FRAME_COL;
	int row = frame / FRAME_COL;

	rect = Math::Rectangle(
		col * FRAME_W,
		row * FRAME_H,
		FRAME_W,
		FRAME_H
	);

	// 行列
	m_scaleMat = Math::Matrix::CreateScale(m_size.x, m_size.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_edmecut::Draw()
{
	if (!Moveflg)return;

	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_tex, rect);//画像の描画
}

void C_edmecut::App(Math::Vector2 p_pos)
{
	if (!Moveflg)
	{
		m_pos = p_pos;
		anm = 0;
		Moveflg = true;
	}
}

void C_edmecut::Release()
{
	m_tex.Release();
}
