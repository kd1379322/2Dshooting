#include "GamePlay.h"
#include "../Efect/pcc.h"

void C_GamePlay::Init()
{
	m_playerTex.Load("Texture/player.png");
	m_player.SetTex(&m_playerTex);

	m_enemyTex.Load("Texture/enemy.png");
	for (int i = 0; i < MaxEnemy; i++)
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
	BulletColorNumber = 1;

	m_player.Init();

	m_pcc = std::make_shared<C_pcc>();
	m_pcc->Init();
}

void C_GamePlay::Update()
{
	GameCnt++;

	//==============================
	// 乱数生成
	//==============================
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 499); // 500分の1

	//==============================
	// 敵生成
	//==============================
	for (int i = 0; i < MaxEnemy; i++)
	{
		if (dist(gen) == 0 && !m_enemy[i].GetMflg())
		{
			m_enemy[i].Init();
		}
	}

	//==============================
	// 更新
	//==============================
	m_player.Update();

	for (int i = 0; i < MaxEnemy; i++) m_enemy[i].Update();
	for (int i = 0; i < MaxcloneEnemy; i++) m_cloneEnemy[i].Update();
	for (int i = 0; i < MaxBullet; i++) m_Bullet[i].Update();

	//==============================
	// 弾の色変更
	//==============================
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		//if (BulletColorNumber != 1)
		{
			BulletColorNumber = 1;
			m_pcc->App(m_player.Getpos());
		}
	}

	if (GetAsyncKeyState('X') & 0x8000)
	{
		//if (BulletColorNumber != 2)
		{
			BulletColorNumber = 2;
			m_pcc->App(m_player.Getpos());
		}
	}

	if (GetAsyncKeyState('C') & 0x8000)
	{
		//if (BulletColorNumber != 3)
		{
			BulletColorNumber = 3;
			m_pcc->App(m_player.Getpos());
		}
	}

	//==============================
	// 弾発射
	//==============================
	//if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!Bulletkeyflg)
		{
			Bulletkeyflg = true;

			for (int i = 0; i < MaxBullet; i++)
			{
				if (!m_Bullet[i].GetMflg() && m_player.GetMflg())
				{
					m_Bullet[i].Init(m_player.Getpos(), BulletColorNumber);
					break; // ← return禁止
				}
			}
		}
	}

	// 発射間隔
	if (Bulletkeyflg)
	{
		BulletCnt++;
		if (BulletCnt >= 10)
		{
			BulletCnt = 0;
			Bulletkeyflg = false;
		}
	}

	//==============================
	// 当たり判定（敵）
	//==============================
	for (int j = 0; j < MaxEnemy; j++) {
		//敵と弾の当たり判定 
		for (int i = 0; i < MaxBullet; i++)
		{
			if (m_enemy[j].GetMflg() && m_Bullet[i].GetMflg() && m_enemy[j].BulletHit(m_Bullet[i].Getpos()))
			{
				m_Bullet[i].HitEnemy();
				if (m_enemy[j].CheckColor(BulletColorNumber, j) == 1)
				{
					for (int k = 0; k < 3; k++) {
						if (!m_cloneEnemy[k].GetMflg())
						{
							m_cloneEnemy[k].PosInit(m_enemy[j].Getpos()); return;
						}
						else { continue; }
					}
				}
				else if (m_enemy[j].CheckColor(BulletColorNumber, j) == 2)
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
				else if (m_enemy[j].CheckColor(BulletColorNumber, j) == 3)
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

			//敵と自機の当たり判定
			if (m_enemy[j].GetMflg() && m_player.EnemyHit(m_enemy[j].Getpos()))
			{
			}


		}
	}


	for (int j = 0; j < MaxcloneEnemy; j++)
	{
		for (int i = 0; i < MaxBullet; i++)
		{
			if (m_cloneEnemy[j].GetMflg() &&
				m_Bullet[i].GetMflg() &&
				m_cloneEnemy[j].BulletHit(m_Bullet[i].Getpos()))
			{
				m_Bullet[i].HitEnemy();

				if (m_cloneEnemy[j].CheckColor(BulletColorNumber, j) == 0);
			}
		}

		// 敵と自機の当たり判定
		if (m_cloneEnemy[j].GetMflg() &&
			m_player.EnemyHit(m_cloneEnemy[j].Getpos()))
		{
		}
	}
	//==============================
	// 背景
	//==============================
	Backgroundpos.x -= 8;
	if (Backgroundpos.x < -640)
	{
		Backgroundpos.x = 640;
	}

	//==============================
	// エフェクト
	//==============================
	m_pcc->Update();

	m_scaleMat = Math::Matrix::CreateScale(1, 1, 0);
	m_transMat = Math::Matrix::CreateTranslation(Backgroundpos.x, Backgroundpos.y, 0);
	m_mat = m_scaleMat * m_transMat;
}

void C_GamePlay::Draw2D()
{

	Math::Rectangle rect = { 0, 0, 1280 * 2, 720 };

	// 行列のセット
	SHADER.m_spriteShader.SetMatrix(m_mat);

	// 背景描画
	SHADER.m_spriteShader.DrawTex(&m_backgroundTex, rect, 1.0f);

	// 弾描画
	for (int i = 0; i < MaxBullet; i++)
	{
		m_Bullet[i].Draw2D();
	}

	// プレイヤー描画
	m_player.Draw2D(BulletColorNumber);

	// 敵描画
	for (int i = 0; i < MaxEnemy; i++)
	{
		m_enemy[i].Draw2D(i);
	}

	// クローン敵描画
	for (int i = 0; i < MaxcloneEnemy; i++)
	{
		m_cloneEnemy[i].Draw2D(i);
	}

	m_pcc->Draw2D(BulletColorNumber);

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