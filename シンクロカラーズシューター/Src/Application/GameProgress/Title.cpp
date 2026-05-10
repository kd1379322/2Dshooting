#include "Title.h"

void C_Title::Init()
{
	m_Tex.Load("Texture/Title.png");
	m_s_Tex.Load("Texture/Spacekey_.png");
	m_t_Tex.Load("Texture/Text_.png");

	m_pos = { 0,100 };
	m_scaleMat = Math::Matrix::CreateScale(0.7f, 0.7f, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Title::Update()
{
	anm++;

	
	m_pos.y += sinf(anm * 0.1f) * 3.0f;


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

	h_sc += h_scAdd;

	if (h_sc < 1.0f)
	{
		h_sc = 1.0f;
		h_scAdd *= -1;
	}
	else if (h_sc > 2.0f)
	{
		h_sc = 2.0f;
		h_scAdd *= -1;
	}

	m_scaleMat = Math::Matrix::CreateScale(0.7f, 0.7f, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
	
	m_scaleMat = Math::Matrix::CreateScale(0.5f, 0.5f, 0);
	m_transMat = Math::Matrix::CreateTranslation(0, -250, 0);
	m_s_mat = m_scaleMat * m_transMat;


	m_scaleMat = Math::Matrix::CreateScale(0.5f, 0.5f, 0);
	m_transMat = Math::Matrix::CreateTranslation(-500, 280, 0);
	m_t_mat = m_scaleMat * m_transMat;

	m_scaleMat = Math::Matrix::CreateScale(h_sc, h_sc, 0);
	m_transMat = Math::Matrix::CreateTranslation(13, -150, 0);
	m_h_mat = m_scaleMat * m_transMat;

}

void C_Title::Draw2D(bool diff)
{

	

	rect = { 0,0,1536,1024 };

	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_Tex, rect,1.0f);//画像の描画

	rect = { 0,0,1280,320 };
	SHADER.m_spriteShader.SetMatrix(m_s_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_s_Tex, rect, s_Alpha);//画像の描画

	rect = { 400,1010,480,340 };
	SHADER.m_spriteShader.SetMatrix(m_t_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_t_Tex, rect, 1.0f);//画像の描画

	if(diff)
	{
		rect = { 380,940,560,90 };
		SHADER.m_spriteShader.SetMatrix(m_h_mat);//行列のセット
		SHADER.m_spriteShader.DrawTex(&m_t_Tex, rect, 1.0f);//画像の描画
	}
}

void C_Title::Release()
{
	m_Tex.Release();
	m_s_Tex.Release();
}
