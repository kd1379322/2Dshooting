#include "Countdown.h"

void C_Countdown::Init()
{
	m_tex.Load("Texture/Countdown.png");
	Moveflg = false;
	Prerep = false;
	Alpha = 0.0f;
	cnt = 0;
	e_cnt = 0;
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Countdown::Update()
{
	if (!Moveflg)return;

	if(Prerep)
	{
		e_cnt++;
		if (e_cnt >= 60) {
			e_cnt = 0;
			Prerep = false;
		}
	}

	m_scale += {0.1f,0.1f};
	Alpha -= 0.03f;
	if (Alpha <= 0.0f)
	{
		Alpha = 0.0f;
		Moveflg = false;
	}

	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Countdown::Draw2D()
{
	if (!Moveflg)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_tex, rect, Alpha);//画像の描画
}

void C_Countdown::App()
{
	Alpha = 1.0f;
	m_scale = { 3,3 };

	

	switch (cnt)
	{
	case 0:
		cnt++;
		rect = { 0,0,80,150 };
		Moveflg = true;
		m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
		m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		m_mat = m_scaleMat * m_transMat;
		break;
	case 1:
		cnt++;
		rect = { 170,0,80,150 };
		Moveflg = true;
		m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
		m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		m_mat = m_scaleMat * m_transMat;
		break;
	case 2:
		cnt++;
		rect = { 340,0,90,150 };
		Moveflg = true;
		m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
		m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		m_mat = m_scaleMat * m_transMat;
		break;
	case 3:
		cnt++;
		rect = { 510,0,425,150 };
		Moveflg = true;
		m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
		m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
		m_mat = m_scaleMat * m_transMat;
		break;
	default:
		break;
	}
}

void C_Countdown::E_App(int i)
{
	if(!Prerep)
	{
		e_cnt = 0;
		Alpha = 1.0f;
		m_scale = { 1,1 };
		Prerep = true;
	}

	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;


	switch (i)
	{	
	case 1:
		rect = { 340,0,90,150 };
		Moveflg = true;
		break;
	case 2:
		rect = { 170,0,80,150 };
		Moveflg = true;
		break;
	case 3:
		rect = { 0,0,80,150 };
		Moveflg = true;
		break;
	default:
		break;
	}
}

void C_Countdown::Release()
{
	m_tex.Release();
}
