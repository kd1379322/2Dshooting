#include "GamePlay.h"

void C_GamePlay::Init()
{
	m_playerTex.Load("Texture/player.png");
	m_player.SetTex(&m_playerTex);

	GameCnt = 0;
	m_player.Init();
}

void C_GamePlay::Update()
{
	GameCnt++;
	m_player.Update();
}

void C_GamePlay::Draw2D()
{
	m_player.Draw2D();
}

void C_GamePlay::ImGuiUpdate()
{
	ImGui::Text("GameC = %d", GameCnt);
	m_player.ImGuiUpdate();
}
