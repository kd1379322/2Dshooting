#include "GamePlay.h"


void C_GamePlay::Init()
{
	
	m_playerTex.Load("Texture/player.png");
	m_player.SetTex(&m_playerTex);

	m_enemyTex.Load("Texture/enemy.png");
	m_enemy.SetTex(&m_enemyTex);

	m_BulletTex.Load("Texture/Bullet.png");

	for (int i = 0; i < MaxBullet; i++)
	{
		m_Bullet[i].SetTex(&m_BulletTex);
	}

	GameCnt = 0;

	Bulletkeyflg = false;
	BulletCnt = 0;

	m_player.Init();
	m_enemy.Init();
	
}

void C_GamePlay::Update()
{
	GameCnt++;
	m_player.Update();
	m_enemy.Update();

	for (int i = 0; i < MaxBullet; i++)
	{
		m_Bullet[i].Update();
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!Bulletkeyflg)
		{
			Bulletkeyflg = true;

			for (int i = 0; i < MaxBullet; i++)
			{
				if (!m_Bullet[i].GetMflg())
				{
					m_Bullet[i].Init(m_player.Getpos());
					return;
				}
				else
				{
					continue;
				}
			}
		}
	}

	if (Bulletkeyflg)
	{
		BulletCnt++;
		if (BulletCnt >= 10)
		{
			BulletCnt = 0;
			Bulletkeyflg = false;
		}
	}


	for (int i = 0; i < MaxBullet; i++)
	{
		if (m_enemy.GetMflg() &&  m_Bullet[i].GetMflg() && m_enemy.BulletHit(m_Bullet[i].Getpos())) {
			m_Bullet[i].HitEnemy();
		}
	}
}

void C_GamePlay::Draw2D()
{
	m_player.Draw2D();
	m_enemy.Draw2D();
	for (int i = 0; i < MaxBullet; i++)
	{
		m_Bullet[i].Draw2D();
	}
}

void C_GamePlay::ImGuiUpdate()
{
	ImGui::Text("GameC = %d", GameCnt);
	m_player.ImGuiUpdate();
}

void C_GamePlay::Release()
{
	m_playerTex.Release();
	m_enemyTex.Release();
	m_BulletTex.Release();
	
}
