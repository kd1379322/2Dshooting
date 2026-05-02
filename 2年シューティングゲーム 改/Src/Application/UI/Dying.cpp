#include "dying.h"

void C_Dying::InitDying()
{
	m_tex.Load("Texture/Dying.png");
	m_pos = { 0,0 };
	m_scale = { 1,1 };
	Alpha = 1.0f;
	tenmetuflg = false;
}

void C_Dying::UpdateDying()
{
	if (Alpha == 1.0f)
	{
		tenmetuflg = false;
	}

	if (Alpha <= 0.3f)
	{
		tenmetuflg = true;
	}

	if (tenmetuflg)
	{
		Alpha += 0.01f;
		if (Alpha > 1.0f)Alpha == 1.0f;
	}
	else
	{
		Alpha -= 0.01f;
		if (Alpha < 0.3f)Alpha == 0.3f;
	}
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Dying::DrawDying()
{

	D3D.SetBlendState(BlendMode::Add);	//‰ÁŽZ‡¬

	Math::Rectangle rect = { 0,0,1280,720 };
	SHADER.m_spriteShader.SetMatrix(m_mat);//s—ñ‚ÌƒZƒbƒg
	SHADER.m_spriteShader.DrawTex(&m_tex, rect, Alpha);//‰æ‘œ‚Ì•`‰æ

	D3D.SetBlendState(BlendMode::Alpha);	//”¼“§–¾
}
