#include "GamePlay.h"
#include "../Efect/pcc.h"
#include "../Efect/circle.h"
#include "../Efect/damage.h"
#include "../Efect/edmecut.h"
#include "../Efect/radar.h"
#include"../Player/Player.h"
#include"../Player/Bullet.h"
#include"../Enemy/Red.h"
#include"../Enemy/Blue.h"
#include"../Enemy/Yellow.h"
#include"../Enemy/green.h"
#include"../Enemy/orange.h"
#include"../Enemy/purple.h"
#include"../UI/Heart.h"
#include"../UI/Dying.h"
#include"../UI/Timer.h"
#include"../UI/Score.h"
#include"../UI/Selectkey.h"
#include"../UI/Countdown.h"
#include"../UI/Text.h"
#include"../Sound/Sound.h"


void C_GamePlay::Init()
{

	GameCnt = 0;
	Bulletkeyflg = false;
	BulletCnt = 0;
	BulletColorNumber = 1;
	m_waitCnt = 0;
	m_waitEndCnt = 0;
	m_player = std::make_shared<C_Player>();
	m_player->Init();

	for (int i = 0; i < 3; ++i)m_enemyList.push_back(std::make_shared<C_Red>());
	for (int i = 0; i < 3; ++i)m_enemyList.push_back(std::make_shared<C_Blue>());
	for (int i = 0; i < 3; ++i)m_enemyList.push_back(std::make_shared<C_Yellow>());

	for (int i = 0; i < 3; ++i)m_multi_enemyList.push_back(std::make_shared<C_Green>());
	for (int i = 0; i < 3; ++i)m_multi_enemyList.push_back(std::make_shared<C_Orange>());
	for (int i = 0; i < 3; ++i)m_multi_enemyList.push_back(std::make_shared<C_Purple>());

	for (auto& e : m_enemyList)
	{
		e->Init();
		e->SetPpos(m_player->Getpos());
	}

	for (auto& e : m_multi_enemyList)
	{
		e->Init();
		e->SetPpos(m_player->Getpos());
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

	for (int i = 15; i < 20; i++)
	{
		m_copyenemy[i] = std::make_shared<C_Green>();
		m_copyenemy[i]->Init();
	}

	for (int i = 20; i < 25; i++)
	{
		m_copyenemy[i] = std::make_shared<C_Orange>();
		m_copyenemy[i]->Init();
	}

	for (int i = 25; i < 30; i++)
	{
		m_copyenemy[i] = std::make_shared<C_Purple>();
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

	m_score = std::make_shared<C_Score>();
	m_score->Init();

	m_damage = std::make_shared<C_damage>();
	m_damage->Init();
	
	m_selectkey = std::make_shared<C_Selectkey>();
	m_selectkey->Init();

	m_countdown = std::make_shared<C_Countdown>();
	m_countdown->Init();

	m_text = std::make_shared<C_Text>();
	m_text->Init();

	m_radar = std::make_shared<C_radar>();
	m_radar->Init();

	for (int i = 0; i < efctMax; ++i)
	{
		m_edmecut[i] = std::make_shared<C_edmecut>();
		m_edmecut[i]->Init();
	}

	for (int i=0;i<CircleMax;++i)
	{
		m_circle[i] = std::make_shared<C_Circle>();
		m_circle[i]->Init();
	}

}

void C_GamePlay::Update(bool p_diff)
{
	GameCnt++;
	m_countdown->Update();
	m_player->AnmUpdate();

	if (m_waitCnt <= 240)
	{
		m_waitCnt++;
		if (m_waitCnt == 60 || m_waitCnt == 120 || m_waitCnt == 180)
		{
			m_countdown->App();
			SOUND.CountDown1_SE();
		}
		else if (m_waitCnt == 240)
		{
			m_countdown->App();
			SOUND.Start_SE();
		}

	}
	else if (Timeup)
	{
		m_waitEndCnt++;
		if (m_waitEndCnt >= 120)
		{
			NextScene = true;
		}
	}
	else
	{
		

		m_timer->Update();
		m_timer->DownAlpha(m_player->Getpos());

		

		if (m_timer->GettotalTime() <= 3 && m_timer->GettotalTime() >= 1)
		{
			m_countdown->E_App(m_timer->GettotalTime());
		}

		if (m_timer->GettotalTime() == 60)
		{
			m_text->Limit60();
		}

		if (m_timer->GettotalTime() == 30)
		{
			m_text->Limit30();
		}


		if (m_timer->GetFinish())
		{
			score_tmp = m_score->GetScore();
			life_tmp = m_player->GetHp();
			m_text->TimeUpApp();
			SOUND.Finish_SE();
			Timeup = true;
		}

		if (!m_player->GetMflg())
		{
			score_tmp = m_score->GetScore();
			life_tmp = m_player->GetHp();
			m_text->GameoverApp();
			Timeup = true;

		}

		if(!p_diff)
		{

			//==============================
			// 敵生成
			//==============================
			

			EnemyApp(3,499,0,m_enemyList);
				
			if (m_timer->GettotalTime() <= 60)
			{

				EnemyApp(1, 999,3, m_multi_enemyList);

			}		
			
		}
		else if(p_diff)   //ハードモード
		{

			EnemyApp(5, 299,0,m_enemyList);
			EnemyApp(3, 299,3,m_multi_enemyList);
		}

		//==============================
		// キャラ更新
		//==============================
		m_player->Update();
		
		for (auto& e : m_enemyList)
		{
			e->Update();
			e->SetPpos(m_player->Getpos());
		}

		for (auto& e : m_multi_enemyList)
		{
			e->Update();
			e->SetPpos(m_player->Getpos());
		}

		for (int i = 0; i < cpyMax; i++)
		{
			m_copyenemy[i]->Update();
			m_copyenemy[i]->SetPpos(m_player->Getpos());
		}

		for (int i = 0; i < MaxBullet; i++) m_Bullet[i]->Update();


		//==============================
		// 弾の色変更
		//==============================
		//static short prevZ = 0;
		//static short prevX = 0;
		//static short prevC = 0;

		static int changeInterval = 0;   // インターバル用カウンタ

		// 毎フレーム減らす
		if (changeInterval > 0)
		{
			changeInterval--;
		}

		//short nowZ = GetAsyncKeyState('Z');
		//short nowX = GetAsyncKeyState('X');
		//short nowC = GetAsyncKeyState('C');

		//// インターバル中じゃない時だけ入力受付
		////if (changeInterval <= 0)
		//{
		//	// Z
		//	if ((nowZ & 0x8000) && !(prevZ & 0x8000))
		//	{
		//		if (BulletColorNumber != 1)
		//		{
		//			BulletColorNumber = 1;
		//			SOUND.Chenge_SE();
		//			m_pcc->App(m_player->Getpos(), BulletColorNumber);

		//			//changeInterval = 0;   // 30フレーム待つ
		//		}
		//	}

		//	// X
		//	if ((nowX & 0x8000) && !(prevX & 0x8000))
		//	{
		//		if (BulletColorNumber != 2)
		//		{
		//			BulletColorNumber = 2;
		//			SOUND.Chenge_SE();
		//			m_pcc->App(m_player->Getpos(), BulletColorNumber);

		//			//changeInterval = 0;
		//		}
		//	}

		//	// C
		//	if ((nowC & 0x8000) && !(prevC & 0x8000))
		//	{
		//		if (BulletColorNumber != 3)
		//		{
		//			BulletColorNumber = 3;
		//			SOUND.Chenge_SE();
		//			m_pcc->App(m_player->Getpos(), BulletColorNumber);

		//			//changeInterval = 0;
		//		}
		//	}
		//}

		//// 状態更新
		//prevZ = nowZ;
		//prevX = nowX;
		//prevC = nowC;

		/*if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if(!m_radar->GetMflg() && (changeInterval <= 0))
			{
				m_radar->App(m_player->Getpos());
				changeInterval = 120;

			}
		}*/

		if (m_radar->GetMflg())
		{
			for (auto& e : m_enemyList)
			{
				if (m_player->C_EnemyHit(e->Getpos(), m_radar->GetSize()))
				{
					e->ColorApp();
				}

			}

			for (auto& e : m_multi_enemyList)
			{
				if (m_player->C_EnemyHit(e->Getpos(), m_radar->GetSize()))
				{
					e->ColorApp();
				}

			}
		}

		//==============================
		// 弾発射
		//==============================
		if (!m_radar->GetMflg())
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
						Edmecut(e->Getpos());
						break;
					case 1:
						ChengeColor();

						m_score->ScoreUp();
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
						ChengeColor();

						m_score->ScoreUp();
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
						ChengeColor();

						m_score->ScoreUp();
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
						ChengeColor();

						m_score->ScoreUp();
						Circle(e->Getpos(), m_Bullet[i]->Getbcn());
						e->Kill();
						break;
					default:
						break;
					}

				}
			}
		}

		for (auto& e : m_multi_enemyList)
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
						Edmecut(e->Getpos());
						break;
					case 1:
						ChengeColor();

						m_score->ScoreUp();
						Circle(e->Getpos(), m_Bullet[i]->Getbcn());
						e->Kill();
						for (int j = 0; j < 5; j++)
						{
							if (!m_copyenemy[j]->GetMflg())
							{
								m_copyenemy[j]->PosApp({ e->Getpos().x,e->Getpos().y});
								break;
							}
						}
						break;
					case 2:
						ChengeColor();

						m_score->ScoreUp();
						Circle(e->Getpos(), m_Bullet[i]->Getbcn());
						e->Kill();
						for (int j = 5; j < 10; j++)
						{
							if (!m_copyenemy[j]->GetMflg())
							{
								m_copyenemy[j]->PosApp({ e->Getpos().x,e->Getpos().y });
								break;
							}
						}
						break;
					case 3:
						ChengeColor();

						m_score->ScoreUp();
						Circle(e->Getpos(), m_Bullet[i]->Getbcn());
						e->Kill();
						for (int j = 10; j < 15; j++)
						{
							if (!m_copyenemy[j]->GetMflg())
							{
								m_copyenemy[j]->PosApp({ e->Getpos().x,e->Getpos().y });
								break;
							}
						}
						break;
					case 10:
						ChengeColor();

						m_score->ScoreUp();
						Circle(e->Getpos(), m_Bullet[i]->Getbcn());
						e->Kill();
						break;
					default:
						break;
					}

				}
			}
		}

		for (auto& e : m_enemyList)
		{
			//敵と自機の当たり判定
			if (e->GetMflg())
			{
				if (m_player->EnemyHit(e->Getpos()))
				{
					m_damage->App(m_player->Getpos());
					m_player->Damege();
					if (m_player->GetHp() <= 1)m_text->RemStamina1();
				}

			}
		}

		for (auto& e : m_multi_enemyList)
		{
			//敵と自機の当たり判定
			if (e->GetMflg())
			{
				if (m_player->EnemyHit(e->Getpos()))
				{
					m_damage->App(m_player->Getpos());
					m_player->Damege();
					if (m_player->GetHp() <= 1)m_text->RemStamina1();
				}

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
						Edmecut(m_copyenemy[i]->Getpos());
						break;
					case 1:
						m_score->ScoreUp();
						Circle(m_copyenemy[i]->Getpos(), m_Bullet[j]->Getbcn());
						m_copyenemy[i]->Kill();
						for (int k = 0; k < 5; k++)
						{
							if (!m_copyenemy[k]->GetMflg())
							{
								m_copyenemy[k]->PosApp(m_copyenemy[i]->Getpos());
								break;
							}
						}
						break;
					case 2:
						m_score->ScoreUp();
						Circle(m_copyenemy[i]->Getpos(), m_Bullet[j]->Getbcn());
						m_copyenemy[i]->Kill();
						for (int k = 5; k < 10; k++)
						{
							if (!m_copyenemy[k]->GetMflg())
							{
								m_copyenemy[k]->PosApp(m_copyenemy[i]->Getpos());
								break;
							}
						}
						break;
					case 3:
						m_score->ScoreUp();
						Circle(m_copyenemy[i]->Getpos(), m_Bullet[j]->Getbcn());
						m_copyenemy[i]->Kill();
						for (int k = 10; k < 15; k++)
						{
							if (!m_copyenemy[k]->GetMflg())
							{
								m_copyenemy[k]->PosApp(m_copyenemy[i]->Getpos());
								break;
							}
						}
						break;
					case 10:
						m_score->ScoreUp();
						Circle(m_copyenemy[i]->Getpos(), m_Bullet[j]->Getbcn());
						m_copyenemy[i]->Kill();
						break;
					default:
						break;
					}
				}
			}
		}

		for (int i = 0; i < cpyMax; i++)
		{
			if (m_copyenemy[i]->GetMflg())
			{
				if (m_player->EnemyHit(m_copyenemy[i]->Getpos()))
				{
					m_damage->App(m_player->Getpos());
					m_player->Damege();
					if (m_player->GetHp() <= 1)m_text->RemStamina1();
				}

			}
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
	// エフェクト,UI更新
	//==============================
	m_heart->Update();
	m_heart->DownAlpha(m_player->Getpos());
	m_dying->UpdateDying();
	m_pcc->Update();
	m_score->Update();
	m_damage->Update();
	m_selectkey->Update();
	m_selectkey->DownAlpha(m_player->Getpos());
	m_radar->Update();

	for(auto& i: m_edmecut)
	{
		i->Update();
	}

	for (auto& i : m_circle)
	{
		i->Update();
	}

	m_text->Update();

}

void C_GamePlay::Draw2D()
{
	m_heart->Draw2D(m_player->GetHp());
	m_score->Draw2D();
	m_score->DownAlpha(m_player->Getpos());
	m_selectkey->Draw();
	m_timer->Draw2D();
	m_radar->Draw2D();

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

	for (auto& e : m_multi_enemyList)
	{
		e->Draw2D();
	}

	for (int i = 0; i < cpyMax; i++)
	{
		m_copyenemy[i]->Draw2D();
	}

	if(m_player->GetHp() <= 1)
	{
		m_dying->DrawDying();
	}
	m_pcc->Draw2D();
	for (auto& i : m_circle)
	{
		i->Draw2D();
	}
	m_damage->Draw();
	m_countdown->Draw2D();
	m_text->Draw2D();

	for (auto& i : m_edmecut)
	{
		i->Draw();
	}
}

void C_GamePlay::ImGuiUpdate()
{
	ImGui::Text("GameC = %d", GameCnt);
	m_player->ImGuiUpdate();
}

void C_GamePlay::EnemyApp(
	int p_RespawnNum,
	int p_dist,
	int p_CheckSec,
	std::vector<std::shared_ptr<C_EnemyBase>>& p_list)
{
	//==============================
	// タイマー
	//==============================
	static int CheckCnt = 0;

	if (p_CheckSec > 0)
	{
		CheckCnt++;

		if (CheckCnt < p_CheckSec * 60)
		{
			return;
		}

		CheckCnt = 0;
	}

	//==============================
	// 乱数生成
	//==============================
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_int_distribution<int> spawnDist(0, p_dist);

	//==============================
	// Color_codeごとに敵を分類
	//==============================
	std::map<int, std::vector<std::shared_ptr<C_EnemyBase>>> colorGroups;

	for (auto& e : p_list)
	{
		colorGroups[e->GetCode()].push_back(e);
	}

	//==============================
	// 各Color_codeで「全員いない」なら1体出す
	//==============================
	for (auto& group : colorGroups)
	{
		auto& enemies = group.second;

		bool exist = false;

		for (auto& e : enemies)
		{
			if (e->GetMflg())
			{
				exist = true;
				break;
			}
		}

		// 全員いないなら1体出す
		if (!exist)
		{
			std::vector<std::shared_ptr<C_EnemyBase>> inactiveEnemies;

			for (auto& e : enemies)
			{
				if (!e->GetMflg())
				{
					inactiveEnemies.push_back(e);
				}
			}

			if (!inactiveEnemies.empty())
			{
				std::uniform_int_distribution<int>
					enemyDist(0, (int)inactiveEnemies.size() - 1);

				inactiveEnemies[enemyDist(gen)]->App(p_list);
			}
		}
	}

	//==============================
	// 通常ランダム出現
	//==============================
	for (auto& e : p_list)
	{
		if (spawnDist(gen) == 0 && !e->GetMflg())
		{
			e->App(p_list);
		}
	}
}

void C_GamePlay::Reset()
{
	// 単体オブジェクト
	m_player = nullptr;
	m_heart = nullptr;
	m_dying = nullptr;
	m_pcc = nullptr;
	m_timer = nullptr;
	m_score = nullptr;
	m_damage = nullptr;
	m_selectkey = nullptr;
	m_countdown = nullptr;
	m_text = nullptr;
	m_radar = nullptr;

	// 敵リスト（vector）
	m_enemyList.clear();
	m_multi_enemyList.clear();

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

	for (int i = 0; i < efctMax; i++)
	{
		m_edmecut[i] = nullptr;
	}

	// フラグ系もリセット（重要）
	Timeup = false;
	GameCnt = 0;
	Bulletkeyflg = false;
	BulletCnt = 0;
	BulletColorNumber = 1;
	score_tmp = 0;

	Timeup = false;
	NextScene = false;
	diff = false;
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

void C_GamePlay::Edmecut(Math::Vector2 p_pos)
{
	for (auto& i : m_edmecut)
	{
		if (!i->GetMflg())
		{
			i->App(p_pos);
			break;
		}
	}
}

void C_GamePlay::ChengeColor()
{
	BulletColorNumber++;
	if (BulletColorNumber > 3)BulletColorNumber = 1;
	SOUND.Chenge_SE();
	m_pcc->App(m_player->Getpos(), BulletColorNumber);
}


void C_GamePlay::Release()
{
	//m_enemyTex.Release();
	//m_BulletTex.Release();	
}