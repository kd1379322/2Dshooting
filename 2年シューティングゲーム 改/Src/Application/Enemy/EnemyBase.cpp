#include "EnemyBase.h"

void C_EnemyBase::Init()
{
	
}

void C_EnemyBase::App()
{
	Moveflg = true;

	m_pos = { ScreenRight + Size, RandomApp() };

	anm = 0;
	rect = { 0,0,64,64 };

	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
	
}

void C_EnemyBase::PosApp(Math::Vector2 p_pos)
{
	Moveflg = true;

	m_pos = p_pos;

	anm = 0;
	rect = { 0,0,64,64 };

	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;

}

void C_EnemyBase::Update()
{

}

void C_EnemyBase::Draw2D()
{
	
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
	if (m_pos.x > ScreenRight)return false;

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

int C_EnemyBase::CheckColor(int i)
{
	return false;
}

void C_EnemyBase::Release()
{
	m_Tex.Release();
}
