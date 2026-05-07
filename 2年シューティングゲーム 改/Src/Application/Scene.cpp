#include "main.h"
#include "Scene.h"
#include "GameProgress/Title.h"
#include "GameProgress/GamePlay.h"
#include "GameProgress/Result.h"
#include "UI/Mosaic.h"
#include"Sound/Sound.h"

void Scene::Draw2D()
{
	switch (nowScene)
	{
	case Title:
		m_Title->Draw2D();
		break;
	case GamePlay:
		m_GamePlay->Draw2D();
		break;
	case Result:
		m_Result->Draw2D();
		break;
	default:
		break;
	}

	m_mosaic->Draw();
}

void Scene::Update()
{
	m_mosaic->Update();

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
			nowScene = GamePlay;
			m_GamePlay->Reset();
			m_GamePlay->Init();
			SOUND.Game_BGM();
			m_mosaic->Down();
			SoundPlayed = false;
		}
		

		break;
	case GamePlay:
		m_GamePlay->Update();
		if (m_GamePlay->GetResultGo_T())
		{
			
			m_Result->SetScore(m_GamePlay->GetRastScore());
			m_mosaic->Up();
			Spacekeyflg = true;
			
		}

		if (m_mosaic->GetMax_A())
		{
			m_mosaic->Down();
			nowScene = Result;
			m_Result->Init();
			SOUND.Result_BGM();
		}
		
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
	default:
		break;
	}

	
}

void Scene::Init()
{
	m_Title = std::make_shared<C_Title>();
	m_GamePlay = std::make_shared<C_GamePlay>();
	m_Result = std::make_shared<C_Result>();
	m_mosaic = std::make_shared<C_Mosaic>();
	nowScene = Title;
	m_Title->Init();
	m_mosaic->Init();
	m_mosaic->Down();
	SOUND.Init();
	SOUND.Title_BGM();
	Spacekeyflg = false;
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
