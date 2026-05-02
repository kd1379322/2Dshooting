#include "main.h"
#include "Scene.h"
#include "GameProgress/Title.h"
#include "GameProgress/GamePlay.h"
#include "UI/Mosaic.h"

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
			}
		}
		

		if (m_mosaic->GetMax_A())
		{
			nowScene = GamePlay;
			m_GamePlay->Reset();
			m_GamePlay->Init();
			m_mosaic->Down();
		}
		else
		{
			Spacekeyflg = false;
		}

		break;
	case GamePlay:
		m_GamePlay->Update();
		if (m_GamePlay->GetResultGo_T())
		{
			if (!Spacekeyflg)
			{
				m_mosaic->Up();

				Spacekeyflg = true;
			}
		}

		if (m_mosaic->GetMax_A())
		{
			m_mosaic->Down();
			nowScene = Result;

		}
		else
		{
			Spacekeyflg = false;
		}

		break;
	case Result:
		if (GetAsyncKeyState('T') & 0x8000)
		{
			if (!Spacekeyflg)
			{
				m_mosaic->Up();
				Spacekeyflg = true;
			}
		}


		if (m_mosaic->GetMax_A())
		{
			nowScene = Title;
			m_Title->Init();
			m_mosaic->Down();
		}
		else
		{
			Spacekeyflg = false;
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
	m_mosaic = std::make_shared<C_Mosaic>();
	nowScene = Title;
	m_Title->Init();
	m_mosaic->Init();
	m_mosaic->Down();
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
