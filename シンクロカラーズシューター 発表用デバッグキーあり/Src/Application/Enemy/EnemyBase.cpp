#include "EnemyBase.h"
#include"../Sound/Sound.h"

void C_EnemyBase::Init()
{
	
}

void C_EnemyBase::App(
	const std::vector<std::shared_ptr<C_EnemyBase>>& p_list)
{
	Moveflg = true;

	m_pos =
	{
		ScreenRight + Size,
		RandomApp(p_list)
	};

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

float C_EnemyBase::RandomApp(
	const std::vector<std::shared_ptr<C_EnemyBase>>& p_list)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	float minY = ScreenBottom + Size;
	float maxY = ScreenTop - Size;

	std::uniform_real_distribution<float>
		dist(minY, maxY);

	const float SafeRange = 80.0f;

	// 最大試行回数
	const int MaxTry = 100;

	for (int i = 0; i < MaxTry; i++)
	{
		float y = dist(gen);

		bool overlap = false;

		for (auto& e : p_list)
		{
			if (!e->GetMflg())
				continue;

			float dy = abs(y - e->Getpos().y);

			if (dy < SafeRange)
			{
				overlap = true;
				break;
			}
		}

		// 重なっていなければ採用
		if (!overlap)
		{
			return y;
		}
	}

	//==============================
	// 見つからなかった場合
	//==============================
	return dist(gen);
}

bool C_EnemyBase::BulletHit(Math::Vector2 p_pos)
{
	if (m_pos.x > ScreenRight)return false;
	if (!Moveflg)return false;


	const float x = m_pos.x - p_pos.x;
	const float y = m_pos.y - p_pos.y;
	const float z = sqrt(x * x + y * y);

	
	if (z < 64)
	{

		return true;
	}
	else
	{
		return false;
	}

	
}

int C_EnemyBase::CheckColor(int i)
{
	return false;
}

void C_EnemyBase::Kill()
{
	SOUND.EnemyDamage_SE();
	Moveflg = false;
}

void C_EnemyBase::Release()
{
	m_Tex.Release();
}
