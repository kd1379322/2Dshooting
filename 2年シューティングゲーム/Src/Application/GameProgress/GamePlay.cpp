#include "GamePlay.h"


void C_GamePlay::Init()
{
	
	m_playerTex.Load("Texture/player.png");
	m_player.SetTex(&m_playerTex);

	m_enemyTex.Load("Texture/enemy.png");
	for(int i= 0;i<MaxEnemy;i++)
	{
		m_enemy[i].SetTex(&m_enemyTex);
	}
	for (int i = 0; i < MaxcloneEnemy; i++)
	{
		m_cloneEnemy[i].SetTex(&m_enemyTex);
	}

	m_BulletTex.Load("Texture/Bullet.png");

	for (int i = 0; i < MaxBullet; i++)
	{
		m_Bullet[i].SetTex(&m_BulletTex);
	}

	m_backgroundTex.Load("Texture/pixelart_starfield.png");

	GameCnt = 0;

	Bulletkeyflg = false;
	BulletCnt = 0;
	BulletColor = { 1,0,0,1 };
	BulletColorNumber = 1;
	m_player.Init();
	
	
}

void C_GamePlay::Update()
{
	GameCnt++;

	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 500);
	
	
	for (int i = 0; i < MaxEnemy; i++)
	{
		if (dist(gen) == 0 && !m_enemy[i].GetMflg())
		{
			m_enemy[i].Init();
		}
	}
	

	m_player.Update();
	for (int i = 0; i < MaxEnemy; i++)
	{
		m_enemy[i].Update();
	}
	for (int i = 0; i < MaxcloneEnemy; i++)
	{
		m_cloneEnemy[i].Update();
	}
	for (int i = 0; i < MaxBullet; i++)
	{
		m_Bullet[i].Update();
	}

	//弾の色を変更
	if (GetAsyncKeyState('Z') & 0x8000) {
		
		BulletColorNumber = 1; //赤
	}

	if (GetAsyncKeyState('X') & 0x8000) {
		
		BulletColorNumber = 2;	//青
	}

	if (GetAsyncKeyState('C') & 0x8000) {
		
		BulletColorNumber = 3;	//黄
	}

	//弾発射処理
	//if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!Bulletkeyflg)
		{
			Bulletkeyflg = true;

			for (int i = 0; i < MaxBullet; i++)
			{
				if (!m_Bullet[i].GetMflg() && m_player.GetMflg())
				{
					m_Bullet[i].Init(m_player.Getpos(),BulletColorNumber);
					return;
				}
				else
				{
					continue;
				}
			}
		}
	}

	//弾発射間隔用
	if (Bulletkeyflg)
	{
		BulletCnt++;
		if (BulletCnt >= 10)
		{
			BulletCnt = 0;
			Bulletkeyflg = false;
		}
	}

	
	for (int j = 0; j < MaxEnemy; j++)
	{
		//敵と弾の当たり判定
		for (int i = 0; i < MaxBullet; i++)
		{
			if (m_enemy[j].GetMflg() && m_Bullet[i].GetMflg() && m_enemy[j].BulletHit(m_Bullet[i].Getpos()))
			{
				m_Bullet[i].HitEnemy();
				
				if (m_enemy[j].CheckColor(BulletColorNumber, j) == 1) {
					for (int k = 0; k < 3; k++)
					{
						if(!m_cloneEnemy[k].GetMflg())
						{
							m_cloneEnemy[k].PosInit(m_enemy[j].Getpos());
							return;
						}
						else
						{
							continue;
						}
					}
				}
				else if(m_enemy[j].CheckColor(BulletColorNumber, j) == 2)
				{
					for (int k = 3; k < 6; k++)
					{
						if (!m_cloneEnemy[k].GetMflg())
						{
							m_cloneEnemy[k].PosInit(m_enemy[j].Getpos());
							return;
						}
						else
						{
							continue;
						}
					}
				}
				else if(m_enemy[j].CheckColor(BulletColorNumber, j) == 3)
				{
					for (int k = 6; k < 9; k++)
					{
						if (!m_cloneEnemy[k].GetMflg())
						{
							m_cloneEnemy[k].PosInit(m_enemy[j].Getpos());
							return;
						}
						else
						{
							continue;
						}
					}
				}
				
			}
			
		}

		//敵と自機の当たり判定
		if (m_enemy[j].GetMflg() && m_player.EnemyHit(m_enemy[j].Getpos()))
		{

		}
	}

	for (int j = 0; j < MaxcloneEnemy; j++)
	{
		for (int i = 0; i < MaxBullet; i++)
		{
			if (m_cloneEnemy[j].GetMflg() && m_Bullet[i].GetMflg() && m_cloneEnemy[j].BulletHit(m_Bullet[i].Getpos())) {
				m_Bullet[i].HitEnemy();
				if (m_cloneEnemy[j].CheckColor(BulletColorNumber, j) == 0);
			}
		}
		//敵と自機の当たり判定
		if (m_cloneEnemy[j].GetMflg() && m_player.EnemyHit(m_cloneEnemy[j].Getpos()))
		{

		}
	}

	Backgroundpos.x -= 8;
	if (Backgroundpos.x < -640)
	{
		Backgroundpos.x = 640;
	}

	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_transMat = Math::Matrix::CreateTranslation(Backgroundpos.x, Backgroundpos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_GamePlay::Draw2D()
{

	Math::Rectangle rect = { 0,0,1280*2,720 };
	SHADER.m_spriteShader.SetMatrix(m_mat);//行列のセット
	SHADER.m_spriteShader.DrawTex(&m_backgroundTex, rect, 1.0f);//画像の描画

	for (int i = 0; i < MaxBullet; i++)
	{
		m_Bullet[i].Draw2D();
	}

	m_player.Draw2D(BulletColorNumber);

	for (int i = 0; i < MaxEnemy; i++)
	{
		m_enemy[i].Draw2D(i);
	}
	
	for (int i = 0; i < MaxcloneEnemy; i++)
	{
		m_cloneEnemy[i].Draw2D(i);
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
