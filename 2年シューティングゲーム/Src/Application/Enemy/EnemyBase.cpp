#include "EnemyBase.h"

void C_EnemyBase::Init()
{
	m_Tex.Load("Texture/enemy.png");

	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_scaleMat * m_transMat;
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
	if (!Moveflg)return;


	m_pos.x += m_moveSpeed;

	if (m_pos.x < ScreenLeft - Size)
	{
		Moveflg = false;
		//m_pos = { ScreenRight + Size,  RandomApp() };
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
		color = { 1,0,0,1 };		//赤
	}
	else if (i >= 3 && i < 6)
	{
		color = { 0,0,1,1 };		//青
	}
	else if (i >= 6 && i < 9)
	{
		color = { 1,1,0,1 };		//黄
	}
	else if (i >= 9 && i < 12)
	{
		color = { 0,1,0,1 };		//緑(青＋黄)
	}
	else if (i >= 12 && i < 15)
	{
		color = { 1,0.3f,0,1 };		//橙(赤＋黄)
	}
	else if (i >= 15 && i < 18)
	{
		color = { 1,0,1,1 };		//紫(青＋赤)
	}

	//プレイヤーの描画
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex_Color(&m_Tex, rect, color);//画像の描画
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

int C_EnemyBase::CheckColor(int i, int j)//iが弾の色、jが敵の色
{

	if ((i == 1 && j >= 0 && j < 3) ||
		(i == 2 && j >= 3 && j < 6) ||
		(i == 3 && j >= 6 && j < 9))
	{
		Moveflg = false;
		return 10;
	}

	else if(i == 1)
	{
		if (j >= 12 && j < 15)
		{
			Moveflg = false;
			//黄色召喚
			return 3;
		}

		if (j >= 15 && j < 18)
		{
			Moveflg = false;
			return 2;
		}
	}


	else if (i == 2)
	{
		if (j >= 9 && j < 12)
		{
			Moveflg = false;
			return 3;
		}

		if (j >= 15 && j < 18)
		{
			Moveflg = false;
			return 1;
		}
	}

	else if (i == 3)
	{
		if(j >= 12 && j < 15)
		{
			Moveflg = false;
			//赤召喚
			return 1;
		}

		else if (j >= 9 && j < 12)
		{
			Moveflg = false;
			//青召喚
			return 2;
		}
	}

	
	else
	{
		return 0;
	}

}

bool C_EnemyBase::CheckColor(int i)
{
	return false;
}

void C_EnemyBase::Release()
{
	m_Tex.Release();
}
