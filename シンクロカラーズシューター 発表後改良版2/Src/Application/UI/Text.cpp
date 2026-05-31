#include "Text.h"

void C_Text::Init()
{
	m_tex.Load("Texture/Text_.png");
	Moveflg = false;
	Alpha = 0.0f;
	cnt = 0;
	type = 0;
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Text::Update()
{
	if (!Moveflg)return;

	if (type == 0)
	{

	}
	else if (type == 2)
	{
		blinkCnt++;

		// ===== 点滅フェーズ（3秒）=====
		if (!isFading)
		{
			if (blinkCnt <= 120) // 約3秒
			{
				// 点滅
				if ((blinkCnt / 10) % 2 == 0)
				{
					Alpha = 1.0f;
				}
				else
				{
					Alpha = 0.0f;
				}
			}
			else
			{
				// フェードへ移行
				isFading = true;
				Alpha = 1.0f; // フェード開始は見えてる状態から
			}
		}
		// ===== フェードアウトフェーズ =====
		else
		{
			Alpha -= 0.02f; // 徐々に減らす

			if (Alpha <= 0.0f)
			{
				Alpha = 0.0f;
				Moveflg = false;
				isFading = false;
				blinkCnt = 0;
			}
		}
	}
	else
	{
		Alpha -= 0.05f;
		if (Alpha <= 0.0f)
		{
			Alpha = 0.0f;
			m_scale = { 1.0f,1.0f };
			Moveflg = false;
		}
	}

	

	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Text::Draw2D()
{
	if (!Moveflg)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_tex, rect, Alpha);//画像の描画
}

void C_Text::Limit30()
{
	rect = { 0,120,1280,120 };
	Alpha = 1.0f;
	m_pos = { 0,100 };
	m_scale = { 1,1 };
	type = 1;
	Moveflg = true;
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Text::Limit60()
{
	rect = { 0,0,1280,120 };
	Alpha = 1.0f;
	m_pos = { 0,100 };
	m_scale = { 1,1 };
	type = 1;
	Moveflg = true;
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Text::TimeUpApp()
{
	rect = {0,740,1280,190};
	Alpha = 1.0f;
	m_pos = { 0,0 };
	m_scale = { 1.0f,1.0f };
	type = 0;
	Moveflg = true;
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Text::GameoverApp()
{
	rect = { 0,380,1280,120 };
	Alpha = 1.0f;
	m_pos = { 0,0 };
	m_scale = { 2.0f,2.0f };
	type = 0;
	Moveflg = true;
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_Text::RemStamina1()
{
	rect = { 0,260,1280,120 };
	Alpha = 1.0f;
	m_pos = { 0,100 };
	m_scale = { 2.0f,2.0f };
	type = 2;
	Moveflg = true;
	m_scaleMat = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}


void C_Text::Release()
{
	m_tex.Release();
}
