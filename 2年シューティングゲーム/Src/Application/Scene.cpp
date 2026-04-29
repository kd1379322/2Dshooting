#include "main.h"
#include "Scene.h"
#include "GameProgress/Title.h"
#include "GameProgress/GamePlay.h"

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
}

void Scene::Update()
{
	switch (nowScene)
	{
	case Title:
		m_Title->Update();
		if (GetAsyncKeyState(VK_SPACE)&0x8000)
		{
			if(!Spacekeyflg)
			{
				nowScene = GamePlay;
				m_GamePlay->Init();
				Spacekeyflg = true;
			}
		}
		else
		{
			Spacekeyflg = false;
		}
		break;
	case GamePlay:
		m_GamePlay->Update();
		
		break;
	case Result:
		break;
	default:
		break;
	}
}

void Scene::Init()
{
	m_Title = std::make_shared<C_Title>();
	m_GamePlay = std::make_shared<C_GamePlay>();
	nowScene = Title;
	m_Title->Init();
	Spacekeyflg = false;
}

void Scene::Release()
{

}

void Scene::ImGuiUpdate()
{
	//return;

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
