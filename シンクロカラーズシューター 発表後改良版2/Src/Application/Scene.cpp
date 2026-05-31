#include "main.h"
#include "Scene.h"
#include "GameProgress/Title.h"
#include "GameProgress/GamePlay.h"
#include "GameProgress/Result.h"
#include "GameProgress/Ranking.h"
#include "GameProgress/manual.h"
#include "UI/Mosaic.h"
#include "UI/Backgraund.h"
#include"Sound/Sound.h"

void Scene::Draw2D()
{
	m_backgraund->Draw(diff);

	switch (nowScene)
	{
	case Title:
		m_Title->Draw2D(diff);
		break;
	case GamePlay:
		m_GamePlay->Draw2D();
		break;
	case Result:
		m_Result->Draw2D();
		break;
	case Ranking:
		m_Ranking->Draw();
		break;
	case Manual:
		m_manual->Draw();
		break;
	default:
		break;
	}

	m_mosaic->Draw();
}

void Scene::Update()
{
	m_mosaic->Update();
	m_backgraund->Update();

	switch (nowScene)
	{
	case Title:
		m_Title->Update();
		if (GetAsyncKeyState(VK_SPACE)&0x8000)
		{
			if(!Spacekeyflg)
			{
				m_mosaic->Up();
				Spacekeyflg = true;
				Tgoto = GamePlay;

				// まだ音を鳴らしていない時だけ
				if (!SoundPlayed)
				{
					SOUND.DecisionSound_SE();
					SoundPlayed = true;
				}
			}
		}
		else
		{
			Spacekeyflg = false;
		}

		if (GetAsyncKeyState('X') & 0x8000)
		{
			if(!Xkeyflg)
			{
				diff = !diff;
				Xkeyflg = true;
				// まだ音を鳴らしていない時だけ
				if (!SoundPlayed)
				{
					SOUND.DecisionSound_SE();
					//SoundPlayed = true;
				}
			}
		}
		else
		{
			Xkeyflg = false;
		}

		
		if (GetAsyncKeyState('Z') & 0x8000)
		{
			m_mosaic->Up();
			Spacekeyflg = true;
			Tgoto = Ranking;

			if (!SoundPlayed)
			{
				SOUND.DecisionSound_SE();
				SoundPlayed = true;
				// まだ音を鳴らしていない時だけ
				if (!SoundPlayed)
				{
					SOUND.DecisionSound_SE();
					SoundPlayed = true;
				}
			}
		}
		else
		{
			Spacekeyflg = false;
		}

		if (GetAsyncKeyState('C') & 0x8000)
		{
			m_mosaic->Up();
			Spacekeyflg = true;
			Tgoto = Manual;

			if (!SoundPlayed)
			{
				SOUND.DecisionSound_SE();
				SoundPlayed = true;
				// まだ音を鳴らしていない時だけ
				if (!SoundPlayed)
				{
					SOUND.DecisionSound_SE();
					SoundPlayed = true;
				}
			}
		}
		else
		{
			Spacekeyflg = false;
		}

		if (m_mosaic->GetMax_A())
		{
			if(Tgoto == GamePlay)
			{
				nowScene = GamePlay;
				m_GamePlay->Reset();
				m_GamePlay->Init();
				SOUND.Game_BGM();
				m_mosaic->Down();
				SoundPlayed = false;
			}
			else if(Tgoto == Ranking)
			{
				nowScene = Ranking;
				m_Ranking->Init();
				m_mosaic->Down();
				SoundPlayed = false;
			}
			else if (Tgoto == Manual)
			{
				nowScene = Manual;
				m_manual->Init();
				m_mosaic->Down();
				SoundPlayed = false;
			}
		}
		

		break;
	case GamePlay:
		m_GamePlay->Update(diff);
		if (m_GamePlay->GetResultGo_T())
		{
			
			m_mosaic->Up();
			Spacekeyflg = true;
			
		}

		if (m_mosaic->GetMax_A())
		{
			m_Result->SetScore(m_GamePlay->GetRastScore(),m_GamePlay->Getlife());
			m_mosaic->Down();
			nowScene = Result;
			m_Result->Init();
			SOUND.Result_BGM();
		}
		
		/*if (GetAsyncKeyState(VK_F1) & 0x8000)
		{
			m_mosaic->Up();
			Spacekeyflg = true;
		}*/

		break;
	case Result:
		m_Result->Update();
		if (m_Result->GetNextScene() && GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (!Spacekeyflg)
			{
				m_mosaic->Up();
				Spacekeyflg = true;
				// まだ音を鳴らしていない時だけ
				if (!SoundPlayed)
				{
					SOUND.DecisionSound_SE();
					SoundPlayed = true;
				}
			}
		}
		else
		{
			Spacekeyflg = false;
		}

		if (m_mosaic->GetMax_A())
		{
			nowScene = Title;
			m_Title->Init();
			SOUND.Title_BGM();
			m_mosaic->Down();
			SoundPlayed = false;
		}
	
		break;
	case Ranking:
		m_Ranking->Update();
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (!Spacekeyflg)
			{
				m_mosaic->Up();
				Spacekeyflg = true;
				// まだ音を鳴らしていない時だけ
				if (!SoundPlayed)
				{
					SOUND.DecisionSound_SE();
					SoundPlayed = true;
				}
			}
		}
		else
		{
			Spacekeyflg = false;
		}

		if (m_mosaic->GetMax_A())
		{
			nowScene = Title;
			m_Title->Init();
			SOUND.Title_BGM();
			m_mosaic->Down();
			SoundPlayed = false;
		}

		break;
	case Manual:
		m_manual->Update();
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (!Spacekeyflg)
			{
				m_mosaic->Up();
				Spacekeyflg = true;
				// まだ音を鳴らしていない時だけ
				if (!SoundPlayed)
				{
					SOUND.DecisionSound_SE();
					SoundPlayed = true;
				}
			}
		}
		else
		{
			Spacekeyflg = false;
		}

		if (m_mosaic->GetMax_A())
		{
			nowScene = Title;
			m_Title->Init();
			SOUND.Title_BGM();
			m_mosaic->Down();
			SoundPlayed = false;
		}
	default:
		break;
	}

	
}

void Scene::Init()
{
	m_Title = std::make_shared<C_Title>();
	m_GamePlay = std::make_shared<C_GamePlay>();
	m_Result = std::make_shared<C_Result>();
	m_Ranking = std::make_shared<C_Ranking>();
	m_mosaic = std::make_shared<C_Mosaic>();
	m_backgraund = std::make_shared<C_Backgraund>();
	m_manual = std::make_shared<C_Manual>();
	nowScene = Title;
	m_backgraund->Init();
	m_Title->Init();
	m_mosaic->Init();
	m_mosaic->Down();
	SOUND.Init();
	SOUND.Title_BGM();
	Spacekeyflg = false;
	Tgoto = Title;

}

void Scene::Release()
{

}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		m_GamePlay->ImGuiUpdate();
	}
	ImGui::End();
}
