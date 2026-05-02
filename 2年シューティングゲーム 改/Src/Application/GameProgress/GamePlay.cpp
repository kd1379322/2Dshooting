#include "GamePlay.h"
#include "../Efect/pcc.h"
#include "../Efect/circle.h"
#include"../Player/Player.h"
#include"../Enemy/Red.h"
#include"../Enemy/Blue.h"
#include"../Enemy/Yellow.h"
#include"../Enemy/green.h"
#include"../Enemy/orange.h"
#include"../Enemy/purple.h"
#include"../Player/Bullet.h"
#include"../UI/Heart.h"
#include"../UI/Dying.h"
#include"../UI/Timer.h"

void C_GamePlay::Init()
{
	

	m_backgroundTex.Load("Texture/pixelart_starfield.png");

	GameCnt = 0;
	Bulletkeyflg = false;
	BulletCnt = 0;
	BulletColorNumber = 1;

	m_player = std::make_shared<C_Player>();
	m_player->Init();

	for (int i = 0; i < 3; ++i)m_enemyList.push_back(std::make_shared<C_Red>());
	for (int i = 0; i < 3; ++i)m_enemyList.push_back(std::make_shared<C_Blue>());
	for (int i = 0; i < 3; ++i)m_enemyList.push_back(std::make_shared<C_Yellow>());
	for (int i = 0; i < 3; ++i)m_enemyList.push_back(std::make_shared<C_Green>());
	for (int i = 0; i < 3; ++i)m_enemyList.push_back(std::make_shared<C_Orange>());
	for (int i = 0; i < 3; ++i)m_enemyList.push_back(std::make_shared<C_Purple>());

	

	for (auto& e : m_enemyList)
	{
		e->Init();
	}

	
	for (int i = 0; i < 5; i++)
	{
		m_copyenemy[i] = std::make_shared<C_Red>();
		m_copyenemy[i]->Init();
	}
	
	for (int i = 5; i < 10; i++)
	{
		m_copyenemy[i] = std::make_shared<C_Blue>();
		m_copyenemy[i]->Init();
	}

	for (int i = 10; i < 15; i++)
	{
		m_copyenemy[i] = std::make_shared<C_Yellow>();
		m_copyenemy[i]->Init();
	}

	for (int i = 0; i < MaxBullet; i++)
	{
		m_Bullet[i] = std::make_shared<C_Bullet>();
		m_Bullet[i]->Init();
	}

	m_heart = std::make_shared<C_Heart>();
	m_heart->Init();

	m_dying = std::make_shared<C_Dying>();
	m_dying->InitDying();

	m_pcc = std::make_shared<C_pcc>();
	m_pcc->Init();

	m_timer = std::make_shared<C_Timer>();
	m_timer->Init();

	for (int i=0;i<CircleMax;++i)
	{

		m_circle[i] = std::make_shared<C_Circle>();
		m_circle[i]->Init();
	}

	if (m_timer->GetFinish())
	{
		Timeup = true;
	}
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
	for (auto& e : m_enemyList)
	{
		if (dist(gen) == 0 && !e->GetMflg())
		{
			e->App();
		}
	}

	//==============================
	// 更新
	//==============================
	m_player->Update();
	for (auto& e : m_enemyList)
	{
		e->Update();	
	}

	for (int i = 0; i < cpyMax; i++)
	{
		m_copyenemy[i]->Update();
	}
	
	for (int i = 0; i < MaxBullet; i++) m_Bullet[i]->Update();


	//==============================
	// 弾の色変更
	//==============================
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		if (BulletColorNumber != 1)
		{
			BulletColorNumber = 1;
			m_pcc->App(m_player->Getpos(), BulletColorNumber);
		}
	}

	if (GetAsyncKeyState('X') & 0x8000)
	{
		if (BulletColorNumber != 2)
		{
			BulletColorNumber = 2;
			m_pcc->App(m_player->Getpos(), BulletColorNumber);
		}
	}

	if (GetAsyncKeyState('C') & 0x8000)
	{
		if (BulletColorNumber != 3)
		{
			BulletColorNumber = 3;
			m_pcc->App(m_player->Getpos(), BulletColorNumber);
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
				if (!m_Bullet[i]->GetMflg() && m_player->GetMflg())
				{
					m_Bullet[i]->App(m_player->Getpos(), BulletColorNumber);
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
	for (auto& e : m_enemyList)
	{

		//弾
		for (int i = 0; i < MaxBullet; i++)
		{
			if (e->GetMflg() && m_Bullet[i]->GetMflg() && e->BulletHit(m_Bullet[i]->Getpos()))
			{
				m_Bullet[i]->HitEnemy();
				
				switch (e->CheckColor(m_Bullet[i]->Getbcn()))
				{
				case 0:
					break;
				case 1:
					Circle(e->Getpos(), m_Bullet[i]->Getbcn());
					e->Kill();
					for (int j = 0; j < 5; j++)
					{
						if (!m_copyenemy[j]->GetMflg())
						{
							m_copyenemy[j]->PosApp(e->Getpos());
							break;
						}
					}
					break;
				case 2:
					Circle(e->Getpos(), m_Bullet[i]->Getbcn());
					e->Kill();
					for (int j = 5; j < 10; j++)
					{
						if (!m_copyenemy[j]->GetMflg())
						{
							m_copyenemy[j]->PosApp(e->Getpos());
							break;
						}
					}
					break;
				case 3:
					Circle(e->Getpos(), m_Bullet[i]->Getbcn());
					e->Kill();
					for (int j = 10; j < 15; j++)
					{
						if (!m_copyenemy[j]->GetMflg())
						{
							m_copyenemy[j]->PosApp(e->Getpos());
							break;
						}
					}
					break;
				case 10:
					Circle(e->Getpos(), m_Bullet[i]->Getbcn());
					e->Kill();
					break;
				default:
					break;
				}

			}
		}

		//敵と自機の当たり判定
		if (e->GetMflg() && m_player->EnemyHit(e->Getpos()));
		{
			
		}

	}

	for (int i = 0; i < cpyMax; i++)
	{
		for (int j = 0; j < MaxBullet; j++)
		{
			if (m_copyenemy[i]->GetMflg() && m_Bullet[j]->GetMflg() && m_copyenemy[i]->BulletHit(m_Bullet[j]->Getpos()))
			{
				m_Bullet[j]->HitEnemy();
				switch (m_copyenemy[i]->CheckColor(m_Bullet[j]->Getbcn()))
				{
				case 0:
					break;
				case 10:
					Circle(m_copyenemy[i]->Getpos(), m_Bullet[j]->Getbcn());
					m_copyenemy[i]->Kill();
					break;
				default:
					break;
				}
			}
		}

		if (m_copyenemy[i]->GetMflg() && m_player->EnemyHit(m_copyenemy[i]->Getpos()))
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
	// エフェクト,UI
	//==============================
	m_heart->Update();
	m_dying->UpdateDying();
	m_pcc->Update();
	m_timer->Update();

	for (auto& i : m_circle)
	{
		i->Update();
	}

	if (m_timer->GetFinish())
	{
		Timeup = true;
	}

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
		m_Bullet[i]->Draw2D();
	}

	// プレイヤー描画
	m_player->Draw2D(BulletColorNumber);

	for (auto& e : m_enemyList)
	{
		e->Draw2D();
	}

	for (int i = 0; i < cpyMax; i++)
	{
		m_copyenemy[i]->Draw2D();
	}

	m_heart->Draw2D(m_player->GetHp());
	if(m_player->GetHp() <= 1)
	{
		m_dying->DrawDying();
	}
	m_pcc->Draw2D();
	m_timer->Draw2D();
	for (auto& i : m_circle)
	{
		i->Draw2D();
	}
}

void C_GamePlay::ImGuiUpdate()
{
	ImGui::Text("GameC = %d", GameCnt);
	m_player->ImGuiUpdate();
}

void C_GamePlay::Reset()
{
	// 単体オブジェクト
	m_player = nullptr;
	m_heart = nullptr;
	m_dying = nullptr;
	m_pcc = nullptr;
	m_timer = nullptr;

	// 敵リスト（vector）
	m_enemyList.clear();

	// 配列系
	for (int i = 0; i < MaxBullet; i++)
	{
		m_Bullet[i] = nullptr;
	}

	for (int i = 0; i < 15; i++)
	{
		m_copyenemy[i] = nullptr;
	}

	for (int i = 0; i < CircleMax; i++)
	{
		m_circle[i] = nullptr;
	}

	// フラグ系もリセット（重要）
	Timeup = false;
	GameCnt = 0;
	Bulletkeyflg = false;
	BulletCnt = 0;
	BulletColorNumber = 1;

	Timeup = false;
}

void C_GamePlay::Circle(Math::Vector2 p_pos, int a)
{
	for(auto& i: m_circle)
	{
		if(!i->GetMflg())
		{
			i->App(p_pos, a);
			break;
		}
	}

}


void C_GamePlay::Release()
{
	m_playerTex.Release();
	//m_enemyTex.Release();
	//m_BulletTex.Release();	
}