#include "EnemyBase.h"

void C_EnemyBase::Init()
{
	Moveflg = true;

	m_pos = { ScreenRight + Size, RandomApp()};

	anm = 0;
	rect = { 0,0,64,64 };

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

void C_EnemyBase::Draw2D(int i)
{
	if (!Moveflg)return;

	Math::Color color;

	if (i >= 0 && i < 3)
	{
		color = { 1,0,0,1 };
	}
	else if (i >= 3 && i < 6)
	{
		color = { 0,0,1,1 };
	}
	else if (i >= 6 && i < 9)
	{
		color = { 1,1,0,1 };
	}
	else if (i >= 9 && i < 12)
	{
		color = { 0,1,0,1 };
	}
	else if (i >= 12 && i < 15)
	{
		color = { 1,0.3f,0,1 };
	}
	else if (i >= 15 && i < 18)
	{
		color = { 1,0,1,1 };
	}

	//プレイヤーの描画
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex_Color(m_Tex,rect, color);//画像の描画
}

float C_EnemyBase::RandomApp()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(ScreenBottom + Size, ScreenTop - Size);
    return dist(gen);
}

bool C_EnemyBase::BulletHit(Math::Vector2 p_pos)
{
	const float x = m_pos.x - p_pos.x;
	const float y = m_pos.y - p_pos.y;
	const float z = sqrt(x * x + y * y);

	if (Moveflg)
	{
		if (z < 64)
		{
			
			return true;
		}
		else
		{
			return false;
		}

	}
}

void C_EnemyBase::CheckColor(int i,int j)
{
	if ((i == 1 && j < 3) ||
		(i == 2 && j >= 3 && j < 6) ||
		(i == 3 && j >= 6 && j < 9))
	{
		Moveflg = false;
	}

}
