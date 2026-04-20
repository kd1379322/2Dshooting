#include "EnemyBase.h"

void C_EnemyBase::Init()
{
	Moveflg = true;

	m_pos = { ScreenRight + Size, RandomApp()};

	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x,m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_EnemyBase::Update()
{
	if (!Moveflg)return;

	m_pos.x += m_moveSpeed;

	if (m_pos.x < ScreenLeft - Size)
	{
		m_pos = { ScreenRight + Size,  RandomApp() };
	}

	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_EnemyBase::Draw2D()
{
	if (!Moveflg)return;

	rect = { 0,0,64,64 };
	//プレイヤーの描画
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex_Color(m_Tex, Math::Rectangle(0, 0, 64, 64), Math::Color(1, 0, 0, 1));//画像の描画
}

float C_EnemyBase::RandomApp()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(ScreenBottom + Size, ScreenTop - Size);
    return dist(gen);
}
