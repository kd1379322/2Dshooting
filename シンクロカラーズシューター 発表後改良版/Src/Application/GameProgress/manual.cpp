#include "manual.h"
#include"../Sound/Sound.h"

void C_Manual::Init()
{
	m_pageTex[0].Load("Texture/manual/page1_.png");
	m_pageTex[1].Load("Texture/manual/page2_.png");
	m_pageTex[2].Load("Texture/manual/page3_.png");
	m_pageTex[3].Load("Texture/manual/page4_.png");

	m_t_Tex.Load("Texture/Text_.png");

	i = 0;

	RightKeyFlg = false;
	LeftKeyFlg = false;
}

void C_Manual::Update()
{

	s_Alpha += s_alphaAdd;

	if (s_Alpha < 0.3f)
	{
		s_Alpha = 0.3f;
		s_alphaAdd *= -1;
	}
	else if (s_Alpha > 1.0f)
	{
		s_Alpha = 1.0f;
		s_alphaAdd *= -1;
	}

	//==============================
	// 右キーで次のページ
	//==============================
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (!RightKeyFlg)
		{
			i++;

			// 最大ページ制限
			if (i > 3)
			{
				i = 3;
			}
			else
			{
				SOUND.DecisionSound_SE();
			}

			RightKeyFlg = true;
		}
	}
	else
	{
		RightKeyFlg = false;
	}

	//==============================
	// 左キーで前のページ
	//==============================
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (!LeftKeyFlg)
		{
			i--;

			// 最小ページ制限
			if (i < 0)
			{
				i = 0;
			}
			else
			{
				SOUND.DecisionSound_SE();
			}

			LeftKeyFlg = true;
		}
	}
	else
	{
		LeftKeyFlg = false;
	}

	m_scaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 0);
	m_transMat = Math::Matrix::CreateTranslation(0, 50, 0);
	m_mat = m_scaleMat * m_transMat;

	m_scaleMat = Math::Matrix::CreateScale(0.6f, 0.6f, 0);

	m_transMat = Math::Matrix::CreateTranslation(450, -300, 0);
	m_rmat = m_scaleMat * m_transMat;
	
	m_transMat = Math::Matrix::CreateTranslation(-450, -300, 0);
	m_lmat = m_scaleMat * m_transMat;
	
	m_transMat = Math::Matrix::CreateTranslation(5, -300, 0);
	m_tmat = m_scaleMat * m_transMat;



}

void C_Manual::Draw()
{
	Math::Rectangle rect = { 0,0,1280,720 };

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_pageTex[i], rect, 1.0f);

	if(i != 3)
	{
		rect = { 360,1370,560,100 };
		SHADER.m_spriteShader.SetMatrix(m_rmat);
		SHADER.m_spriteShader.DrawTex(&m_t_Tex, rect, 1.0f);
	}

	if(i != 0)
	{
		rect = { 360,1500,560,100 };
		SHADER.m_spriteShader.SetMatrix(m_lmat);
		SHADER.m_spriteShader.DrawTex(&m_t_Tex, rect, 1.0f);
	}

	rect = { 0,620,1280,100 };
	SHADER.m_spriteShader.SetMatrix(m_tmat);
	SHADER.m_spriteShader.DrawTex(&m_t_Tex, rect, s_Alpha);
}

void C_Manual::Relese()
{
	for(auto& a:m_pageTex)
	{
		a.Release();
	}

	m_t_Tex.Release();
}
